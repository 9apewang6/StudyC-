#include <iostream>
#include <vector>
using namespace std;
struct Biorhythms
{
	int p;
	int e;
	int i;
	int d;
	Biorhythms()
	{
		p = -1;
		e = -1;
		i = -1;
		d = -1;
	}
};
const int BODYCYCLE = 23;
const int EMOTIONCYCLE = 28;
const int INTELLIGENCECYCLE = 33;
const int TOTALCYCLE = BODYCYCLE*EMOTIONCYCLE*INTELLIGENCECYCLE;
int function(Biorhythms& bio)
{
	int i = 0;
	while (i <= TOTALCYCLE)
	{
		++i;
		if (((bio.d + i - bio.p) % BODYCYCLE == 0) && ((bio.d + i - bio.e) % EMOTIONCYCLE == 0) && ((bio.d + i - bio.i) % INTELLIGENCECYCLE == 0))
		{
			return i;
		}
	}
	return TOTALCYCLE;
}
int main()
{
	vector<int> ans;
	int size = 0;
	while (true)
	{
		Biorhythms biorhy;
		cin >> biorhy.p;
		cin >> biorhy.e;
		cin >> biorhy.i;
		cin >> biorhy.d;
		if (biorhy.p==-1&&biorhy.e==-1&&biorhy.i==-1&&biorhy.d==-1)break;
		ans.push_back(function(biorhy));
	}
	size = ans.size();
	for (int i =0 ; i <size;i++)
	{
		printf("Case %d: the next triple peak occurs in %d days.\n",(i+1),ans.at(i));
	}
}


/************************************************************************/
/*
生物规律
有人认为，一个人的生命从出生的那一天开始就有三个周期。这三个周期是身体，情感和智力周期，分别为23天，28天和33天。在一个周期的每个周期中都有一个峰值。
在一个周期的高峰期，一个人在相应的领域（身体，情感或精神）上表现最佳。例如，如果这是心理曲线，则思维过程将更加清晰，专心将更容易。
由于三个周期的周期不同，因此三个周期的峰值通常出现在不同的时间。我们想确定任何人何时出现三重峰（所有三个周期的峰均在同一天出现）。对于每个周期
，将从当前年份开始的天数，其中出现一个高峰（不一定是第一个高峰）。您还将获得一个日期，表示为从当年年初开始的天数。您的任务是确定从给定日期到下一个三重高峰的天数。
给定的日期不计算在内。例如，如果给定的日期是10，而下一个三重高峰发生在第12天，则答案是2，而不是3。如果在给定的日期中出现了三重高峰，则应指定下一次出现a的天数三重峰。
输入项

您会收到许多案例。每种情况的输入均由一行包含四个整数p，e，i和d的行组成。值p，e和i分别是从当年年初开始的身体，情绪和智力周期达到顶峰的天数。值d是给定的日期，
可以小于p，e或i中的任何一个。所有值均为非负值，最多365，并且您可以假定在给定日期的21252天内将出现三重峰值。输入的结尾由一行表示，其中p = e = i = d = -1。
输出量
23*28*33 =  21252


对于每个测试用例，以以下格式打印案例编号，然后显示一条消息，指示到达下一个三重高峰的天数：

案例1：下一个三重高峰发生在1234天。

即使答案为1，也应使用复数形式``天''。

样本输入
5+23m 20+28n 34+33k

0 0 0 0
0 0 0 100
5 20 34 325
4 5 6 7
283 102 23 320
203 301 203 40
-1 -1 -1 -1
样本输出

情况1：下一个三重高峰发生在21252天。
情况2：下一个三重高峰发生在21152天。
情况3：下一个三重高峰发生在19575天。
情况4：下一个三重高峰发生在16994天。
情况5：下一个三重高峰发生在8910天内。
情况6：下一个三重高峰发生在10789天
*/
/************************************************************************/