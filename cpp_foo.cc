
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

using namespace std;

int main(int argc,char **argv)
{

	vector<int> v,u;

	v.insert(v.end(),3);
	v.insert(v.end(),4);
	v.insert(v.end(),1);
	v.insert(v.begin(),10);

	u.insert(u.end(),3);
	u.insert(u.end(),4);
	u.insert(u.end(),88);
	u.insert(u.begin(),20);


	vprint("v:",v);

	std::stable_sort(v.begin(),v.end());

	vprint("v:",v);

	vector<int>::iterator p = std::max_element(v.begin(),v.end());

	std::cout << "pp: " << *p << std::endl;

	vector<int> r(20);
	std::set_union(v.begin(),v.end(),u.begin(),u.end(),r.begin()); // union of v and u into r, r must be big enough

	vprint("r:",r);

	std::fill(r.begin(),r.end(),0); // fill it with zero

	vprint("r:",r);


	return 0;
}

