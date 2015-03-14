
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

class AVL
{
	public:

		AVL(int d)
		{
			_d = d;
			_left = 0;
			_right = 0;
		}
		AVL* get_left()
		{
			return _left;
		}
		AVL* get_right()
		{
			return _right;
		}
		void set_right(AVL *n)
		{
			_right = n;
		}
		void set_left(AVL *n)
		{
			_left = n;
		}

		AVL* get_parent()
		{
			return _parent;
		}
		void set_parent(AVL *parent)
		{
			_parent = parent;
		}

		int get_data()const
		{
			return _d;
		}
		void set_data(int d)
		{
			_d = d;
		}

	private:
		AVL *_left,*_right,*_parent;
		int _d;
};

void rotate_right(AVL *avl)
{

}
void rotate_left(AVL *avl)
{

}


void insert(AVL *avl,int v)
{
	if(v <= avl->get_data()) {

		if(avl->get_left()==0) {
			avl->set_left(new AVL(v));
		//	return;
		} else {
			insert(avl->get_left(),v);
		}
	} else {

		if(avl->get_right()==0) {
			avl->set_right(new AVL(v));
		//	return;
		} else {
			insert(avl->get_right(),v);
		}
	}

	rebalance(avl);
}

int get_height(AVL *root)
{
	int left_height = 0;
	int right_height = 0;

	if(root->get_left())
		left_height = 1 + get_height(root->get_left());

	if(root->get_right())
		right_height = 1 + get_height(root->get_right());

	if(left_height > right_height)
		return left_height;
	return right_height;
}

void rebalance(AVL *root)
{
	int balance_factor = get_height(root->get_left()) - get_height(root->get_right());

	if(balance_factor < -1) {
		rotate_left(root);
		rebalance(root->get_left());
	}
	if(balance_factor > 1) {
		rotate_right(root);
		rebalance(root->get_right());
	}

}

AVL* search(AVL *root,int v)
{

	if(root->get_data()==v)
		return root;

	if(root->get_data() <= v && root->get_left()!=0)
		return search(root->get_left(),v);
	else if(root->get_right()!=0)
		return search(root->get_right(),v);

	return 0;
}

void replace_child(AVL *new_child,AVL *current_child)
{
	if(current_child->get_parent()==0)
		fatal("replace_child....dies no parent");

	AVL *parent = current_child->get_parent();

	if(parent->get_left()==current_child)
		parent->set_left(new_child);
	else if(parent->get_right()==current_child)
		parent->set_right(new_child);
}

int delete_node(AVL *target)
{
	// if it is a leaf just delete it.
	if(target->get_right()==0 && target->get_left()==0) {

		replace_child(0,target);

		delete target;
	}

	if(target->get_right()==0) {
		AVL *new_me = target->get_left();
		while(new_me->get_right()!=0) {
			new_me = new_me->get_right();
		}

			// new_me's parent is given new_me's left child if it exists
			// if it does not exist, then new_me's parent gets a leaf
		replace_child(new_me->get_left(),new_me); // new_me is leaving its parent
		replace_child(new_me,target); // new_me is replacing target as a child

		new_me->set_left(target->get_left());
		new_me->set_right(target->get_right());

		delete target;
	}

	if(target->get_left()==0) {
		AVL *new_me = target->get_right();
		while(new_me->get_left()!=0) {
			new_me = new_me->get_left();
		}

			// new_me's parent is given new_me's right child if it exists
			// if it does not exist, then new_me's parent gets a leaf
		replace_child(new_me->get_right(),new_me); // new_me is leaving its parent
		replace_child(new_me,target); // new_me is replacing target as a child

		new_me->set_left(target->get_left());
		new_me->set_right(target->get_right());

		delete target;
	}
}


void tree_print(const std::string &msg,int tab_count,AVL *root)
{

	if(root==0)
		return;

	for(int i=0;i<tab_count;++i)
		std::cout << "\t";

	std::cout << msg << " ";
	std::cout << root->get_data() << ",";
	std::cout << std::endl;

	tree_print("",tab_count+1,root->get_left());
	tree_print("",tab_count+1,root->get_right());
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

	vprint("v:",vi);

	AVL *avl = new AVL(vi[0]);
	for(int i=1;i<vi.size();++i) {
		insert(avl,vi[i]);
		tree_print("root:",0,avl);
	}

	AVL *ff = search(avl,15);

	tree_print("boo:",0,ff);

	delete_node(ff);
	tree_print("boo:",0,avl);

	return 0;
}

