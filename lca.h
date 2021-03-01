#ifndef LCA_H    
#define LCA_H
#include <cassert>
#include <vector>
#include <iostream>
#include <random>

using namespace std;

#include "btree.h"

struct lca {
    vector<int> height;
    vector<int> first_visit; 
    int block_size, block_cnt;
    int MAX = 1000000;
    vector<int> euler_tour;
    vector<int> array_log;
    vector<vector<int> > st;
    vector<int> array_B;
    vector<int> array_C;
    vector<vector<vector<int> > > blocks;
    vector<int> block_bit;
    clock_t start;
    double duration;
    lca(){
		vector<int> height;
        vector<int> first_visit; 
        int block_size, block_cnt;
        int MAX = 10000000;
        vector<int> euler_tour;
        vector<int> array_log;
        vector<vector<int> > st;
        vector<int> array_B;
        vector<int> array_C;
        vector<vector<vector<int> > > blocks;
        vector<int> block_bit;
        clock_t start;
        double duration;
	}
};

void eulerTree(struct lca* lca, struct Node* root, int h);
int min_by_height(struct lca* lca, int i, int j);
void build_sparse_table(struct lca* lca, int euler_size);
void compute_all_block_binary_nums(struct lca* lca, int euler_size);
void compute_all_combinations(struct lca* lca, int euler_size);
void build_log_array(struct lca* lca);
void precompute_lca(struct lca* lca, struct Node* root);
int get_in_block_min(struct lca* lca, int b, int l, int r);
int get_lca(struct lca* lca, int u, int v);
double random(int range_to);
struct Node* generate(int N);
struct Node* generate_skewed_right(int N);
struct Node* generate_n_nodes_tree(int N);
struct Node* insertLevelOrder(vector<int> arr, Node* root, int i, int n);
void test_1(struct lca* lca, int k);
void test_2(struct lca* lca, int k);
void test_right_skewed(struct lca* lca, int k);
void test_balanced_btree(struct lca* lca, int k);



#endif
