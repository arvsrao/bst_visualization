#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QPointF>
#include <QWidget>

#include "bstnode.h"
#include "balancedbstnode.h"
#include "generaterandominteger.h"

// GLOBAL DISPLAY CONSTANT
const int WIDTH = 25;

void shiftTreeToRight(BstNode* root, int delta) {
   if (root->getLeft() != nullptr) shiftTreeToRight(root->getLeft(), delta);
   root->setX(root->getX() + delta);
   if (root->getRight() != nullptr) shiftTreeToRight(root->getRight(), delta);
}

class CircledText : public QGraphicsEllipseItem
{
public:
    int num;
    CircledText(int _num, int _width, QPoint _pos): num(_num) {
        this->setRect(QRect(0,0, _width, _width));
        this->setPos(_pos);
    }

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {
       painter->setRenderHint(QPainter::Antialiasing);
       painter->drawEllipse(this->rect());
       painter->drawText(this->rect(), Qt::AlignCenter, QString::number(num));
    }
};

void display(BstNode* tree, QGraphicsScene* scene, int width) {
    if (tree->getLeft() != nullptr) {
        // draw line from parent to the left node
        scene->addLine(tree->getX(), tree->getY() + width/2, tree->getLeft()->getX() + width/2, tree->getLeft()->getY());

        display(tree->getLeft(), scene, width);
    }

    // Create an instance of CircledText & add it to the scene.
    CircledText *c = new CircledText(tree->getValue(), width, QPoint(tree->getX(), tree->getY()));
    scene->addItem(c);

    if (tree->getRight() != nullptr) {
        // draw line from parent to the right node
        scene->addLine(tree->getX() + width, tree->getY() + width/2, tree->getRight()->getX() + width/2, tree->getRight()->getY());

        display(tree->getRight(), scene, width);
    }
}

// generate a BST with randomly geneated positive integers
BstNode* generateRandomBst(const int N, const int RANGE) {
   GenerateRandomInteger integer_generator(RANGE);

   auto root = new BstNode { integer_generator() };
   for ( int i = 0; i < N ; i++) root->insert(integer_generator());

   return root;
}

BstNode* testBst() {
    const int array_size = 12;
    const int test_array[] = { 14, 7, 0, 3, 9, 13, 39, 28, 27, 29, 45, 40 };//,35,31,39};
    auto tree = new BstNode { test_array[0] };
    for ( int i = 1; i <= array_size - 1 ; i++) tree->insert( test_array[i] );

    return tree;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //    auto tree = new BalancedBstNode { BalancedBstNode::BLACK, integer_generator() };
    //    for ( int i = 0; i < N ; i++) BalancedBstNode::insert(tree, BalancedBstNode::BLACK, integer_generator(), WIDTH );

    BstNode* tree = generateRandomBst(30, 150);
    BstNode::updateCoordinates(tree, WIDTH);

    // Shift the all the x coords back into the image domain.
    // BTW QT will render the coords with negative x values.
    // if (tree->getMin() < 0) shiftTreeToRight(tree, -1 * tree->getMin());

    // Create a view, put a scene in it and add tiny circles to the scene
    QGraphicsView * view = new QGraphicsView();
    QGraphicsScene * scene = new QGraphicsScene();

    view->setScene(scene);
    display(tree, scene, WIDTH);

    // the text is rendered with a 90 degree clockwise rotation
    QMatrix transformMatrix = QMatrix(0.0, 1.0, -1.0, 0.0, 0.0, 0.0);
    view->setMatrix(transformMatrix);
    view->rotate(-90);
    view->show();

    // delete the tree
    delete tree;

    // or add the view to the layout inside another widget
    return a.exec();
}
