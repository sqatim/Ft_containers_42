#include <iostream>
#include "ReverseIterator.class.hpp"
#include <vector>
#include <typeinfo>
#include <math.h>

#include "Vector.class.hpp"
// class Vector
// {
// puitlic:
//   it int x;
//     Vector(): x(20)
//     {

//     };
// };

template <typename T>
class A
{
    // public:

public:
    T i[5];
    A(/* args */)
    {
        i[0] = "samir";
        // std::cout << "before: " << i[0] << std::endl;
        i[0].~T();
        i[0].~T();
        i[0].~T();
        i[0].~T();
        i[0].~T();
    };
    ~A(){};
};

// int main()
// {
//     // Vector<int> a;
//     // std::cout  << a.max_size() << std::endl;
//     std::vector<int> ss;
//     ss.push_back(1);
//     ss.push_back(2);
//     ss.push_back(3);
//     ss.push_back(4);
//     ss.push_back(5);

//     for (std::vector<int>::iterator it = ss.begin(); it < ss.end(); it++)
//     {
//         std::cout << *it << std::endl;
//     }
//     std::cout << "capacity: " << ss.capacity() << std::endl;
//     ss.reserve(9);
//     for (std::vector<int>::iterator it = ss.begin(); it < ss.end(); it++)
//     {
//         std::cout << *it << std::endl;
//     }
//     std::cout << "capacity: " << ss.capacity() << std::endl;
//     ss.push_back(10);
//     ss.push_back(10);
//     ss.push_back(10);
//     ss.push_back(10);
//     ss.push_back(10);
//     std::cout << "capacity: " << ss.capacity() << std::endl;
//     ss.push_back(10);
//     ss.push_back(10);
//     ss.push_back(10);
//     ss.push_back(10);
//     ss.push_back(10);
//     ss.push_back(10);
//     ss.push_back(10);
//     ss.push_back(10);
//     ss.push_back(10);
//     ss.push_back(10);
//     ss.push_back(10);
//     ss.push_back(10);
//     ss.push_back(10);
//     ss.push_back(10);
//     ss.push_back(10);
//     std::cout << "capacity: " << ss.capacity() << std::endl;
//     // std::vector<int> i;
//     // std::cout << "capacity: "<<i.capacity() << std::endl;
//     // std::cout << "size: "<<i.size() << std::endl;

//     // i.push_back(2);
//     // std::cout << "capacity: "<<i.capacity() << std::endl;
//     // std::cout << "size: "<<i.size() << std::endl;
//     // std::cout << "***********************************" << std::endl;
//     // i.push_back(5);
//     // std::cout << "capacity: "<<i.capacity() << std::endl;
//     // std::cout << "size: "<<i.size() << std::endl;

//     // std::cout << "***********************************" << std::endl;
//     // std::cout << "clear" << std::endl;
//     // i.clear();
//     // std::cout << "***********************************" << std::endl;
//     // // i.push_back(5);
//     // std::cout << "===> " << i.at(0) << " <===" << std::endl;
//     // std::cout << "capacity: "<<i.capacity() << std::endl;
//     // std::cout << "size: "<<i.size() << std::endl;

//     // Vector<int> i;
//     // Vector<int> i(10, 20);

//     // std::cout << i[2] << std::endl;
//     // const int& rci = 20;
//     // std::cout << rci <<std::endl;
//     // const_cast<int&> (rci) = 30;
//     // std::cout << rci <<std::endl;
//     // const Vector& a = Vector();
//     // a.x = 30;
//     // std::cout << a.x << std::endl;
//     // a.x = 20;

//     // Vector<int> i(2, 10);
//     // std::cout << i[0] << std::endl;
//     // int i = int();
//     // std::cout << i << std::endl;
//     // std::vector<int> s(10);
//     // std::cout << s[0] << std::endl;
// }

// int main()
// {
//     std::vector<int> myvector;
//     int sum(0);
//     myvector.push_back(100);
//     myvector.push_back(200);
//     myvector.push_back(300);
//     myvector.push_back(300);
//     std::cout << "size: " << myvector.size() << std::endl;
//     // myvector.pop_back();
//     myvector.resize(10);
//     // std::cout << "The elements of myvector add up to " << sum << '\n';
//     std::vector<int>::iterator it = myvector.begin();
//     // std::cout << myvector[0] << std::endl;
//     for (std::vector<int>::iterator it = myvector.begin(); it < myvector.end(); it++)
//     {
//         // std::cout << "said" << std::endl;
//         std::cout << *it << std::endl;
//     }
//     std::cout << myvector.capacity() << std::endl;

//     return 0;
// }

// int main()
// {
//     std::vector<int> b;
//     Vector<int> v;
//     v.push_back(10);
//     v.push_back(20);
//     v.push_back(30);
//     v.push_back(40);
//     b.push_back(10);
//     b.push_back(20);
//     b.push_back(30);
//     b.push_back(40);

//     std::vector<int>::iterator it = b.begin();
//     Vector<int>::iterator it1 = v.begin();
//     std::cout << "normal_reverse_iterator: " << *it << std::endl;
//     std::cout << "costum_reverse_iterator: " << *it1 << std::endl;
//     std::cout << "****************************************************" << std::endl;
//     it++;
//     it1++;
//     std::cout << "normal_reverse_iterator: " << *it << std::endl;
//     std::cout << "costum_reverse_iterator: " << *it1 << std::endl;
//     std::cout << "****************************************************" << std::endl;
//     it++;
//     it1++;
//     std::cout << "normal_reverse_iterator: " << *it << std::endl;
//     std::cout << "costum_reverse_iterator: " << *it1 << std::endl;
//     std::cout << "****************************************************" << std::endl;
//     it++;
//     it1++;
//     std::cout << "normal_reverse_iterator: " << *it << std::endl;
//     std::cout << "costum_reverse_iterator: " << *it1 << std::endl;
//     return (0);
// }

int main()
{
    Vector<int> v1;
    v1.push_back(10);
    v1.push_back(20);
    Vector<int> v2;
    v2.push_back(100);
    v2.push_back(90);

    std::cout << "************ v1 ************" << std::endl;
    std::cout << v1[0] << std::endl;
    std::cout << v1[1] << std::endl;
    std::cout << "************ v2 ************" << std::endl;
    std::cout << v2[0] << std::endl;
    std::cout << v2[1] << std::endl;
    std::cout << "************ swap ************" << std::endl;
    v1.swap(v2);
    std::cout << "************ v1 ************" << std::endl;
    std::cout << v1[0] << std::endl;
    std::cout << v1[1] << std::endl;
    std::cout << "************ v2 ************" << std::endl;
    std::cout << v2[0] << std::endl;
    std::cout << v2[1] << std::endl;

    std::cout << "************ size v1 ************" << std::endl;
    // std::cout << v1.() << std::endl;
    return (0);
}