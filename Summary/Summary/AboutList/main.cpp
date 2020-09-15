#include <iostream>
#include <time.h>
#include "ArrayList.h"
#include "Linklist.h"
using namespace std;
const int datasize = 10;
void tarraylist()
{
    srand((unsigned int)time(0));
    ListArray la;
    int val = 0;
    for (int i = 0; i < datasize; i++)
    {
        val = rand() % 20 + i;
        la.addElem(val);
        cout << (i + 1) << "     ." << val << endl;
    }
    cout << " list array show" << endl;
    la.display();

    cout << " do ascending" << endl;
    la.Aescending();
    la.display();

    cout << " do desending " << endl;
    la.Descending();
    la.display();


    la.reverse();

    cout << " after reverse , show " << endl;
    la.display();
}
void tlinklist()
{
    LinkList lk;
    lk.addElem(Element(1));
    lk.addElem(Element(2));
    lk.addElem(Element(3));
    lk.addElem(Element(5));
    lk.addElem(Element(4));
    lk.display();

    cout << " insert 6 in position 3" << endl;
    lk.insertElem(Element(6), 8);
    lk.display();

    cout << "insert 7 in position 5" << endl;
    ListNode* newnode = new ListNode(Element(7));
    lk.insertNode(newnode, 5);
    lk.display();

    cout << " ready to delete idx 4" << endl;
    lk.deleteElem(6);
    lk.display();

    cout << " addback 5" << endl;
    lk.addBack(8);
    lk.display();

    cout << " modify 8 to 18" << endl;
    lk.modify(8, 18);
    lk.display();

    cout << "search 18," << lk.search(18) << endl;

    cout << " sort descending " << endl;
    lk.Descending();
    lk.display();

    cout << " sort ascending " << endl;
    lk.Ascending();
    lk.display();

    cout << "reverse " << endl;
    lk.reverse();
    lk.display();
}
int main(void)
{
    tlinklist();

    system("pause");
}