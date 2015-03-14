
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

		// right_index is used as pivot
int partition(std::vector<int> &v,int left_index,int right_index)
{

		// index1 and index2 must be initialized outide of the infinite loop.
		// Their state is preserved across each loop so that eventually they satisfy index1>=index2
		// no matter what.
	int index1 = left_index - 1; // -1 to offset the first increment of the while
	int index2 = right_index-1 + 1; // +1 to offset starting decrement of while

	while(1) {

		++index1; // we do this to bump index1 up from last while loop no matter what, otherwise we can loop forever with duplicate keys
		--index2; // same as above but down.

			// move left to right
			// note you do not move past the right_index.
			// right_index is like the upper bound of the "lesser" list.
		for(;index1<right_index;++index1) {

				// we use v[right_index] as our pivot's value.
				// we take each item that should be to the right of the pivot
			if(v[index1] >= v[right_index]) {
				break;
			}
		}

			// move from right to left
			// left_index is the lower bound of the "greater" list.
		for(;index2>=left_index;--index2) {
			if(v[index2] <= v[right_index]) {
				break;
			}
		}

			// once we get to this state we are done with the partition.  All items should be sorted around
			// the pivot so that the "lesser" list is less than the pivot and "greater" list is greater than the pivot.
		if(index1 >= index2)
			break;

			// if we are not done, then we must have found items to swap around the pivot.
		vswap(v,index1,index2);

	}

		// finally, put the pivot in its place
	vswap(v,index1,right_index);

	return index1;
}

void quicksort(std::vector<int> &v, int L, int r)
{

	if(v.size()==0) {
		return;
	}

	if(r <= L) // zero size partitions do not need sorted
		return;

	int new_pivot = partition(v,L,r);

		// lesser list
	quicksort(v,L,new_pivot-1);
		// greater list
	quicksort(v,new_pivot+1,r);

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

	quicksort(v,0,v.size()-1);

	vprint("v:",v);


	return 0;
}

