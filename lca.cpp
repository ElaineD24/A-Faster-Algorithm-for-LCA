#include <cassert>
#include <vector>

using namespace std;

#include "btree.h"


vector<int> height;
vector<int> first_visit; 
int block_size, block_cnt, nodes_count;
int MAX = 10000;
vector<int> euler_tour;
vector<int> array_log;
vector<vector<int> > st;
vector<int> array_B;
vector<int> array_C;
vector<vector<vector<int> > > blocks;
vector<int> block_bit;

void eulerTree(struct Node* root, int h) { 
    // store current node's data 
    height.push_back(h);
    euler_tour.push_back(root->data);
    nodes_count ++;
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
    first_visit.assign(MAX, -1);  
    eulerTree(root, 0); 

    for (int i = 0; i < euler_tour.size(); i++) 
        cout << euler_tour[i] << " "; 
    cout << endl << endl << "Height Array L(A): ";
    for (int i = 0; i < height.size(); i++) 
        cout << height[i] << " "; 
    cout << endl << endl << "First_visit Array R: ";    
    for (int i = 0; i < nodes_count; i++) 
        cout << first_visit[i] << " "; 
    cout << endl << endl;
} 


int min_by_height(int i, int j) {

    return height[i] <= height[j] ? i : j;
}

void build_sparse_table(int euler_size){
    
    // precompute minimum of each block and build sparse table
    st.assign(array_log[block_cnt] + 1, vector<int>(block_cnt));
    // first row of the sparse table, divide by the block size
    for (int i = 0, j = 0, b = 0; i < euler_size; i++, j++) {
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

void compute_all_block_bit_nums(int euler_size){
    // precompute bit mask for each block
    block_bit.assign(block_cnt, 0);
    for (int i = 0, j = 0, b = 0; i < euler_size; i++, j++) {
        if (j == block_size)
            j = 0, b++;
        if (j > 0 && (i >= euler_size || min_by_height(i - 1, i) == i - 1))
            block_bit[b] += 1 << (j - 1);
    }

    cout << "Block Bit array: " << endl;
    // print sparse table
    for (int i = 0; i < block_bit.size(); ++i) {
        cout << block_bit[i] << ' ';
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
    build_sparse_table(m);

    compute_all_block_bit_nums(m);

    // precompute RMQ for each unique block
    // each num can be normalized to 0 or 1, so 2^(block size - 1)
    int num_possible_blocks = 1 << (block_size - 1);
    blocks.resize(num_possible_blocks);
    // for each block
    for (int b = 0; b < block_cnt; b++) {
        // get bit string for this block
        int bit_num = block_bit[b];
        // if this is a new block (which hasn't been computed before), do the computation
        // otherwise, go to the next block and check
        if (!blocks[bit_num].empty())
            continue;
        // compute for all n choose 2 combinations
        blocks[bit_num].assign(block_size, vector<int>(block_size));
        // left index
        for (int l = 0; l < block_size; l++) {
            blocks[bit_num][l][l] = l;
            // right index, increase by 1 each time to cover all combinations
            for (int r = l + 1; r < block_size; r++) {
                blocks[bit_num][l][r] = blocks[bit_num][l][r - 1];
                if (b * block_size + r < m)
                    // check if current min is smaller or not
                    // "- b * block_size" to match the index inside the block
                    blocks[bit_num][l][r] = min_by_height(b * block_size + blocks[bit_num][l][r], 
                            b * block_size + r) - b * block_size;
            }
        }
    }

}


int lca_in_block(int b, int l, int r) {
    // block_bit[b]: unique bit string, eg: 110 -> 6
    // if it is 2nd block, block size is 4, the min in this block from l to r is index 3 (in this block)
    // then the return index should be 3 + 2 * 4
    return blocks[block_bit[b]][l][r] + b * block_size;
}

int lca(int u, int v) {
    int l = first_visit[u];
    int r = first_visit[v];
    if (l > r)
        swap(l, r);
    // print l and r
    // cout << "l: " << l << endl;
    // cout << "r: " << r << endl;

    int block_l = array_C[l];
    int block_r = array_C[r];
    // print block l and block r
    // cout << "Block l: " << block_l << endl;
    // cout << "Block r: " << block_r << endl;

    // if u and v are in the same block
    if (block_l == block_r)
        // min in the block which contains both u and v, starting from u to v (or v to u, whichever is smaller)
        return euler_tour[lca_in_block(block_l, l % block_size, r % block_size)];
    
    // index of the min in the block which contains u, starting from u to the end of this block
    int min1_in_block = lca_in_block(block_l, l % block_size, block_size - 1);
    // index of the min in the block which contains v, starting from the beginning of this block to v
    int min2_in_block = lca_in_block(block_r, 0, r % block_size);
    // choose the smaller one
    int ans = min_by_height(min1_in_block, min2_in_block);

    // print ans1 ans2 and ans
    // cout << "Ans1: " << min1_in_block << endl;
    // cout << "Ans2:  " << min2_in_block << endl;
    // cout << "Ans:  " << ans << endl;

    // if there are gaps (blocks) between block_l and block_r (blocks which contain u and v)
    if (block_l + 1 < block_r) {
        // compute log of (number of blocks between block_l and block_r), exclusively
        // to compute which row we should use to look up in sparse table
        int b = array_log[block_r - block_l - 1];
        // cout << "b: " << b << endl;

        // look up in the sparse table and get the min among the blocks starting from block_l + 1
        // to 2^(b-1) more blocks
        int min1_blocks = st[b][block_l+1];
        // cout << "min1_block: " << min1_blocks << endl;

        // look up in the sparse table and get the min among the blocks starting from block_r - 2^b
        // to 2^(b-1) more blocks
        int min2_blocks = st[b][block_r - (1 << b)];
        // cout << "min2_block: " << min2_blocks << endl;
       
        ans = min_by_height(ans, min_by_height(min1_blocks, min2_blocks));
        // cout << "ans: " << ans << endl;

        // ans = min_by_height(ans, ans3);

    }
    return euler_tour[ans];
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
    // cout << "Test: Min value index from block 5 to 6: " << st[array_log[6-5]+1][5] << endl;
    
    // cout << "Test: Min value index from block 2 to 7: " << st[array_log[7-2]+1][2] << endl;

    // check for node 4 and 5 (u5 and u6 in the book)
    int result = lca(root->right->right->data, root->right->left->left->data);
    cout << "Result (should be 2): " << result << endl;

    // check for node 0 and 5 (u1 and u6 in the book)
    result = lca(root->data, root->right->left->left->data);
    cout << "Result (should be 0): " << result << endl;

    // check for node 6 and 7 (u7 and u8 in the book)
    result = lca(root->right->left->right->data, root->left->left->data);
    cout << "Result (should be 0): " << result << endl;
}

