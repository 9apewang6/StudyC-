#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
int function(string& str)
{
	int sum = 0;
	int length = str.size();
	for (int i = 0; i < length-1; i++)
	{
		int temp = 0;
		for (int j = i + 1; j < length; j++)
		{
			if (str[i] > str[j])
			{
				temp++;
			}
		}
		sum += temp;
	}
	return sum;
}
bool sortbyvalue(const pair<string,int> &a,const pair<string,int> &b)
{
	return a.second < b.second;
}
int main()
{
	int sequencelength = 0;
	int sequencecount = 0;
	vector<pair<string, int>> ans;
	int i=0,j = 0;
	cin >> sequencelength;
	cin >> sequencecount;
	cin.get();
	string line;
	for (i = 0; i < sequencecount; i++)
	{
		getline(cin,line);
		if (line.size() != sequencelength)
		{
			i--;
			continue;
		}
		ans.push_back(pair<string, int>(line, function(line)));
	}
	sort(ans.begin(), ans.end(),sortbyvalue);
	vector<pair<string, int>>::iterator iter = ans.begin();
	for (; iter != ans.end(); ++iter)
	{
		cout << iter->first << endl;
	}
}



  
/************************************************************************/
/* 

����

������``δ����''��һ�������Ǳ˴˲���ص���Ŀ�Ե����������磬����ĸ����``DAABEC''�У��˶���Ϊ5����ΪD�������ұߵ��ĸ���ĸ��E�������ұߵ�һ����ĸ��
�ö�����Ϊ�����еķ�ת��������``AACEDGG''������һ�����ݣ�E��D��-����������--������``ZWQM''����6�����ݣ��������ܲ�������--�����Ƿ������򣩡�

�������DNA�ַ������У��������ĸ���ĸA��C��G��T�����У����з��ࡣ���ǣ�����ϣ������ĸ˳������ǽ��з��࣬��Ҫ��``����''��˳������ǽ��з��࣬
��``������''��``�����''�������ַ����ĳ�����ͬ��
������

��һ�а�������������һ��������n��0 <n <= 50�������ַ����ĳ��ȣ���һ��������m��0 <m <= 100�������ַ����������Ǻ�����m�У�ÿ�а���һ������Ϊn���ַ�����
�����

��������ַ����б���``������''��``�����''�����������ַ������Ծ��ȵ�������������ԭʼ˳��������ǡ�
Sample Input

10 6
AACATGAAGG
TTTTGGCCAA
TTTGGCCAAA
GATCAGATTT
CCCGGGGGGA
ATCGATGCAT


Sample Output

CCCGGGGGGA
AACATGAAGG
GATCAGATTT
ATCGATGCAT
TTTTGGCCAA
TTTGGCCAAA




*/
/************************************************************************/