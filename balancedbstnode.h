#ifndef BALANCEDBSTNODE_H
#define BALANCEDBSTNODE_H

#include "bstnode.h"

struct BalancedBstNode : BstNode
{
    enum Color {RED, BLACK};
    Color color;

    BalancedBstNode* balanced_left;
    BalancedBstNode* balanced_right;

    BalancedBstNode(int _value);
    BalancedBstNode(Color _color, int _value);
    BalancedBstNode(Color _color, int _value, int _x, int _y);

    bool isRed();
    bool isBlack();
    virtual BalancedBstNode* getLeft();
    virtual BalancedBstNode* getRight();

    void setRed();
    void setBlack();
    void setLeft(BalancedBstNode* node);
    void setRight(BalancedBstNode* node);

    // rotate a tree so that only the left edge/link is red.
    static BalancedBstNode* rotateLeft(BalancedBstNode* parent);

    static void insert(BalancedBstNode* node, int val);

    virtual ~BalancedBstNode();
};

#endif // BALANCEDBSTNODE_H
