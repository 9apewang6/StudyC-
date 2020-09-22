#pragma once
#include "publicdef.h"
class Solutionpro538
{
public:
    // ¶þ²æËÑË÷Ê÷  ×ª ÀÛ¼ÓÊ÷ 
    TreeNode* convertBST(TreeNode* root) {
        if (!root)return root;
        queue<TreeNode*> Q;
        Q.push(root);
        vector<int> vals;

       // vec.push_back(root->val);
        while (!Q.empty())
        {
            TreeNode* head = Q.front();
            Q.pop();
            if (!head)continue;
            vals.push_back(head->val);
            if (head->left)Q.push(head->left);
            if (head->right)Q.push(head->right);
        }

        int len = vals.size();
        int i, j;
        vector<int> res;
        res.resize(len);
        for (i = 0; i < len; i++)
        {
            res[i] = vals[i];
            for (j = 0; j < len; j++)
            {
                if (vals[j] > vals[i]) {
                    res[i] += vals[j];
                }
            }
        }

        Q.push(root);
        i = 0;
        while (!Q.empty())
        {
            TreeNode* head = Q.front();
            Q.pop();
            if (!head)continue;
            head->val = res[i];
            i++;
            if (head->left)Q.push(head->left);
            if (head->right)Q.push(head->right);
        }
        
        return root;
    }
    void test()
    {
        string inputstr;
        TreeNode* root=nullptr;
        TreeNode* ans=nullptr;
        char marks;
        while (getline(cin, inputstr))
        {
            root = stringTotreenode(inputstr);
            ans = convertBST(root);
            cout << " do  you want to continue .. y/n" << endl;
            cin.get(marks);
            if (marks != 'y')break;
            cin.get();
        }
    }
};