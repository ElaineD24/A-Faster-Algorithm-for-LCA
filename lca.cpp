#include <cassert>
#include <vector>

using namespace std;

#include "btree.h"


vector<int> height;
vector<int> first_visit; 
int block_size, block_cnt;

vector<int> euler_tour;
vector<int> array_log;
vector<vector<int> > st;
vector<int> array_B;
vector<int> array_C;

void eulerTree(struct Node* root, int h) { 
    // store current node's data 
    height.push_back(h);
    euler_tour.push_back(root->data);
    first_visit[root->data] = euler_tour.size()-1;

    // If left node exists 
    if (root->left) { 
        // traverse left subtree 
        eulerTree(root->left, h+1); 

        height.push_back(h);

        // store parent node's data  
        euler_tour.push_back(root->data); 
    } 
  
    // If right node exists 
    if (root->right) { 
        // traverse right subtree 
        eulerTree(root->right, h+1);  
        
        height.push_back(h);
  
        // store parent node's data 
        euler_tour.push_back(root->data); 
    } 
} 
  
// Function to print Euler Tour of tree 
void printEulerTour(Node *root) { 
    // Stores Euler Tour 
    // vector<int> Euler;  
    // TODO, 9
    first_visit.assign(9, -1);  
    eulerTree(root, 0); 

    for (int i = 0; i < euler_tour.size(); i++) 
        cout << euler_tour[i] << " "; 
    cout << endl << endl << "Height Array L(A): ";
    for (int i = 0; i < height.size(); i++) 
        cout << height[i] << " "; 
    cout << endl << endl << "First_visit Array R: ";    
    for (int i = 0; i < first_visit.size(); i++) 
        cout << first_visit[i] << " "; 
    cout << endl << endl;
} 


int min_by_height(int i, int j) {

    return height[i] <= height[j] ? i : j;
}

void build_sparse_table(int block_cnt){
    
    int m = euler_tour.size();

    // precompute minimum of each block and build sparse table
    st.assign(array_log[block_cnt] + 1, vector<int>(block_cnt));
    // first row of the sparse table, divide by the block size
    for (int i = 0, j = 0, b = 0; i < m; i++, j++) {
        if (j == block_size)
            j = 0, b++;
        // build up array C which stores the block #
        array_C.push_back(b);
        if (j == 0 || min_by_height(i, st[0][b]) == i)
            st[0][b] = i;
    }
    
    for (int l = 1; l <= array_log[block_cnt]; l++) {
        for (int i = 0; i < block_cnt; i++) {
            // ni = i + 2^(l-1), on level 1 we compare 1+1 values, on level 2 we compare 1+2 values, on level 3 we compare 1+4 values ... 
            int ni = i + (1 << (l - 1));
            // if range exceed the num length
            if (ni >= block_cnt)
                st[l][i] = st[l-1][i];
            else
                // choose the min value among the range
                st[l][i] = min_by_height(st[l-1][i], st[l-1][ni]);
        }
    }

    cout << "Sparse Table: " << endl;
    // print sparse table
    for (int i = 0; i < st.size(); ++i) {
        for (int j = 0; j < st[0].size(); ++j) {
            cout << st[i][j] << ' ';
        }
        cout << endl;
    }    
    cout << endl;

    
}

void precompute_lca() {

    // precompute all log values without using floor and logarithm functions
    int m = euler_tour.size();
    array_log.reserve(m + 1);
    // for index 0
    array_log.push_back(-1);
    cout << "Array log: ";
    for (int i = 1; i <= m; i++) {
        array_log.push_back(array_log[i / 2] + 1);
        cout << array_log[i-1] << " ";
    }
    cout << array_log[-1] << " ";
    cout << endl << endl;

    // calculate block size and total number of blocks via log array
    block_size = max(1, array_log[m] / 2);
    block_cnt = (m + block_size - 1) / block_size;
    cout << "block size: " << block_size << endl;
    cout << "block count: " << block_cnt << endl;

    cout << endl;
    // build up sparse table for 2n/logn (# of blocks) total numbers 
    build_sparse_table(block_cnt);

    
    
}


/* Driver function to check the above algorithm. */
int main() {
    struct Node* root = new Node(0);
    root->left = new Node(1);    
    root->right = new Node(2);
    root->left->left = new Node(7);
    root->left->right = new Node(8);
    root->right->left = new Node(3);
    root->right->right = new Node(4);
    root->right->left->left = new Node(5);
    root->right->left->right = new Node(6);

    // insert(root, 2);
	// insert(root, 3);
	// insert(root, 8);
	// insert(root, 9);
	// insert(root, 4);
	// insert(root, 5);
	// insert(root, NULL);
	// insert(root, NULL);
    // insert(root, NULL);
	// insert(root, NULL);
	// insert(root, 6);
	// insert(root, 7);

    cout << endl;
    cout << "Euler tour traversal: ";
    // traversal(root);

    printEulerTour(root);  
    precompute_lca();

    // print sparse table array B
    cout << "Array B: " << endl;
    // int row_for_B = array_log[block_size] - 1;

    // get query in B in O(1) time
    array_B = st[0];
    for (int j = 0; j < array_B.size(); ++j) {
        cout << array_B[j] << ' ';
    }
    cout << endl;

    // print out array C
    cout << "Array C: " << endl;
    for (int j = 0; j < array_C.size(); ++j) {
        cout << array_C[j] << ' ';
    }
    cout << endl << endl;

    // TEST: get min value index in block 5 and 6
    cout << "Test: Min value index from block 5 to 6: " << st[array_log[6-5]+1][5] << endl;
    
    cout << "Test: Min value index from block 2 to 7: " << st[array_log[7-2]+1][2] << endl;
}

