#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <sstream>
using namespace std;

typedef struct  A
{
	char a;
	int b;
	short c;

}a1;
typedef struct B
{
	int a;
	char b;
	short c;

}b1;
 struct C{
	 short c;
	 int b;
	 char a;

}c1;
 const int INF = 1E8;
 struct RevideData
 {
	 int u[50], l;
	 RevideData()
	 {
		 memset(u, 0, sizeof(u));
		 l = 0;
	 }
	 void converToInt(string a)
	 {
		 int len = a.size(), k = len / 8,i=0;
		 l = k + (len % 8 > 0);
		 for (len; len > 8; len-=8)
		 {
			 sscanf(a.substr(len - 8, 8).c_str(), "%d", &u[i++]);
		 }
		 if (len > 0)
		 {
			 sscanf(a.substr(0, len).c_str(), "%d", &u[i]);
		 }
	 }
	 void Print()
	 {
		 printf("\n");

		 int k = l - 1;
		 printf("%d",u[k--]);
		 while (k >= 0)printf("%8.8d", u[k--]);
		 printf("\n");
	 
	 }

 };
////大数加法////
void LargeAdd(string a,string b)
{
	char A[100], B[100];
	//sprintf_s(A,100,"%s",a);
	//sprintf_s(B,100,"%s",b);
	strcpy_s(A,a.c_str());
	strcpy_s(B,b.c_str());
	unsigned int A1[101], B1[100];
	memset(A1, 0, 101 * sizeof(unsigned int));
	memset(B1, 0, 100 * sizeof(unsigned int));
	unsigned int Alen = strlen(A);
	unsigned int Blen = strlen(B);
	 int i = 0, t;
	for (i = 0; i < Alen; i++)
	{
		A1[i] = A[Alen - 1 - i] - '0';

	}
	for (i=0; i < Blen; i++)
	{
		B1[i] = B[Blen - 1 - i] - '0';
	}
	for (i = 0; i <= max(Alen, Blen); i++)
	{
		t = A1[i] + B1[i];
		A1[i] = t % 10;
		A1[i + 1] += t / 10;
	}
	for (i=max(Alen,Blen)-1; i >= 0; i--)
	{
		printf("%d",A1[i]);
	}
}
void LargeAdd_WithPressure(string a, string b)
{
	RevideData c, d;
	c.converToInt(a);

	d.converToInt(b);

	for (int i = 0; i < 50; i++)
	{
		c.u[i] += d.u[i];
		c.u[i + 1] += c.u[i] / INF;
		c.u[i] %= INF;
	}
	int j = 49;
	for (; c.u[j] == 0 && j > 0; j--);
	c.l = j + 1;
	c.Print();

}
void LargeDel(string a, string b)
{


}

void LargeMul(string a, string b)
{
	char A[100], B[100];
	strcpy_s(A, a.c_str());
	strcpy_s(B, b.c_str());
	int A1[100] = { 0 }, B1[100] = { 0 }, C1[200] = {0};
	int Alen = strlen(A);
	int Blen = strlen(B);
	int i = 0,j=0;
	int suffix = 0;
	for (i = 0; i < Alen; i++)
	{
		A1[i] = A[Alen-1-i] - '0';

	}
	for (i = 0; i < Blen; i++)
	{
		B1[i] = B[Blen-1-i] - '0';
	}
	for (i = 0; i < Alen; i++)
	{
		for (j = 0; j < Blen; j++)
		{
			C1[i+j]+= A1[i] * B1[j];
		}
	}
	for (i = 0; i < Alen + Blen; i++)
	{
			C1[i + 1] += C1[i] / 10;
			C1[i] = C1[i] % 10;
	}
	for (i = Alen + Blen; C1[i] == 0 && i > 0; i--);
	printf("\n");
	for (j = i; j >=0; j--)
	{
		printf("%d",C1[j]);
	}
	printf("\n");
}
void LargeAdd(int c[], int b[], int(&d)[200])
{


}
void LargeMul(unsigned int c[],unsigned int Cnum, unsigned int b[],unsigned int bNum,unsigned int (&d)[200])
{
	unsigned int i = Cnum , j = bNum;
	for (i = 0; i < Cnum; i++)
	{
		for (j = 0; j < bNum; j++)
		{
			d[i + j] += c[i] * b[j];
		}
	}
	for (i = 0; i < Cnum + bNum; i++)
	{
		d[i + 1] += d[i] / 10;
		d[i] = d[i] % 10;
	}

}
void LargePow(string a,int N)
{
	char A[100], B[100];
	strcpy_s(A, a.c_str());
	strcpy_s(B,a.c_str());
	unsigned int A1[200] = { 0 }, B1[200] = { 0 }, C1[200] = { 0 }, D[200] = {0};
	unsigned int Alen = strlen(A), Blen = strlen(B);
	 int i = 0, j = 0;
	for (i = 0; i < Alen; i++)
	{
		A1[i] = A[Alen - i - 1] - '0';
	}
	for (i = 0; i < Blen; i++)
	{
		B1[i] = B[Blen - i - 1] - '0';
	}
	for (i = 0; i < N; i++)
	{
		LargeMul(A1,Alen, B1,Blen, D);
		memcpy(A1,D,sizeof(unsigned int)*200);
		
		//计算D长度
		for (j = Alen + Blen; D[j] == 0 && j > 0; j--);
		Alen = j+1;
		for (; j >= 0; j--)
		{
			printf("%d", D[j]);
		}
		printf("\n");
		memset(D, 0, sizeof(unsigned int) * 200);
	}
}
void LargeDevide(string a, string b)
{
	char A[100], B[100];
	strcpy_s(A,a.c_str());
	strcpy_s(B,b.c_str());
	unsigned int A1[100] = { 0 }, B1[100] = { 0 }, C1[100] = { 0 };
	unsigned int Alen = strlen(A), Blen = strlen(B);
	unsigned int i = 0, j = 0;
	for (i =0;i<Alen;i++)
	{
		A1[i] = A[Alen - i - 1] - '0';
	}
	for (i = 0; i < Blen; i++)
	{
		B1[i] = B[Blen - i - 1] - '0';
	}

}
int main()
{
	int a2[10] = { 0 };
	string str = "";
	for (int k = 0; k < 10; k++)
	{
		str += to_string(a2[k]);
	}
	printf("%s", str.data());
	int size_struct = 0;
	size_struct = sizeof(a1);
	cout << size_struct << endl;
	size_struct = sizeof(b1);
	cout << size_struct << endl;
	size_struct = sizeof(c1);
	cout << size_struct << endl;
	string a, b;
	string Result;
	cin >> a >> b;
	
	LargeAdd(a, b);
//	printf("a+b = %s",Result);
	LargeAdd_WithPressure(a, b);

	LargeDel(a, b);
	//printf("a-b = %s",Result);
	LargeMul(a, b);
	//printf("a*b = %s",Result);
	LargeDevide(a, b);

	LargePow(a, 10);
	//printf("a/b =%s",Result);
	cout << endl;
	system("pause");
	return 0;
}