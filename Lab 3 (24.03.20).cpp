#include <iostream>
#include <queue>

using namespace std;

class BinaryTreeNode {
	int val;
	BinaryTreeNode* left, * right;
public:
	BinaryTreeNode(int new_val) : val(new_val), left(NULL), right(NULL) {}
	void print() { cout << val << " "; }

	friend class BinaryTree;
	friend class BinaryTreeTest;	
};

class BinaryTree {
	BinaryTreeNode* root;
	int size;
public:
    BinaryTree(): root(NULL), size(0){} //default constructor
		// TODO Insert missing steps here
    
	~BinaryTree() {
        clean_up(root);
        root = NULL; //just in case someone tries to access the root before clean up finishes
        size = 0;
    }
		// TODO Insert missing steps here	

	int min(BinaryTreeNode* T) {
		// TODO Insert missing steps here
        
        if(!T) //base case: empty tree
            return -1;
        
        //our general case: non empty tree
        BinaryTreeNode* cur = T;
        while(cur && cur -> left){ //don't need to check cur, cur ->left will be null when cur is null
            cur = cur -> left;
        }
    
        return cur-> val; //returns
        
	}
	
    int min() {
        
		return min(root);
	}
	
	int max(BinaryTreeNode* T) {
		// TODO Insert missing steps here
        // TODO Insert missing steps here
        
        if(!T) //base case: empty tree
            return -1;
        
        //our general case: non empty tree
        BinaryTreeNode* cur = T;
        while(cur && cur -> right){ //don't need to check cur, cur ->left will be null when cur is null
            cur = cur -> right; //our important/main iterator line
            //we can't use root (this destroys the whole structure of the tree)
        }
        
        return cur-> val; //returns
	}

	int max() {
		return max(root);
	}
	
	bool exists(BinaryTreeNode* T, int key) { //our "search"
		// TODO Insert missing steps here
        BinaryTreeNode* cur = T;
        while(cur) {
            if(cur->val == key)
                return true;
            
            if (key < cur-> val) //move left if the given key is smaller than cur's value
                cur = cur-> left;
            else//move right (the key is greater)
                cur = cur -> right;
        }
        return false;
	}
    //this moves depending on the key value (because it a binary search tree we can divide our searching time in half each time we compare a subroot and choose a path)

	bool exists(int key) { //this is a function override...correct?
		return exists(root, key);
	}
	
	bool insert(BinaryTreeNode new_node) {
		// TODO Insert missing steps here
        //this approach uses double pointers

        BinaryTreeNode** cur = &root;//points to the place where the root pointer is stored (cur -> root -> root value)
        
        while(cur) {
            if((*cur)->val == new_node.value)//rejects duplicates (if found)
                return false;
            
            if (new_node.value < (*cur)-> val) //move left if the given key is smaller than cur's value
                cur = &((*cur)-> left); //moving cur as a double pointer
            //cur is the address of the pointer that points to the left node
            //points to the location where cur's left pointer is stored
            
            else//move right (the key is greater)
                cur = &((*cur)-> right); //point to the location where the pointer to the right node is stored
        }
        *cur = new BinaryTreeNode(new_node);
        ++size;
        
        return true;
        
        //why doesn't (*cur) = (*cur)->right; work?
        //why are we using the exists structure and double pointers
        //double pointers: we can set the pointer location directly and modify it directly (instead of using two pointers)
	}

	void pre_order(BinaryTreeNode* T) {
		if (T == NULL) return;
		T->print();
		pre_order(T->left);
		pre_order(T->right);
	}

	void pre_order() { //this is considred a wrapper function (it calls a helper that does have parameters (this cleans up the interface))
		pre_order(root);
	}

	void in_order(BinaryTreeNode* T) {
		if (T == NULL) return;
		in_order(T->left);
		T->print();
		in_order(T->right);
	}

	void in_order() {
		// TODO Insert missing steps here
	}

	void post_order(BinaryTreeNode* T) {
		if (T == NULL) return;
		post_order(T->left);
		post_order(T->right);
		T->print();
	}

	void post_order() {
		// TODO Insert missing steps here
	}

	void BFT(BinaryTreeNode* T) {
		if (T == NULL) return;
		
		queue<BinaryTreeNode*> bft_queue;
		bft_queue.push(T);

		while(!bft_queue.empty()) {
			BinaryTreeNode* cur = bft_queue.front();
			bft_queue.pop();

			cur->print();
			if (cur->left) bft_queue.push(cur->left);
			if (cur->right) bft_queue.push(cur->right);
		}
	}

	void BFT() {
		// TODO Insert missing steps here
        BFT(root);
	}
	
	void clean_up(BinaryTreeNode* T) {
		if (T == NULL) return;
		clean_up(T->left);
		clean_up(T->right);
		delete T;
	}
};

class BinaryTreeTest {
public:
	void test_traversals(BinaryTree& test_tree) {
		
		cout << endl << "Test PreOrder Traversal" << endl;		
		test_tree.pre_order();	

		cout << endl << "Test InOrder Traversal" << endl;		
		test_tree.in_order();	
		
		cout << endl << "Test PostOrder Traversal" << endl;		
		test_tree.post_order();	
		
		cout << endl << "Test Breadth First Traversal" << endl;
		test_tree.BFT();
	}
	
	void test_scenario1() {
		BinaryTree test_tree;

		BinaryTreeNode* root = new BinaryTreeNode(14);
		root->left = new BinaryTreeNode(12);
		root->right = new BinaryTreeNode(25);
		root->right->left = new BinaryTreeNode(21);
		root->right->right = new BinaryTreeNode(36);

		cout << "Min value is " << test_tree.min(root) << endl;
		cout << "Max value is " << test_tree.max(root) << endl;

		cout << (test_tree.exists(root, 25) ? "25 exists" : "25 does not exist") << endl;
		cout << (test_tree.exists(root, 32) ? "32 exists" : "32 does not exist") << endl;
		
		test_tree.clean_up(root);	
	}	
	
	void test_scenario2() {
		BinaryTree test_tree;

		test_tree.insert(BinaryTreeNode(15));
		test_tree.insert(BinaryTreeNode(13));
		test_tree.insert(BinaryTreeNode(11));
		test_tree.insert(BinaryTreeNode(12));
		test_tree.insert(BinaryTreeNode(14));
		test_tree.insert(BinaryTreeNode(10));
		test_tree.insert(BinaryTreeNode(9));
		test_tree.insert(BinaryTreeNode(8));
		test_tree.insert(BinaryTreeNode(7));

		test_traversals(test_tree);
	}	

	void test_scenario3() {
		BinaryTree test_tree;

		test_tree.insert(BinaryTreeNode(15));
		test_tree.insert(BinaryTreeNode(12));
		test_tree.insert(BinaryTreeNode(14));
		test_tree.insert(BinaryTreeNode(16));
		test_tree.insert(BinaryTreeNode(11));
		test_tree.insert(BinaryTreeNode(18));
		test_tree.insert(BinaryTreeNode(13));
		test_tree.insert(BinaryTreeNode(17));
		test_tree.insert(BinaryTreeNode(19));

		cout << endl << "Min value is " << test_tree.min() << endl;
		cout << "Max value is " << test_tree.max() << endl;

		cout << (test_tree.exists(16) ? "16 exists" : "16 does not exist") << endl;
		cout << (test_tree.exists(42) ? "42 exists" : "42 does not exist") << endl;
		
		test_traversals(test_tree);	
	}	

	void run_tests() {
		test_scenario1();
		test_scenario2();	
		test_scenario3();	
	}
};

int main() {	
	BinaryTreeTest test1;
	test1.run_tests();
}
