#include "BinaryTree.hh"
#include <iostream>

//public

BinaryTree::BinaryTree() : root(nullptr){

}

BinaryTree::BinaryTree(int value) : root(new Node(value)){

};

BinaryTree::~BinaryTree(){
    destroy(root);
    std::cout << "BinaryTree destroyed !!" << std::endl;
}

void BinaryTree::preorder() const{
    std::cout << "PreOrder of BinaryTree:" << std::endl;
    preOrder(root);
    std::cout << std::endl;
}

void BinaryTree::inorder() const{
    std::cout << "InOrder of BinaryTree:" << std::endl;
    inOrder(root);
    std::cout << std::endl;
}

void BinaryTree::postorder() const{
    std::cout << "PostOrder of BinaryTree:" << std::endl;
    postOrder(root);
    std::cout << std::endl;
}

int BinaryTree::size() const{
    return size(root);
}

int BinaryTree::height() const{
    return height(root);
}

bool BinaryTree::contains(int target) const{
    return contains(root, target);
}

//private
void BinaryTree::preOrder(Node* node) const{
    if(!node) return;

    std::cout << node->val << " ";
    preOrder(node->left);
    preOrder(node->right);
}

void BinaryTree::inOrder(Node* node) const{
    if(!node) return;

    inOrder(node->left);
    std::cout << node->val << " ";
    inOrder(node->right);
}

void BinaryTree::postOrder(Node* node) const{
    if(!node) return;

    postOrder(node->left);
    postOrder(node->right);
    std::cout << node->val << " ";
}

void BinaryTree::destroy(Node* node) {
    if(!node) return;

    destroy(node->left);
    destroy(node->right);
    delete node;
    return;
}

int BinaryTree::size(Node* node) const{
    if(!node) return 0;

    return 1 + size(node->left) + size(node->right);
}

int BinaryTree::height(Node* node) const{
    if(!node) return 0;

    return 1+std::max(height(node->left), height(node->right));
}

bool BinaryTree::contains(Node* node, int target) const{
    if(!node) return false;

    return node->val==target || contains(node->left, target) || contains(node->right, target);
}
