#include <iostream>
#include "lab3_binary_search_tree.hpp"

using namespace std;

// PURPOSE: Default/empty constructor
BinarySearchTree::BinarySearchTree() {
	root = NULL;
	size = 0;
}

void BinarySearchTree::destroy(TaskItem* node){
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
	return size;
}

// PURPOSE: Returns the maximum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::max() const {
	  if(!root || size == 0)
        return BinarySearchTree::TaskItem(-1, "N/A");
    else if (size == 1)
        return *root;
//    else if(!root -> right && size == 2){
//        return *root;
//    }
    else{
        TaskItem* cur = root;
        while(cur -> right){
            cur = cur -> right;
        }
        return *cur;
    }
    //return BinarySearchTree::TaskItem(-1, "N/A");
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
unsigned int BinarySearchTree::height()  {
	
	if (!root) {
		return 0;
	}
	
	TaskItem **cur = &root;
	
	int max = 0, curMax = 0;

	max = height(cur, max, curMax);
	return max;

}

unsigned int BinarySearchTree::height(TaskItem** cur, int max, int curMax)  {
	if (!((*cur)->left || (*cur)->right)) {
		return 0;
	}
	else if ((*cur)->left) {
		curMax = height(&((*cur)->left), max, curMax) + 1;
		if (curMax > max) {
			max = curMax;
		}
	} else if ((*cur)->right) {
		curMax = height(&((*cur)->right), max, curMax) + 1;
		if (curMax > max) {
			max = curMax;
		}
	}

	return max;
}

// PURPOSE: Prints the contents of the tree; format not specified
void BinarySearchTree::print() const {
	TaskItem* cur = root;
	print(cur);
}


void BinarySearchTree::print(BinarySearchTree::TaskItem * val) const {
	if (val == NULL) {
		return;
	}
	else {
		cout << val->priority << " " << val->description << "\n";
		print(val->left);
		print(val->right);
	}
	
}

// PURPOSE: Optional helper function that returns a pointer to the root node
BinarySearchTree::TaskItem* BinarySearchTree::get_root_node() {
    return root;
}

// PURPOSE: Optional helper function that returns the root node pointer address
BinarySearchTree::TaskItem** BinarySearchTree::get_root_node_address() {
      if (root)
        return &root;
    else
        return NULL;
}

// PURPOSE: Optional helper function that gets the maximum depth for a given node
int BinarySearchTree::get_node_depth( BinarySearchTree::TaskItem* n ) const {
	    if(!root || size == 0 || !exists(*n)){
        cout << "base case triggered";
        return 0;
    }
    TaskItem* cur = root;
    if (size == 1)
        return 1;
    else {
        int count = 2;
        
        for (int i = 0; i < size; i++){
            if(cur -> priority == n -> priority){
                cout << "base case triggered" << endl;
                return count;
               
            }
            else if (cur -> priority > n -> priority){
                if (cur -> right) {
                    cur = cur -> right;
                    count++;
                }
            }
            else if (cur -> priority < n -> priority)
                if (cur -> left) {
                    cur = cur -> left;
                    count++;
                }
        }
    }
}

// PURPOSE: Inserts the value val into the tree if it is unique
// returns true if successful; returns false if val already exists
bool BinarySearchTree::insert( BinarySearchTree::TaskItem val ) {
	TaskItem** cur = &root;
	if (!root) {
		*cur = new TaskItem(val);
		++size;
		return true;
	}

	while (*cur) {
		if ((*cur)->priority == val.priority) {
			return false;
		}
		else if ((*cur)->priority > val.priority) {
			cur = &((*cur)->left);
		}
		else if ((*cur)->priority < val.priority) {
			cur = &((*cur)->right);
		}
	}

	(*cur) = new TaskItem(val);
	++size;
    return true;
}

// PURPOSE: Removes the node with the value val from the tree
// returns true if successful; returns false otherwise
bool BinarySearchTree::remove(BinarySearchTree::TaskItem val) {
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
		if (*(cur) == val)
			found = true;
		else if (cur->priority > val.priority && cur->left != NULL) {
			if (*(cur->left) == val){//stops if next one is node
				prev = cur;
				found = true;
			}
			cur = cur->left;
		}
		else if (cur->priority < val.priority && cur->right != NULL) {
			if (*(cur->right) == val) {//ditto
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
		TaskItem* temp_right = temp->right;
		TaskItem* temp_left = temp->left;

		temp->right = cur->right;
		temp->left = cur->left;
		*cur = *temp;
		cur = temp;
		*cur = val;
		cur->right = temp_right;
		cur->left = temp_left;
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
