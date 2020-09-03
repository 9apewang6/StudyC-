#ifndef _MYEXPO_H_
#define _MYEXPO_H_
#include <iostream>
#include <vector>
using std::vector;
const int DATASIZE = 120;
class MyExpo
{
	struct Mydata
	{
		short integer_[DATASIZE];
		short decimalpart_[DATASIZE];
		int integer_effective;
		int decimal_effective;
		int total_size ;
		Mydata()
		{
			memset(integer_, 0, sizeof(short)*DATASIZE);
			memset(decimalpart_,0,sizeof(short)*DATASIZE);
			integer_effective = 0;
			decimal_effective = 0;
			total_size = 0;
		}
	};
public:
	MyExpo(vector<int> vec);
	MyExpo(double in);
	MyExpo();
	~MyExpo();
	void init(const MyExpo& ohr);
	MyExpo(const MyExpo& ohr);
	MyExpo(MyExpo&& ohr);
	MyExpo(const Mydata& data);
	MyExpo& operator=(const MyExpo& ohr);
	MyExpo& operator+(const MyExpo& ohr);
	MyExpo& addOperate(const MyExpo& ohr);
	MyExpo MulOperate(const MyExpo& ohr);
	MyExpo SubOperate(const MyExpo& chr);
	MyExpo DivideOperate(const MyExpo& chr);
	MyExpo powOperate(int power);
	void display()const;
private:
	Mydata  data_;	
	short multipiler[DATASIZE]{ 0 };
	short multicand[DATASIZE]{ 0 };

	short res[DATASIZE]{ 0 };
};


#endif //_MYEXPO_H_