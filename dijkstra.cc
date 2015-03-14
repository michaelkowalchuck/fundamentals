
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

class Link
{
	public:
		Link(const std::string &isrc,const std::string &idst,int iwgt)
		{
			src = isrc;
			dst = idst;
			wgt = iwgt;
		}
		std::string src;
		std::string dst;
		int wgt;
};

class Path
{
	public:
		Path(int iwgt,const std::vector<std::string> inodes)
		{
			wgt = iwgt;
			nodes.assign(inodes.begin(),inodes.end());
		}

		std::vector<std::string> nodes;
		int wgt;

		const std::string& get_last()const
		{
			return nodes[nodes.size()-1];
		}
};

std::string get_link_partner(const Link link,const std::string &nodename)
{
	if(link.src==nodename)
		return link.dst;
	if(link.dst==nodename)
		return link.src;
	return "";
}

const Path& get_path(const std::string &nodename,const std::vector<Path> &paths)
{
	for(int i=0; i<paths.size(); ++i) {
		if(paths[i].get_last()==nodename)
			return paths[i];
	}
	fatal("get_path() failed on nodename: " + toString(nodename));
}
int get_path_wgt(const std::string &nodename,const std::vector<Path> &paths)
{
	for(int i=0; i<paths.size(); ++i) {
		if(paths[i].get_last()==nodename)
			return paths[i].wgt;
	}
	fatal("get_path_wgt() failed on nodename: " + toString(nodename));
}
bool path_exists(const std::string &nodename,const std::vector<Path> &paths)
{
	for(int i=0; i<paths.size(); ++i) {
		if(paths[i].get_last()==nodename)
			return true;
	}
	return false;
}
void remove_link(int index,std::vector<Link> &linklist)
{
	linklist.erase(linklist.begin()+index);
}
void remove_node(const std::string &nodename,std::vector<std::string> &nodes)
{
	std::vector<std::string>::iterator itr;
	itr = std::find(nodes.begin(),nodes.end(),nodename);
	nodes.erase(itr);
}
void dijkstra(const std::vector<Link> &adjlist,std::vector<std::string> &nodes)
{
	std::string cnode = nodes[0];
	std::string saved_dst = "";

	std::vector<Path> paths;
	paths.push_back(Path(0,std::vector<std::string>(1,cnode)));

	std::vector<Link> linklist;
	linklist.assign(adjlist.begin(),adjlist.end());

	while(1)
	{
		int min_ind = -1;
		int min_wgt = 10000; // max weight?

		int path_wgt;

		std::string dst="";
		for(int i=0;i<linklist.size();++i) {

			Link link = linklist[i];

			if((dst = get_link_partner(link,cnode))!="") {

				if(path_exists(dst,paths)) {
					// remove this link since we are done with it.
					remove_link(i,linklist);
					continue;
				}

					// find cost to get to dst through cnode
				path_wgt = link.wgt + get_path_wgt(cnode,paths);

					// if this is the shortest path we've found so far from cnode,
					// save it
				if(path_wgt < min_wgt) {
					min_ind = i;
					min_wgt = path_wgt;
					// NOTE: the dst here should be saved because it will be set to "" if another link exists with cnode but no dst
					//
					saved_dst = dst;
				}
			}

		}

			// its almost as if this if should be inside the for() loop
		if(min_ind!=-1) { // if we found a new shortest path through cnode

			// WRONG cnode will be nodes[0] which is not right it appears!

			// add a new path to dst through cnode
			const Path &path = get_path(cnode,paths);
			std::vector<std::string> new_path;
			new_path.assign(path.nodes.begin(),path.nodes.end());
			new_path.push_back(dst); // append new dst
			paths.push_back(Path(path_wgt,new_path));

			//cnode = dst;
			cnode = saved_dst;

			// remove this link since we are done with it.
			remove_link(min_ind,linklist);

		} else {
		}

		if(dst=="") {
			// we have taken every link associated with cnode.
			remove_node(cnode,nodes);
			if(nodes.size()==0)
				break; // done

			cnode = nodes[0];
		}
	}
}

int main(int argc,char **argv)
{
	std::vector<Link> a;

	a.push_back(Link("A","B",1));
	a.push_back(Link("E","A",15));
	a.push_back(Link("D","B",4));
	a.push_back(Link("B","C",3));
	a.push_back(Link("C","D",1));
	a.push_back(Link("E","D",1));

	std::vector<std::string> nodes;

	nodes.push_back("A");
	nodes.push_back("B");
	nodes.push_back("C");
	nodes.push_back("D");
	nodes.push_back("E");

	dijkstra(a,nodes);

/*
	std::cout << "spanning tree..." << std::endl;
	for(int i=0;i<st.size();++i) {
		const Path &p = st.get_path(i);
		for(int j=0;j<p.size();++j) {
			std::cout << p.get_node(j) << ",";
		}
		std::cout << p.get_wgt() << std::endl;
	}
*/

	return 0;
}

