#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

void LargeMul( int c[],  int Cnum,  int b[],  int bNum,  int(&d)[200])
{
	unsigned int i = Cnum, j = bNum;
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
 int* LargePow(string a, int N, int &size)
{
	char A[100], B[100];
	strcpy_s(A, a.c_str());
	strcpy_s(B, a.c_str());
	 int A1[200] = { 0 }, B1[200] = { 0 }, C1[200] = { 0 }, D[200] = { 0 };
	 int Alen = strlen(A), Blen = strlen(B);
	int i = 0, j = 0;
	for (i = 0; i < Alen; i++)
	{
		A1[i] = A[Alen - i - 1] - '0';
	}
	for (i = 0; i < Blen; i++)
	{
		B1[i] = B[Blen - i - 1] - '0';
	}
	if (N == 1)
	{
		memcpy(C1, A1, sizeof( int) * 200);
		size = Alen;
		return C1;
		/*	for (j = Alen + Blen; A1[j] == 0 && j > 0; j--);
			Alen = j + 1;*/
	}
	for (i = 0; i < N-1; i++)
	{
		LargeMul(A1, Alen, B1, Blen, D);
		memcpy(A1, D, sizeof( int) * 200);
		memcpy(C1, D, sizeof( int) * 200);
		//¼ÆËãD³¤¶È
		for (j = Alen + Blen; D[j] == 0 && j > 0; j--);
		Alen = j + 1;


		memset(D, 0, sizeof( int) * 200);
		
	}
	size = Alen-1;
	return C1;
}

 int main()
 {

 	 int Result[200] = {0};
 	string Input1_="";
 	
 	int Input2_=0;
 	int k = 0;
 	 int DotID=0;
 	  int ReSize=0;
 	 int TotalNum = 0;
	 int firstIndex = -1;
	 int lastIndex = -1;
 	while (cin>>Input1_>>Input2_)
 	{
		firstIndex = -1;
		lastIndex = -1;
		DotID = Input1_.find_first_of('.');
 		if (DotID >= 0)
 		{
 			DotID = Input1_.length() - Input1_.find_first_of('.') - 1;
			DotID = DotID*Input2_;
 		}
 		else
 		{
			DotID = 0;
			DotID = DotID*Input2_;
 		}
 		Input1_.erase(std::remove(Input1_.begin(), Input1_.end(), '.'), Input1_.end());
 
 		memcpy(Result, LargePow(Input1_, Input2_, ReSize), sizeof(unsigned int) * 200);
		
		for (int i = 200 - 1; i >= DotID; i--)
		{
			if (Result[i] > 0)
			{
				firstIndex = i;
				break;
			}
		}
		for (int i = 0; i < DotID; i++)
		{
			if (Result[i] > 0)
			{

				lastIndex = i;
				break;
			}
		}

		if (firstIndex != -1)
		{
			for (int j = firstIndex; j >= DotID; j--)
			{
				printf("%d", Result[j]);
			}
		}
		if (lastIndex != -1)
		{
			printf(".");
			for (int j = DotID - 1; j >= lastIndex; j--)
			{
				printf("%d", Result[j]);
			}
		}
		
		printf("\n");
 		Input2_ = 0;	
 	}
 	getchar();
 	getchar();
 	return 0;
 }

 
