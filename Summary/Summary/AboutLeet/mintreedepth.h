#ifndef _MINTREEDEPTH_H_
#define _MINTREEDEPTH_H_
#include "publicdef.h"

class Mintreedepth
{
public:
//     void dfs(TreeNode* node)
//     {
// 
//     }
    //深度优先
//     int minDepth(TreeNode* root)
//     {
//         if (root == nullptr)
//         {
//             return 0;
//        }
//         if (root->left == nullptr&& root->right == nullptr)
//         {
//             return 1;
//         }
//         int min_depth = INT_MAX;
//         if (root->left != nullptr)
//         {
//             min_depth = min(minDepth(root->left), min_depth);
//         }
//         if (root->right != nullptr)
//         {
//             min_depth = min(minDepth(root->right),min_depth);
//         }
//         return min_depth + 1;
//     }
    // 广度优先
    int minDepth(TreeNode* root)
    {
        if (root == nullptr)
        {
            return 0;

        }
        queue<pair<TreeNode*, int>> que;
        que.emplace(root, 1);
        while (!que.empty())
        {
            TreeNode* node = que.front().first;
            int depth = que.front().second;
            que.pop();
            if (node->left == nullptr&&node->right == nullptr)
            {
                return depth;
            }
            if (node->left != nullptr)
            {
                que.emplace(node->left, depth + 1);
            }
            if (node->right != nullptr)
            {
                que.emplace(node->right, depth + 1);
            }
        }
        return 0;
    }
    void test()
    {
        string inputtree;
        TreeNode* head = nullptr;
        char marks;
        while (getline(cin, inputtree))
        {
            head = stringTotreenode(inputtree);
            cout << minDepth(head) << endl;
            cout << "do you want to continue ...(y/n)" << endl;
            cin.get();
            cin.get(marks);
            if (marks != 'y')break;
            cin.get();
        }
    }
};


#endif //_MINTREEDEPTH_H_