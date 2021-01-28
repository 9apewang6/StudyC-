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



//���·��ת����·����vectorʵ�� 
//����·����/home/abs/../temp/new/../ ,���·��Ϊ��/home/temp

vector<string> pathChange(string input) {
    vector<string> inputpath, outputpath;
    string tmp;
    for (int i = 0; i < input.size(); i++) {   //��input�ַ�������/���ֿ��洢��inputpath 
        if (input[i] != '/') {			//�����С� ע�⣺��һ��Ϊ���ַ����� 
            tmp += input[i];
        }
        else {
            inputpath.push_back(tmp);
            tmp.clear();
        }
    }

    while (!inputpath.empty()) {			//�ж�vector���һ�������Ƿ�Ϊ��..������ 
        if (inputpath.back() != "..") {	//�ǣ�������2��ɾ��β���ݣ�������β�� 
            tmp = inputpath.back();		//�ݴ浽outputpath�У���ɾ��inputpath�е� 
            outputpath.push_back(tmp);	//β���ݡ� 
            inputpath.pop_back();
        }
        else {
            inputpath.pop_back();
            inputpath.pop_back();
        }
    }

    while (!outputpath.empty()) {					//��outputpath�е����ݴ�β��ͷת 
        inputpath.push_back(outputpath.back());	//�浽inputpath�еĴ�ͷ��β�� 
        outputpath.pop_back();
    }
    return inputpath;
}

void testReal() {
    string input = "./Memorty.txt", output;
    vector<string> outputpath;
    cout << "�������·����" << input << endl;
    outputpath = pathChange(input);
    cout << "�������·����";
    for (unsigned i = 1; i < outputpath.size(); i++)
        cout << "/" << outputpath.at(i);			//��������������outputpath������ 
    cout << endl;									//Ϊ�գ�  
    
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

