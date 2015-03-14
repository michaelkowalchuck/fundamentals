
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <cmath>

#include "utils.h"

int main(int argc,char **argv)
{

	std::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(6);
	v.push_back(7);

	vprint("v:",v);

	std::vector<int>::iterator itr,itr2;
	itr = v.begin();
	itr2 = v.begin();

	++itr2;
	++itr2;
	++itr2;
	std::cout << "*itr2222: " << *itr2 << std::endl;

	std::cout << "*itr: " << *itr << std::endl;
	++itr;
	std::cout << "*itr: " << *itr << std::endl;
	++itr;
	std::cout << "*itr: " << *itr << std::endl;

	v.erase(itr); // automatically pushes itr to the next element!

	std::cout << "*itr: " << *itr << std::endl;
	++itr;
	std::cout << "*itr: " << *itr << std::endl;

	std::cout << "*itr2222: " << *itr2 << std::endl;

	vprint("v:",v);

	return 0;
}

