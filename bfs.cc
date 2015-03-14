
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


template<typename T>
fun::Path find_path_bfs(const fun::Graph<T> &g,const std::string &src_name,const std::string &dst_name)
{
	fun::Path p_ret;

	if(false==g.has_node(src_name) || false==g.has_node(dst_name))
		return p_ret;

	fun::Queue<std::string> queue;

	std::vector<std::string> neighbors;

	int src_index = g.get_node_index(src_name);

	// node_paths[dst_index] tells you the node before dst_index on the path from src_index ---> dst_index
	// if node_paths[dst_index] == src_index, then you are done with the path
	std::vector<int> node_paths(g.node_count(),-1);
	node_paths[src_index]=src_index;

	// the wgt of getting to any node from src_index
	std::vector<T> path_wgts(g.node_count(),-1);
	path_wgts[src_index]=0;

	g.get_neighbors(neighbors,src_name);

	queue.put(src_name);

	std::map<std::string,bool> visited;

	while(queue.size()) {

		std::string n = queue.getnext();
		int n_index = g.get_node_index(n);

		if(visited[n]==true)
			continue;

		visited[n]=true;


		g.get_neighbors(neighbors,n);

			// when I add neighbors to the queue, tell node_paths which parent node
			// all these neighbors came from.
		for(int i=0;i<neighbors.size();++i) {

			std::string neighbor = neighbors[i];
			int neighbor_index = g.get_node_index(neighbor);

			T link_wgt;
			g.get_link_weight(link_wgt,n,neighbor);

			int path_wgt = path_wgts[n_index] + link_wgt;

			if(path_wgts[neighbor_index]==-1 || path_wgt < path_wgts[neighbor_index]) {
				path_wgts[neighbor_index] = path_wgt;
				node_paths[neighbor_index] = n_index;
			}

			//if(node_paths[neighbor_index]==-1)
				//node_paths[neighbor_index] = n_index;

			queue.put(neighbor);

		}

	}

	vprint("node_paths: ",node_paths);

	p_ret.add_node(dst_name);

	int index = g.get_node_index(dst_name);
	while(1) {

		p_ret.add_node(g.get_node_by_index(node_paths[index]));
		index = node_paths[index];

		if(node_paths[index]==src_index) {
			p_ret.add_node(src_name);
			return p_ret;
		}

		if(node_paths[index]==-1)
			return p_ret;
	}

	return p_ret;
}

int main(int argc,char **argv)
{

	//std::string fname = "graph.csv";
	std::string fname = "graph_wgt.csv";

	fun::Graph<int> g;
	if(0!=fun::graph_adjlist_read(fname,g))
		fatal("fun::graph_adjlist_read() failed on: " + fname);

	g.print_links();

	fun::Path p = find_path_bfs(g,"0","4");

	std::cout << "0,4,Path: " << p << std::endl;

	return 0;
}

