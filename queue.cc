
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <cmath>
#include <new>

#include "utils.h"

int main(int argc,char **argv)
{

	Queue<int> q;

	q.push_back(0);
	q.push_back(5);
	q.push_back(10);
	q.push_back(15);
	q.push_back(20);
	q.push_back(25);
	q.push_back(30);
	q.push_back(35);
	q.push_back(40);
	q.push_back(45);
	q.push_back(50);
	q.push_back(55);
	q.push_back(60);

	std::cout << "size: " << q.size() << std::endl;
	std::cout << "peek: " << q.peek() << std::endl;

	while(q.size()) {
		int f = q.get_front();
		std::cout << "fff: " << f << std::endl;
	}

	return 0;
}

