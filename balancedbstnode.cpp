#include "balancedbstnode.h"

BalancedBstNode::BalancedBstNode(int _value) : BstNode(_value)
{
    color = BLACK;
    balanced_left = nullptr;
    balanced_right = nullptr;
}

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

bool BalancedBstNode::isLeftRed() {
    if (balanced_left != nullptr) return balanced_left->isRed();
    return false;
}

bool BalancedBstNode::isLeftLeftRed() {
    if (balanced_left != nullptr) return balanced_left->isLeftRed();
    return false;
}


bool BalancedBstNode::isLeftBlack() {
    if (balanced_left != nullptr) return balanced_left->isBlack();
    return false;
}

bool BalancedBstNode::isRightRed() {
    if (balanced_right != nullptr) return balanced_right->isRed();
    return false;
}

bool BalancedBstNode::isRightBlack() {
    if (balanced_right != nullptr) return balanced_right->isBlack();
    return false;
}

void BalancedBstNode::setRed() { color = RED; }
void BalancedBstNode::setBlack() { color = BLACK; }

BalancedBstNode* BalancedBstNode::getLeft() { return balanced_left; }
BalancedBstNode* BalancedBstNode::getRight() { return balanced_right; }

void BalancedBstNode::setLeft(BalancedBstNode* node) { balanced_left = node; }
void BalancedBstNode::setRight(BalancedBstNode* node) { balanced_right = node; }

// rotate a node that leans right.
void BalancedBstNode::flipColors(BalancedBstNode* node) {
    node->getLeft()->setBlack();
    node->getRight()->setBlack();
    node->setRed(); // maintain perfect black balance.
}

// rotate a node that leans right.
BalancedBstNode* BalancedBstNode::rotateLeft(BalancedBstNode* parent) {
   BalancedBstNode* r = parent->getRight(); // the new parent
   parent->setRight(r->getLeft());
   r->setLeft(parent);

   // parent is now a left node and has a RED link to it.
   r->color = parent->color;
   parent->setRed();
   return r;
}

// rotate a node right
BalancedBstNode* BalancedBstNode::rotateRight(BalancedBstNode* parent) {
   BalancedBstNode* l = parent->getLeft(); // the new parent
   parent->setLeft(l->getRight());
   l->setRight(parent);

   // parent is now a left node and has a RED link to it.
   l->color = parent->color;
   parent->setRed();
   return l;
}

// The child is in the left tree of the grandparent then it, the child, must not have x coord > x coord of
// grandparent; similarly, if the child is the right tree of the grandparent
BalancedBstNode* BalancedBstNode::insert(BalancedBstNode* node, int val) {
    if (node == nullptr) return new BalancedBstNode(RED, val);

    if ( val < node->getValue() ) node->setLeft(insert(node->getLeft(), val));
    else node->setRight(insert(node->getRight(), val));

    if (!node->isLeftRed() && node->isRightRed()) node = rotateLeft(node);
    if (node->isLeftRed() && node->isLeftLeftRed()) node = rotateRight(node);
    if (node->isLeftRed() && node->isRightRed()) flipColors(node);

    return node;
}

BalancedBstNode::~BalancedBstNode() {
    std::cout << "deleting: " << this->getValue() << "\n";
    delete balanced_left;
    delete balanced_right;
}
