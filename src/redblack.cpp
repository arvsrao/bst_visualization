#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QPointF>
#include <QWidget>
#include <QPen>

#include "include/bst_visualization/bstnode.h"
#include "include/bst_visualization/balancedbstnode.h"
#include "include/bst_visualization/generaterandominteger.h"

// GLOBAL DISPLAY CONSTANT
const int WIDTH = 25;

class CircledText : public QGraphicsEllipseItem {
 public:
  int num;
  CircledText(int _num, int _width, QPoint _pos) : num(_num) {
    this->setRect(QRect(0, 0, _width, _width));
    this->setPos(_pos);
  }

 protected:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawEllipse(this->rect());
    painter->drawText(this->rect(), Qt::AlignCenter, QString::number(num));
  }
};

void display(BalancedBstNode *tree, QGraphicsScene *scene, int width) {

  if (tree->getLeft() != nullptr) {
    // draw line from parent to the left node
    if (tree->getLeft()->isRed()) {
      scene->addLine(tree->getX(),
                     tree->getY() + width / 2,
                     tree->getLeft()->getX() + width / 2,
                     tree->getLeft()->getY(),
                     QPen(Qt::red, 3));
    } else {
      scene->addLine(tree->getX(),
                     tree->getY() + width / 2,
                     tree->getLeft()->getX() + width / 2,
                     tree->getLeft()->getY());
    }
    display(tree->getLeft(), scene, width);
  }

  // Create an instance of CircledText & add it to the scene.
  CircledText *c = new CircledText(tree->getValue(), width, QPoint(tree->getX(), tree->getY()));
  scene->addItem(c);

  if (tree->getRight() != nullptr) {
    // draw line from parent to the right node
    if (tree->getRight()->isRed()) {
      scene->addLine(tree->getX() + width,
                     tree->getY() + width / 2,
                     tree->getRight()->getX() + width / 2,
                     tree->getRight()->getY(),
                     QPen(Qt::red, 3));
    } else {
      scene->addLine(tree->getX() + width,
                     tree->getY() + width / 2,
                     tree->getRight()->getX() + width / 2,
                     tree->getRight()->getY());
    }

    display(tree->getRight(), scene, width);
  }
}

// generate a BST with randomly geneated positive integers
BalancedBstNode *generateRandomBst(const int N, const int RANGE) {
  GenerateRandomInteger integer_generator(RANGE);

  auto root = new BalancedBstNode{integer_generator()};
  for (int i = 0; i < N; i++) {
    root = BalancedBstNode::insert(root, integer_generator());
    root->setBlack();
  }

  return root;
}

BalancedBstNode *testBst() {
  const int array_size = 18;
  const int test_array[] = {20, 2, 1, 3, 9, 13, 234, 76, -34, 39, 28, 27, 29, 45, 40, 35, 31, 39};
  auto tree = new BalancedBstNode{test_array[0]};
  for (int i = 1; i <= array_size - 1; i++) {
    tree = BalancedBstNode::insert(tree, test_array[i]);
    tree->setBlack();
  }

  return tree;
}

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  auto tree = generateRandomBst(23, 200);
  // auto tree = testBst();
  BalancedBstNode::updateCoordinates(tree, WIDTH);

  // Create a view, put a scene in it and add tiny circles to the scene
  QGraphicsView *view = new QGraphicsView();
  QGraphicsScene *scene = new QGraphicsScene();

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
