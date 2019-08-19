#include "bstnode.h"

BstNode::BstNode(int _value) : value(_value), x(0), y(0),  min(0), max(0), left(nullptr), right(nullptr) {}
BstNode::BstNode(int _value, int _x, int _y) : value(_value), x(_x), y(_y), min(_x), max(_x), left(nullptr), right(nullptr) {}
BstNode::BstNode(int _value, BstNode* _left, BstNode* _right) : value(_value), x(0), y(0), min(0), max(0), left(_left), right(_right) {}
BstNode::BstNode(int _value, int _x, int _y, BstNode* _left, BstNode* _right) : value(_value), x(_x), y(_y), min(0), max(0), left(_left), right(_right) {}

int BstNode::getValue() { return value; }
int BstNode::getMin() { return min; }
int BstNode::getMax() { return max; }
int BstNode::getX() { return x; }
int BstNode::getY() { return y; }
BstNode* BstNode::getLeft() { return left; }
BstNode* BstNode::getRight() { return right; }

void BstNode::setMin(int _min) { min = _min; }
void BstNode::setMax(int _max) { max = _max; }
void BstNode::setValue(int _value) { value = _value; }
void BstNode::setX(int _x) { x = _x; }
void BstNode::setY(int _y) { y = _y; }

// The child is in the left tree of the grandparent then it, the child, must not have x coord > x coord of
// grandparent; similarly, if the child is the right tree of the grandparent
void BstNode::insert(int val) {
    if ( val < this->getValue() ) {
        if ( left == nullptr ) left = new BstNode(val);
        else left->insert(val);
    }
    else {
        if (right == nullptr ) right = new BstNode(val);
        else right->insert(val);
    }
}

/*
 * alter all the x coords in the tree
 * by delta
 */
void BstNode::maintainInvariant(int delta) {
     if (this->getLeft() != nullptr) this->getLeft()->maintainInvariant(delta);
     this->setX( this->getX() + delta );
     this->setMin(this->getMin() + delta);
     this->setMax(this->getMax() + delta);
     if (this->getRight() != nullptr) this->getRight()->maintainInvariant(delta);
 }

void BstNode::updateCoordinates(BstNode* node, int width ) {

    if (node->getLeft() != nullptr) {
        node->getLeft()->setY(node->getY() + 2*width);
        node->getLeft()->setX(node->getX() - 2*width);
        node->getLeft()->setMin(node->getX() - 2*width);
        node->getLeft()->setMax(node->getX() - 2*width);

        updateCoordinates(node->getLeft(), width);

        // update the min
        node->setMin( std::min(node->getLeft()->getMin(), node->getMin()) );

        // Now check that current node is at least +2 units greater than the left max
        if (node->getX() < node->getLeft()->getMax() + 2*width) {
            int delta = (node->getX() - 2*width) - node->getLeft()->getMax();
            node->getLeft()->maintainInvariant(delta);
            node->setMin( std::min(node->getLeft()->getMin(), node->getMin()) );
        }
      }

    if (node->getRight() != nullptr) {
        node->getRight()->setY(node->getY() + 2*width);
        node->getRight()->setX(node->getX() + 2*width);
        node->getRight()->setMin(node->getX() + 2*width);
        node->getRight()->setMax(node->getX() + 2*width);

        updateCoordinates(node->getRight(), width);

        // update the max
        node->setMax( std::max(node->getRight()->getMax(), node->getMax()) );

        // Now check that current node is at  most -2 units less than the right min
        if (node->getRight()->getMin() < node->getX() + 2*width) {
            int delta = (node->getX() + 2*width) - node->getRight()->getMin();
            node->getRight()->maintainInvariant(delta);
            node->setMax( std::max(node->getRight()->getMax(), node->getMax()) );
        }
    }
}

 void BstNode::printInOrder() {
     if (this->left != nullptr) this->left->printInOrder();
     std::cout << this->getValue() << " with (" << this->getX() << ", " << this->getY() << ") ";
     if (this->getRight() != nullptr) this->getRight()->printInOrder();
 }

BstNode::~BstNode() {
        std::cout << "deleting: " << this->getValue() << "\n";
        delete left;
        delete right;
}
