
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

void selection_sort(std::vector<int> &v,int left_index,int right_index)
{

	for(int i=left_index;i<right_index;++i) {

		int min = v[i];
		int min_index = i;

		for(int j=i+1;j<=right_index;++j) {

			if(v[j] < min) {
				min = v[j];
				min_index = j;
			}
		}

		vswap(v,i,min_index);
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

	selection_sort(v,0,v.size()-1);

	vprint("v:",v);


	return 0;
}

