
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

	Stack<int> st;

	st.push(0);
	st.push(5);
	st.push(10);
	st.push(15);
	st.push(20);
	st.push(25);
	st.push(30);
	st.push(35);
	st.push(40);
	st.push(45);
	st.push(50);
	st.push(55);
	st.push(60);

	std::cout << "size: " << st.size() << std::endl;
	std::cout << "peek: " << st.peek() << std::endl;

	while(st.size()) {
		int f = st.pop();
		std::cout << "fff: " << f << std::endl;
	}


	return 0;
}

