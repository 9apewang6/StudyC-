#include <iostream>
#include <vector>
#include <cmath>
#define PI 3.1415926
using namespace  std;
struct point {
	double x_pos;
	double y_pos;
	point()
	{
		x_pos = 0.0;
		y_pos = 0.0;
	}
};
int function(point &pi)
{
	double area = (pi.x_pos * pi.x_pos + pi.y_pos * pi.y_pos)*PI/2;
	return (int)(area / 50 + 1);
}
int main()
{
	int count = 0;
	cin >> count;
	cin.get();
	int  i = 0;
	vector<int> ans;
	ans.resize(count);
	for (i = 0; i < count; i++)
	{
		point p;
		cin >> p.x_pos;
		cin >> p.y_pos;
		ans.at(i) = function(p);
	}
	for (i = 0; i < count; i++)
	{
		printf("Property %d: This property will begin eroding in year %d.\n",(i+1),ans.at(i));	
	}
	cout << "END OF OUTPUT.";
}