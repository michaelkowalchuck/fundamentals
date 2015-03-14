
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

class Tree;
class Tree *ROOT;
void tree_print(const std::string &msg,int tab_count,Tree *root);

void print_node_data(const std::string &msg,Tree *n);

class Tree
{
	public:

		Tree(int data)
		{
			_parent = 0;
			_d.push_back(data);
		}

		void set_parent(Tree *parent)
		{
			_parent = parent;
		}
		Tree* get_child(int index)
		{
			if(index > _children.size())
				fatal("get_child...dies");

			return _children[index];
		}
		int get_data(int index)
		{
			if(index > _d.size())
				fatal("get_data...dies");

			return _d[index];
		}

		void remove_data(int index)
		{
			if(index >= _d.size())
				fatal("remove_data failed on index:" + toString(index));

			_d.erase(_d.begin()+index);
		}

		void remove_child(int index)
		{
			if(index >= _children.size())
				fatal("remove_child failed on index:" + toString(index));

			_children.erase(_children.begin()+index);
		}
		void set_child(int index, Tree *c)
		{
			if(index > _children.size())
				fatal("set_child() dies on index: " + toString(index));

			c->set_parent(this);
			_children[index] = c;
		}
		void add_child(Tree *c)
		{
			c->set_parent(this);
			_children.push_back(c);
		}
		void clear_children()
		{
			_children.clear();
		}

		void insert_child_before_index(int index,Tree *n)
		{
			if(index > _children.size())
				fatal("insert_child_before_index...dies");

			_children.insert(_children.begin()+index,n);
		}

		void insert_data_before_index(int index,int data)
		{
			if(index > _d.size())
				fatal("insert_data_before_index...dies");

			_d.insert(_d.begin()+index,data);
		}

		bool is_4node()const
		{
			return data_count()==3;
		}
		bool is_leaf()const
		{
			return child_count()==0;
		}
		int data_count()const
		{
			return _d.size();
		}
		int child_count()const
		{
			return _children.size();
		}

		int which_data(int data)
		{
			for(int i=0;i<_d.size();++i) {
				if(data<=_d[i])
					return i;
			}
			// be careful with this, since this is an invalid index for usage
			// in get_data(), only call this funcion for use in
			// std::vector::insert calls where you want to insert at the end of
			// the vector, which is just like a push_back
			return _d.size();
		}

		int which_child(int s)const
		{
			for(int i=0;i<_d.size();++i) {
				if(s<=_d[i])
					return i;
			}
				// children size is one more than data, so this means pursue
				// the last child
			return _d.size();
		}

			// split a 4node into three 2nodes
		void split()
		{
			if(is_4node()==false)
				fatal("split() dies...");

			// create 2 new 2nodes with no children, but
			// use 4node's data[0] and data[2] as 2node data
			Tree *left_node = new Tree(get_data(0));
			Tree *right_node = new Tree(get_data(2));

			// original 4node is downgraded to a 2node
			remove_data(0);
			remove_data(1); // was at 2, but since we removed 0 it becomes 1

			// take original 4node's children and use them as new 2nodes' children.
			// Since the children were in order in the 4node, we just put them in
			// the same order in each 2node.  The position relative to the new
			// 2node parent will be correct automatically since we create the 2node
			// parent using data from the middle of the original 4node
			if(false == is_leaf()) {
				left_node->add_child(get_child(0));
				left_node->add_child(get_child(1));
				right_node->add_child(get_child(2));
				right_node->add_child(get_child(3));
			}

			// use original 4node's data as data for new 2nodes' data.
				// this is automatic since we removed the other data elements earlier.

			// remove old children
			// the pointers for the old children are now in the children of
			// the new 2nodes, left_node and right_node
			clear_children();
			// finally, add left_node and right_node as children of new 2node
			add_child(left_node);
			add_child(right_node);
		}


		void upgrade_node(int data)
		{
			int data_index = which_data(data);
			insert_data_before_index(data_index,data);
		}

		void rebalance()
		{
				// we do not rebalance if we are at the top already,
				// the tree just grows up
			if(_parent==0)
				return;

				// parent cannot absorb child if it is already a 4node, so split
				// note this may cause recursive splitting/rebalancing up the tree.

			_parent->absorb_2node_child(this);
		}

		void absorb_2node_child(Tree *c)
		{
			if(is_4node())
				fatal("absorb_child dies...");

				// c is always a 2node!!!!

			int child_index = which_child(c->get_data(0));
			int data_index = which_data(c->get_data(0));

				// add the child's data, thus upgrading this node
			insert_data_before_index(data_index,c->get_data(0));

				// note, that we have the space in _children for c that we can
				// reuse, but c has 2 children so we'll need to insert one of them.
			set_child(child_index,c->get_child(1)); // note the child index
			insert_child_before_index(child_index,c->get_child(0));

				// I chose the set() on child 1 and insert() on child 0 above in order to
				// maintain the order of the children

				// c has been absorbed, it is little more than a hollow husk now
				// remove c from memory
			delete c;
		}

		void insert(int data)
		{
			if(is_4node()) {
				split();
				rebalance();
			}

			// if the node has children, then insert it into one of them.
			if(child_count()) {
				int child_index = which_child(data);
				get_child(child_index)->insert(data);
			} else {
					// upgrade to a 3node, 4node, or split
				upgrade_node(data);
			}
		}

		void delete_node(int data)
		{
			// TODO
		}

	private:
		std::vector<int> _d;
		std::vector<Tree*> _children;
		Tree *_parent;
};

void tree_print(const std::string &msg,int tab_count,Tree *root)
{

	for(int i=0;i<tab_count;++i)
		std::cout << "\t";

	std::cout << msg << " ";
	for(int i=0;i<root->data_count();++i) {
		std::cout << root->get_data(i) << ",";
	}
	std::cout << std::endl;

	for(int i=0;i<root->child_count();++i)
		tree_print("",tab_count+1,root->get_child(i));
}

void print_node_data(const std::string &msg,Tree *n)
{
	std::cout << msg;
	for(int i=0;i<n->data_count();++i) {
		std::cout << n->get_data(i) << ",";
	}
	std::cout << std::endl;
}

int main(int argc,char **argv)
{
	std::vector<char> vc;
	std::vector<int> vi;

	std::string s = "THIS IS WHAT WE ARE LOOKING FOR";

	string_to_vector(vc,s);
	string_to_vector(vi,s);

	vprint("v:",vc);
	vprint("v:",vi);

vi.clear();
vi.push_back(0);
vi.push_back(5);
vi.push_back(10);
vi.push_back(15);
vi.push_back(20);
vi.push_back(25);
vi.push_back(30);
vi.push_back(35);
vi.push_back(40);
vi.push_back(45);
vi.push_back(50);
vi.push_back(55);
vi.push_back(60);
vi.push_back(65);
vi.push_back(70);
vi.push_back(75);
vi.push_back(80);
vi.push_back(85);

	//Tree *r = new Tree(vi[0]);
	ROOT = new Tree(vi[0]);

	for(int i=1;i<vi.size();++i) {
		ROOT->insert(vi[i]);
		tree_print("root:",0,ROOT);
	}


	return 0;
}

