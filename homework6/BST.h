#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <queue>
#include <algorithm> 

class node {
	public:
		int key; // hp
		int index; // the index of pSet
		node* left;
		node* right;
		node(int hp, int id):key(hp), index(id), left(NULL), right(NULL) {}
}; // end node

class BSTree {
	
	node* root; // root of tree
	int visit; // number of visited nodes
	std::vector<int> idSet;
	
	void setNode( node* newNode, int hp, int id ) {
		// set a new node for insertion
		newNode->key = hp;
		newNode->index = id;
		newNode->right = NULL;
		newNode->left = NULL;
	} // creatNode()
		
	node* insertNode(node *root, int hp, int id) {
		// id is index of pSet
		if ( root == NULL ) {
			return new node(hp, id);
		} // if
		
		else if ( hp > root->key ) {
			root->right = insertNode( root->right, hp, id );
		} // if
		
		else if ( hp <= root->key ) {
			root->left = insertNode( root->left, hp, id );
		} // else 
		
		return root;
	} // insertNode()
	
	int getH(node* root) const {
		// get the bst's height
		if ( root == NULL )
			return 0;
		else {
			int leftH = getH( root->left );
			int rightH = getH( root->right );
			 
			return std::max( leftH, rightH ) + 1;
		} // else
	} // getH()
	
	node* search( node* p, int key ) { // search the value which greater than low
		if ( !root )
			return NULL;
		
		if ( key == root->key )
			return root;
		
		if ( k < root->key )
			return search( root->left, key );
		
		return search( root->right, key );
	} // search()

	void clearBST();
	
	public:
		BSTree():root(NULL), visit(0) {} // constructor
		
		void test() {
			std::cout << root->key << std::endl;
		} // test()
		
		int heightOfBST() const {
			return getH( root );
		} // heightOfBST()
		
		bool isEmpty() {
			if ( root != NULL )
				return false;
			else
				return true;			
		} // isEmpty()
		
		void add(int hp, int id) { 
			root = insertNode( root, hp, id );
		} // add()
		
		void searchGreater( int low ) {
			search( root, low );
		} // searchGreater()
		
		int delMax() { // delete the max key
		
		} // delMax()
		 
		void clear();
		
		~BSTree() {
			//clear();
		} // destructor
		
}; // end BSTree

