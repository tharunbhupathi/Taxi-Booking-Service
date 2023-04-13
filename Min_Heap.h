#include <bits/stdc++.h>
#include "RBT.h"
using namespace std;

// A MinHeap class that contains all methods required to do insert, delete, search, heapify etc
class MinHeap
{
private:
	vector<Node*> harr; 

	int heap_size;

	void swap(Node *x, Node *y);

	int parent(int i) { return (i-1)/2; } // Returns the parent index for a given node index

	int left(int i) { return (2*i + 1); } // Returns the left child index for a given node index

	int right(int i) { return (2*i + 2); } // Returns the right child index for a given node index

	bool is_Heap_Cond_Fail(int i, int j);

	bool insert(Node* node);

	void heapifyDown(Node* );

public:

	MinHeap();

	void heapifyUP(int i);

	bool insertRide(Node* node);

	void deleteRide(int i);

	int deleteMinCostRide();

	Node* getMin() { return harr[0]; } // Returns root of the MinHeap which is the ride with min cost.

	string print();

};
