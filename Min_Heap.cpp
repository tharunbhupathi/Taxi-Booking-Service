#include <bits/stdc++.h>
#include <string>
#include<vector>
#include "Min_Heap.h"
using namespace std;

MinHeap::MinHeap()
{
	heap_size = 0;
}

// Swaps to nodes of the heap array
// Here, the heap_index variable also gets swapped.
void MinHeap::swap(Node *x, Node *y)
{
    int temp = x->heap_index;
    x->heap_index = y->heap_index;
    y->heap_index = temp;
	harr[x->heap_index]=x;
	harr[y->heap_index]=y;
}

// function to check if two nodes fail the heap property
// conditions to satisfy heap property are child node's(j) ride cost is greater than child node ride's(i) cost. 
// If both are same then child's trip Duration is greater than parent's trip Duration
bool MinHeap::is_Heap_Cond_Fail(int i, int j){
	if((harr[i]->cost > harr[j]->cost) || ((harr[i]->cost == harr[j]->cost) && (harr[i]->dur > harr[j]->dur)))
		return true;
	else
		return false;
}

// This function inserts new node into Heap tree
bool MinHeap::insert(Node* node)
{
	// First insert the new key at the end
	heap_size++;
	int i = heap_size - 1;
    node->heap_index=i;
	harr.push_back(node);
	heapifyUP(i); // Fix the min heap property if it is violated
	return true;
}

// This function heapifies the subtree rooted at "node"
void MinHeap::heapifyDown(Node* node)
{
	int i = node->heap_index;
	int l = left(i);
	int r = right(i);
	int smallest = i;
	if (l < heap_size && !is_Heap_Cond_Fail(l,i))
		smallest = l;
	if (r < heap_size && !is_Heap_Cond_Fail(r,smallest))
		smallest = r;
	if (smallest != i)
	{
		swap(harr[i], harr[smallest]);
		heapifyDown(harr[smallest]);
	}
}

// The main method from gatorTaxi.cpp calls the insertRide which is public with respect to MinHeap class
// The insertRide method calls the insert method which is declared private
// insert method is made private so that it cannot be hampered from external.
bool MinHeap::insertRide(Node* node){
	return insert(node);
}

// This method deletes the node at given index.
// Firstly, node to be deleted is replaced with the last node in heap array
// Heapify is called to maintain the heap property
void MinHeap::deleteRide(int index)
{
	harr[index] = harr[heap_size-1];
	harr[index]->heap_index = index;
	heap_size--;
	harr.erase(harr.end()-1);
	heapifyDown(harr[0]);
}

// This method deletes the root of the min heap.
// Follows the same procedure as the above delete Ride method
int MinHeap::deleteMinCostRide()
{
	if (heap_size <= 0)
		return -1;
	Node* root = harr[0];
	if (heap_size == 1)
	{
		heap_size--;
		harr.erase (harr.end()-1);
		return root->ride;
	}
// root node is replaced with the last node from the heap array.
// Delete the last Node. Reduce the Heap Size variable.
// Perform Heapify Operation to maintain the MinHeap Property
	harr[0] = harr[heap_size-1];
	harr[0]->heap_index = 0;
	heap_size--;
	harr.erase (harr.end()-1);
	heapifyDown(harr[0]);
	return root->ride;
}

//This method heapifies the specific branch from given node at index i to the root node
void MinHeap::heapifyUP(int i){
	while (i != 0 && is_Heap_Cond_Fail(parent(i),i))
	{
	swap(harr[i], harr[parent(i)]);
	i = parent(i);
	}
}

string MinHeap::print(){
	string s ="";
	for(int i=0;i<heap_size;i++){
		s = s + "("+to_string(harr[i]->ride)+","+to_string(harr[i]->cost)+","+to_string(harr[i]->dur)+","+to_string(harr[i]->heap_index)+") ";
	}
	return s;
}