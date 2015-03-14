
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

/*
	1) node is either red or black
	2) root is black
	3) all leaves are black and null
	4) both children of every red node is black
	5) every simple path from a node to its leaves has the same number of black nodes

	-- the color of a node is really the color of the link leading to it.
	-- rb trees are like btrees of order 4

	O(log) n for worst and average case on all operations like: insert, delete, search 
	O(n) for memory
*/


class RB
{
	public:
		RB(int data)
		{
			_d = data;
			_is_red = 0;
			_left = 0;
			_right = 0;
		}
		int get_data()const
		{
			return _d;
		}
		RB* left()
		{
			return _left;
		}
		void set_left(RB *t)
		{
			_left = t;
		}
		RB* right()
		{
			return _right;
		}
		void set_right(RB *t)
		{
			_right = t;
		}
		bool is_red()const
		{
			return _is_red;
		}
		bool is_black()const
		{
			return !_is_red;
		}
		void set_black()
		{
			_is_red = false;
		}
		void set_red()
		{
			_is_red = true;
		}
		RB *get_parent()
		{
			return _parent;
		}
		void set_parent(RB *p)
		{
			_parent = p;
		}
		RB* grandparent()
		{
			if(_parent==0)
				return 0;
			return _parent->get_parent();
		}
		RB* uncle()
		{
			if(_parent==0)
				return 0;
			if(grandparent()->left()==_parent)
				return grandparent()->right();
			else
				return grandparent()->left();
		}

		void rotate_right()
		{

			if(!_parent || _parent->left()!=this)
				fatal("cannot call rotate_right() when you are not on left!");

			RB *pivot = this;

			_parent->set_left(pivot->right());

			RB *tmp = pivot->right();
			pivot->set_right(_parent);
			_parent->set_left(tmp);

			_parent = _parent->get_parent();

			pivot->right()->set_parent(this);

		}
		void rotate_left()
		{

			if(!_parent || _parent->right()!=this)
				fatal("cannot call rotate_left() when you are not on right!");

			RB *pivot = this;

			_parent->set_right(pivot->left());

			RB *tmp = pivot->left();
			pivot->set_left(_parent);
			_parent->set_right(tmp);

			_parent = _parent->get_parent();

			pivot->left()->set_parent(this);

		}

		RB* search(int data)
		{
			if(data <= get_data()) {
				if(!_left)
					return this;
				return _left->search(data);
			} else {
				if(!_right)
					return this;
				return _right->search(data);
			}
		}

		void insert_case5(RB *n)
		{
			RB *g = n->grandparent();

			n->get_parent()->set_black();
			g->set_red();
			if(n==n->get_parent()->left())
				g->rotate_right();
			else
				g->rotate_left();
		}

		void insert_case4(RB *n)
		{
			RB *g = n->grandparent();

			if( (n==n->get_parent()->right()) && (n->get_parent() == g->left())) {
				n->get_parent()->rotate_left();
				n = n->left();
			} else if((n==n->get_parent()->left()) && (n->get_parent() == g->right())) {
				n->get_parent()->rotate_right();
				n = n->right();
			}

			insert_case5(n);
		}

		void insert_case3(RB *n)
		{
			if(n->get_parent()->uncle()!=0 && n->uncle()->is_red()) {
				n->get_parent()->set_black();
				n->get_parent()->uncle()->set_black();
				n->grandparent()->set_red();
				insert_case1(n);
			} else {
				insert_case4(n);
			}
		}

		void insert_case2(RB *n)
		{
			if(n->get_parent()->is_black())
				return;
			else
				insert_case3(n);
		}

		void insert_case1(RB *n)
		{
			if(n->get_parent()==0)
				n->set_black();
			else
				insert_case2(n);
		}

		void insert(int data)
		{
			// make a new node
			RB *N = new RB(data);

			// find last RB node before null leafs
			RB *P = search(data);

			if(data <= P->get_data())
				P->set_left(N);
			else
				P->set_right(N);

			N->set_parent(P);
			insert_case1(N);
		}

		int _d;
		bool _is_red;
		RB *_parent;
		RB *_left,*_right;
	private:
};


void tree_print(const std::string &msg,int tab_count,RB *root)
{

	if(root==0)
		return;

	for(int i=0;i<tab_count;++i)
		std::cout << "\t";

	std::cout << msg << " ";
	std::cout << root->get_data() << ",";
	std::cout << std::endl;

	tree_print("",tab_count+1,root->left());
	tree_print("",tab_count+1,root->right());
}

int main(int argc,char **argv)
{
	std::vector<int> vi;
vi.clear();
vi.push_back(0);
vi.push_back(5);
vi.push_back(10);
vi.push_back(15);
vi.push_back(20);
vi.push_back(25);
/*
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
*/
	vprint("v:",vi);

	RB *r = new RB(vi[0]);
	for(int i=1;i<vi.size();++i) {
		r->insert(vi[i]);
		tree_print("root:",0,r);
	}

RB *p1 = new RB(1);
p1->set_parent(0);
RB *p2 = new RB(2);
RB *p3 = new RB(3);
RB *p4 = new RB(4);
RB *p5 = new RB(5);
RB *p6 = new RB(6);
RB *p7 = new RB(7);

p1->_left = p2;
p2->set_parent(p1);
p1->_right = p3;
p3->set_parent(p1);

p2->_left = p4;
p3->set_parent(p2);
p2->_right = p5;
p5->set_parent(p2);

p3->_left = p6;
p6->set_parent(p3);
p3->_right = p7;
p7->set_parent(p3);

tree_print("p time:",0,p1);

p2->rotate_right();
tree_print("p time:",0,p2);

p1->rotate_left();
tree_print("p time:",0,p1);

	return 0;
}

