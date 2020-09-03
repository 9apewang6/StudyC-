#include <iostream>
using namespace  std;

int main()
{

	system("pause");
}


/************************************************************************/
/* 

在上次放假期间，马亚教授对旧的玛雅历法做出了令人惊讶的发现。教授从一条古老的信息中发现，玛雅文明使用了长达365天的一年，称为Haab，历时19个月。前18个月的每个月均为20天，每个月的名称为pop，no，zip，zotz，tzec，xul，yoxkin，mol，chen，yax，zac，ceh，mac，kankin，muan，pax，科雅卜，科胡。几个月中的几天没有用名称来表示，而是用从0到19的数字表示。Haab的最后一个月称为uayet，有5天用数字0、1、2、3、4表示。Maya认为一个月很不幸，法院没有开庭，交易停止了，人们甚至没有席卷地板。

出于宗教目的，玛雅人使用了另一个日历，其中将这一年称为“ Tzolkin”（冬青年）。一年分为13个时期，每个时期20天。每天由一对数字和一天的名称组成。他们使用了20个名称：imix，ik，akbal，kan，chicchan，cimi，manik，lamat，muluk，ok，chuen，eb，ben，ix，mem，cib，caban，eznab，canac，ahau和13个数字；都是循环的。

请注意，每一天都有明确的描述。例如，在年初，对日期的描述如下：

1 imix，2 ik，3 akbal，4 kan，5 chicchan，6 cimi，7 manik，8 lamat，9 muluk，10 ok，11 chuen，12 eb，13 ben，1 ix，2 mem，3 cib，4 caban，5 eznab，6 canac，7 ahau，并在下一个时期再次出现8 imix，9 ik，10 akbal。。。

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



*/
/************************************************************************/