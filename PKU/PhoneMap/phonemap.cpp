#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;
map<char, char> phonemaps;
char hyphan = '-';
char ignorechar1 = 'Q';
char ignorechar2 = 'Z';
void tranvert(std::string& str,map<string,int>& Ans)
{
	int len = str.size();
	int  prenum = 0;
	int  i = 0;
	
	for (i = 0; i < len; ++i)
	{
		if (str[i] == hyphan || str[i]==ignorechar1 || str[i] == ignorechar2)
		{
			str.erase(i,1);
			--i;
			--len;
			continue;
		}
		std::map<char,char>::iterator iter = phonemaps.find(str[i]);
		if (iter != phonemaps.end())
		{
			str.replace(i, 1, 1,iter->second);
			++prenum;
			continue;
		}
		
		if (str[i] >= '0'&&str[i] <= '9')
		{
			++prenum;
			continue;
		}
	}

	if (prenum == 7 && str.size() == 7)
	{
		str.insert(3, 1, hyphan);
		Ans[str]++;
	}


}
void initmap()
{
	phonemaps['A'] = phonemaps['B'] = phonemaps['C'] = '2';
	phonemaps['D'] = phonemaps['E'] = phonemaps['F'] = '3';
	phonemaps['G'] = phonemaps['H'] = phonemaps['I'] = '4';
	phonemaps['J'] = phonemaps['K'] = phonemaps['L'] = '5';
	phonemaps['M'] = phonemaps['N'] = phonemaps['O'] = '6';
	phonemaps['P'] = phonemaps['R'] = phonemaps['S'] = '7';
	phonemaps['T'] = phonemaps['U'] = phonemaps['V'] = '8';
	phonemaps['W'] = phonemaps['X'] = phonemaps['Y'] = '9';

}
int main()
{
	initmap();
	map<string, int> ans;
	bool hasRepeatedNumber = false;
	int	 phonecount = 0;
	string line;
	cin >> phonecount;
	cin.get();
	int i = 0;
	for (i = 0; i < phonecount; i++)
	{
		getline(cin, line);
		if (line.size() == 0)
		{
			i--;
			continue;
		}
		tranvert(line, ans);
	}
	map<string, int>::iterator iter = ans.begin();
	for (;iter!=ans.end();++iter)
	{
		if (iter->second > 1)
		{
			hasRepeatedNumber = true;
			cout << iter->first << " " << iter->second << endl;
		}
	}
	if (!hasRepeatedNumber)
	{
		cout << "No duplicates." << endl;
	}
	system("pause");
	return 0;
}
// int main(void)
// {
// 	ifstream fin;
// 	bool hasRepeatedNumber = false;
// 
// 	fin.open("a.txt");
// 	if (!fin.is_open())
// 	{
// 		return 0;
// 	}
// 	string line;
// 	//vector<string> input;
// 	map<string, int> ans;
// 
// 	while (getline(fin, line))
// 	{
// 		tranvert(line, ans);
// 	//	input.push_back(line);
// 	}
// 
// 	for (auto iter : ans)
// 	{
// 		if (iter.second > 1)
// 		{
// 			hasRepeatedNumber = true;
// 			cout << iter.first << "	" << iter.second << endl;
// 		}
// 	}
// 	if (!hasRepeatedNumber)
// 	{
// 		cout << "No duplicates" << endl;
// 	}
// 	system("pause");
// }

/*
A，B和C映射到2
D，E和F映射到3
G，H和I映射到4
J，K和L映射到5
M，N和O映射到6
P，R和S映射到7
T，U和V映射到8
W，X和Y映射到9
*/
// const map<const char, char> phonemaps = {
// 	{'A','2'},
// 	{'B','2'},
// 	{'C','2'},
// 	{ 'D','3' },
// 	{ 'E','3' },
// 	{ 'F','3' },
// 	{ 'G','4' },
// 	{ 'H','4' },
// 	{ 'I','4' },
// 	{ 'J','5' },
// 	{ 'K','5' },
// 	{ 'L','5' },
// 	{ 'M','6' },
// 	{ 'N','6' },
// 	{ 'O','6' },
// 	{ 'P','7' },
// 	{ 'R','7' },
// 	{ 'S','7' },
// 	{ 'T','8' },
// 	{ 'U','8' },
// 	{ 'V','8' },
// 	{ 'W','9' },
// 	{ 'X','9' },
// 	{ 'Y','9' }
// };