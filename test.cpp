#include <cstdio>
#include <ctime>
using namespace std;

#include "btree.h"
#include "lca.h"

int main() {
    cout << endl << "======================================================================================" << endl;
    cout << "*** select two nodes in left subtree and right subtree of node root->left, should return root->left ***" << endl << endl;
    struct lca* lca_1 = new lca();
    test_1(lca_1, 1000);
    struct lca* lca_2 = new lca();
    test_1(lca_2, 10000);
    struct lca* lca_3 = new lca();
    test_1(lca_3, 100000);

    cout << "=======================================================================================" << endl;
    cout << "*** select one node in the subtree of root->left, should return root->left ***" << endl << endl;
    struct lca* lca_4 = new lca();
    test_2(lca_4, 1000);
    struct lca* lca_5 = new lca();
    test_2(lca_5, 10000);
    struct lca* lca_6 = new lca();
    test_2(lca_6, 100000);

    cout << "=======================================================================================" << endl;
    cout << "*** Right skewed tree: select one node in the subtree of root->right, should return root->right ***" << endl << endl;
    struct lca* lca_7 = new lca();
    test_right_skewed(lca_7, 1000);
    struct lca* lca_8 = new lca();
    test_right_skewed(lca_8, 10000);
    struct lca* lca_9 = new lca();
    test_right_skewed(lca_9, 100000);

    cout << "=======================================================================================" << endl;
    cout << "*** 'Balanced binary tree': select two nodes in left subtree and right subtree of node root->left, should return root->left ***" << endl << endl;
    struct lca* lca_10 = new lca();
    test_balanced_btree(lca_10, 1000);
    struct lca* lca_11 = new lca();
    test_balanced_btree(lca_11, 10000);
    struct lca* lca_12 = new lca();
    test_balanced_btree(lca_12, 100000);
}