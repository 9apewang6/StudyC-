#ifndef _PUBLICDEF_H_
#define _PUBLICDEF_H_
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

struct ListNode
{
    int val;
    ListNode* next_;
    ListNode() :val(0), next_(NULL) {};
    ListNode(int v) :val(v), next_(NULL) {};
};

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) :val(v),left(nullptr), right(nullptr) {  };
};

void trimleftspace(std::string &str)
{
    //删除从左到右是空格的
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [=](int val) {return !isspace(val); }));
}
void trimrightspace(std::string &str)
{
    str.erase(std::find_if(str.rbegin(), str.rend(), [=](int val) {return !isspace(val); }).base(),str.end());
}

template<typename T>
std::string vectorTostring(vector<T> &vec)
{
    std::string trans = "";
    for (auto iter : vec)
    {
        trans += "";
        trans += std::to_string(iter);
        trans += "--";
    }
    return trans;
}

// string to vector
vector<int> stringtovector(std::string& str)
{
    // [1,3] 
    int len = str.size();
    vector<int> ans;
    for (int i = 0; i < len; i++)
    {
        if (str[i] >= '0'&&str[i] <= '9')
        {
            ans.push_back(str[i]-'0');
        }
    }
    return ans;
}

vector<int> stringTovector(std::string& str)
{
    vector<int> output;
    trimleftspace(str);
    trimrightspace(str);

    str = str.substr(1, str.size() - 2);
    stringstream ss;
    ss.str(str);
    string item;
    char delim = ',';
    while (getline(ss, item, delim))
    {
        output.push_back(stoi(item));
    }
    return output;
}



ListNode* stringTolistnode(std::string &str)
{
    vector<int> list = stringtovector(str);

    ListNode* head = new ListNode(0);
    ListNode* tail = head;
    for (auto item : list)
    {
        tail->next_ = new ListNode(item);
        tail = tail->next_;
    }
    tail = head->next_;
    delete head;
    return tail;
}

TreeNode* stringTotreenode(std::string& str)
{
    trimleftspace(str);
    trimrightspace(str);
    str = str.substr(1, str.size() - 2);
    if (!str.size())
    {
        return nullptr;
    }
    string item;
    stringstream ss;
    ss.str(str);

    getline(ss,item,',');
    
    TreeNode *root = new TreeNode(stoi(item));

    queue<TreeNode*> nodeQueue;
    nodeQueue.push(root);

    while (true)
    {
        TreeNode* node = nodeQueue.front();
        nodeQueue.pop();
        if (!getline(ss, item, ','))
        {
            break;
        }
        trimleftspace(item);
        if (item != "null")
        {
            int leftnumber = stoi(item);
            node->left = new TreeNode(leftnumber);
            nodeQueue.push(node->left);
    
        }
        if (!getline(ss, item, ','))
        {
            break;
        }
        trimleftspace(item);
        if (item != "null")
        {
            int rightnumber = stoi(item);
            node->right = new TreeNode(rightnumber);
            nodeQueue.push(node->right);
        }
    }
    return root;
}


string listnodetostring(ListNode* head)
{
    if (head == nullptr)
    {
        return "[]";
    }
    string res;
    while (head)
    {
        res += to_string(head->val) + ",";
        head = head->next_;
    }
    return "[" + res.substr(0, res.size() - 1) + "]";

}

string booltostring(bool b)
{
    return b ? "True" : "False";
}

#endif //_PUBLICDEF_H_