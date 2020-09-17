#pragma once
#include "publicdef.h"
class Solutionp543 {
private:
    int depth;
    int getDepth(TreeNode* head) {
        if (head == nullptr)
        {
            return 0;
        }
        int dep1 = getDepth(head->left);

        int dep2 = getDepth(head->right);

        depth = max(depth, dep1 + dep2 + 1);

        return max(dep1,dep2)+1;
    }
public:
 
        
    int diameterOfBinaryTree(TreeNode* root) {
        depth = 0;
        getDepth(root);
        return depth-1;        
    }
};