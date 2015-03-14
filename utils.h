
#ifndef UTILS_H_HH_H_H
#define UTILS_H_HH_H_H

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



unsigned long int get_file_size(const char *fname)
{
	std::fstream f(fname);
	if(f.is_open()==0)
		return 0;

	f.seekg(0,std::ios::end);
	unsigned long int ret = f.tellg();
	f.close();
	return ret;
}


template<typename T>
class Stack
{
	public:
		std::size_t size()const
		{
			return _d.size();
		}

		T pop()
		{
			T t = _d.front();
			_d.erase(_d.begin());
			return t;
		}

		void push(const T &t)
		{
			_d.insert(_d.begin(),t);
		}

		const T& peek()const
		{
			return _d.front();
		}

		bool is_empty()const
		{
			return _d.size()==0;
		}

		void clear()
		{
			_d.clear();
		}

	private:
		std::vector<T> _d;
};

template<typename T>
class Queue
{
	public:
		std::size_t size()const
		{
			return _d.size();
		}

		T get_front()
		{
			T t = _d.front();
			_d.erase(_d.begin());
			return t;
		}
		void push_back(const T &t)
		{
			_d.push_back(t);
		}

		const T& peek()const
		{
			return _d.front();
		}

		bool is_empty()const
		{
			return _d.size()==0;
		}

		void clear()
		{
			_d.clear();
		}
	private:
		std::vector<T> _d;
};



void read_sort_file(std::vector<int> &v,const std::string &fname)
{

}

template<typename T>
std::string toString(const T &t)
{
	std::stringstream str;
	str << t;
	return str.str();
}

void fatal(const std::string &msg)
{
	std::cout << msg << std::endl;
	exit(1);
}

void string_to_vector(std::vector<int> &v,const std::string &s)
{
	for(int i=0;i<s.size();++i) {
		v.push_back((int)s[i]);
	}
}

void string_to_vector(std::vector<char> &v,const std::string &s)
{
	for(int i=0;i<s.size();++i) {
		v.push_back(s[i]);
	}
}

template<typename T>
void vprint(const std::string &msg,const std::vector<T> &v)
{
	std::cout << msg << " ";
	for(int i=0;i<v.size();++i) {
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;
}

template<typename T>
void vswap(std::vector<T> &v,int index1,int index2)
{
	if(index1>=v.size())
		fatal("vswap dies...1");

	if(index2>=v.size())
		fatal("vswap dies...2");

//std::cout << "\t\tswapping indices: " << index1 << " and " << index2 << std::endl;

	T t = v[index1];
	v[index1] = v[index2];
	v[index2] = t;
}

class TreeNode
{
	public:
		int get_data()const
		{
			return _d;
		}
		void set_data(int x)
		{
			_d = x;
		}
		const std::vector<TreeNode*>& get_children()const
		{
			return _children;
		}
		std::vector<TreeNode*>& get_children()
		{
			return _children;
		}
		TreeNode* get_child(int index)
		{
			return _children[index];
		}
		void add_child(TreeNode *c)
		{
			_children.push_back(c);
		}

	private:
		int _d;
		std::vector<TreeNode*> _children;
};

namespace fun
{

template<typename T>
class Queue
{
	public:
		void put(const T &t)
		{
			_d.push_back(t);
		}

		void put(const std::vector<T> &v)
		{
			for(int i=0;i<v.size();++i)
				_d.push_back(v[i]);
		}

		T getnext()
		{
			if(0==_d.size())
				fatal("fun::Queue::get_front() on empty queue");

			T d = _d[0];
			_d.erase(_d.begin());
			return d;
		}

		const T& peek()const
		{
			if(0==_d.size())
				fatal("fun::Queue::peek() on empty queue");

				return _d[0];
		}

		void clear()
		{
			_d.clear();
		}

		std::size_t size()const
		{
			return _d.size();
		}

	private:
		std::vector<T> _d;
};

template<typename T>
class Link
{
	public:
		Link(const std::string &src,const std::string &dst,T wgt)
		{
			_src_name = src;
			_dst_name = dst;
			_wgt = wgt;
		}
		const std::string& get_src_name()const
		{
			return _src_name;
		}
		const std::string& get_dst_name()const
		{
			return _dst_name;
		}
		T get_wgt()const
		{
			return _wgt;
		}
    template<typename S> friend std::ostream& operator<<(std::ostream &out,const Link<S> &link);

	private:
		std::string _src_name,_dst_name;
		T _wgt;
};

template<typename T>
std::ostream& operator<<(std::ostream &os,const Link<T> &link)
{
	os << link._src_name << "," << link._dst_name << "," << link._wgt;
	return os;
}

template<typename T>
class Graph
{
	public:

		int get_link_weight(T &wgt,const std::string &src_name,const std::string &dst_name)const
		{
			for(int i=0;i<_adjlist.size();++i) {
				if(_adjlist[i].get_src_name()==src_name) {
					if(_adjlist[i].get_dst_name()==dst_name) {
						wgt = _adjlist[i].get_wgt();
						return 0;
					}
				} else if(_adjlist[i].get_dst_name()==src_name) {
					if(_adjlist[i].get_src_name()==dst_name) {
						wgt = _adjlist[i].get_wgt();
						return 0;
					}
				}
			}
			return 1;
		}

		void add_link(const Link<T> &link)
		{
			std::string src_name = link.get_src_name();
			std::string dst_name = link.get_dst_name();

			if(_nodes.end()==std::find(_nodes.begin(),_nodes.end(),src_name))
				_nodes.push_back(src_name);

			if(_nodes.end()==std::find(_nodes.begin(),_nodes.end(),dst_name))
				_nodes.push_back(dst_name);

			_adjlist.push_back(link);
		}

		void print_links()const
		{
			for(int i=0;i<_adjlist.size();++i) {
				std::cout << _adjlist[i] << std::endl;
			}
		}

		bool has_node(const std::string &node_name)const
		{
			return _nodes.end()!=std::find(_nodes.begin(),_nodes.end(),node_name);
		}

		std::size_t node_count()const
		{
			return _nodes.size();
		}

		int get_node_index(const std::string &node_name)const
		{
			for(int i=0;i<_nodes.size();++i) {
				if(_nodes[i]==node_name)
					return i;
			}
			return -1;
		}

		std::string get_node_by_index(int index)const
		{
			if(index >= _nodes.size())
				return "";

			return _nodes[index];
		}

		int get_neighbors(std::vector<std::string> &neighbors,const std::string &n_name)const
		{
			for(int i=0;i<_adjlist.size();++i) {

				std::string neighbor = "";

				if(_adjlist[i].get_src_name()==n_name) {
					neighbor = _adjlist[i].get_dst_name();

				} else if(_adjlist[i].get_dst_name()==n_name) {
					neighbor = _adjlist[i].get_src_name();

				}

				if(neighbor=="")
					continue;

				int j;
				for(j=0;j<neighbors.size();++j) {
					if(neighbor == neighbors[j])
						break;
				}
				if(j==neighbors.size())
					neighbors.push_back(neighbor);
			}
		}

	private:
		std::vector<Link<T> > _adjlist;
		std::vector<std::string> _nodes;
};


template<typename S,typename T>
T convert(const S &s)
{ }

template<>
int convert(const std::string &s)
{
	return atoi(s.c_str());
}

template<>
float convert(const std::string &s)
{
	return (float)atof(s.c_str());
}

template<typename T>
int graph_adjlist_read(const std::string &fname,Graph<T> &g)
{
	std::fstream fin;

	fin.open(fname.c_str(),std::ios::in);
	if(!fin.is_open())
		return 1;

	std::string rawline;
	while(std::getline(fin,rawline)) {

		std::vector<std::string> toks;
		std::string tok = "";

		for(int i=0;i<rawline.size();++i) {
			if(rawline[i]==',') {
				toks.push_back(tok);
				tok = "";
			} else
				tok = tok + rawline[i];
		}
		toks.push_back(tok);

		if(toks.size()==3) {
			g.add_link(Link<T>(toks[0],toks[1],convert<std::string,T>(toks[2])));
		}

		toks.clear();
	}
	return 0;
}

class Path
{
	public:
		void add_node(const std::string &node_name)
		{
			_node_names.push_back(node_name);
		}
	private:
		std::vector<std::string> _node_names;
	friend std::ostream& operator<<(std::ostream &os,const Path &p)
	{
		for(int i=0;i<p._node_names.size();++i) {
			os << p._node_names[i];
			if(i<p._node_names.size()-1)
				os << ",";
		}
		return os;
	}
};



/*
class AdjList
{
	public:
		void add_link(const std::string &src,const std::string &dst,int wgt)
		{

		}
		int get_link_count()const
		{
			return _links.size();
		}
		const Link& get_link(int index)const
		{
			if(index >= _links.size())
				fatal("get_link()....dead");
			return _links[index];
		}
		Link& get_link(int index)
		{
			if(index >= _links.size())
				fatal("get_link()....dead");
			return _links[index];
		}
	private:
		std::vector<Link> _links;
};

*/


class AllocUnit
{
	public:
		AllocUnit(unsigned char *addr,unsigned int byte_count)
		{
			_addr = addr;
			_byte_count = byte_count;
		}
		unsigned char *get_addr()const
		{
			return _addr;
		}
		unsigned int get_byte_count()const
		{
			return _byte_count;
		}

	private:
		unsigned char *_addr;
		unsigned int _byte_count;
};

class MemoryManager
{
	public:
		~MemoryManager()
		{
			if(_units.size()) {
				std::cout << "WARNING:" << std::endl;
				std::cout << "\tMemoryManager is not empty on exit!" << std::endl;
			}
		}
		unsigned char *malloc(unsigned int size)
		{
			unsigned char *ret;
			ret = new (std::nothrow) unsigned char[size];
			if(ret==NULL) {
				fatal("MemoryManager.malloc() died...size: " + toString(size));
			}
			_add_alloc(ret,size);
			return ret;
		}

		template<typename T>
		void free(T &t)
		{
			unsigned char *c = (unsigned char*)t;
			_delete_unit_by_addr(c);
		}

		void free_all_memory()
		{
			std::vector<AllocUnit>::iterator itr = _units.begin();
			while(itr!=_units.end()) {
				delete[](itr->get_addr());
				++itr;
			}
			_units.clear();
		}

		static MemoryManager& getMemoryManager()
		{
			static MemoryManager _m;
			return _m;
		}

	private:
		MemoryManager() // singleton
		{ }
		void _add_alloc(unsigned char *c,unsigned int size)
		{
			AllocUnit unit(c,size);
			_units.push_back(unit);
		}
		void _delete_unit_by_addr(unsigned char *c)
		{
			std::vector<AllocUnit>::iterator itr = _units.begin();
			while(itr!=_units.end()) {
				if(c==itr->get_addr()) {
					_units.erase(itr);
					delete[](c);
					return;
				}
				++itr;
			}
			fatal("MemoryManager() delete_unit_by_addr() dies...");
		}



		std::vector<AllocUnit> _units;
};

}; // namespace fun

// UTILS_H_HH_H_H
#endif

