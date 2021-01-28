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


void testValueType()
{
    std::vector<int> mMoveDoneVec;

    for (int i = 0; i < 10; i++)
    {
        mMoveDoneVec.push_back(i);
    }

    mMoveDoneVec.erase(remove(mMoveDoneVec.begin(), mMoveDoneVec.end(), 2), mMoveDoneVec.end());
    for (auto iter : mMoveDoneVec)
    {
        printf("iter:%d\n",iter);
    }
}



//相对路径转绝对路径，vector实现 
//输入路径：/home/abs/../temp/new/../ ,输出路径为：/home/temp

vector<string> pathChange(string input) {
    vector<string> inputpath, outputpath;
    string tmp;
    for (int i = 0; i < input.size(); i++) {   //将input字符串按‘/’分开存储到inputpath 
        if (input[i] != '/') {			//向量中。 注意：第一个为空字符串！ 
            tmp += input[i];
        }
        else {
            inputpath.push_back(tmp);
            tmp.clear();
        }
    }

    while (!inputpath.empty()) {			//判断vector最后一个数据是否为“..”，若 
        if (inputpath.back() != "..") {	//是，则连续2次删除尾数据，若否，则将尾数 
            tmp = inputpath.back();		//据存到outputpath中，并删除inputpath中的 
            outputpath.push_back(tmp);	//尾数据。 
            inputpath.pop_back();
        }
        else {
            inputpath.pop_back();
            inputpath.pop_back();
        }
    }

    while (!outputpath.empty()) {					//将outputpath中的数据从尾到头转 
        inputpath.push_back(outputpath.back());	//存到inputpath中的从头到尾中 
        outputpath.pop_back();
    }
    return inputpath;
}

void testReal() {
    string input = "./Memorty.txt", output;
    vector<string> outputpath;
    cout << "输入相对路径：" << input << endl;
    outputpath = pathChange(input);
    cout << "输出绝对路径：";
    for (unsigned i = 1; i < outputpath.size(); i++)
        cout << "/" << outputpath.at(i);			//由上述函数可以outputpath首数据 
    cout << endl;									//为空！  
    
}
void testreal()
{
  //  char* buffer;
//     if ((buffer = _getcwd(NULL, 0)) == NULL) {
//         perror("_getcwd error");
//     }
//     else {
//         printf("Current Dir: %s\n", buffer);
//         //free(buffer);
//     }

    char currentdir[1024] = { 0 }, dir[1024] = { 0 };
    sprintf(currentdir, "./BommingMotion.ini");

    printf("%s\n", currentdir);
#ifdef _WIN32
    _fullpath(dir, currentdir, 1024);
#else
    realpath(currentdir, dir);
#endif
    printf("dir=%s\n", dir);
}

void inline   LocalToUTF8(string strTextLocal, string& strTextUtf8)
{
    strTextUtf8 = "";

    if (0 == strTextLocal.length())
    {
        return;
    }

    vector<WCHAR> strUnicode;

    int nSize = MultiByteToWideChar(CP_ACP, 0, strTextLocal.c_str(), -1, NULL, 0);

    strUnicode.resize(nSize + 1);

    MultiByteToWideChar(CP_ACP, 0, strTextLocal.c_str(), -1, strUnicode.data(), (int)strUnicode.size());

    strUnicode[strUnicode.size() - 1] = NULL;

    vector<CHAR> strUTF8;

    nSize = WideCharToMultiByte(CP_UTF8, 0, strUnicode.data(), -1, NULL, 0, NULL, NULL);

    strUTF8.resize(nSize + 1);

    WideCharToMultiByte(CP_UTF8, 0, strUnicode.data(), -1, strUTF8.data(), (int)strUTF8.size(), NULL, NULL);

    strUTF8[strUTF8.size() - 1] = NULL;

    strTextUtf8 = strUTF8.data();
}

int main()
{
  //  testUnordermap();
  //  testMap();
   // testValueType();
    testreal();
    system("pause");
    return 0;
}

