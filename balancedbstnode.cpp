#include "balancedbstnode.h"

BalancedBstNode::BalancedBstNode(Color _color, int _value) : BstNode(_value)
{
    color = _color;
    balanced_left = nullptr;
    balanced_right = nullptr;
}

BalancedBstNode::BalancedBstNode(Color _color, int _value, int _x, int _y) : BstNode(_value, _x, _y)
{
    color = _color;
    balanced_left = nullptr;
    balanced_right = nullptr;
}

bool BalancedBstNode::isRed() { return color == RED; }
bool BalancedBstNode::isBlack() { return color == BLACK; }

void BalancedBstNode::setRed() { color = RED; }
void BalancedBstNode::setBlack() { color = BLACK; }

BalancedBstNode* BalancedBstNode::getLeft() { return balanced_left; }
BalancedBstNode* BalancedBstNode::getRight() { return balanced_right; }

void BalancedBstNode::setLeft(BalancedBstNode* node) { balanced_left = node; }
void BalancedBstNode::setRight(BalancedBstNode* node) { balanced_right = node; }

// The child is in the left tree of the grandparent then it, the child, must not have x coord > x coord of
// grandparent; similarly, if the child is the right tree of the grandparent
void BalancedBstNode::insert(BalancedBstNode* node, Color color, int val, int width) {
    if ( val < node->getValue() ) {
        if ( node->getLeft() == nullptr ) node->setLeft(new BalancedBstNode(RED, val, node->getX() - 2*width, node->getY() + 2*width));
        else insert(node->getLeft(), color, val, width);

        // update the min
        node->setMin( std::min(node->getLeft()->getMin(), node->getMin()) );

        // Now check that current node is at least +2 units greater than the left max
        if (node->getX() - node->getLeft()->getMax() < 2*width) {
            node->getLeft()->maintainInvariant(-2*width);
            node->setMin( std::min(node->getLeft()->getMin(), node->getMin()) );
        }
    }
    else {
        if ( node->getRight() == nullptr ) {
            node->setRight(new BalancedBstNode(BLACK, val, node->getX() + 2*width, node->getY() + 2*width));
           // node->setRed();
        }
        else insert(node->getRight(), color, val, width);

        // update the max
        node->setMax( std::max(node->getRight()->getMax(), node->getMax()) );

        // Now check that current node is at  most -2 units less than the right min
        if (node->getRight()->getMin() - node->getX() < 2*width) {
            node->getRight()->maintainInvariant(+2*width);
            node->setMax( std::max(node->getRight()->getMax(), node->getMax()) );
        }
    }
}

BalancedBstNode::~BalancedBstNode() {
    std::cout << "deleting: " << this->getValue() << "\n";
    delete balanced_left;
    delete balanced_right;
}
