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

描述

序列中``未排序''的一种量度是彼此不相关的条目对的数量。例如，在字母序列``DAABEC''中，此度量为5，因为D大于其右边的四个字母，E大于其右边的一个字母。
该度量称为序列中的反转数。序列``AACEDGG''仅具有一个反演（E和D）-几乎被排序--而序列``ZWQM''具有6个反演（它尽可能不被排序--正好是反向排序）。

您负责对DNA字符串序列（仅包含四个字母A，C，G和T的序列）进行分类。但是，您不希望按字母顺序对它们进行分类，而要按``排序''的顺序对它们进行分类，
从``最排序''到``最不排序''。所有字符串的长度相同。
输入项

第一行包含两个整数：一个正整数n（0 <n <= 50）给出字符串的长度；和一个正整数m（0 <m <= 100）给出字符串数。它们后面是m行，每行包含一个长度为n的字符串。
输出量

输出输入字符串列表，从``最排序''到``最不排序''。由于两个字符串可以均等地排序，因此请根据原始顺序输出它们。
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