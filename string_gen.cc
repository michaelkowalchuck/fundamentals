
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


unsigned char random_char()
{
	return 'a'+ rand()%26;
}


int main(int argc,char **argv)
{
	if(argc!=2) {
		std::cout << "string_gen line_count" << std::endl;
		exit(1);
	}

	int line_count = atoi(argv[1]);

	unsigned char s[80];
	int v=0;
	while(v<line_count) {
		for(int i=0;i<6;++i) {
			s[i] = random_char();
		}
		s[6]=0;
		++v;
		std::cout << s << std::endl;
	}

	return 0;
}

