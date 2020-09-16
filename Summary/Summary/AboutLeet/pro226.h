#pragma once
#include "publicdef.h"
class Solutionp226 {
public:
//     TreeNode* tranvert(TreeNode* left, TreeNode* right)
//     {
// 
//     }
    TreeNode*  dfs(TreeNode* root)
    {
        if (root == nullptr) {
            return nullptr;
        }
        TreeNode* left = dfs(root->left);
        TreeNode* right = dfs(root->right);
        root->left = right;
        root->right = left;
        return root;

        
    }
    TreeNode* invertTree(TreeNode* root) {

        queue<TreeNode*> Q;
        Q.push(root);
        
        while (!Q.empty())
        {
            TreeNode* head = Q.front();
            Q.pop();
            if (head == nullptr)break;
            if (head->left == nullptr&&head->right == nullptr)continue;
            TreeNode* temp = head->left;
            head->left = head->right;
            head->right = temp;

            if (head->left!=nullptr)
            {
                Q.push(head->left);
            }
            if (head->right != nullptr)
            {
                Q.push(head->right);
            }

        }
        return root;
    }
    void test()
    {
        string inputtree;
        TreeNode* head = nullptr;
        TreeNode* ans = nullptr;
        char marks;
        while (getline(cin, inputtree))
        {
            head = stringTotreenode(inputtree);
            ans = dfs(head);
           
            cout << "do you want to continue ...(y/n)" << endl;
           
            cin.get(marks);
            if (marks != 'y')break;
            cin.get();
        }
    }
};