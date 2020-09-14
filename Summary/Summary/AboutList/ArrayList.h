#ifndef _ARRAYLIST_H_
#define _ARRAYLIST_H_
const int DATASIZE = 100;
/*
ADT  : list 
Elem : {int or ...}
operation :
1.  创建链表   initlist
3.  链表复制
4.  链表移动
2.  删除链表
5.  增加元素
6.  删除元素
7.  查找
8.  修改元素
9.  升序排列
10. 降序排列
11. 倒序
12. 获取链表长度
13. 判断是否为空
14. 显示链表
*/
class ListArray
{
public:
    ListArray();
    ListArray(const ListArray& la);
    ListArray(ListArray&& la);
    ListArray& operator=(const ListArray& la);
    ~ListArray();

    void clear();

    void addElem(int a);

    int deleteElem(int index)noexcept;
    
    void modifyElem(int index, int e);

    int search(int elem);

    bool isEmpty()const;

    int getLength()const;

    void Aescending();

    void Descending();

    void reverse(); 

    
    void display()const;
private:
    void initList(const ListArray& la);
    void bubblesort(int arr[],int len, bool Asending = false);
private:
    int data_[DATASIZE];
    int size_;
};




#endif //_ARRAYLIST_H_