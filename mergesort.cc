
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

void merge1(std::vector<int> &ret,const std::vector<int> &a,const std::vector<int> &b)
{
	int i,j;
	i=0;
	j=0;

	while(1) {

		if(ret.size()==(a.size() + b.size()))
			return;

		if(i >= a.size()) {

			if(j < b.size()) {
				ret.push_back(b[j++]);
				continue;
			}
		} else if(j >= b.size()) {

			if(i < a.size()) {
				ret.push_back(a[i++]);
				continue;
			}

		} else {

			ret.push_back(a[i] < b[j] ? a[i++] : b[j++]);

		}

	}
}

void merge2()
{

}


void mergesort(std::vector<int> &v)
{

	std::vector<int> a,b,c;

	if(v.size()==1)
		return;


	int m = v.size() / 2;


	for(int i=0;i<m;++i)
		a.push_back(v[i]);

	for(int i=m;i<v.size();++i)
		b.push_back(v[i]);

	mergesort(a);
	mergesort(b);

	merge1(c,a,b);

	v.assign(c.begin(),c.end());
}

void mergesort_file(std::vector<int> &v,unsigned int fsize,const std::string &fname)
{
}


int main(int argc,char **argv)
{
	std::vector<int> v;

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

	mergesort(v);

	vprint("v:",v);

	std::string fname = "crud";

	unsigned long int fsize = get_file_size(fname.c_str());

	std::cout << "fsize: " << fsize << std::endl;

	// use fsize as a approximation for how to split the work up


	std::fstream fin;

	fin.open(fname.c_str(),std::ios::in);

	if(!fin.is_open())
		fatal("could not open fname: " + fname);


	std::string rawline;
	//while(rawline = fin.get(rawline)) {
	while(std::getline(fin,rawline)) {

		std::cout << "rawline: " << rawline << std::endl;

		mergesort_file(fname,fsize/2);

	}


	return 0;
}

