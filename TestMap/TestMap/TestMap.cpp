// TestMap.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

void testMultimap()
{
    multimap<std::string, std::string> test_map;
    test_map.insert(make_pair("1", "test1"));
    test_map.insert(make_pair("2", "test2"));
    test_map.insert(make_pair("3", "test3"));
    test_map.insert(make_pair("4", "test4"));
    test_map.insert(make_pair("5", "tset5"));
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
}
void testUnordermap()
{
    std::unordered_map<std::string, int> Map_;
    Map_["ʱ��"] = 1;
    Map_["�о߱���"] = 2;
    Map_["��ض�ά��"] = 1;
    Map_["�۱߿������"] = 2;
    Map_["�۱߿������"] = 1;
    Map_["�۱߿�Ⱦ�ֵ"] = 2;
    Map_["�۱߿�����ֵ"] = 1;
    Map_["�۱߿����Сֵ"] = 2;
    Map_["�Ƿ����۽�"] = 1;
    Map_["�۽ǿ������"] = 2;
    Map_["�۽ǿ������"] = 1;
    Map_["�۽ǿ��"] = 2;

    for (auto iter : Map_)
    {
        cout << " unorder map first " << iter.first.c_str() << " : second " << iter.second << endl;
    }
    cout << " --------------- �ָ��� ---------------- " << endl;
}
void testMap()
{
    std::map<std::string, int> Map_;
    Map_["ʱ��"] = 1;
    Map_["�о߱���"] = 2;
    Map_["��ض�ά��"] = 1;
    Map_["�۱߿������"] = 2;
    Map_["�۱߿������"] = 1;
    Map_["�۱߿�Ⱦ�ֵ"] = 2;
    Map_["�۱߿�����ֵ"] = 1;
    Map_["�۱߿����Сֵ"] = 2;
    Map_["�Ƿ����۽�"] = 1;
    Map_["�۽ǿ������"] = 2;
    Map_["�۽ǿ������"] = 1;
    Map_["�۽ǿ��"] = 2;
    for (auto iter : Map_)
    {
        cout << "  map first " << iter.first.c_str() << " : second " << iter.second << endl;
    }
    cout << " --------------- �ָ��� ---------------- " << endl;
}
int main()
{
    testUnordermap();
    testMap();
    system("pause");
    return 0;
}

