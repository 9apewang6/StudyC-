#include <iostream>
#include <memory>
#include "ArrayList.h"

ListArray::ListArray():size_(0)
{
    memset(data_,0x00,sizeof(int)*DATASIZE);
}

void ListArray::initList(const ListArray& la)
{
    int i = 0;
    for (i = 0; i < la.size_; i++)
    {
        data_[i] = la.data_[i];
    }
    size_ = la.size_;
}

ListArray::ListArray(const ListArray& la)
{
    initList(la);
}

ListArray::ListArray(ListArray&& la)
{
    initList(la);
}

ListArray::~ListArray()
{

}

ListArray& ListArray::operator=(const ListArray& la)
{
    if (&la == this)
        return *this;
    initList(la);
    return *this;
}

void ListArray::clear()
{
    int i = 0;
    for (i = 0; i < size_; i++)
    {
        data_[i] = 0;
    }
    size_ = 0;
}

void ListArray::addElem(int a)
{
    if (size_ >= DATASIZE)
    {
        throw std::logic_error("memory not enough");
    }
    data_[size_] = a;
    size_ = size_ + 1;
}

int ListArray::deleteElem(int index) noexcept
{
    if (index < 0 || index >= size_)
    {
        throw std::logic_error("index invalid");
    }
    int val = data_[index];
    int i = 0;
    for (i = index; i < (size_-1); i++)
    {
        data_[i] = data_[i + 1];
    }
    data_[i] = 0;
    --size_;
}

void ListArray::modifyElem(int index, int e)
{
    if (index < 0 || index >= size_)
    {
        throw std::logic_error("index invalid");
    }
    data_[index] = e;
}

int ListArray::search(int elem)
{
    int i = 0;
    for (; i < size_; i++)
    {
        if (elem == data_[i])
        {
            return i;
        }
        continue;
    }
}

bool ListArray::isEmpty() const
{
    return size_ > 0;
}

int ListArray::getLength() const
{
    return size_;
}
//ÉýÐò
//

void ListArray::Aescending()
{

}

void ListArray::Descending()
{

}
void swap(int *p, int *q)
{
    if (p == q)return;
    *p = *p^*q;
    *q = *p^*q;
    *p = *p^*q;
}
void ListArray::reverse()
{

}

void ListArray::display() const
{
    int i = 0;
    for (; i < size_; i++)
    {
        std::cout << (i + 1) << " ." << data_[i] << std::endl;
    }
}
