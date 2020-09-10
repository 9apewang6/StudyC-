#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
using namespace  std;
map<string,int> HaabTable;
map<int,string> TzolkinTable;
const int HaabMonths = 19;
const int TzolkinMonths = 13;
// 1.  haab :   NumberOfTheDay. Month Year   18*20+5 = 365
// 2. Tzolkin:  Number NameOfTheDay Year	13*20 = 260
const char HaabDelimiter = '.';
struct Haab
{
	char Delimiter;
	int Numberofday;
	int Year;
	string Month;

	Haab()
	{
		Numberofday = 0;
		Delimiter = HaabDelimiter;
		Month = "pop";
		Year = 0;
	}
};

struct Tzolkin
{
	int Number;
	int year;
	string NameOftheday;
	Tzolkin()
	{
		Number = 0;
		year = 0;
		NameOftheday = "invalid";
	}
	friend ostream& operator<<(ostream& io, const Tzolkin& p);
};
ostream& operator<<(ostream& os, const Tzolkin &p)
{
	os << p.Number << " " << p.NameOftheday << " " << p.year << endl;
	return os;
}
void initHaab()
{
	HaabTable.clear();
	// pop, no, zip, zotz, tzec, xul, yoxkin, mol, chen, yax, zac, ceh, mac, kankin, muan, pax, koyab, cumhu
	HaabTable.insert(pair<string,int>("pop",1));
	HaabTable.insert(pair<string, int>("no",2));
	HaabTable.insert(pair<string, int>("zip",3));
	HaabTable.insert(pair<string, int>("zotz",4));
	HaabTable.insert(pair<string, int>("tzec",5));
	HaabTable.insert(pair<string, int>("xul",6));

	HaabTable.insert(pair<string, int>("yoxkin",7));
	HaabTable.insert(pair<string, int>("mol",8));
	HaabTable.insert(pair<string, int>("chen",9));
	HaabTable.insert(pair<string, int>("yax",10));
	HaabTable.insert(pair<string, int>("zac",11));
	HaabTable.insert(pair<string, int>("ceh",12));

	HaabTable.insert(pair<string, int>("mac",13));
	HaabTable.insert(pair<string, int>("kankin",14));
	HaabTable.insert(pair<string, int>("muan",15));
	HaabTable.insert(pair<string, int>("pax",16));
	HaabTable.insert(pair<string, int>("koyab",17));
	HaabTable.insert(pair<string, int>("cumhu",18));
	HaabTable.insert(pair<string, int>("uayet",19));

}
void initTzolkin()
{
	TzolkinTable.clear();
	// imix, ik, akbal, kan, chicchan, cimi, manik, lamat, muluk, ok, chuen, eb, ben, ix, mem, cib, caban, eznab, canac, ahau
	TzolkinTable.insert(pair<int, string>(1,"imix"));
	TzolkinTable.insert(pair<int, string>(2,"ik"));
	TzolkinTable.insert(pair<int, string>(3,"akbal"));
	TzolkinTable.insert(pair<int, string>(4,"kan"));

	TzolkinTable.insert(pair<int, string>(5,"chicchan"));
	TzolkinTable.insert(pair<int, string>(6,"cimi"));
	TzolkinTable.insert(pair<int, string>(7,"manik"));
	TzolkinTable.insert(pair<int, string>(8,"lamat"));

	TzolkinTable.insert(pair<int, string>(9,"muluk"));
	TzolkinTable.insert(pair<int, string>(10,"ok"));
	TzolkinTable.insert(pair<int, string>(11,"chuen"));
	TzolkinTable.insert(pair<int, string>(12,"eb"));

	TzolkinTable.insert(pair<int, string>(13,"ben"));
	TzolkinTable.insert(pair<int, string>(14,"ix"));
	TzolkinTable.insert(pair<int, string>(15,"mem"));
	TzolkinTable.insert(pair<int, string>(16,"cib"));

	TzolkinTable.insert(pair<int, string>(17,"caban"));
	TzolkinTable.insert(pair<int, string>(18,"eznab"));
	TzolkinTable.insert(pair<int, string>(19,"canac"));
	TzolkinTable.insert(pair<int, string>(20,"ahau"));
}

Tzolkin function(Haab& in)
{
	Tzolkin tz;

	int totalday = 0;
	int month = 0;
	if (HaabTable.find(in.Month)!=HaabTable.end())
	{
		month = HaabTable[in.Month]; 
	}
	
	totalday = in.Numberofday + (month - 1) * 20 + in.Year * 365;


	tz.year = totalday / (13 * 20);

	int currentyear = totalday % (13 * 20);

	tz.Number = (currentyear % 13+1);
	tz.NameOftheday = TzolkinTable[(currentyear % 20)+1];

	

	return tz;
}
void trimleftspace(string& str)
{
	//str.erase(str.begin(), find_if(str.begin(), str.end(), [=](int val) {return !isspace(val); }));
	
	int pos = str.find_first_not_of(' ');
	if (pos >= 0)
	{
		str.erase(0, pos);
	}
}
void trimrightspace(string& str)
{
	//str.erase(find_if(str.rbegin(), str.rend(), [=](int val) {return !isspace(val); }).base(),str.end());
	int pos = str.find_last_of(' ');
	if (pos == (str.size() - 1))
	{
		int pos2 = str.find_last_not_of(' ');
		if (pos2 >= 0)
		{
			str.erase(pos2 + 1, pos - pos2 + 1);
		}
	}
}
int stringtoint(const string& str)
{
	int len = str.size();
	int i = 0;
	int j = 0;
	int sum = 0;
	
	for (i = len - 1,j=0; i >= 0; i--,j++)
	{
		switch (i)
		{
		case 0:
			sum += (str[j] - '0');
			break;
		case 1:
			sum += (str[j] - '0')*10;
			break;
		case 2:
			sum += (str[j] - '0')*100;
			break;
		case 3:
			sum += (str[j] - '0')*1000;
			break;
		case 4:
			sum += (str[j] - '0') * 10000;
			break;
		case 5:
			sum += (str[j] - '0') * 100000;
			break;
		case 6:
			sum += (str[j] - '0') * 1000000;
			break;
		case 7:
			sum += (str[j] - '0') * 10000000;
			break;
		case 8:
			sum += (str[j] - '0') * 100000000;
			break;
		case 9:
			sum += (str[j] - '0') * 1000000000;
			break;
		}

	}
	return sum;
}
void formaToHaab(Haab& des, string& line)
{
	trimleftspace(line);
	trimrightspace(line);

	int Delimiterpos = line.find(HaabDelimiter);

	des.Numberofday = stringtoint(line.substr(0, Delimiterpos));

	int lastspace = line.find_last_of(' ');
	des.Year = stringtoint(line.substr(lastspace + 1, line.size()));

	des.Month = line.substr(Delimiterpos+1, lastspace-Delimiterpos);
	trimleftspace(des.Month);
	trimrightspace(des.Month);
}
int main()
{
	vector<Tzolkin> ans;
	initHaab();
	initTzolkin();
	int inputCount = 0;
	cin >> inputCount;
	cin.get();
	string line;

	for (int i = 0; i < inputCount; i++)
	{
		getline(cin, line);
		if (line.size() == 0 || line.find(HaabDelimiter) < 0)
		{
			i--;
			continue;
		}
		Haab ha;
		formaToHaab(ha, line);
		ans.push_back(function(ha));
	}
	vector<Tzolkin>::iterator iter = ans.begin();
	cout << ans.size() << endl;
	for (;iter!=ans.end();++iter)
	{
		cout << *iter;
	}
}



/************************************************************************/
/* 

在上次放假期间，马亚教授对旧的玛雅历法做出了令人惊讶的发现。教授从一条古老的信息中发现，玛雅文明使用了长达365天的一年，称为Haab，
历时19个月。前18个月的每个月均为20天，每个月的名称为pop，no，zip，zotz，tzec，xul，yoxkin，mol，chen，yax，zac，ceh，mac，kankin，muan，pax，
koyab，cumhu。几个月中的几天没有用名称来表示，而是用从0到19的数字表示。Haab的最后一个月称为uayet，有5天用数字0、1、2、3、4表示。Maya认为一个月很不幸，
法院没有开庭，交易停止了，人们甚至没有席卷地板。

出于宗教目的，玛雅人使用了另一个日历，其中将这一年称为“ Tzolkin”（冬青年）。一年分为13个时期，每个时期20天。每天由一对数字和一天的名称组成。
他们使用了20个名称：imix，ik，akbal，kan，chicchan，cimi，manik，lamat，muluk，ok，chuen，eb，ben，ix，mem，cib，caban，eznab，canac，ahau和13个数字；都是循环的。

请注意，每一天都有明确的描述。例如，在年初，对日期的描述如下：

1 imix，2 ik，3 akbal，4 kan，5 chicchan，6 cimi，7 manik，8 lamat，9 muluk，10 ok，11 chuen，12 eb，13 ben，1 ix，2 mem，3 cib，4 caban，5 eznab，6 canac，7 ahau，
并在下一个时期再次出现8 imix，9 ik，10 akbal。。。

年份（Haab和Tzolkin都用数字0、1，:::表示），其中数字0是世界的开始。因此，第一天是：

Haab：

0。pop 0 Tzolkin：1 imix 0
帮助MA Ya教授并为其编写一个程序，以将Haab日历的日期转换为Tzolkin日历。



Sample Input

3
10. zac 0
0. pop 0
10. zac 1995

Sample Output

3
3 chuen 0
1 imix 0
9 cimi 2801




总结前人给的数据，关键测试数据
Posted by KAISHEN at 2020-04-01 18:56:43 on Problem 1008
输入
7
0. pop 0
19. mac 0
0. kankin 0
1. kankin 0
4. uayet 0
4. uayet 259
12. cumhu 1845
输出
7
1 imix 0
13 ahau 0
1 imix 1
2 ik 1
1 chicchan 1
13 ahau 364
1 eznab 2591

*/
/************************************************************************/