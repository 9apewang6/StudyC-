#include<stdio.h>
#include<iostream>
#include<string>
#include<string.h>
using namespace std;
int multiplicator[110], multiplicand[110], result[110], firstindex, lastindex;
int main()
{
	int i, j, l, n, m, k, t, point;
	string s;
	while (cin >> s >> n)
	{
		firstindex = -1;
		lastindex = -1;
		point = s.find('.');
		//printf("%d\n",point);
		if (point != -1)
		{
			point = (5 - point)*n;
		}
		else
		{
			point = 0;
		}
		memset(multiplicator, 0, sizeof(multiplicator));
		memset(multiplicand, 0, sizeof(multiplicand));
		for (i = 5, j = 0; i >= 0; i--)
		{
			if (s[i] != '.')
			{
				multiplicator[j] = multiplicand[j] = s[i] - '0';
				j++;
			}
		}
		while (n >= 2)
		{
			n--;
			memset(result, 0, sizeof(result));
			for (i = 0; i < 5; i++)
			{
				if (multiplicator[i] != 0)
				{
					for (j = 0; j < 110; j++)
					{
						int tmp = multiplicator[i] * multiplicand[j];
						result[i + j] += tmp;
						for (l = i + j; result[l] > 9; l++)
						{
							result[l + 1] += result[l] / 10;
							result[l] = result[l] % 10;
						}
					}
				}
			}
			for (i = 0; i < 110; i++)
			{
				multiplicand[i] = result[i];
			}
		}
		for (i = 110 - 1; i >= point; i--)
		{
			if (multiplicand[i] > 0)
			{
				firstindex = i;
				break;
			}
		}
		for (i = 0; i < point; i++)
		{
			if (multiplicand[i] > 0)
			{
				lastindex = i;
				break;
			}
		}
		if (firstindex != -1)
		{
			for (j = firstindex; j >= point; j--)
			{
				printf("%d", multiplicand[j]);
			}
		}
		if (lastindex != -1)
		{
			printf(".");
			for (j = point - 1; j >= lastindex; j--)
			{
				printf("%d", multiplicand[j]);
			}
		}
		printf("\n");
	}
	return 0;
}
