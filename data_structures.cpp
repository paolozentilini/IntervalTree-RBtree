#include "data_structures.h"

using namespace std;

IntervalTree::IntervalTree(){
    _tnil = new Node;                //_tnil represents the null pointer T.nil (no key)
    _tnil->_right = nullptr;
    _tnil->_left = nullptr;
    _tnil->_color = 1;
    _root = _tnil;
}

IntervalTree::~IntervalTree(){}


Node* IntervalTree::interval_overlap_search(Interval i){
  Node* x = this->_root;
  while (x != _tnil && overlap(i, x->_interval)==0){
    if (x->_left != _tnil && x->_left->_max >= i._low) x = x->_left;
    else x = x->_right;
  }
  if (x == _tnil) return nullptr;
  else return x;
}


void IntervalTree::right_rotate(Node* x){
  Node* y = x->_left;
  x->_left = y->_right;
  if ( y->_right != _tnil )  y->_right->_parent = x;
  y->_parent = x->_parent;
  if ( x->_parent == nullptr )  this->_root = y;
  else if ( x == x->_parent->_right )  x->_parent->_right = y;
  else  x->_parent->_left = y;
  y->_right = x;
  x->_parent = y;
  x->_max = maximum(x);
  y->_max = maximum(y);
}


void IntervalTree::left_rotate(Node* x){
  Node* y = x->_right;
  x->_right = y->_left;
  if ( y->_left != _tnil )  y->_left->_parent = x;
  y->_parent = x->_parent;
  if ( x->_parent == nullptr )  this->_root = y;
  else if ( x == x->_parent->_left )  x->_parent->_left = y;
  else  x->_parent->_right = y;
  y->_left = x;
  x->_parent = y;
  x->_max = maximum(x);
  y->_max = maximum(y);
}


void IntervalTree::insert_node(Interval i){
  Node* z = new Node;
  z->_interval = i;
  z->_key = i._low;
  z->_left = _tnil;
  z->_right = _tnil;
  Node* y = nullptr;
  Node* x = this->_root;
  while (x != _tnil) {
      y = x;
      if (z->_key <= x->_key) x = x->_left;
      else x = x->_right;
  }
  z->_parent = y;
  if (y == nullptr)  {
      this->_root = z;
      z->_color = 1;
  }  else if  (z->_key <= y->_key)  y->_left = z;
  else  y->_right = z;

  if (z->_parent == nullptr || z->_parent->_parent == nullptr) return;

  insert_fixup(z);

  while (z->_parent != _tnil && z->_parent != nullptr){
    z->_max = maximum(z);
    z = z->_parent;
  }
  if (z == _root) z->_max = maximum(z);
  this->_root->_parent = _tnil;
}


void IntervalTree::insert_fixup(Node* z){
  Node* y;
  while (z->_parent->_color == 0) {
      if (z->_parent == z->_parent->_parent->_left) {
          y = z->_parent->_parent->_right;
          if (y->_color == 0) {
              z->_parent->_color = 1;
              y->_color = 1;
              z->_parent->_parent->_color = 0;
              z = z->_parent->_parent;
          }else{
              if (z == z->_parent->_right){
                  z = z->_parent;
                  left_rotate(z);
              }
              z->_parent->_color = 1;
              z->_parent->_parent->_color = 0;
              right_rotate(z->_parent->_parent);
          }
      }else{
          y = z->_parent->_parent->_left;
          if (y->_color == 0) {
              z->_parent->_color = 1;
              y->_color = 1;
              z->_parent->_parent->_color = 0;
              z = z->_parent->_parent;
          }else{
              if (z == z->_parent->_left){
                  z = z->_parent;
                  right_rotate(z);
              }
              z->_parent->_color = 1;
              z->_parent->_parent->_color = 0;
              left_rotate(z->_parent->_parent);
          }
      }
      if (z == this->_root)  break;
  }
  this->_root->_color = 1;
}

void IntervalTree::print(Node* z, string indent, bool last) {
  if (z != _tnil) {
      cout << indent;
      if (last) {
        cout << "R----";
        indent += "   ";
      } else {
        cout << "L----";
        indent += "|  ";
      }
      string sColor = z->_color ? "BLACK" : "RED";
      cout << "[" << z->_interval._low << " , " << z->_interval._high << "]" << " " << sColor << " " << z->_max << endl;
      print(z->_left, indent, 0);
      print(z->_right, indent, 1);
  }
}


void IntervalTree::printTree() {
    if (_root) print(this->_root, "   ", 1);
}

bool overlap(Interval i1, Interval i2){ //i1.low <= i2.high && i2.low <= i1.high
  if (i1._low <= i2._high && i2._low <= i1._high) return true;
  else return false;
}

double IntervalTree::maximum(Node* z){
  double h = z->_interval._high;
  if (z->_left == _tnil && z->_right == _tnil) return h;
  else{
    if (z->_left == _tnil) return max(z->_right->_max,h);
    if (z->_right == _tnil) return max(z->_left->_max,h);
    return max(z->_right->_max,z->_left->_max,h);
  }
}

double max(double a,double b,double c){
  if (a>=b){
    if (a>=c) return a;
    else return c;
  }else{
    if (b>=c) return b;
    else return c;
  }
}

//////////////////////////////////////////////////////////////////////////////////

Node* IntervalTree::search(Interval i){
  double key = i._low;
  double high = i._high;
  Node* z = _tnil;
  Node* node = this->_root;
  while (node != _tnil) {
    if (node->_key == key && node->_interval._high == high) z = node;
    if (node->_key <= key) node = node->_right;
    else node = node->_left;
  }
  if (z == _tnil) cout << "\n" << "Interval [" << i._low << "," << i._high << "] not found in the tree!" << "\n" << endl;
  return z;
}


void IntervalTree::rb_transplant(Node* u, Node* v){
    if (u->_parent == _tnil) this->_root = v;
    else if (u == u->_parent->_left) u->_parent->_left = v;
    else u->_parent->_right = v;
    v->_parent = u->_parent;
}


void IntervalTree::delete_node(Interval i) {
    Node *x, *y, *z;
    z = search(i);
    if (z==_tnil) return;
    y = z;
    bool y_original_color = y->_color;
    if (z->_left == _tnil) {
      x = z->_right;
      rb_transplant(z, z->_right);
    } else if (z->_right == _tnil) {
      x = z->_left;
      rb_transplant(z, z->_left);
    } else {
      y = minimum(z->_right);
      y_original_color = y->_color;
      x = y->_right;
      if (y->_parent == z) x->_parent = y;
      else {
        rb_transplant(y, y->_right);
        y->_right = z->_right;
        y->_right->_parent = y;
      }
      rb_transplant(z, y);
      y->_left = z->_left;
      y->_left->_parent = y;
      y->_color = z->_color;
    }
    if (y_original_color == 1) delete_fixup(x);
    this->_root->_max = maximum(this->_root);
}


void IntervalTree::delete_fixup(Node* x){
    Node* w;
    while (x != this->_root && x->_color == 1) {
      if (x == x->_parent->_left) {
          w = x->_parent->_right;
          if (w->_color == 0) {
              w->_color = 1;
              x->_parent->_color = 0;
              left_rotate(x->_parent);
              w = x->_parent->_right;
          }
          if (w->_left->_color == 1 && w->_right->_color == 1) {
              w->_color = 0;
              x = x->_parent;
          }else{
              if (w->_right->_color == 1) {
                  w->_left->_color = 1;
                  w->_color = 0;
                  right_rotate(w);
                  w = x->_parent->_right;
              }
              w->_color = x->_parent->_color;
              x->_parent->_color = 1;
              w->_right->_color = 1;
              left_rotate(x->_parent);
              x = this->_root;
              }
      }else{
          w = x->_parent->_left;
          if (w->_color == 0) {
              w->_color = 1;
              x->_parent->_color = 0;
              right_rotate(x->_parent);
              w = x->_parent->_left;
          }
          if (w->_right->_color == 1 && w->_right->_color == 1) {
              w->_color = 0;
              x = x->_parent;
          }else{
              if (w->_left->_color == 1) {
                  w->_right->_color = 1;
                  w->_color = 0;
                  left_rotate(w);
                  w = x->_parent->_left;
              }
              w->_color = x->_parent->_color;
              x->_parent->_color = 1;
              w->_left->_color = 1;
              right_rotate(x->_parent);
              x = this->_root;
          }
      }
  }
  x->_color = 1;
  x->_max = maximum(x);
}


Node* IntervalTree::minimum(Node* x) {
    while (x->_left != _tnil) x = x->_left;
    return x;
}
