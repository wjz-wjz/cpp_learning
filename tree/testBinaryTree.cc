#include "BinaryTree.hh"
#include <iostream>

int main(){
    auto BT = new BinaryTree();

    BT->setRoot(new BinaryTree::Node(1));
    BT->getRoot()->left = new BinaryTree::Node(2);
    BT->getRoot()->right = new BinaryTree::Node(3);
    BT->getRoot()->left->left = new BinaryTree::Node(4);
    BT->getRoot()->left->right = new BinaryTree::Node(5);
    BT->getRoot()->right->right = new BinaryTree::Node(6);
    BT->getRoot()->right->left = new BinaryTree::Node(7);

    BT->preorder();
    BT->inorder();
    BT->postorder();

    delete BT;

    return 1;
}