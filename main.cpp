#include <iostream>
#include <string>
#include "data_structures.h"
#include <vector>
#include <chrono>
#include <fstream>

using namespace std;

int main(){

  IntervalTree RedBlackT;
  Interval i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12;

  i1._low = 16;
  i1._high = 21;
  i2._low = 8;
  i2._high = 9;
  i3._low = 25;
  i3._high = 30;
  i4._low = 17;
  i4._high = 19;
  i5._low = 26;
  i5._high = 26;
  i6._low = 19;
  i6._high = 20;
  i7._low = 15;
  i7._high = 23;
  i8._low = 5;
  i8._high = 8;
  i9._low = 6;
  i9._high = 10;
  i10._low = 0;
  i10._high = 3;
  i11._low = 20;
  i11._high = 21;
  i12._low = 31;
  i12._high = 32;

  RedBlackT.insert_node(i1);
  RedBlackT.insert_node(i2);
  RedBlackT.insert_node(i3);
  RedBlackT.insert_node(i4);
  RedBlackT.insert_node(i5);
  RedBlackT.insert_node(i6);
  RedBlackT.insert_node(i7);
  RedBlackT.insert_node(i8);
  RedBlackT.insert_node(i9);
  RedBlackT.insert_node(i10);
  RedBlackT.insert_node(i11);
//RedBlackT.insert_node(i12);

  cout << "Before deleting node:" << endl;
  RedBlackT.printTree();

  RedBlackT.delete_node(i1);
  cout << "After deleting node:" << endl;
  RedBlackT.printTree();

  Node *node;
  node = RedBlackT.interval_overlap_search(i12);
  if(node != nullptr)  cout << endl << "The first interval that overlaps " << "[" << i12._low << " , "
        << i12._high << "] is: [" << node->_interval._low << " , " << node->_interval._high << "]" << endl;
  else  cout << "Interval that overlaps " << "[" << i12._low << " , " << i12._high << "] not found!" << endl;

/*  //Calcolo tempo di ricerca:

  IntervalTree Tree;
  Interval interval,interval_target0,interval_target1;
  vector<Interval> data_interval;
  vector<double> data_time;
  Node* node;
  int n_nodes = 50;
  int step = 5e5;
  int dim = n_nodes/step;

  interval_target0._high = 1000;
  interval_target0._low = 1000;
  interval_target1._high = -1;
  interval_target1._low = -1;

  for(int i=0; i<n_nodes; i++){
      interval._low = i;
      interval._high = i+1;
      Tree.insert_node(interval);
      data_interval.push_back(interval);
      auto start_time = chrono::high_resolution_clock::now();
      for (int k = 0; k < step; k++){
         node = Tree.interval_overlap_search(interval_target0);
         node = Tree.interval_overlap_search(interval_target1);
      }
      auto end_time = chrono::high_resolution_clock::now();
      auto time = end_time - start_time;
      //std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time-start_time).count() << endl;
      long double t = time/chrono::nanoseconds(1);
      data_time.push_back(t);
  }
  ofstream outfile;
  outfile.open("Results.dat");
  for (int i=0; i<n_nodes; i++) outfile << data_time[i] << endl;
  outfile.close();
*/

return 0;
}
