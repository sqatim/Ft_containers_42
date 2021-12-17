#include <iostream>
#include <map>
// #include "RedBlackTree/RedBlackTree.class.hpp"
#include "Map.class.hpp"

// int main()
// {
//     RedBlackTree<int, std::string> tree;
//     tree.insert(50, "50");
//     tree.insert(25, "25");
//     tree.insert(75, "75");
//     tree.insert(26, "26");
//     tree.insert(30, "30");
//     tree.insert(28, "28");
//     tree.insert(29, "29");
//     tree.insert(40, "40");
//     tree.insert(45, "45");
//     tree.insert(42, "42");
//     tree.insert(41, "41");
//     tree.insert(47, "47");
//     tree.insert(48, "48");
//     // tree.insert(6, "6");
//     // tree.insert(2, "oussama");
//     // tree.print(tree.getRoot());
//     std::cout << RED << "-------------------====-------------------" << DEFAULT << std::endl;
//     tree.deleteNode(41);
//     tree.deleteNode(47);
//     tree.deleteNode(50);
//     tree.deleteNode(29);
//     tree.insert(27, "27");
//     tree.deleteNode(25);
//     tree.print(tree.getRoot());
//     std::cout << RED << "-------------------====-------------------" << DEFAULT << std::endl;
//     // tree.deleteNode(1);
//     // tree.print(tree.getRoot());
//     // std::cout << "***************************************" << std::endl;
//     // tree.print(tree.getRoot());
//     // std::cout << std::boolalpha << true << std::endl;
//     // tree.print(tree.getRoot());
//     // std::cout << tree.
//     return (0);
// }

int main()
{
    // int tab[] = {10, 20, 30, 40};
    // ft::map<int, int> map(tab, tab + 3);
    ft::map<int, std::string> map;
    ft::map<int, std::string> map1;
    // ft::map<int, std::string>::iterator it;
    // std::pair<ft::map<int, std::string>::iterator, bool> var;
    map.insert(std::make_pair(1, "samir"));
    map.insert(std::make_pair(0, "oussama"));
    map.insert(std::make_pair(2, "achraf"));
    map.insert(std::make_pair(3, "amine"));
    map.insert(std::make_pair(4, "youssef"));
    map.insert(std::make_pair(-1, "anas"));
    ft::map<int, std::string>::iterator it;
    // it--;
    // std::cout << it->first << std::endl;
    // std::cout << it->second << std::endl;
    // it = map.insert(map.begin(), std::make_pair(3, "amine"));

    // std::cout << it->first << std::endl;
    // std::cout << it->second << std::endl;
    map1.insert(map.begin(), map.end());

    // std::cout << "wa shamir" << std::endl;
    it = map1.begin();
    map1.print();
    // map1.print();
    // for (; it != map1.end(); it++)
    // {
    //     std::cout << "it[" << it->first << "] ==> " << it->second << std::endl;
    // }

    return (0);
}