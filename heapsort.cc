
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

// literature says this:
// parent of node in position j is in j/2
// children of a node in position j is in 2j and 2j+1
//
// however, literature always uses v[0] as a sentinal set to maxValue
// This means literature always assumes v[1] is first real element of heap.
// If you are using v[0] as first element the above forumlas do not work.
// You must add 1 to the j before you use the formula.
// Then you must -1 after you can an answer to put it back into 0 based coords


void swap(std::vector<int> &v,int a,int b)
{
	int t = v[a];
	v[a] = v[b];
	v[b] = t;
}

void heapify(std::vector<int> &v)
{

	for(int i=0;i<v.size();++i) {

		int max = v[i];
		int max_ind = i;
		for(int j=i;j<v.size();++j) {

			if(max<v[j]) {
				max = v[j];
				max_ind = j;
			}

		}
		swap(v,max_ind,i);
	}
}

void swap_items(std::vector<int> &v,int a,int b)
{
	int tmp = v[a];
	v[a] = v[b];
	v[b] = tmp;
}

int get_parent_index(int k)
{
	// heap literature counts everything from 1 because they usually use v[0] as
	// a sentianal with value maxHeap.  To get around this we add 1 to our input
	// index, which will be zero based, so the +1 makes it like the heap
	// literature.  Then after the formula is done, we -1 to undo our earlier +1.
	return (k+1)/2 - 1;
}

int get_left_child_index(int k)
{
	return 2*(k+1) - 1;
}

// This might not work!
// Instead prepend it to the top of heap and use downheap on it
void insert_heap(std::vector<int> &v, int new_item)
{
	v.push_back(new_item);

	int k = v.size()-1; // last element

	int parent_index = get_parent_index(k);
	if(v[parent_index] <= v[k]) {
		swap_items(v,parent_index,k);
	}
}

void downheap(std::vector<int> &v,int k)
{
	int cind = get_left_child_index(k);

	if(cind >= v.size())
		return;

	if(cind+1 < v.size() && v[cind] < v[cind+1])
		cind = cind+1;

	if(v[k] < v[cind]) {
		swap(v,k,cind);
		downheap(v,cind);
	}
}

int pop_top_heap(std::vector<int> &v)
{
	int ret = v[0]; // save the top of the heap
	v[0] = v[v.size()-1]; // copy bottom of heap to top
	v.resize(v.size()-1); // shrink heap by 1
	downheap(v,0); // move new top of heap down to its new correct spot
	return ret;
}

void delete_heap(std::vector<int> &v,int k)
{
}

int main(int argc,char **argv)
{
	std::vector<int> v;

	v.push_back(0);
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(6);
	v.push_back(7);
	v.push_back(8);
	v.push_back(9);

	vprint("v:",v);

	heapify(v);

	vprint("v:",v);

	// heapsort!
	while(v.size()) {
		std::cout << pop_top_heap(v) << "," << std::endl;
	}

	return 0;
}

