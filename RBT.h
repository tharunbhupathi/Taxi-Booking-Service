#include <bits/stdc++.h>
#include "Node.h"
using namespace std;


class RedBlackTree {
  
private:
  Node* root; // This is root node of the Red Black Tree.

  Node* Ext_Black; // Ext_Black is the external Black dummy node.

  Node* getRoot();

  Node* insert(int ride_no, int ride_cost, int ride_dur);

  void Balance_After_Insert(Node* k);

  void Delete(Node* node, int ride_no);

  void Balance_After_Delete(Node* x);

  Node* minimum(Node* node);

  void replace(Node* u, Node* v);

  Node* search(Node* node, int ride_no);

  void search(Node* trav, int ride1, int ride2, vector<string> &ans);

  void Rotate_Left(Node* x);

  void Rotate_Right(Node* x);

public:

  Node* insertRide(int ride_no, int ride_cost, int ride_dur);

  void deleteRide(int ride_no);

  Node* searchRide(int ride_no);

  void searchRide(int ride1, int ride2, vector<string> &ans);

  RedBlackTree();

  Node* getExt_Black();

};
