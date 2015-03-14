
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

int strcmp_span(const std::string &s1,int s1_start,int s1_end,const std::string &s2,int s2_start, int s2_end)
{
	int index1 = s1_start;
	int index2 = s2_start;

	if(s1_end-s1_start != s2_end-s2_start)
		return 3; // error code

	while(index1<s1_end) {
		if(s1[index1] != s2[index2]) {
			return 1; // not equal
		}
		++index1;
		++index2;
	}

	return 0; // equal
}

bool string_rot_test1(const std::string &s1,const std::string &s2)
{
	if(s1.size()!=s2.size()) return false;

	int size = s1.size();

	int index1 = 0;
	int index2 = 0;

	while(index2<size) {

		if(s1[index1]==s2[index2]) {
			int offset = index2;
			int s1_start = 0;
			int s1_end = size-offset-1;
			int s2_start = offset;
			int s2_end = size-1;
std::cout << "substr1:" << s1.substr(s1_start,s1_end) << std::endl;
std::cout << "substr2:" << s2.substr(s2_start,s2_end) << std::endl;

			if(0==strcmp_span(s1,s1_start,s1_end,s2,s2_start,s2_end)) {

				s1_start = size-offset;
				s1_end = size-1;
				s2_start = 0;
				s2_end = offset-1;
std::cout << "substr1:" << s1.substr(s1_start,s1_end) << std::endl;
std::cout << "substr2:" << s2.substr(s2_start,s2_end) << std::endl;
				if(0==strcmp_span(s1,s1_start,s1_end,s2,s2_start,s2_end)) {
					return true;
				}
			}
		}
		++index2;

	}
	return false;

}

int main(int argc,char **argv)
{

	std::string s1 = "buttery goodness";
	std::string s2 = "essbuttery goodn";

	std::cout << "s1 = " << s1 << std::endl;
	std::cout << "s2 = " << s2 << std::endl;

	std::cout << "string_rot_test1(): " << string_rot_test1(s1,s2) << std::endl;

	return 0;
}

