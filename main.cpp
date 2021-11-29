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
    // std::cout << "operator[0] ==> " << v[0] << std::endl;
    // std::cout << "at ==> " << v.at(0) << std::endl;
    // // std::cout << "vector.front() ==> " << v.front() << std::endl;
    // std::cout << "vector.back() ==> " << v.back() << std::endl;
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
    // std::cout << "operator[0] ==> " << v[0] << std::endl;
    // std::cout << "at ==> " << v.at(0) << std::endl;
    // // std::cout << "vector.front() ==> " << v.front() << std::endl;
    // std::cout << "vector.back() ==> " << v.back() << std::endl;
    return;
}

int main()
{
    try
    {
        /*-----------------------System-----------------------*/
        std::vector<int> v0;
        v0.reserve(6);
        v0.push_back(1);
        v0.push_back(2);
        v0.push_back(3);
        std::vector<int>::iterator it0 = v0.begin();
        v0.insert(it0, 100);
        v0.insert(it0+2, 100);
        v0.insert(it0+5, 100);
        std::vector<int>::iterator result0 = v0.insert(it0+5, 200);
        std::cout << "result: " << *result0 << std::endl;
        // v0.insert(it0+10, 100);
        it0 = v0.begin();
        container(v0, it0);

        std::cout << "################################################################################" << std::endl;

        /*----------------------- MINE -----------------------*/
        Vector<int> v1;
        v1.reserve(6);
        v1.push_back(1);
        v1.push_back(2);
        v1.push_back(3);
        Vector<int>::iterator it1 = v1.begin();
        v1.insert(it1, 100);
        v1.insert(it1+2, 100);
        v1.insert(it1+5, 100);
        Vector<int>::iterator result1 = v1.insert(it1+5, 200);
        std::cout << "result: " << *result1 << std::endl;
        it1 = v1.begin();
        myContainer(v1, it1);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return (0);
}

// bug to fix
//   v1.assign(3, 100); nnormalement hadi khasha dkhul fal function lakhra
//   v1.assign(3, 100); nnormalement hadi khasha dkhul fal function lakhra
