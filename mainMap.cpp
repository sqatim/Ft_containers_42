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
    map.insert(std::make_pair(0, "samir"));
    map.insert(std::make_pair(1, "oussama"));
    map.insert(std::make_pair(2, "achraf"));
    map.insert(std::make_pair(3, "amine"));
    int ss = map.insert(std::make_pair(4, "said"));
    std::cout << "ss ==> " << ss << std::endl;
    // std::cout << "samir" << std::endl;
    // std::map<int, std::string>::iterator it = map.begin();
    // std::cout << std::boolalpha << ss.second << std::endl;
    // std::cout << (*ss.first).second << std::endl;
    // std::cout << it->second << std::endl;

    return (0);
}