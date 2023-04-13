
// Node common to both Red Black Tree and Min Heap
struct Node {
  int ride;
  int cost;
  int dur;
  Node* parent; // parent node pointer
  Node* left; // left child node pointer
  Node* right; //right child node pointer
  int color; // 0:black 1:red
  int heap_index; // This parameter is related to the MinHeap 
};