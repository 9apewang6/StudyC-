#include "buyStock2.h"
#include "findmink.h"
#include "mintreedepth.h"
#include "MaxPalindrome.h"
#include "middlenode.h"
#include "of22.h"
#include "of04.h"
#include "155.h"
#include "of05.h"
#include "0106.h"
#include "pro112.h"
#include "pro167.h"
#include "0101.h"
#include "pro226.h"
#include "1716.h"
#include "pro1013.h"
#include "pro685.h"
#include "off10_1.h"

#include "pro257.h"
#include "pro538.h"

#include "pro404.h"

void testbuystock2()
{
    Solution122 _s122;
    _s122.test();
}
void testfindmink()
{
    Solutionof40 _f40;
    _f40.test();
}
void testmintreedepth()
{
    Mintreedepth mintree;
    mintree.test();
}
void testmaxpalind()
{
    Maxpalindrome maxpalind;
    maxpalind.test();
}
void testmiddlenode()
{
    GetMidNode getmid;
    getmid.test();
}
void testoff22()
{
    Solutionof22 of22;
    of22.test();
}
void testoff04()
{
    Solutionof04 of04;
    of04.test();
}
/*
["MinStack","push","push","push","getMin","top","pop","getMin"]
[[],[-2],[0],[-1],[],[],[],[]]
*/
void test155()
{
    MinStack minStack;
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-1);
    cout << " min value is " << endl;
   cout << minStack.getMin()<<endl;
   cout << " before pop " << endl;
   cout << minStack.top() << endl;
    minStack.pop();
   
    cout << " min value is " << endl;
    cout <<minStack.getMin()<<endl;
}
void testvector()
{
    vector<int> vec;
    vec.push_back(1);
    cout << " insert 1" << endl;
    vec.push_back(2);
    cout << " insert 2" << endl;

    vec.push_back(3);
    cout << " insert 3" << endl;

    vec.push_back(4);
    cout << " insert 4" << endl;

    int fron = vec.front();
    cout << " vec. fornt is " << fron << endl;
    int bak = vec.back();
    cout << " vec. back is " << bak << endl;
    
    vec.pop_back();

    cout << " after pop_back " << endl;
    for (auto iter : vec)
    {
        cout << iter << endl;
    }



    vector<vector<int>> ans;
    vector<int> perm;
    perm.push_back(1);
    ans.emplace_back(perm);
    perm.push_back(2);
    ans.emplace_back(perm);
    perm.push_back(3);
    ans.emplace_back(perm);
    
}
void testqueue()
{
    queue<int> tque;
    tque.push(1);
    cout << " insert 1" << endl;
    tque.push(2);
    cout << " insert 2" << endl;

    tque.push(3);
    cout << " insert 3" << endl;

    tque.push(4);
    cout << " insert 4" << endl;

    int front = tque.front();
    cout << " front is " << front << endl;
    int back = tque.back();
    cout << " back is " << back << endl;

    tque.pop();
    cout << " after pop " << endl;
}
void testof05()
{
    Solutionof05 of05;
    of05.test();
}
void test0106()
{
    Solution0106 o0106;
    o0106.test();
}
void testp112()
{
    Solutionp112 p112;
    p112.test();
}
void testp167()
{
    Solutionp167 p167;
    p167.test();
}
void test0101()
{
    Solution0101 p0101;
    p0101.test();
}
void testpro226()
{
    Solutionp226 p226;
    p226.test();
}
void test1716()
{
    Solution1716 p1716;
    p1716.test();
}
void testmap()
{
    map<string, bool> hashm;
    hashm["a"] = true;
    hashm["b"] = true;
    hashm["c"] = true;
    cout << hashm["d"] << endl;
}
void testpro1013()
{
    Solutionpro1013 p1013;
    p1013.test();
}
void testvecvec()
{
    string inputstr;
    vector<vector<int>> ans;
    char marks;
    while (getline(cin, inputstr))
    {
        ans = stringtovectorvector(inputstr);
        cout << " do you want to continue .. y/n"<<endl;
        cin.get(marks);
        if (marks != 'y')break;
        cin.get();
    }
}
void test685()
{
    Solutionp685 p685;
    p685.test();
}
void testoff10_1()
{
    string ans = "123412341234";
    ans = ans.substr(0, ans.size()-1);
    Solutionoff10_1 off10_1;
    cout <<off10_1.fib(5)<<endl;
}
void test257()
{
    Solutionp257  s257;
    s257.test();
}
void test538()
{
    Solutionpro538 p538;
    p538.test();
}
void testpro404()
{
    Solutionpro404 pro404;
    pro404.test();
}
#include "01.h"
void test01()
{
    Solution s;
    s.test();
}
int main()
{

    test01();

    system("pause");
}