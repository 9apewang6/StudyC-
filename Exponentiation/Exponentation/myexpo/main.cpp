#include <iostream>
#include <string>
#include "myexpo.h"
using namespace  std;


void testmyexpo()
{
	double input_value = 0.0;
	cout << "please input a double number:" << endl;
	cin >> input_value;
	MyExpo p1(input_value);
	p1.display();
	cout << " please input a double number:" << endl;
	cin >> input_value;
	MyExpo p2(input_value);
	p2.display();
// 	MyExpo  p3 = p1 + p2;
// 
// 	p3.display();
	MyExpo  p4 = p1.MulOperate(p2);
	p4.display();

	MyExpo p5 = p1.powOperate(10);
	p5.display();
}
int main(void)
{
	/*
	short result[DATASIZE];
	short multipiler[DATASIZE];
	short multicand[DATASIZE];
	memset(result, 0, sizeof(short)*DATASIZE);
	memset(multipiler, 0, sizeof(short)*DATASIZE);
	memset(multicand, 0, sizeof(short)*DATASIZE);

	string input_mul1;
	int n=0;
	int pot_pos = 0;
	int strlength = 0;
	char pot = '.';
	int i = 0, j = 0;
	int firstindex=0, lastindex=0;
	while (cin >> input_mul1 >> n)
	{
		strlength = input_mul1.size();
		if (strlength == 0)break;
		pot_pos = input_mul1.find(pot);
		if (pot_pos < 0)
		{
			for (j = strlength - 1, i = 0; j >= 0; j--, ++i)
			{
				multipiler[i] = input_mul1[j] - '0';
				multicand[i] = multipiler[i];
			}
			pot_pos = 0;
		}
		else
		{
			for (j = strlength - 1, i = 0; j >= 0; j--, i++)
			{
				if (j == pot_pos)
				{
					--i;
					continue;
				}
				multipiler[i] = input_mul1[j] - '0';
				multicand[i] = multipiler[i];
			}
			pot_pos = (strlength - pot_pos - 1)*n;
		}
		
		while (n >= 2)
		{
			n--;
			for (i = 0; i < strlength-1; i++)
			{
				if (multipiler[i] != 0)
				{
					for ( j = 0; j < DATASIZE; j++)
					{
						int tmp = multipiler[i] * multicand[j];
						result[i + j] += tmp;
						for (int l = i + j; result[l] > 9; l++)
						{
							result[l + 1] += result[l] / 10;
							result[l] = result[l] % 10;
						}
					}
				}
			}

			for ( i = 0; i < DATASIZE; i++)
			{
				multicand[i] = result[i];
			}
		}

		for (i = DATASIZE - 1; i >= pot_pos; i--)
		{
			if (multicand[i] > 0)
			{
				firstindex = i;
				break;
			}
		}
		for (i = 0; i < pot_pos; i++)
		{
			if (multicand[i] > 0)
			{
				lastindex = i;
				break;
			}
		}
		if (firstindex != -1)
		{
			for (j = firstindex; j >= pot_pos; j--)
			{
				printf("%d", multicand[j]);
			}
		}
		if (lastindex != -1)
		{
			printf(".");
			for (j = pot_pos - 1; j >= lastindex; j--)
			{
				printf("%d", multicand[j]);
			}
		}
	}*/
char key = ',';
while (cin >> key)
{
	if (key == 'q')break;
	testmyexpo();
}
	system("pause");
	return 0;
}
