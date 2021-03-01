// #include<queue>
// using namespace std;

// #include "btree.h"


// /* Function to insert the formed nodes to the tree when a parent node does not have a right or the left child. */
// void insert(struct Node *root, int data) {
//     struct Node *temp;
//     queue<struct Node*>q;
//     q.push(root);
//     while(!q.empty()) 
//     {
//         temp = q.front();
//         q.pop();

//         /* Insert node as the left child of the parent node. */
//         if(temp->left == NULL) {
// 			if(data != NULL){
//             	temp->left = new Node(data);
// 			}else{
// 				cout << "NULL " << temp->data << "\n";
// 				temp->left = new Node();
// 			}
//             break;
//         }

//         /* If the left node is not null push it to the queue. */
//         else
//             q.push(temp->left);
        
//         /* Insert node as the right child of the parent node. */
//         if(temp->right == NULL) {
// 			if(data != NULL){
//             	temp->right = new Node(data);
// 			}else{
// 				cout << "NULL_r " << temp->data << "\n";

// 				temp->right = new Node();
// 			}
//             break;
//         }

//         /* If the right node is not null push it to the queue. */
//         else
//             q.push(temp->right);
//     }
// }

// /* Function for tree traversal of every node in the tree. */
// void traversal(struct Node *root) {
//     if(root == NULL)
//         return;
	
// 	if(root->data != 0){
// 		cout << root->data << " ";
// 	}
	
//     traversal(root->left);
//     traversal(root->right);
// }
