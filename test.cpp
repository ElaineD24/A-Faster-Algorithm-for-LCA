#include <cstdio>
#include <ctime>
using namespace std;

#include "btree.h"
#include "lca.h"

int main() {
    cout << endl << "======================================================================================" << endl;
    cout << "*** select two nodes in left subtree and right subtree of node root->left, should return root->left ***" << endl << endl;
    struct lca* lca_1 = new lca();
    cout << "Testing on 1000 nodes" << endl;
    test_1(lca_1, 500);
    struct lca* lca_2 = new lca();
    cout << "Testing on 10000 nodes" << endl;
    test_1(lca_2, 5000);
    struct lca* lca_3 = new lca();
    cout << "Testing on 100000 nodes" << endl;
    test_1(lca_3, 50000);

    // cout << "=======================================================================================" << endl;
    // cout << "*** select one node in the subtree of root->left, should return root->left ***" << endl << endl;
    // struct lca* lca_4 = new lca();
    // cout << "Testing on 1000 nodes" << endl;
    // test_2(lca_4, 500);
    // struct lca* lca_5 = new lca();
    // cout << "Testing on 10000 nodes" << endl;
    // test_2(lca_5, 5000);
    // struct lca* lca_6 = new lca();
    // cout << "Testing on 100000 nodes" << endl;
    // test_2(lca_6, 50000);

    cout << "=======================================================================================" << endl;
    cout << "*** Right skewed tree: select one node in the subtree of root->right, should return root->right ***" << endl << endl;
    struct lca* lca_7 = new lca();
    cout << "Testing on 1000 nodes" << endl;
    test_right_skewed(lca_7, 500);
    struct lca* lca_8 = new lca();
    cout << "Testing on 10000 nodes" << endl;
    test_right_skewed(lca_8, 5000);
    struct lca* lca_9 = new lca();
    cout << "Testing on 100000 nodes" << endl;
    test_right_skewed(lca_9, 50000);

    cout << "=======================================================================================" << endl;
    cout << "*** 'Balanced binary tree': select two nodes in left subtree and right subtree of node root->left, should return root->left ***" << endl << endl;
    struct lca* lca_10 = new lca();
    cout << "Testing on 1000 nodes" << endl;
    test_balanced_btree(lca_10, 1000);
    struct lca* lca_11 = new lca();
    cout << "Testing on 10000 nodes" << endl;
    test_balanced_btree(lca_11, 10000);
    struct lca* lca_12 = new lca();
    cout << "Testing on 100000 nodes" << endl;
    test_balanced_btree(lca_12, 100000);
}