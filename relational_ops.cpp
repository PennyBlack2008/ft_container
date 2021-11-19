#include <iostream>
#include <list>
#include <vector>
#include "vector/vector.hpp"

template <class T, class Alloc>
void	cmp(const std::vector<T, Alloc> &lhs, const std::vector<T, Alloc> &rhs)
{
	static int i = 0;

	std::cout << "############### [" << i++ << "] ###############"  << std::endl;
	std::cout << "eq: " << (lhs == rhs) << " | ne: " << (lhs != rhs) << std::endl;
	std::cout << "lt: " << (lhs <  rhs) << " | le: " << (lhs <= rhs) << std::endl;
	std::cout << "gt: " << (lhs >  rhs) << " | ge: " << (lhs >= rhs) << std::endl;
}

int		main(void)
{
	std::vector<int> vct(4);
	std::vector<int> vct2(4);

	cmp(vct, vct);  // Passed 0
	/**
	 * eq: 1 | ne: 0
	 * lt: 0 | le: 1
	 * gt: 0 | ge: 1
	 **/

	cmp(vct, vct2); // Passed 1 
	/**
	 * eq: 1 | ne: 0
	 * lt: 0 | le: 1
	 * gt: 0 | ge: 1
	 **/

	vct2.resize(10);

	cmp(vct, vct2); // 2

	/*
		eq: 0 | ne: 1
		lt: 1 | le: 1
		gt: 0 | ge: 0
	*/
	
	cmp(vct2, vct); // 3
	/*
		eq: 0 | ne: 1
		lt: 0 | le: 0
		gt: 1 | ge: 1
	*/

	vct[2] = 42;

	cmp(vct, vct2); // 4
	/*
		eq: 0 | ne: 1
		lt: 0 | le: 0
		gt: 1 | ge: 1
	*/
	
	cmp(vct2, vct); // 5
	/*
		eq: 0 | ne: 1
		lt: 1 | le: 1
		gt: 0 | ge: 0
	*/
	std::swap(vct, vct2); 

	cmp(vct, vct2); // 6
	/*
		eq: 0 | ne: 1
		lt: 1 | le: 1
		gt: 0 | ge: 0
	*/

	cmp(vct2, vct); // 7
	/*
		eq: 0 | ne: 1
		lt: 0 | le: 0
		gt: 1 | ge: 1
	*/
	return (0);
}
