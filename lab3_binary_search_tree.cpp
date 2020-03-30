#include <iostream>
#include "lab3_binary_search_tree.hpp"

using namespace std;

// PURPOSE: Default/empty constructor
BinarySearchTree::BinarySearchTree() {
	root = NULL;
	size = 0;
}

void BinarySearchTree::destroy(TaskItem* node){ //ADD TO HEADER
	if (node)
	{
		destroy(node->left);
		destroy(node->right);
		delete node;
	}
}

// PURPOSE: Explicit destructor of the class BinarySearchTree
BinarySearchTree::~BinarySearchTree() {
	destroy(root);
	root = NULL;
	size = 0;
}

// PURPOSE: Returns the number of nodes in the tree
unsigned int BinarySearchTree::get_size() const {
	return 0;
}

// PURPOSE: Returns the maximum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::max() const {
	return BinarySearchTree::TaskItem(-1, "N/A");
}

// PURPOSE: Returns the minimum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::min() const {
	if (!root)
		return BinarySearchTree::TaskItem(-1, "N/A");
	TaskItem* cur = root;
	if (size == 1)
		return *cur;
	while ((cur->left))
		cur = cur->left;
	return *cur;
}

// PURPOSE: Returns the tree height
unsigned int BinarySearchTree::height() const {
	return 0;
}

// PURPOSE: Prints the contents of the tree; format not specified
void BinarySearchTree::print() const {
}

// PURPOSE: Returns true if a node with the value val exists in the tree	
// otherwise, returns false
bool BinarySearchTree::exists( BinarySearchTree::TaskItem val ) const {
	return false;
}

// PURPOSE: Optional helper function that returns a pointer to the root node
BinarySearchTree::TaskItem* BinarySearchTree::get_root_node() {
    return root;
}

// PURPOSE: Optional helper function that returns the root node pointer address
BinarySearchTree::TaskItem** BinarySearchTree::get_root_node_address() {
    return NULL;
}

// PURPOSE: Optional helper function that gets the maximum depth for a given node
int BinarySearchTree::get_node_depth( BinarySearchTree::TaskItem* n ) const {
	return 0;
}

// PURPOSE: Inserts the value val into the tree if it is unique
// returns true if successful; returns false if val already exists
bool BinarySearchTree::insert( BinarySearchTree::TaskItem val ) {
    return false;
}

// PURPOSE: Removes the node with the value val from the tree
// returns true if successful; returns false otherwise
bool BinarySearchTree::remove( BinarySearchTree::TaskItem val ) {
    if (!root)
		return false;
	if (root->priority == val.priority && size == 1) {//if one element
		delete root;
		root = NULL;
		size--;
		return true;
	}

	TaskItem* cur = root;
	TaskItem* prev = root;
	bool found = false;
	//finding node to remove
	while (!found) {
		if (cur->priority > val.priority && cur->left != NULL) {
			if (cur->left->priority == val.priority){//stops if next one is node
				prev = cur;
				found = true;
			}
			cur = cur->left;
		}
		else if (cur->priority < val.priority && cur->right != NULL) {
			if (cur->right->priority == val.priority) {//ditto
				prev = cur;
				found = true;
			}
			cur = cur->right;
		}
		else
			return false;
	}

	//removing node
	while (cur->right != NULL || cur->left != NULL){//if not leaf node
		TaskItem* temp = cur;
		prev = cur;

		if (cur->left != NULL) {//moving successor up
			temp = temp->left;
			while (temp->right != NULL) {
				if (temp->right->right == NULL)
					prev = temp;
				temp = temp->right;
			}
		}
		else {//moving predecessor up
			temp = temp->right;
			while (temp->left != NULL) {//>1 child
				if (temp->left->left == NULL)
					prev = temp;
				temp = temp->left;
			}
		}
		*cur = *temp;
		cur = temp;
		*cur = val;
	}

	//deleting extra node
	if (prev->left == cur) {
		delete prev->left;
		prev->left = NULL;
	}
	else {
		delete prev->right;
		prev->right = NULL;
	}
	size--;
	return true;
}
