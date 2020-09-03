
/*
 #include <iostream>
 using namespace std;

 int main(){
 	double in;
 	int r;
 	while(cin>>in&&in!=0.0&(5.20-in)>=0){		
 		for(r=1;in>0;++r){
 			in-=1.0/(r+1);
 		}
		cout <<(r-1)<<" card(s)"<<endl;
 	}
 }

*/
/*
1.00	3
3.71	61
0.04	1s
5.19	273
0.00

1/2+1/3+...+1/n  ,1/(n+1)
*/
#include <iostream>
using namespace std;
int dealwith(double value)
{
	int i = 1;
	double sum = 0.0;
	while ((value - sum) > 0)
	{
		++i;
		sum += 1.0 / i;
	}
	return (i-1);
}
int main()
{
	double value;
	while (cin >> value)
	{
		if (value < 0 || (value - 5.20)>0)
			continue;
		int cards = dealwith(value);
		if (cards > 0)
		{
			cout << cards << " card(s)" << endl;
		}
	}

	return 0;
}