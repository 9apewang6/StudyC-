#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

	
#include "pdf417-imp.h"
#include "pdf417.h"
#include "barcode-lib.h"
	
const char* MIXED_SET	= "0123456789&\r\t,:#-.$/+%*=^";
const char* PUNCTUATION_SET = ";<>@[\\]_`~!\r\t,:\n-.$/\"|*()?{}'";

typedef struct _listElement 
{
	char type;
	int start;
	int end;
} listElement, *pListElement;

typedef struct _arrayList 
{
	pListElement array;
	int size;
	int capacity;
} arrayList, *pArrayList;

typedef struct _pdf417class 
{
	int bitPtr;
	int cwPtr;
	PDF417PARAM *param;
} pdf417class, *pPdf417class;


static void listInit(pArrayList list) 
{
	list->capacity = 20;
	list->size = 0;
	list->array = (pListElement)malloc(list->capacity * sizeof(listElement));
}

static void listFree(pArrayList list) 
{
	free(list->array);
	list->array = NULL;
}

static void listAdd(pArrayList list, char type, int start, int end) 
{
	if (list->size == list->capacity) 
	{
		pListElement temp;
		list->capacity *= 2;
		temp = (pListElement)malloc(list->capacity * sizeof(listElement));
		memcpy(temp, list->array, list->size * sizeof(listElement));
		free(list->array);
		list->array = temp;
	}
	list->array[list->size].type = type;
	list->array[list->size].start = start;
	list->array[list->size].end = end;
	++list->size;
}

static pListElement listGet(pArrayList list, int idx) 
{
	if (idx >= list->size || idx < 0)
		return NULL;
	return list->array + idx;
}

static void listRemove(pArrayList list, int idx) 
{
	if (idx >= list->size || idx < 0)
		return;
	--list->size;
	memmove(list->array + idx, list->array + (idx + 1), (list->size - idx) * sizeof(listElement));
}

static int checkElementType(pListElement p, char type) 
{
	if (!p)
		return 0;
	return (p->type == type);
}

static int getElementLength(pListElement p)
{
	if (!p)
		return 0;
	return p->end - p->start;
}

void pdf417init(PPDF417PARAM param) 
{
	param->options = 0;
	param->outBits = NULL;
	param->lenBits = 0;
	param->error = 0;
	param->lenText = -1;
	param->text = "";
	param->yHeight = 3;
	param->aspectRatio = 0.5;
}

void pdf417free(PPDF417PARAM param) 
{
	if (param->outBits != NULL) 
	{
		free(param->outBits);
		param->outBits = NULL;
	}
}

static void outCodeword17(pPdf417class p, int codeword) 
{
	int bytePtr = p->bitPtr / 8;
	int bit = p->bitPtr - bytePtr * 8;
	p->param->outBits[bytePtr++] |= codeword >> (9 + bit);
	p->param->outBits[bytePtr++] |= codeword >> (1 + bit);
	codeword <<= 8;
	p->param->outBits[bytePtr] |= codeword >> (1 + bit);
	p->bitPtr += 17;
}

static void outCodeword18(pPdf417class p, int codeword) 
{
	int bytePtr = p->bitPtr / 8;
	int bit = p->bitPtr - bytePtr * 8;
	p->param->outBits[bytePtr++] |= codeword >> (10 + bit);
	p->param->outBits[bytePtr++] |= codeword >> (2 + bit);
	codeword <<= 8;
	p->param->outBits[bytePtr] |= codeword >> (2 + bit);
	if (bit == 7)
		p->param->outBits[++bytePtr] |= 0x80;
	p->bitPtr += 18;
}

static void outCodeword(pPdf417class p, int codeword) 
{
	outCodeword17(p, codeword);
}

static void outStopPattern(pPdf417class p) 
{
	outCodeword18(p, STOP_PATTERN);
}

static void outStartPattern(pPdf417class p) 
{
	outCodeword17(p, START_PATTERN);
}

static void outPaintCode(pPdf417class p) 
{
	int codePtr = 0;
	int row;
	int rowMod;
	int *cluster;
	int edge;
	int column;
	p->param->bitColumns = START_CODE_SIZE * (p->param->codeColumns + 3) + STOP_SIZE;
	p->param->lenBits = ((p->param->bitColumns - 1) / 8 + 1) * p->param->codeRows;
	p->param->outBits = (char*)malloc(p->param->lenBits);
	memset(p->param->outBits, 0, p->param->lenBits);
	for (row = 0; row < p->param->codeRows; ++row) 
	{
		p->bitPtr = ((p->param->bitColumns - 1) / 8 + 1) * 8 * row;
		rowMod = row % 3;
		cluster = CLUSTERS[rowMod];
		outStartPattern(p);
		edge = 0;
		switch (rowMod) 
		{
		case 0:
			edge = 30 * (row / 3) + ((p->param->codeRows - 1) / 3);
			break;
		case 1:
			edge = 30 * (row / 3) + p->param->errorLevel * 3 + ((p->param->codeRows - 1) % 3);
			break;
		default:
			edge = 30 * (row / 3) + p->param->codeColumns - 1;
			break;
		}
		outCodeword(p, cluster[edge]);
		
		for (column = 0; column < p->param->codeColumns; ++column) 
		{
			outCodeword(p, cluster[p->param->codewords[codePtr++]]);
		}
		
		switch (rowMod) 
		{
		case 0:
			edge = 30 * (row / 3) + p->param->codeColumns - 1;
			break;
		case 1:
			edge = 30 * (row / 3) + ((p->param->codeRows - 1) / 3);
			break;
		default:
			edge = 30 * (row / 3) + p->param->errorLevel * 3 + ((p->param->codeRows - 1) % 3);
			break;
		}
		outCodeword(p, cluster[edge]);
		outStopPattern(p);
	}
	if (p->param->options & PDF417_INVERT_BITMAP) 
	{
		char* pm = p->param->outBits;
		char* end = pm + p->param->lenBits;
		while (pm < end)
			*(pm++) ^= 0xff;
	}
}

static void calculateErrorCorrection(pPdf417class p, int dest)
{
	int t1 = 0;
	int t2 = 0;
	int t3 = 0;
	int *A;
	int Alength;
	int *E;
	int lastE;
	int k, e, j;
	if (p->param->errorLevel < 0 || p->param->errorLevel > 8)
		p->param->errorLevel = 0;
	A = ERROR_LEVEL[p->param->errorLevel];
	Alength = 2 << p->param->errorLevel;
	E = p->param->codewords + dest;
	memset(E, 0, Alength * sizeof(int));
	lastE = Alength - 1;
	for (k = 0; k < p->param->lenCodewords; ++k) 
	{
		t1 = p->param->codewords[k] + E[0];
		for (e = 0; e <= lastE; ++e)
		{
			t2 = (t1 * A[lastE - e]) % MOD;
			t3 = MOD - t2;
			E[e] = ((e == lastE ? 0 : E[e + 1]) + t3) % MOD;
		}
	}
	for (j = 0; j < Alength; ++j)
		E[j] = (MOD - E[j]) % MOD;
}
	
static int getTextTypeAndValue(char* text, int size, int idx) 
{
	int c;
	char *ms, *ps;
	if (idx >= size)
		return 0;
	c = text[idx];
	if (c >= 'A' && c <= 'Z')
		return (ALPHA + c - 'A');
	if (c >= 'a' && c <= 'z')
		return (LOWER + c - 'a');
	if (c == ' ')
		return (ALPHA + LOWER + MIXED + SPACE);
	ms = strchr(MIXED_SET, c);
	ps = strchr(PUNCTUATION_SET, c);
	if (!ms && !ps)
		return (ISBYTE + (c & 0xff));
	if (ms - MIXED_SET == ps - PUNCTUATION_SET)
		return (MIXED + PUNCTUATION + (ms - MIXED_SET));
	if (ms != NULL)
		return (MIXED + (ms - MIXED_SET));
	return (PUNCTUATION + (ps - PUNCTUATION_SET));
}
	
static void textCompaction(pPdf417class p, int start, int length)
{
	int dest[ABSOLUTE_MAX_TEXT_SIZE * 2];
	char* text = p->param->text;
	int mode = ALPHA;
	int ptr = 0;
	int fullBytes = 0;
	int v = 0;
	int k;
	int size;
	memset(dest, 0, sizeof(dest));
	length += start;
	for (k = start; k < length; ++k)
	{
		v = getTextTypeAndValue(text, length, k);
		if ((v & mode) != 0)
		{
			dest[ptr++] = v & 0xff;
			continue;
		}
		if ((v & ISBYTE) != 0)
		{
			if ((ptr & 1) != 0)
			{
				dest[ptr++] = (mode & PUNCTUATION) != 0 ? PAL : PS;
				mode = (mode & PUNCTUATION) != 0 ? ALPHA : mode;
			}
			dest[ptr++] = BYTESHIFT;
			dest[ptr++] = v & 0xff;
			fullBytes += 2;
			continue;
		}
		switch (mode)
		{
		case ALPHA:
			if ((v & LOWER) != 0)
			{
				dest[ptr++] = LL;
				dest[ptr++] = v & 0xff;
				mode = LOWER;
			}
			else if ((v & MIXED) != 0)
			{
				dest[ptr++] = ML;
				dest[ptr++] = v & 0xff;
				mode = MIXED;
			}
			else if ( (getTextTypeAndValue(text, length, k + 1) & 
				getTextTypeAndValue(text, length, k + 2) & PUNCTUATION) 
				!= 0 )
			{
				dest[ptr++] = ML;
				dest[ptr++] = PL;
				dest[ptr++] = v & 0xff;
				mode = PUNCTUATION;
			}
			else {
				dest[ptr++] = PS;
				dest[ptr++] = v & 0xff;
			}
			break;
		case LOWER:
			if ((v & ALPHA) != 0)
			{
				if ( (getTextTypeAndValue(text, length, k + 1) & 
					getTextTypeAndValue(text, length, k + 2) & ALPHA) 
					!= 0 )
				{
					dest[ptr++] = ML;
					dest[ptr++] = AL;
					mode = ALPHA;
				}
				else 
				{
					dest[ptr++] = AS;
				}
				dest[ptr++] = v & 0xff;
			}
			else if ((v & MIXED) != 0)
			{
				dest[ptr++] = ML;
				dest[ptr++] = v & 0xff;
				mode = MIXED;
			}
			else if ( (getTextTypeAndValue(text, length, k + 1) & 
					getTextTypeAndValue(text, length, k + 2) & PUNCTUATION) 
					!= 0)
			{
				dest[ptr++] = ML;
				dest[ptr++] = PL;
				dest[ptr++] = v & 0xff;
				mode = PUNCTUATION;
			}
			else 
			{
				dest[ptr++] = PS;
				dest[ptr++] = v & 0xff;
			}
			break;
		case MIXED:
			if ((v & LOWER) != 0)
			{
				dest[ptr++] = LL;
				dest[ptr++] = v & 0xff;
				mode = LOWER;
			}
			else if ((v & ALPHA) != 0)
			{
				dest[ptr++] = AL;
				dest[ptr++] = v & 0xff;
				mode = ALPHA;
			}
			else if ( (getTextTypeAndValue(text, length, k + 1) & 
					getTextTypeAndValue(text, length, k + 2) & PUNCTUATION) 
					!= 0)
			{
				dest[ptr++] = PL;
				dest[ptr++] = v & 0xff;
				mode = PUNCTUATION;
			}
			else 
			{
				dest[ptr++] = PS;
				dest[ptr++] = v & 0xff;
			}
			break;
		case PUNCTUATION:
			dest[ptr++] = PAL;
			mode = ALPHA;
			--k;
			break;
		}
	}
	if ((ptr & 1) != 0)
	dest[ptr++] = PS;
	size = (ptr + fullBytes) / 2;
	if (size + p->cwPtr > MAX_DATA_CODEWORDS)
	{
		p->param->error = PDF417_ERROR_TEXT_TOO_BIG;
		return;
	}
	length = ptr;
	ptr = 0;
	while (ptr < length)
	{
		v = dest[ptr++];
		if (v >= 30)
		{
			p->param->codewords[p->cwPtr++] = v;
			p->param->codewords[p->cwPtr++] = dest[ptr++];
		}
		else
			p->param->codewords[p->cwPtr++] = v * 30 + dest[ptr++];
	}
}

static void basicNumberCompaction(pPdf417class p, int start, int length)
{
	char* text = p->param->text;
	int* ret = p->param->codewords + p->cwPtr;
	int retLast = length / 3;
	int ni, k;
	p->cwPtr += retLast + 1;
	memset(ret, 0, (retLast + 1) * sizeof(int));
	ret[retLast] = 1;
	length += start;
	for (ni = start; ni < length; ++ni)
	{
		// multiply by 10
		for (k = retLast; k >= 0; --k)
			ret[k] *= 10;
		// add the digit
		ret[retLast] += text[ni] - '0';
		// propagate carry
		for (k = retLast; k > 0; --k)
		{
			ret[k - 1] += ret[k] / 900;
			ret[k] %= 900;
		}
	}
}

static void numberCompaction(pPdf417class p, int start, int length)
{
	int full = (length / 44) * 15;
	int size = length % 44;
	int k;
	if (size == 0)
		size = full;
	else
		size = full + size / 3 + 1;
	if (size + p->cwPtr > MAX_DATA_CODEWORDS)
	{
		p->param->error = PDF417_ERROR_TEXT_TOO_BIG;
		return;
	}
	length += start;
	for (k = start; k < length; k += 44)
	{
		size = length - k < 44 ? length - k : 44;
		basicNumberCompaction(p, k, size);
	}
}

static void byteCompaction6(pPdf417class p, int start)
{
	int length = 6;
	char* text = p->param->text;
	int* ret = p->param->codewords + p->cwPtr;
	int retLast = 4;
	int ni, k;
	p->cwPtr += retLast + 1;
	memset(ret, 0, (retLast + 1) * sizeof(int));
	length += start;
	for (ni = start; ni < length; ++ni)
	{
		// multiply by 256
		for (k = retLast; k >= 0; --k)
			ret[k] *= 256;
		// add the digit
		ret[retLast] += (int)text[ni] & 0xff;
		// propagate carry
		for (k = retLast; k > 0; --k)
		{
			ret[k - 1] += ret[k] / 900;
			ret[k] %= 900;
		}
	}
}

static void byteCompaction(pPdf417class p, int start, int length)
{
	int k, j;
	int size = (length / 6) * 5 + (length % 6);
	if (size + p->cwPtr > MAX_DATA_CODEWORDS)
	{
		p->param->error = PDF417_ERROR_TEXT_TOO_BIG;
		return;
	}
	length += start;
	for (k = start; k < length; k += 6)
	{
		size = length - k < 44 ? length - k : 6;
		if (size < 6)
		{
			for (j = 0; j < size; ++j)
				p->param->codewords[p->cwPtr++] = (int)p->param->text[k + j] & 0xff;
		}
		else 
		{
			byteCompaction6(p, k);
		}
	}
}

static void breakString(pPdf417class p, pArrayList list)
{
	char* text = p->param->text;
	int textLength = p->param->lenText;
	int lastP = 0;
	int startN = 0;
	int nd = 0;
	char c = 0;
	int k, ptrS, lastTxt, j, txt;
	pListElement v;
	pListElement vp;
	pListElement vn;
	list->size = 0;
	for (k = 0; k < textLength; ++k)
	{
		c = text[k];
		if (c >= '0' && c <= '9')
		{
			if (nd == 0)
				startN = k;
			++nd;
			continue;
		}
		if (nd >= 13)
		{
			if (lastP != startN)
			{
				c = text[lastP];
				ptrS = lastP;
				lastTxt = (c >= ' ' && c < 127) || c == '\r' || c == '\n' || c == '\t';
				for (j = lastP; j < startN; ++j)
				{
					c = text[j];
					txt = (c >= ' ' && c < 127) || c == '\r' || c == '\n' || c == '\t';
					if (txt != lastTxt)
					{
						listAdd(list, (char)(lastTxt ? 'T' : 'B'), lastP, j);
						lastP = j;
						lastTxt = txt;
					}
				}
				listAdd(list, (char)(lastTxt ? 'T' : 'B'), lastP, startN);
			}
			listAdd(list, 'N', startN, k);
			lastP = k;
		}
		nd = 0;
	}
	if (nd < 13)
		startN = textLength;
	if (lastP != startN)
	{
		c = text[lastP];
		ptrS = lastP;
		lastTxt = (c >= ' ' && c < 127) || c == '\r' || c == '\n' || c == '\t';
		for (j = lastP; j < startN; ++j)
		{
			c = text[j];
			txt = (c >= ' ' && c < 127) || c == '\r' || c == '\n' || c == '\t';
			if (txt != lastTxt)
			{
				listAdd(list, (char)(lastTxt ? 'T' : 'B'), lastP, j);
				lastP = j;
				lastTxt = txt;
			}
		}
		listAdd(list, (char)(lastTxt ? 'T' : 'B'), lastP, startN);
	}
	if (nd >= 13)
		listAdd(list, 'N', startN, textLength);
	//optimize
	//merge short binary
	for (k = 0; k < list->size; ++k)
	{
		v = listGet(list, k);
		vp = listGet(list, k - 1);
		vn = listGet(list, k + 1);;
		if (checkElementType(v, 'B') && getElementLength(v) == 1)
		{
			if (checkElementType(vp, 'T') && checkElementType(vn, 'T') 
				&& getElementLength(vp) + getElementLength(vn) >= 3)
			{
				vp->end = vn->end;
				listRemove(list, k);
				listRemove(list, k);
				k = -1;
				continue;
			}
		}
	}
	//merge text sections
	for (k = 0; k < list->size; ++k)
	{
		v = listGet(list, k);
		vp = listGet(list, k - 1);
		vn = listGet(list, k + 1);;
		if (checkElementType(v, 'T') && getElementLength(v) >= 5)
		{
			int redo = 0;
			if ((checkElementType(vp, 'B') && getElementLength(vp) == 1) || checkElementType(vp, 'T'))
			{
				redo = 1;
				v->start = vp->start;
				listRemove(list, k - 1);
				--k;
			}
			if ((checkElementType(vn, 'B') && getElementLength(vn) == 1) || checkElementType(vn, 'T'))
			{
				redo = 1;
				v->end = vn->end;
				listRemove(list, k + 1);
			}
			if (redo)
			{
				k = -1;
				continue;
			}
		}
	}
	//merge binary sections
	for (k = 0; k < list->size; ++k)
	{
		v = listGet(list, k);
		vp = listGet(list, k - 1);
		vn = listGet(list, k + 1);;
		if (checkElementType(v, 'B'))
		{
			int redo = 0;
			if ((checkElementType(vp, 'T') && getElementLength(vp) < 5) || checkElementType(vp, 'B'))
			{
				redo = 1;
				v->start = vp->start;
				listRemove(list, k - 1);
				--k;
			}
			if ((checkElementType(vn, 'T') && getElementLength(vn) < 5) || checkElementType(vn, 'B'))
			{
				redo = 1;
				v->end = vn->end;
				listRemove(list, k + 1);
			}
			if (redo)
			{
				k = -1;
				continue;
			}
		}
	}
	// check if all numbers
	if (list->size == 1 && (v = listGet(list, 0))->type == 'T' && getElementLength(v) >= 8)
	{
		for (k = v->start; k < v->end; ++k)
		{
			c = text[k];
			if (c < '0' || c > '9')
				break;
		}
		if (k == v->end)
			v->type = 'N';
	}
}

static void assemble(pPdf417class p, pArrayList list)
{
	int k;
	if (list->size == 0)
		return;
	p->cwPtr = 1;
	for (k = 0; k < list->size; ++k)
	{
		pListElement v = listGet(list, k);
		switch (v->type)
		{
		case 'T':
			if (k != 0)
				p->param->codewords[p->cwPtr++] = TEXT_MODE;
			textCompaction(p, v->start, v->end - v->start);
			break;
		case 'N':
			p->param->codewords[p->cwPtr++] = NUMERIC_MODE;
			numberCompaction(p, v->start, v->end - v->start);
			break;
		case 'B':
			p->param->codewords[p->cwPtr++] = (v->end - v->start) % 6 ? BYTE_MODE : BYTE_MODE_6;
			byteCompaction(p, v->start, v->end - v->start);
			break;
		}
		if (p->param->error)
			return;
	}
}

static int maxPossibleErrorLevel(int remain)
{
	int level = 8;
	int size = 512;
	while (level > 0)
	{
		if (remain >= size)
			return level;
		--level;
		size >>= 1;
	}
	return 0;
}

static void dumpList(pPdf417class p, pArrayList list)
{
	int k;
	if (list->size == 0)
		return;
	for (k = 0; k < list->size; ++k)
	{
		pListElement v = listGet(list, k);
		printf("%c%.*s\n", v->type, v->end - v->start, p->param->text + v->start);
	}
}

static int getMaxSquare(PPDF417PARAM p)
{
	if (p->codeColumns > 21)
	{
		p->codeColumns = 29;
		p->codeRows = 32;
	}
	else 
	{
		p->codeColumns = 16;
		p->codeRows = 58;
	}
	return MAX_DATA_CODEWORDS + 2;
}

void paintCode(PPDF417PARAM p)
{
	pdf417class pp;
	arrayList list;
	int maxErr, fixedColumn, lenErr, tot, skipRowColAdjust, pad;
	pp.param = p;
	p->error = 0;
	if (p->options & PDF417_USE_RAW_CODEWORDS)
	{
		if (p->lenCodewords > MAX_DATA_CODEWORDS || p->lenCodewords < 1 || p->lenCodewords != p->codewords[0])
		{
			p->error = PDF417_ERROR_INVALID_PARAMS;

			return;
		}
	}
	else 
	{
		if (p->lenText < 0)
			p->lenText = strlen(p->text);
		if (p->lenText > ABSOLUTE_MAX_TEXT_SIZE)
		{
			p->error = PDF417_ERROR_TEXT_TOO_BIG;
			return;
		}
		listInit(&list);
		breakString(&pp, &list);
		dumpList(&pp, &list);
		assemble(&pp, &list);
		listFree(&list);
		if (p->error)
			return;
		p->codewords[0] = p->lenCodewords = pp.cwPtr;
	}
	maxErr = maxPossibleErrorLevel(MAX_DATA_CODEWORDS + 2 - p->lenCodewords);
	if (!(p->options & PDF417_USE_ERROR_LEVEL))
	{
		if (p->lenCodewords < 41)
			p->errorLevel = 2;
		else if (p->lenCodewords < 161)
			p->errorLevel = 3;
		else if (p->lenCodewords < 321)
			p->errorLevel = 4;
		else
			p->errorLevel = 5;
	}
	if (p->errorLevel < 0)
		p->errorLevel = 0;
	else if (p->errorLevel > maxErr)
		p->errorLevel = maxErr;
	if (p->codeColumns < 1)
		p->codeColumns = 1;
	else if (p->codeColumns > 30)
		p->codeColumns = 30;
	if (p->codeRows < 3)
		p->codeRows = 3;
	else if (p->codeRows > 90)
		p->codeRows = 90;
	lenErr = 2 << p->errorLevel;
	fixedColumn = !(p->options & PDF417_FIXED_ROWS);
	skipRowColAdjust = 0;
	tot = p->lenCodewords + lenErr;
	if (p->options & PDF417_FIXED_RECTANGLE) 
	{
		tot = p->codeColumns * p->codeRows;
		if (tot > MAX_DATA_CODEWORDS + 2) 
		{
			tot = getMaxSquare(p);
		}
		if (tot < p->lenCodewords + lenErr)
			tot = p->lenCodewords + lenErr;
		else
			skipRowColAdjust = 1;
	}
	else if (!(p->options & (PDF417_FIXED_COLUMNS | PDF417_FIXED_ROWS)))
	{
		double c, b;
		fixedColumn = 1;
		if (p->aspectRatio < 0.001)
			p->aspectRatio = 0.001f;
		else if (p->aspectRatio > 1000)
			p->aspectRatio = 1000;
		b = 73 * p->aspectRatio - 4;
		c = (-b + sqrt(b * b + 4 * 17 * p->aspectRatio * (p->lenCodewords + lenErr) * p->yHeight)) / (2 * 17 * p->aspectRatio);
		p->codeColumns = (int)(c + 0.5);
		if (p->codeColumns < 1)
			p->codeColumns = 1;
		else if (p->codeColumns > 30)
			p->codeColumns = 30;
	}
	if (!skipRowColAdjust) 
	{
		if (fixedColumn) 
		{
			p->codeRows = (tot - 1) / p->codeColumns + 1;
			if (p->codeRows < 3)
				p->codeRows = 3;
			else if (p->codeRows > 90) {
				p->codeRows = 90;
				p->codeColumns = (tot - 1) / 90 + 1;
			}
		}
		else 
		{
			p->codeColumns = (tot - 1) / p->codeRows + 1;
			if (p->codeColumns > 30) 
			{
				p->codeColumns = 30;
				p->codeRows = (tot - 1) / 30 + 1;
			}
		}
		tot = p->codeRows * p->codeColumns;
	}
	if (tot > MAX_DATA_CODEWORDS + 2)
	{
		tot = getMaxSquare(p);
	}
	p->errorLevel = maxPossibleErrorLevel(tot - p->lenCodewords);
	lenErr = 2 << p->errorLevel;
	pad = tot - lenErr - p->lenCodewords;
	pp.cwPtr = p->lenCodewords;
	while (pad--)
		p->codewords[pp.cwPtr++] = TEXT_MODE;
	p->codewords[0] = p->lenCodewords = pp.cwPtr;
	calculateErrorCorrection(&pp, pp.param->lenCodewords);
	pp.param->lenCodewords = tot;
	outPaintCode(&pp);
}
namespace z_pdf417
{
	// ��hdc�ϻ���pdf417��ά��
	// ��hdcΪnullʱ,left,top�ֱ�������ֿ�Ⱥ͸߶�Ϊcode_x,code_yʱ,pdf��ά��ͼ����Ҫ��ͼ���Ⱥ͸߶�.
	// code_x,code_y�ֱ�ָ��ÿ��pdf417���ֵĿ�Ⱥ͸߶�.
	HRESULT PDF417DrawImg(HDC hdc,PPDF417PARAM pPDF417Param,int &left,int &top,int code_x,int code_y)
	{
		int cols,rows,l,t,i;
//		RECT rc;
		char bit = 0;
		
		paintCode(pPDF417Param);
		if ( PDF417_ERROR_SUCCESS!=pPDF417Param->error )
		{
			return pPDF417Param->error;
		}
		cols = (pPDF417Param->lenBits / pPDF417Param->codeRows)*8;
		rows = (pPDF417Param->codeRows);
		
		if ( !hdc )
		{
			left = cols * code_x;
			top  = rows * code_y;
			pdf417free(pPDF417Param);
			return PDF417_ERROR_SUCCESS;
		}
		
// 		rc.left		= left;
// 		rc.top		= top;
// 		rc.right	= left + cols * code_x ;
// 		rc.bottom	= top  + rows * code_y;
// 		
// 		FillRect(hdc, &rc, (HBRUSH)GetStockObject(BLACK_BRUSH));//����ɫΪ��ɫ
		PatBlt(hdc, left, top, cols * code_x, rows * code_y,BLACKNESS);//����ɫΪ��ɫ
		SelectObject(hdc, GetStockObject(WHITE_BRUSH));	//ѡ��ˢΪ��ɫ
		SelectObject(hdc, GetStockObject(WHITE_PEN));	//ѡ�񻭱�Ϊ��ɫ
		
		//��ʼ����pdf417��ά��
		for(i=0; i< pPDF417Param->lenBits; i++)
		{
			char j = 0;
			bit = pPDF417Param->outBits[i];
			t = top + ((i*8)/cols) * code_y;		
			while( j!=8 )
			{
				if( bit & 0x80 )//bit���λΪ1
				{
					l = left + code_x*((i*8)%cols+j);
					Rectangle(hdc,l,t,l+code_x,t+code_y);
				}
				j++;
				bit = bit<<1 ;
			}
		}
		pdf417free(pPDF417Param);
		return PDF417_ERROR_SUCCESS;

	}
// 	// ��hdc�ϻ���pdf417��ά��
// 	// ��hdcΪnullʱ,ccol_,crow_�ֱ������ά�������������
// 	// ��hdc��nullʱ,ccol_,crow_�ֱ�ΪҪ����pdf417��ά�����صĿ�Ⱥ͸߶�,����
// 	// �Զ�����ͼ���Ⱥ͸߶�ccol_,crow_ָ����ֵ.
// 	// ccol_,crow_Ӧ�ô��ڶ�ά�������������.����ͼƬ��������.
// 	HRESULT PDF417DrawImg(HDC hdc,PPDF417PARAM pPDF417Param,int left,int top,int &ccol_,int &crow_)
// 	{
// 		int img_w,img_h ;			//ͼƬ���ص�λ�ĸ߶ȺͿ��
// 		int i,rowNumber;			//��ʱ����
// 		RECT rc;
// 		char bit = 0;
// 		HDC tmpHdc = NULL;
// 		HBITMAP oldHbitmap = NULL,newHbitmap = NULL; 
// 		
// 		img_w = pPDF417Param->bitColumns + 1;
// 		img_h = pPDF417Param->codeRows;
// 		
// 		if ( !hdc )
// 		{
// 			ccol_ = img_w;
// 			crow_ = img_h;
//			pdf417free(pPDF417Param);
// 			return PDF417_ERROR_SUCCESS;
// 		}
// 		
// 		if ( PDF417_ERROR_SUCCESS!=pPDF417Param->error)
// 		{
// 			return pPDF417Param->error;
// 		}
// 
// 		if ( NULL!=(tmpHdc=CreateCompatibleDC(hdc)) )
// 		{
// 			if ( NULL!=(newHbitmap=CreateCompatibleBitmap(tmpHdc, img_w, img_h)) )
// 			{
// 				oldHbitmap = (HBITMAP)SelectObject(tmpHdc,newHbitmap);
// 			}
// 			else
// 			{
// 				DeleteDC(tmpHdc);
// 				return 4;	// ����HBITMAPʧ��
// 			}
// 		}
// 		else
// 		{
// 			return 3;		//����HDCʧ��
// 		}
// 		
// 		// ͼƬ���Ϊ��ɫ
// 		rowNumber = 0;
// 		rc.left = rc.top = 0;
// 		rc.right= img_w ;
// 		rc.bottom = img_h;
// 		FillRect(tmpHdc, &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));
// 		
// 		for(i=0; i< pPDF417Param->lenBits; i++)
// 		{
// 			char j = 0;
// 			bit = pPDF417Param->outBits[i];
// 			rowNumber = (i*8)/img_w;
// 			while( j!=8 )
// 			{
// 				if( !(bit & 0x80) )//bit���λΪ1
// 				{
// 					SetPixel(tmpHdc,((i*8)%img_w)+j,rowNumber,0x0);
// 				}
// 				j++;
// 				bit = bit<<1 ;
// 			}
// 		}
// 		StretchBlt(hdc,left,top,ccol_,crow_,tmpHdc,0,0,img_w,img_h,SRCCOPY);
// 		SelectObject(tmpHdc,oldHbitmap);
// 		DeleteObject(newHbitmap);
// 		DeleteDC(tmpHdc);
//		pdf417free(pPDF417Param);
// 		return NULL;
// 	}

}
