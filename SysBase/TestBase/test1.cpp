#include <thread>

#include "SysBase_Interface.h"
using namespace SysBase;
using namespace std;
void testDateTime()
{
    CDateTime _date;
    printf("CDateTime getDay(%d)\n",_date.GetDay());
    printf("CDateTime GetMillisecond(%d)\n", _date.GetMillisecond());
    std::this_thread::sleep_for(std::chrono::milliseconds(40));
    printf("CDateTime GetMillisecond(%d)\n", _date.GetMillisecond());

    CDateTime _test1(2021,01,12); //
    printf("CDateTime getDay[%d],getSecond[%d]\n", _test1.GetDay(), _test1.GetSecond());

}
struct T_Data {
    int val;
    float f_val;
};
void test_AutoPtr()
{
   

    CSharedPtr<T_Data> _test_sharedptr =  CSharedPtr<T_Data>(new T_Data());
    std::shared_ptr<T_Data> _test_std = std::make_shared<T_Data>();
    _test_sharedptr->val = 1;
    _test_sharedptr->f_val = 2.5;
    _test_std->val = 2;
    _test_std->f_val = 3.4;
    
    printf("the CSharedPtr T_data val [%d],f_val[%.2f] , isEmpty[%d]\n",_test_sharedptr->val,_test_sharedptr->f_val);
    printf("the std::shared_ptr T_data val is [%d], f_Val[%.2f]\n", _test_std->val, _test_std->f_val);



}

void testSingleMgr()
{
    class Test :public CObject
    {
    public :
        Test();
        ~Test();
    public:
        int val;
    };
    Test t = CSingletonT<Test>::Instance();
    t.val = 1;
    Test t2 = CSingletonT<Test>::Instance();
    printf("t2.val is [%d]",t2.val);
}
int main()
{
    test_AutoPtr();
    system("pause");
    return 0;
}