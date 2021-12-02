#include <iostream>
#include "ReverseIterator.class.hpp"
#include <vector>
#include <typeinfo>
#include <math.h>

#include "Vector.class.hpp"

void printIterator(ft::vector<int>::iterator it, ft::vector<int>::iterator end)
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

void myContainer(ft::vector<int> &v, ft::vector<int>::iterator &it)
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
        int array[] = {100, 200, 300, 400};
        /*-----------------------System-----------------------*/
        std::vector<int> v0;
        v0.reserve(2);
        v0.push_back(1);
        v0.push_back(2);
        v0.push_back(3);
        std::vector<int>::iterator it0 = v0.begin();
        v0.insert(it0, 2, 300);
        it0 = v0.begin();
        container(v0, it0);

        std::cout << "################################################################################" << std::endl;

        /*----------------------- MINE -----------------------*/

        ft::vector<int> v1;
        ft::vector<int> v2;
        v2.push_back(1000);
        v2.push_back(2000);
        v2.push_back(3000);
        ft::vector<int>::iterator it2 = v2.begin();
        v1.reserve(10);
        // v1.push_back(1);
        // v1.push_back(2);
        // v1.push_back(3);
        ft::vector<int>::iterator it1 = v1.begin();
        // v1.insert(it1, array, array + 2);
        // v1.insert(it1, it2,it2 + 2);
        v1.insert(it1, 2, 100);
        it1 = v1.begin();
        myContainer(v1, it1);
        // v1.printo(it1);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    catch (const std::string &e)
    {
        std::cerr << e << '\n';
    }

    return (0);
}

// bug to fix
//   v1.assign(3, 100); nnormalement hadi khasha dkhul fal function lakhra
//   v1.assign(3, 100); nnormalement hadi khasha dkhul fal function lakhra
