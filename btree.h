#ifndef BTREE_H    
#define BTREE_H
#include <iostream>

using namespace std;

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
 
    // val is the key or the value that
    // has to be added to the data part
    Node(int val){
        data = val;
 
        // Left and right child for node
        // will be initialized to null
        left = NULL;
        right = NULL;
    }
	Node(){
		
	}
};

// void insert(Node *root, int data);
// void traversal(Node *root);

#endif
