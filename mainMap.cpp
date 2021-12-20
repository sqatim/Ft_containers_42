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

// int main()
// {
//     // int tab[] = {10, 20, 30, 40};
//     // ft::map<int, int> map(tab, tab + 3);
//     ft::map<int, std::string> map;
//     ft::map<int, std::string> map1;
//     // ft::map<int, std::string>::iterator it;
//     // std::pair<ft::map<int, std::string>::iterator, bool> var;
//     map.insert(std::make_pair(1, "samir"));
//     map.insert(std::make_pair(0, "oussama"));
//     map.insert(std::make_pair(2, "achraf"));
//     map.insert(std::make_pair(3, "amine"));
//     map.insert(std::make_pair(4, "youssef"));
//     map.insert(std::make_pair(-1, "anas"));
//     ft::map<int, std::string>::iterator it;
//     // it--;
//     // std::cout << it->first << std::endl;
//     // std::cout << it->second << std::endl;
//     // it = map.insert(map.begin(), std::make_pair(3, "amine"));

//     // std::cout << it->first << std::endl;
//     // std::cout << it->second << std::endl;
//     map1.insert(map.begin(), map.end());

//     // std::cout << "wa shamir" << std::endl;
//     it = map1.begin();
//     // map1.print();
//     std::cout << RED << "   --------------------WARNING--------------------" << DEFAULT << std::endl;

//     it = map1.find(-1);
//     if (it != map1.end())
//     {
//         std::cout << it->second << std::endl;
//     }
//     else
//         std::cout << "not found" << std::endl;
//     // map1.print();
//     // for (; it != map1.end(); it++)
//     // {
//     //     std::cout << "it[" << it->first << "] ==> " << it->second << std::endl;
//     // }

//     return (0);
// }

// int main()
// {
//     std::pair<int, std::string> pair1(3,"samir");
//     std::pair<int, std::string> pair2(1,"oussama");
//     ft::map<int, std::string> map;
//     std::cout << std::boolalpha << map.value_comp()(pair1, pair2) << std::endl;
//     return (0);
// }

// int main()
// {
//   ft::map<int, std::string> mymap;
//   ft::map<int, std::string> mymap1;
//   std::pair<int, std::string> pair;
//   std::pair<int, std::string> pair1;

//   mymap.insert(ft::make_pair(1, "samir"));
//   mymap.insert(ft::make_pair(0, "oussama"));
//   mymap.insert(ft::make_pair(2, "ayoub"));

//   mymap1.insert(ft::make_pair(5, "amine"));
//   mymap1.insert(ft::make_pair(6, "achraf"));
//   mymap1.insert(ft::make_pair(7, "yassir"));
//   mymap1.insert(ft::make_pair(8, "anouar"));
//   // mymap1 = mymap;
//   mymap1.swap(mymap);
//   mymap1.print();
//   std::cout << RED << "------------------- NEW -------------------" << DEFAULT << std::endl;
//   mymap.print();
//   // mymap1.clear();
//   return 0;
// }

int main()
{
	ft::map<int, int> map;
	map.insert(ft::make_pair(20, 20));
	map.insert(ft::make_pair(30, 30));
	map.insert(ft::make_pair(4, 4));
	map.insert(ft::make_pair(0, 0));
	map.insert(ft::make_pair(10, 10));
	map.insert(ft::make_pair(-5, -5));
	map.insert(ft::make_pair(7, 7));
	map.insert(ft::make_pair(12, 12));
	map.insert(ft::make_pair(14, 14));

	// ft::map<int, std::string>::iterator it = map.begin();
	// std::cout << "first: " << RED << it->first << DEFAULT << "\t second: " << RED << it->second << DEFAULT << std::endl;
	// std::cout << YELLOW << "   ------------------- Before -------------------" << DEFAULT << std::endl;
	map.erase(4);
	map.erase(7);
	map.erase(30);
	map.print();
	// for (it = map.begin(); it != map.end(); it++)
	// {
	// 	std::cout << "first: " << RED << it->first << DEFAULT << "\t second: " << RED << it->second << DEFAULT << std::endl;
	// }
	// it = map.begin();
	// it++;
	// it++;
 	// map.erase(it->first);
	// std::cout << YELLOW << "   ------------------- after -------------------" << DEFAULT << std::endl;
	// for (it = map.begin(); it != map.end(); it++)
	// {
	// 	std::cout << "first: " << RED << it->first << DEFAULT << "\t second: " << RED << it->second << DEFAULT << std::endl;
	// }
}