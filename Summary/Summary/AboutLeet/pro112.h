#pragma once
#include "publicdef.h"
class Solutionp112 {
public:
    bool hasPathSum(TreeNode* root, int sum) {
        if (root == nullptr)
        {
            return false;
        }
        if (root->left == nullptr&&root->right == nullptr)
        {
            return sum == root->val;
        }
        sum = sum - root->val;
        bool res = hasPathSum(root->left, sum);
        if (res)return true;
        res =  hasPathSum(root->right, sum);
        return res;
    }
    void test()
    {
        string inputtree;
        TreeNode* head = nullptr;
        char marks;
        int target;
        while (getline(cin, inputtree))
        {
            head = stringTotreenode(inputtree);

            cin >> target;
            cout << booltostring(hasPathSum(head,target)) << endl;
            cout << "do you want to continue ...(y/n)" << endl;
            cin.get();
            cin.get(marks);
            if (marks != 'y')break;
            cin.get();
        }
    }
     
};

/*
给定一个二叉树和一个目标和，判断该树中是否存在
根节点到叶子节点的路径，这条路径上所有节点值相加等于目标和。

说明: 叶子节点是指没有子节点的节点。

示例: 
给定如下二叉树，以及目标和 sum = 22，

5
/ \
4   8
/   / \
11  13  4
/  \      \
7    2      1
返回 true, 因为存在目标和为 22 的根节点到叶子节点的路径 5->4->11->2。


*/