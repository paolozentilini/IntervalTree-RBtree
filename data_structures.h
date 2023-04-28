#ifndef __data_structures__h__
#define __data_structures__h__

#include <string>
#include <iostream>

struct Interval{
  double _low, _high;   //Low and high represent the minimum and the maximum of the interval
};

struct Node{
  Node *_parent;        //pointer to the node parent (if exists, otherwise it represents the tree root and it will points to NIL)
  Node *_right;         //pointer to the right child node (if exists, otherwise it points to NIL)
  Node *_left;          //pointer to the left child node (if exists, otherwise it points to NIL)
  Interval _interval;   //interval stored into the node
  double _key;          //key is the value stores in the tree node
  bool _color;          //0 if the color is red, 1 if the color is black
  double _max;          //Max value of all intervals stored into subtree nodes rooted at node x
};

class IntervalTree{

  private:
    Node* _root;
    Node* _tnil;

  public:
    //Constructor and destructor:
    IntervalTree();
    ~IntervalTree();

    //Methods:
    void right_rotate(Node* node);
    void left_rotate(Node* node);
    void insert_node(Interval i);
    void insert_fixup(Node* node);
    void rb_transplant(Node* u, Node* v);
    void delete_node(Interval i);
    void delete_fixup(Node* node);
    double maximum(Node* node);
    Node* minimum(Node* node);
    Node* search(Interval i);
    Node* interval_overlap_search(Interval i);
    void print(Node* z, std::string indent, bool last);
    void printTree();

};

bool overlap(Interval, Interval);
double max(double, double, double);

#endif
