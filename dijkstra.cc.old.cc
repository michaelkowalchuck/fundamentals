
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
		Link(const std::string &src,const std::string &dst, int wgt)
		{
			_src = src;
			_dst = dst;
			_wgt = wgt;
		}

		int get_wgt()const
		{
			return _wgt;
		}
		void set_wgt(int wgt)
		{
			_wgt = wgt;
		}

		const std::string& get_src()const
		{
			return _src;
		}
		void set_src(const std::string &src)
		{
			_src = src;
		}

		const std::string& get_dst()const
		{
			return _dst;
		}
		void set_dst(const std::string &dst)
		{
			_dst = dst;
		}

		bool operator==(const Link &rhs)const
		{
			return _src==rhs._src && _dst==rhs._dst && _wgt==rhs._wgt;
		}

	private:
		std::string _src,_dst;
		int _wgt;
};

class Path
{
	public:
		Path(const Link &link)
		{
			_items.push_back(link.get_src());
			_items.push_back(link.get_dst());
			_wgt = link.get_wgt();
		}
		int get_wgt()const
		{
			return _wgt;
		}
		void set_wgt(int wgt)
		{
			_wgt = wgt;
		}
		const std::string& get_last_node()const
		{
			return _items[_items.size()-1];
		}
		void add(const std::string &name,int wgt)
		{
			_items.push_back(name);
			_wgt += wgt;
		}

		std::size_t size()const
		{
			return _items.size();
		}

		const std::string& get_node(int index)const
		{
			return _items[index];
		}

	private:
		std::vector<std::string> _items;
		int _wgt;
};

class AdjList
{
	public:

		const Link& get_link(int index)const
		{
			return _links[index];
		}
		Link& get_link(int index)
		{
			return _links[index];
		}

		void add_link(const Link &link)
		{
			if(_links.end() == std::find(_links.begin(),_links.end(),link)) {
				_links.push_back(link);
				_link_taken.push_back(false);
			}
		}

		void add_link(const std::string &src,const std::string &dst, int wgt)
		{
			Link link(src,dst,wgt);
			add_link(link);
		}

		AdjList egonet(const std::string &name)
		{
			AdjList ret;

			for(int i=0;i<_links.size();++i) {
				if(_link_taken[i]==true)
					continue;
				if(_links[i].get_src()==name || _links[i].get_dst()==name)
					std::cout << "\tegonode: " << i << "  " << _links[i].get_src() << "," << _links[i].get_dst() << "," << _links[i].get_wgt() << std::endl;
					ret.add_link(_links[i]);
					_link_taken[i]=true;
			}

			return ret;
		}

		std::size_t size()const
		{
			return _links.size();
		}

		AdjList& operator+=(const AdjList &rhs)
		{
			for(int i = 0; i<rhs.size();++i) {
				add_link(rhs.get_link(i));
			}
			return *this;
		}
		Link& operator[](int index)
		{
			return _links[index];
		}
		const Link& operator[](int index)const
		{
			return _links[index];
		}


		void erase(const std::vector<Link>::iterator &itr)
		{
			_links.erase(itr);
		}
		std::vector<Link>::iterator begin()
		{
			return _links.begin();
		}

	private:
		std::vector<Link> _links;
		std::vector<bool> _link_taken;

};


class SpanningTree
{
	public:
		bool is_reachable(const std::string &name)const
		{
			for(int i=0;i<size();++i) {
				if(_paths[i].get_last_node()==name)
					return true;
			}
			return false;
		}

		const Path& get_path_ending_with(const std::string &name)const
		{
			for(int i=0;i<size();++i) {
				if(_paths[i].get_last_node()==name)
					return _paths[i];
			}
			fatal("get_path_ending_with()...dies");
		}

		std::size_t size()const
		{
			return _paths.size();
		}

		void add_path(const Path &p)
		{
			_paths.push_back(p);
		}

		const Path& get_path(int index)const
		{
			return _paths[index];
		}

	private:
		std::vector<Path> _paths;
};

SpanningTree dijkstra(AdjList &adjlist,const std::vector<std::string> &nodes)
{
	std::vector<std::string> visited,unvisited;

	unvisited.assign(nodes.begin(),nodes.end());

	SpanningTree stree;
	stree.add_path(Path(adjlist[0]));

	AdjList linklist;

// cnode = start_node

while(1) {

	// remove cnode from nodelist

	// get cnode's egonet from adjlist

	// add all new nodes to visited

}


		// get new node
	std::string cnode = nodes[0];

	std::vector<Path> pathlist;
	while(1) {
		std::cout << "new cnode: " << cnode << std::endl;

		// get all links for new node
		AdjList egolist = adjlist.egonet(cnode);


		bool found_new_node=false;
		for(int i=0;i<egolist.size();++i) {
std::cout << "egolist: " << i << "  " << egolist[i].get_src() << "," << egolist[i].get_dst() << "," << egolist[i].get_wgt() << std::endl;
			if(stree.is_reachable(egolist[i].get_src())) {
				Path p = stree.get_path_ending_with(egolist[i].get_src());
				p.add(egolist[i].get_dst(),egolist[i].get_wgt());
				found_new_node=true;
				break;
			} else if(stree.is_reachable(egolist[i].get_dst())) {
				Path p = stree.get_path_ending_with(egolist[i].get_dst());
				p.add(egolist[i].get_src(),egolist[i].get_wgt());
				found_new_node=true;
				break;
			}
		}
		if(!found_new_node)
			break;

		// find new weights for new links
			// for each unknown node in egolist,
				// find path ending with it in stree
				// add path's weight to unknown node's links in egolist
		// add all of new node's weight adjusted links to linklist
		linklist += egolist;

		// find smallest weight link in linklist
		int min=linklist[0].get_wgt();
		int min_ind=0;
		for(int i=1;i<linklist.size();++i) {

			if(linklist[i].get_wgt() < min) {
				min = linklist[i].get_wgt();
				min_ind = i;
			}
		}
		stree.add_path(linklist[min_ind]);
		linklist.erase(linklist.begin()+min_ind);
		cnode = stree.get_path(stree.size()-1).get_last_node();
	}

	return stree;
}

// TIC TAC TOE and what other games?
// tower of hanoi
// snake game?

int main(int argc,char **argv)
{
	AdjList a;

	a.add_link("A","B",1);
	a.add_link("E","A",15);
	a.add_link("D","B",4);
	a.add_link("B","C",3);
	a.add_link("C","D",1);
	a.add_link("E","D",1);

	std::vector<std::string> nodes;

	nodes.push_back("A");
	nodes.push_back("B");
	nodes.push_back("C");
	nodes.push_back("D");
	nodes.push_back("E");

	SpanningTree st;
	st = dijkstra(a,nodes);

	std::cout << "spanning tree..." << std::endl;
	for(int i=0;i<st.size();++i) {
		const Path &p = st.get_path(i);
		for(int j=0;j<p.size();++j) {
			std::cout << p.get_node(j) << ",";
		}
		std::cout << p.get_wgt() << std::endl;
	}

	return 0;
}

