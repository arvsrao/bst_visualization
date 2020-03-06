#ifndef BSTNODE_H
#define BSTNODE_H

#include <iostream>

struct BstNode {

  int value, x, y, min, max;
  BstNode *left;
  BstNode *right;

  BstNode(int _value);
  BstNode(int _value, int _x, int _y);
  BstNode(int _value, BstNode *_left, BstNode *_right);
  BstNode(int _value, int _x, int _y, BstNode *_left, BstNode *_right);

  int getValue();
  int getMin();
  int getMax();
  int getX();
  int getY();
  virtual BstNode *getLeft();
  virtual BstNode *getRight();

  void setMin(int _min);
  void setMax(int _max);
  void setValue(int _value);
  void setX(int _x);
  void setY(int _y);

  void insert(int val);
  static void updateCoordinates(BstNode *node, int width);
  void maintainInvariant(int delta);
  void printInOrder();
  virtual ~BstNode();
};

#endif // BSTNODE_H
