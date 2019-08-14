#ifndef BALANCEDBSTNODE_H
#define BALANCEDBSTNODE_H

#include "bstnode.h"

struct BalancedBstNode : BstNode
{
    enum Color {RED, BLACK};
    Color color;

    BalancedBstNode* balanced_left;
    BalancedBstNode* balanced_right;

    BalancedBstNode(Color _color, int _value);
    BalancedBstNode(Color _color, int _value, int _x, int _y);
    ~BalancedBstNode();

    bool isRed();
    bool isBlack();
    BalancedBstNode* getLeft();
    BalancedBstNode* getRight();


    void setRed();
    void setBlack();
    void setLeft(BalancedBstNode* node);
    void setRight(BalancedBstNode* node);

    static void insert(BalancedBstNode* node, Color color, int val, int width);
};

#endif // BALANCEDBSTNODE_H
