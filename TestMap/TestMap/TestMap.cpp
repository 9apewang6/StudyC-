// TestMap.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int main()
{
	multimap<std::string, std::string> test_map;
	test_map.insert(make_pair("1", "test1"));
	test_map.insert(make_pair("2","test2"));
	test_map.insert(make_pair("3","test3"));
	test_map.insert(make_pair("4","test4"));
	test_map.insert(make_pair("5","tset5"));
	auto iter = test_map.find("1");
	for (; iter != test_map.end(); iter++)
	{
		if (iter->second == "test2")
		{
			test_map.erase(iter->first);
		
			break;
		}
		
	}
	std::string str;
	str = iter->second;
    return 0;
}

