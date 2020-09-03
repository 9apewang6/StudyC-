#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
	double sumprofit = 0.0;
	double permonthprofit = 0.0;
	const int MONTHCOUNT = 12;
	int count = 0;
	while (count<MONTHCOUNT&&cin >> permonthprofit)
	{
		++count;
		sumprofit += permonthprofit;
	}
	cout << setiosflags(ios::fixed);
	cout <<"$"<<setprecision(2)<< sumprofit / MONTHCOUNT;
}