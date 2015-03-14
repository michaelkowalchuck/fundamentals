
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

void insertion_sort(std::vector<int> &v,int left_index,int right_index)
{
	for(int i=left_index+1;i<=right_index;++i) {
		for(int j=i;j>left_index;--j) {
			if(v[j]<v[j-1])
				vswap(v,j-1,j);
		}
	}
}

int main(int argc,char **argv)
{

	std::vector<int> v;

	v.push_back(-10);
	v.push_back(10);
	v.push_back(9);
	v.push_back(8);
	v.push_back(7);
	v.push_back(6);
	v.push_back(5);
	v.push_back(5);
	v.push_back(5);
	v.push_back(4);
	v.push_back(3);
	v.push_back(2);
	v.push_back(5);
	v.push_back(5);
	v.push_back(5);
	v.push_back(1);
	v.push_back(0);

	std::cout << "i: ";
	for(int i=0;i<v.size();++i) {
		std::cout << i << " ";
	}
	std::cout << std::endl;

	vprint("v:",v);

	insertion_sort(v,0,v.size()-1);

	vprint("v:",v);


	return 0;
}

