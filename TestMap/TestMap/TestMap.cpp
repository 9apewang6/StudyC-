// TestMap.cpp : 定义控制台应用程序的入口点。
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
    Map_["时间"] = 1;
    Map_["夹具编码"] = 2;
    Map_["电池二维码"] = 1;
    Map_["折边宽度上限"] = 2;
    Map_["折边宽度下限"] = 1;
    Map_["折边宽度均值"] = 2;
    Map_["折边宽度最大值"] = 1;
    Map_["折边宽度最小值"] = 2;
    Map_["是否检测折角"] = 1;
    Map_["折角宽度上限"] = 2;
    Map_["折角宽度下限"] = 1;
    Map_["折角宽度"] = 2;

    for (auto iter : Map_)
    {
        cout << " unorder map first " << iter.first.c_str() << " : second " << iter.second << endl;
    }
    cout << " --------------- 分割线 ---------------- " << endl;
}
void testMap()
{
    std::map<std::string, int> Map_;
    Map_["时间"] = 1;
    Map_["夹具编码"] = 2;
    Map_["电池二维码"] = 1;
    Map_["折边宽度上限"] = 2;
    Map_["折边宽度下限"] = 1;
    Map_["折边宽度均值"] = 2;
    Map_["折边宽度最大值"] = 1;
    Map_["折边宽度最小值"] = 2;
    Map_["是否检测折角"] = 1;
    Map_["折角宽度上限"] = 2;
    Map_["折角宽度下限"] = 1;
    Map_["折角宽度"] = 2;
    for (auto iter : Map_)
    {
        cout << "  map first " << iter.first.c_str() << " : second " << iter.second << endl;
    }
    cout << " --------------- 分割线 ---------------- " << endl;
}
int main()
{
    testUnordermap();
    testMap();
    system("pause");
    return 0;
}

