#pragma once
#include "publicdef.h"
class Solutionp257 {
private:
    vector<string> ans;
public:
    void dfs(TreeNode* root,string perm)
    {
        if (root == nullptr)return;
        if (root->left == nullptr&&root->right==nullptr)
        {
            perm += to_string(root->val);
            ans.emplace_back(perm);
            return;
        }
        perm += to_string(root->val);
        perm += "->";
        dfs(root->left,perm);
        dfs(root->right,perm);
        return;
    }
    vector<string> binaryTreePaths(TreeNode* root) {
        string per;
        dfs(root, per);
        return ans;

    }

    // bfs 
    vector<string> bfs(TreeNode* root)
    {
        vector<string> paths;
        if (root == nullptr)
        {
            return paths;
        }
        queue<TreeNode*> q;
        queue<string> qpath;
        q.push(root);
        qpath.push(to_string(root->val));
        while (!q.empty())
        {
            TreeNode* tmp = q.front();
            q.pop();
            string path = qpath.front();
            qpath.pop();
            if (tmp == nullptr)continue;
            if (tmp->left == nullptr&&tmp->right == nullptr)
            {
                paths.push_back(path);
            }
            else
            {
                if (tmp->left != nullptr)
                {
                    q.push(tmp->left);
                    qpath.push(path + "->" + to_string(tmp->left->val));
                }
                if(tmp->right!=nullptr)
                {
                    q.push(tmp->right);
                    qpath.push(path + "->" + to_string(tmp->right->val));
                }
            }
        }
        return paths;
           
    }
    void test()
    {
        string inputstr;
        vector<string> ans;
        char marks;
        TreeNode* root = nullptr;
        while (getline(cin, inputstr))
        {
            root = stringTotreenode(inputstr);
            ans = bfs(root);
            for (auto iter : ans) {
                cout << iter << endl;
            }
            cout << "do you want to continue..y/n" << endl;
            cin.get(marks);
            if (marks != 'y')break;
            cin.get();
        }
    }
};