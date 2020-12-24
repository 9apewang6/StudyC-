#pragma once
#include "publicdef.h"
class Solution {
public:
    struct Point {
        int x_;
        int y_;
        Point()
        {
            x_ = 0;
            y_ = 0;
        }
        Point(int x, int y)
        {
            x_ = x;
            y_ = y;
        }
    };
    struct Rec
    {
        Point left_;
        Point right_;
    };
    inline void initpoint(vector<int>& nums, Rec &p)
    {
        p.left_.x_ = nums[0];
        p.left_.y_ = nums[1];
        p.right_.x_ = nums[2];
        p.right_.y_ = nums[3];
    }
    bool checking(Rec& l, Rec& r)
    {
  
        return  !(l.right_.x_ <= r.left_.x_ ||
            l.right_.y_ <= r.left_.y_ ||
            l.left_.x_ >= r.right_.x_ ||
            l.left_.y_ >= r.right_.y_);
    }
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
        if (rec1.size() != 4 || rec2.size() != 4)return false;
        Rec  left;
        Rec right;
        initpoint(rec1, left);
        initpoint(rec2, right);
        return checking(left, right);
    }
};