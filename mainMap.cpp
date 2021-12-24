#include <iostream>
#include <map>
#include <set>
#include "./Containers/Set.class.hpp"
#include "./Containers/Map.class.hpp"
#include "./Iterators/iterator.hpp"

int main()
{
	int ptr[3] = {10,20,30};
	
	ft::iterator_traits<int *>::pointer salam;
	ft::iterator_traits<int *>::value_type said;
	said = 50;
	std::cout << said <<std::endl;
}