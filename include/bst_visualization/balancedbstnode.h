#ifndef BALANCED_BSTNODE_H
#define BALANCED_BSTNODE_H

struct BalancedBstNode : BstNode {
  enum Color { RED, BLACK };
  Color color;

  BalancedBstNode *balanced_left;
  BalancedBstNode *balanced_right;

  BalancedBstNode(int _value);
  BalancedBstNode(Color _color, int _value);
  BalancedBstNode(Color _color, int _value, int _x, int _y);

  bool isRed();
  bool isBlack();

  bool isLeftRed();
  bool isLeftLeftRed();
  bool isRightRed();
  bool isLeftBlack();
  bool isRightBlack();

  virtual BalancedBstNode *getLeft();
  virtual BalancedBstNode *getRight();

  void setRed();
  void setBlack();
  void setLeft(BalancedBstNode *node);
  void setRight(BalancedBstNode *node);

  // rotate a tree so that only the left edge/link is red.
  static void flipColors(BalancedBstNode *node);
  static BalancedBstNode *rotateLeft(BalancedBstNode *parent);
  static BalancedBstNode *rotateRight(BalancedBstNode *parent);

  static BalancedBstNode *insert(BalancedBstNode *node, int val);

  virtual ~BalancedBstNode();
};

#endif // BALANCED_BSTNODE_H
