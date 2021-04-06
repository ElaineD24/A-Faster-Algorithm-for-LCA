# A-Faster-Algorithm-for-LCA

To run the test file:
  g++ -std=c++11 btree.cpp lca.cpp test.cpp -o main.out && ./main.out
  
To run the sample_usage file:
  g++ -std=c++11 btree.cpp lca.cpp sample_usage.cpp -o main.out && ./main.out
  
To use this algorithm
	Include btree.h and lca.h in your file
	Generate a new LCA struct
		Eg: struct lca* your_lca = new lca();
	Command for preprocessing:
		Input: 
      struct lca* lca
      struct Node* root
		Eg: precompute_lca(your_lca, root);
	Command for answering the queries:
		Input: 
      struct lca* lca
      int value_of_node_u
      int value_of_node_v
    Eg: int result = get_lca(your_lca, node_u->data, node_v->data);
    
Language:
  C++
