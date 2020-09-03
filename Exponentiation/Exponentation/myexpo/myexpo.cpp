#include <string>
#include <cmath>
#include <algorithm>
#include "myexpo.h"
using namespace  std;

MyExpo::MyExpo(double in)
{
	//in 
	string to_str = std::to_string(in);
	int in_size = to_str.size();
	int pot_pos = to_str.find('.');

	data_.integer_effective = pot_pos;
	data_.decimal_effective = in_size - pot_pos-1;

	for (int j = pot_pos-1, i = 0; j >= 0; j--, i++)
	{
		data_.integer_[i] = to_str.at(j) - '0';

	}
	for (int j = in_size - 1, i = 0; j > pot_pos; j--, i++)
	{
		data_.decimalpart_[i] = to_str.at(j) - '0';
	}

	data_.total_size = data_.integer_effective + data_.decimal_effective;



}
MyExpo::MyExpo(vector<int> vec)
{
	int vec_size = vec.size();
	for (int i = vec_size - 1, j = 0; i >= 0; i--, j++)
	{
		data_.integer_[j] = vec.at(i);
	}
	data_.integer_effective = vec_size;
	data_.total_size = data_.integer_effective + data_.decimal_effective;

}

MyExpo::MyExpo(const Mydata& data)
{
	data_.integer_effective = data.integer_effective;
	data_.decimal_effective = data.decimal_effective;
	for (int i = 0; i < data_.decimal_effective; i++)
	{
		data_.decimalpart_[i] = data.decimalpart_[i];
	}
	for (int i = 0; i < data_.integer_effective; i++)
	{
		data_.integer_[i] = data.integer_[i];
	}
	data_.total_size = data_.integer_effective + data_.decimal_effective;

}

MyExpo::MyExpo()
{
	
}

void MyExpo::init(const MyExpo& ohr)
{
	for (int i = 0; i < ohr.data_.integer_effective; i++)
	{
		data_.integer_[i] = ohr.data_.integer_[i];
	}
	for (int j = 0; j < ohr.data_.decimal_effective; j++)
	{
		data_.decimalpart_[j] = ohr.data_.decimalpart_[j];
	}
	data_.integer_effective = ohr.data_.integer_effective;
	data_.decimal_effective = ohr.data_.decimal_effective;
	data_.total_size = data_.integer_effective + data_.decimal_effective;

}

MyExpo::MyExpo(const MyExpo&ohr)
{
	init(ohr);
}
MyExpo::MyExpo(MyExpo&& ohr)
{
	init(ohr);
	memset(ohr.data_.integer_, 0, sizeof(short)*DATASIZE);
	memset(ohr.data_.decimalpart_, 0, sizeof(short)*DATASIZE);
	ohr.data_.decimal_effective = 0;
	ohr.data_.integer_effective = 0;
	ohr.data_.total_size = 0;
}

MyExpo& MyExpo::operator=(const MyExpo& ohr)
{
	if (&ohr == this)
	{
		return *this;
	}
	init(ohr);
	return *this;
}

MyExpo& MyExpo::operator+(const MyExpo& ohr)
{
	return this->addOperate(ohr);
}

MyExpo& MyExpo::addOperate(const MyExpo& ohr)
{
	int carry_bit = 0;
	//  小数位相加 。 
	//  小数位 长  
	int decimallength = max(ohr.data_.decimal_effective,data_.decimal_effective);
	data_.decimal_effective = decimallength;
	int tempvalue = 0;
	for (int i = 0; i < decimallength; i++)
	{
		tempvalue = data_.decimalpart_[i] + ohr.data_.decimalpart_[i] + carry_bit;
		data_.decimalpart_[i] = (tempvalue) % 10;
		carry_bit = tempvalue / 10;
	}

	int integerlength = max(ohr.data_.integer_effective,data_.integer_effective);
	data_.integer_effective = integerlength;
	for (int i = 0; i < integerlength; i++)
	{
		tempvalue = data_.integer_[i] + ohr.data_.integer_[i] + carry_bit;
		data_.integer_[i] = tempvalue % 10;
		carry_bit = tempvalue / 10;
	}
	data_.integer_[integerlength] = carry_bit;
	if (carry_bit > 0) data_.integer_effective += 1;
	data_.total_size = data_.integer_effective + data_.decimal_effective;
	return *this;
}

MyExpo MyExpo::MulOperate(const MyExpo& ohr)
{
	int carrybit = 0;
	int tempval = 0;
	// 乘法运算， 考虑小数点， 
	// pot_pos = data_.pot_pos + ohr.data_.pot_pos;
	// 
	memset(multipiler, 0, sizeof(short)*DATASIZE);
	memset(multicand, 0, sizeof(short)*DATASIZE);
	memset(res, 0, sizeof(short)*DATASIZE);

	int i = 0;
	int j = 0;
	int temp = 0;
	for (i = 0; i < data_.decimal_effective; i++)
	{
		multipiler[i] = data_.decimalpart_[i];
	}
	for (i = 0; i < data_.integer_effective; i++)
	{
		multipiler[data_.decimal_effective + i] = data_.integer_[i];
	}

	for (i = 0; i < ohr.data_.decimal_effective; i++)
	{
		multicand[i] = ohr.data_.decimalpart_[i];
	}
	for (i = 0; i <  ohr.data_.integer_effective; i++)
	{
		multicand[ohr.data_.decimal_effective  + i] = ohr.data_.integer_[i];
	}

	int pot_pos = data_.decimal_effective + ohr.data_.decimal_effective;

	for (i = 0; i < data_.integer_effective + data_.decimal_effective ; i++)
	{
		if (multipiler[i] == 0)
		{
			continue;
		}

		for (j = 0; j < ohr.data_.integer_effective + ohr.data_.decimal_effective; j++)
		{
		
			temp = multipiler[i] * multicand[j];
			res[i + j] += temp;
			for (int l = i + j; res[l] > 9; l++)
			{
				res[l + 1] += res[l] / 10;
				res[l] = res[l] % 10;
			}

		}

	}
	
	int preindex = -1;
	int lastindex = -1;
	for (i = DATASIZE - 1; i >= pot_pos; i--)
	{
		if (res[i] != 0)
		{
			preindex = i;
			break;
		}
	}

	for (i = 0; i < pot_pos; i++)
	{
		if (res[i] != 0)
		{
			lastindex = i;
			break;
		}
	}

	MyExpo expo;
	for (i = preindex; i >= pot_pos; i--)
	{
		expo.data_.integer_[i - pot_pos] = res[i];
	}
	if(preindex>0)expo.data_.integer_effective = preindex - pot_pos+1;
	else  expo.data_.integer_effective = 0;
	for (i = pot_pos - 1; i >= lastindex; i--)
	{
		expo.data_.decimalpart_[i] = res[i];
	}
	expo.data_.decimal_effective = pot_pos;
	expo.data_.total_size = expo.data_.decimal_effective + expo.data_.integer_effective;


	return expo;
}

MyExpo MyExpo::SubOperate(const MyExpo& ohr)
{
	return MyExpo(ohr.data_);
}

MyExpo MyExpo::DivideOperate(const MyExpo& ohr)
{
	return MyExpo(ohr.data_);
}

MyExpo MyExpo::powOperate(int power)
{
	MyExpo temp(*this);
	while (power >= 2)
	{
		--power;
		temp = MulOperate(temp);
	}

	return temp;

}

void MyExpo::display() const
{
	int i = 0;
	int lastindex = -1;
	for (i = data_.integer_effective-1; i>=0; i--)
	{
		cout << data_.integer_[i];
	}
	if (data_.decimal_effective > 0)
	{
		cout << ".";
		for (i = 0; i < data_.decimal_effective - 1; i++)
		{
			if (data_.decimalpart_[i] != 0)
			{
				lastindex = i;
				break;
			}
		}
		for ( i = data_.decimal_effective-1; i >= lastindex; i--)
		{
			cout << data_.decimalpart_[i];
		}
	}

	cout << endl;
}

MyExpo::~MyExpo()
{

}

