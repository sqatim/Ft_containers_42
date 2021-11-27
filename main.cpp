#include <iostream>
#include "ReverseIterator.class.hpp"
#include <vector>
#include <typeinfo>
#include <math.h>

#include "Vector.class.hpp"

void printIterator(Vector<int>::iterator it, Vector<int>::iterator end)
{
    while (it != end)
    {
        std::cout << *it << std::endl;
        ++it;
    }
}

void printIterator(std::vector<int>::iterator it, std::vector<int>::iterator end)
{
    while (it != end)
    {
        std::cout << *it << std::endl;
        ++it;
    }
}

void container(std::vector<int> &v, const std::vector<int>::iterator &it)
{
    std::cout << "-----------------------System-----------------------" << std::endl;
    std::cout << "size: " << v.size() << std::endl;
    std::cout << "maxSize: " << v.max_size() << std::endl;
    std::cout << "capacity: " << v.capacity() << std::endl;
    std::cout << "                       printIt                       " << std::endl;
    printIterator(it, v.end());
    if (v.empty())
        std::cout << "is empty" << std::endl;
    else
        std::cout << "is not empty" << std::endl;
    return;
}

void myContainer(Vector<int> &v, Vector<int>::iterator &it)
{
    std::cout << "----------------------- MINE -----------------------" << std::endl;
    std::cout << "size: " << v.size() << std::endl;
    std::cout << "maxSize: " << v.max_size() << std::endl;
    std::cout << "capacity: " << v.capacity() << std::endl;
    std::cout << "                       printIt                       " << std::endl;
    printIterator(it, v.end());
    if (v.empty())
        std::cout << "is empty" << std::endl;
    else
        std::cout << "is not empty" << std::endl;
    return;
}

int main()
{
    /*-----------------------System-----------------------*/
    std::vector<int> v0;
    v0.push_back(42);
    // v0.push_back(24);
    // v0.push_back(244);
    // v0.push_back(422);
    std::vector<int>::iterator it0 = v0.begin();
    // v0.resize(0);
    // v0.reserve(1);
    container(v0, it0);
    v0.reserve(2);
    container(v0, it0);
    // container(v0, it0);
    std::cout << "################################################################################" << std::endl;
    /*----------------------- MINE -----------------------*/
    Vector<int> v1;
    v1.push_back(42);
    // v1.push_back(24);
    // // v1.push_back(244);
    // // v1.push_back(422);
    Vector<int>::iterator it1 = v1.begin();
    Vector<int>::iterator it2;
    // v1.resize(0);
    v1.reserve(1);
    it2 = v1.begin();
    v1.reserve(2);
    myContainer(v1, it2);
    // myContainer(v1, it1);

    return (0);
}