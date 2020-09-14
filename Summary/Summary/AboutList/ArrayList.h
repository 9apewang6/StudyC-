#ifndef _ARRAYLIST_H_
#define _ARRAYLIST_H_
const int DATASIZE = 100;
/*
ADT  : list 
Elem : {int or ...}
operation :
1.  ��������   initlist
3.  ������
4.  �����ƶ�
2.  ɾ������
5.  ����Ԫ��
6.  ɾ��Ԫ��
7.  ����
8.  �޸�Ԫ��
9.  ��������
10. ��������
11. ����
12. ��ȡ������
13. �ж��Ƿ�Ϊ��
14. ��ʾ����
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