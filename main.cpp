#include <iostream>
#include "ReverseIterator.class.hpp"
#include <vector>
#include <typeinfo>
#include <math.h>

#include "Vector.class.hpp"

void printIterator(Vector<int>::reverse_iterator it, Vector<int>::reverse_iterator end)
{
    std::cout << *it << std::endl;
    while (it != end)
    {
        std::cout << *it << std::endl;
        ++it;
    }
}

void printIterator(std::vector<int>::reverse_iterator it, std::vector<int>::reverse_iterator end)
{
    std::cout << *it << std::endl;
    while (it != end)
    {
        std::cout << *it << std::endl;
        ++it;
    }
}

void container(std::vector<int> &v, const std::vector<int>::reverse_iterator &it)
{
    std::cout << "-----------------------System-----------------------" << std::endl;
    std::cout << "size: " << v.size() << std::endl;
    std::cout << "capacity: " << v.capacity() << std::endl;
    std::cout << "                       printIt                       " << std::endl;
    // it += 1;
    // printIterator(it, v.rend());
    return;
}

void myContainer(Vector<int> &v, const Vector<int>::reverse_iterator &it)
{
    std::cout << "----------------------- MINE -----------------------" << std::endl;
    std::cout << "size: " << v.size() << std::endl;
    std::cout << "capacity: " << v.capacity() << std::endl;
    std::cout << "                       printIt                       " << std::endl;
    // *it = 42;
    // printIterator(it, v.rend());
    return;
}

int main()
{
    /*-----------------------System-----------------------*/
    std::vector<int> v0;
    // v0.push_back(1);
    // // v0.push_back(2);
    std::vector<const int>::iterator it0 = v0.begin();
    // std::cout << typeid(std::vector<const int>::iterator::).name() << std::endl;
    // container(v0, it0);
    /*----------------------- MINE -----------------------*/
    Vector<int> v1;
    // v1.push_back(1);d
    // v1.push_back(2);
    // const Vector<int>::reverse_iterator it1 = v1.rbegin();
    Vector<int>::iterator it1 = v1.begin();
    // Vector<const int>::const_iterator it1;
    // Vector<const int>::iterator it2;
    // Vector<int>::const_iterator it3;
    // myContainer(v1, it1);

    return (0);
}