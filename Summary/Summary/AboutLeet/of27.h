#pragma once
#include "publicdef.h"
class Solution {
public:
    TreeNode* dfs(TreeNode* root)
    {
        if (root == nullptr)
        {
            return root;
        }
        TreeNode* left = dfs(root->left);
        TreeNode* right = dfs(root->right);
        root->left = right;
        root->right = left;
        return root;
    }
    TreeNode* mirrorTree(TreeNode* root) {
        if (root == nullptr)return root;

        queue<TreeNode*> Q;
        Q.push(root);
        while (!Q.empty())
        {
            TreeNode* head = Q.front();
            Q.pop();
            TreeNode* tmp = head->left;
            head->left = head->right;
            head->right = tmp;

            if (head->left != nullptr)
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
};