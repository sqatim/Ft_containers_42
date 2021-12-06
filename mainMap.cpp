#include <iostream>
#include <map>
#include "RedBlackTree/RedBlackTree.class.hpp"

int main()
{
    RedBlackTree<int, std::string> tree;
    tree.insert(1, "samir");
    tree.print(tree.getRoot());
    // std::cout << tree.
    return (0);
}