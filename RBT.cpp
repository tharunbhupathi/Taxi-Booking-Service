#include <bits/stdc++.h>
#include <string>
#include<vector>
#include "Min_Heap.h"
using namespace std;

  RedBlackTree::RedBlackTree() {
    //Ext_Black is external dummy black node.
    // When a new RBT is initiated, only external black node is created
    Ext_Black = new Node;
    Ext_Black->color = 0; // black
    Ext_Black->left = nullptr;
    Ext_Black->right = nullptr;
    root = Ext_Black;
  }
  
  // This method returns the root of the Red Black Tree.
  Node* RedBlackTree::getRoot() {
    return this->root;
  }

  // Inserting a node 
  Node* RedBlackTree::insert(int ride_no, int ride_cost, int ride_dur) {
    Node* node = new Node;
    node->parent = nullptr;
    node->ride = ride_no;
    node->cost = ride_cost;
    node->dur = ride_dur;
    node->left = Ext_Black;
    node->right = Ext_Black;
    node->color = 1;

    Node* y = nullptr;
    Node* x = this->root;

  // This while loop finds the parent node to which the new node has to be inserted
    while (x != Ext_Black) {
      y = x;
      if (node->ride < x->ride) {
        x = x->left;
      } else {
        x = x->right;
      }
    }

// This code finds whether new node has to be inserted at left or right of the parent node and inserts it.
    node->parent = y;
    if (y == nullptr) {
      root = node;
    } else if (node->ride < y->ride) {
      y->left = node;
    } else {
      y->right = node;
    }

    if (node->parent == nullptr) {
      node->color = 0;
      return node;
    }

    if (node->parent->parent == nullptr) {
      return node;
    }

// Calls the RBT Balance function to balance the RBT tree after new node insertion
    Balance_After_Insert(node);
    return node;
  }

  // For balancing the tree after insert Operation
  void RedBlackTree::Balance_After_Insert(Node* k) {
    Node* u;
    while (k->parent->color == 1) { 
      if (k->parent == k->parent->parent->right) { // X = R (Right) in XYz rule.
        u = k->parent->parent->left;
        if (u->color == 1) { //z = r (red) in XYz rule. When z is r, irrespective of XY, color swap has to be done until the node and its parent are of different color.
          u->color = 0;
          k->parent->color = 0;
          k->parent->parent->color = 1;
          k = k->parent->parent;
        } 
        else { //z=b (black)
          if (k == k->parent->left) { //Y = L (Left) in XYz rule.
            k = k->parent;
            Rotate_Right(k); // As XYz = RLb, we do RL rotate i.e First Right Rotation
          }
          k->parent->color = 0;
          k->parent->parent->color = 1;
          Rotate_Left(k->parent->parent); // As XYz = RLb, we do RL rotate. We do Left Rotation after Right Rotation.
        }
      } 
      else { // X = L (Left) in XYz rule.
        u = k->parent->parent->right;

        if (u->color == 1) { //z = r (red) in XYz rule. When z is r, irrespective of XY, color swap has to be done until the node and its parent are of different color.
          u->color = 0;
          k->parent->color = 0;
          k->parent->parent->color = 1;
          k = k->parent->parent;
        } 
        else { //z=b (black)
          if (k == k->parent->right) { //Y = R (Right) in XYz rule.
            k = k->parent;
            Rotate_Left(k); // As XYz = LRb, we do LR rotate i.e First Left Rotation
          }
          k->parent->color = 0;
          k->parent->parent->color = 1;
          Rotate_Right(k->parent->parent); // As XYz = LRb, we do LR rotate. We do Right Rotation after Left Rotation.
        }
      }
      if (k == root) {
        break;
      }
    }
    root->color = 0; // Finally, make the root node black
  }

// This method deletes the node with given ride number
  void RedBlackTree::Delete(Node* node, int ride_no) {
    Node* z = Ext_Black;
    Node* x, *y;

// This while loop finds the node with given ride number to delete
    while (node != Ext_Black) {
      if (node->ride == ride_no) {
        z = node;
      }
      if (node->ride <= ride_no) {
        node = node->right;
      } else {
        node = node->left;
      }
    }

    if (z == Ext_Black) {
      return;
    }

    y = z;
    int y_original_color = y->color;

// The following code replaces the node to be deleted with the 
    if (z->left == Ext_Black) { //If the deleting node has no left child ( zero degree or one degree node), then connect the right child to the deleting node's parent
      x = z->right;
      replace(z, z->right); //Replace the node to be deleted with its right child
    } 
    else if (z->right == Ext_Black) { //If the deleting node has no right child (  one degree node), then connect the left child to the deleting node's parent
      x = z->left;
      replace(z, z->left); //Replace the node to be deleted with its left child
    } 
    else { 
      y = minimum(z->right); //If the deleting node has two children (two degree node), then find the lowest node from the right sub tree
      y_original_color = y->color; 
      x = y->right;
      if (y->parent == z) {
        x->parent = y;
      } 
      else {
        replace(y, y->right); // Replace the smallest node with its right child so that smallest node can be replaced to deleting node in the next step
        y->right = z->right;
        y->right->parent = y;
      }
      replace(z, y); // Replace the deleting node with the found smallest node from the right sub tree.
      y->left = z->left;
      y->left->parent = y;
      y->color = z->color;
    }
    delete z;
    if (y_original_color == 0) { // If the deleted node is red. Do nothing. 
      Balance_After_Delete(x); // Balance the RBT after deletion if the deleted node is black
    }
  }

    // For balancing the tree after deletion
  void RedBlackTree::Balance_After_Delete(Node* x) {
    Node* s;
    // This while loop runs until the current node colour is red.
    // The balance follows the XCn rule. 
    while (x != root && x->color == 0) {
      if (x == x->parent->left) {
        s = x->parent->right;
        // Perform color flip and left rotation ff the parent's right child color is red, .
        if (s->color == 1) {
          s->color = 0;
          x->parent->color = 1;
          Rotate_Left(x->parent);
          s = x->parent->right;
        }
        // If both children of the sibling are black, recolor and move up to the parent.
        if (s->left->color == 0 && s->right->color == 0) {
          s->color = 1;
          x = x->parent;
        } 
        else {
          // If the right child of the sibling is black, perform recoloring and rotation.
          if (s->right->color == 0) {
            s->left->color = 0;
            s->color = 1;
            Rotate_Right(s);
            s = x->parent->right;
          }
          // Perform recoloring and rotation to restore balance.
          s->color = x->parent->color;
          x->parent->color = 0;
          s->right->color = 0;
          Rotate_Left(x->parent);
          x = root;
        }
      } else {
        s = x->parent->left;
        // If the sibling's color is red, perform recoloring and rotation.
        if (s->color == 1) {
          s->color = 0;
          x->parent->color = 1;
          Rotate_Right(x->parent);
          s = x->parent->left;
        }
        // If both children of the sibling are black, recolor and move up to the parent.
        if (s->right->color == 0 && s->right->color == 0) {
          s->color = 1;
          x = x->parent;
        } else {
        
        // If the left child of the sibling is black, perform recoloring and rotation.
          if (s->left->color == 0) {
            s->right->color = 0;
            s->color = 1;
            Rotate_Left(s);
            s = x->parent->left;
          }
          // Perform recoloring and rotation to restore balance.
          s->color = x->parent->color;
          x->parent->color = 0;
          s->left->color = 0;
          Rotate_Right(x->parent);
          x = root;
        }
      }
    }
    x->color = 0;
  }

// Function returns the minimum element in the sub tree whose root is node
  Node* RedBlackTree::minimum(Node* node) {
    while (node->left != Ext_Black) {
      node = node->left;
    }
    return node;
  }    

// Function that replaces node u with node v in the Red Black Tree. 
// This is used in delete case  where node has to be replaced with the min element in the right subtree 
  void RedBlackTree::replace(Node* u, Node* v) {
    if (u->parent == nullptr) {
      root = v;
    } else if (u == u->parent->left) {
      u->parent->left = v;
    } else {
      u->parent->right = v;
    }
    v->parent = u->parent;
  }

 // This method checks if a ride with given number exists in the tree and returns the corresponding node.
  Node* RedBlackTree::search(Node* node, int ride_no) {
    if (node == Ext_Black || ride_no == node->ride) {
      return node;
    }
    if (ride_no < node->ride) { // Enters into the left sub tree only if the required ride is less than the root of that sub tree.
      return search(node->left, ride_no);
    }
    return search(node->right, ride_no); // Enters into the right sub tree only if the required ride is greater than the root of that sub tree.
  }

 // This method updates the ans vector with all the rides in between ride 1 and ride 2 .
  void RedBlackTree::search(Node* trav, int ride1, int ride2, vector<string> &ans)
{
    /* base case */
    if(trav == Ext_Black)
      return;

    if(trav->ride > ride1) // Enters into the left sub tree only if the root of that sub tree is greater than the ride1.
      search(trav->left,ride1,ride2,ans);

    if((ride1 <= trav->ride ) && (ride2 >= trav->ride ) ) // If the node value is in between ride 1 and ride 2, then add it into the ans vector
      ans.push_back("("+to_string(trav->ride)+","+to_string(trav->cost)+","+to_string(trav->dur)+")");

    if(trav->ride < ride2) // Enters into the right sub tree only if the root of that sub tree is less than the ride2.
	    search(trav->right,ride1,ride2,ans);
    
}
// This method performs the Left Rotation around the given node
  void RedBlackTree::Rotate_Left(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != Ext_Black) {
      y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      this->root = y;
    } else if (x == x->parent->left) {
      x->parent->left = y;
    } else {
      x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
  }

// This method performs the Right Rotation around the given node
  void RedBlackTree::Rotate_Right(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right != Ext_Black) {
      y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      this->root = y;
    } else if (x == x->parent->right) {
      x->parent->right = y;
    } else {
      x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
  }

Node* RedBlackTree::insertRide(int ride_no, int ride_cost, int ride_dur) {
    return insert(ride_no,ride_cost,ride_dur);
  }

void RedBlackTree::deleteRide(int ride_no) {
    Delete(this->root, ride_no);
  }

Node* RedBlackTree::searchRide(int ride_no) {
    return search(this->root, ride_no);
  }

void RedBlackTree::searchRide(int ride1, int ride2, vector<string> &ans) {
     search(this->root, ride1, ride2, ans);
  }

  Node* RedBlackTree::getExt_Black() {
  return this->Ext_Black;
  }
