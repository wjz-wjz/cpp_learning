#include "RBTree.hh"
#include <algorithm>
#include <stdexcept>
#include <climits>

// public

RBTree::RBTree() : root(nullptr) {}

RBTree::~RBTree() {
    destroy(root);
}

bool RBTree::contains(int target) const {
    return contains(root, target);
}

int RBTree::size() const {
    return size(root);
}

int RBTree::height() const {
    return height(root);
}

void RBTree::inorder() const {
    inOrder(root);
}

void RBTree::preorder() const {
    preOrder(root);
}

void RBTree::postorder() const {
    postOrder(root);
}

int RBTree::findMin() const {
    if (!root) {
        throw std::runtime_error("RBTree is empty");
    }
    return findMin(root)->val;
}

int RBTree::findMax() const {
    if (!root) {
        throw std::runtime_error("RBTree is empty");
    }
    return findMax(root)->val;
}

void RBTree::insert(int value) {
    if(!root){
        RBTree::RBNode* node = new RBTree::RBNode(value);
        root = node;
        root->color = BLACK;
        return;
    }

    RBTree::RBNode* parentNode = nullptr;
    RBTree::RBNode* currentNode = root;
    while(currentNode){
        if(value < currentNode->val){
            parentNode = currentNode;
            currentNode = currentNode->left;
        }
        else if(value > currentNode->val){
            parentNode = currentNode;
            currentNode = currentNode->right;
        }
        else{
            return;
        }
    }
    RBTree::RBNode* newNode = new RBTree::RBNode(value);
    newNode->parent = parentNode;
    if(value < parentNode->val){
        parentNode->left = newNode;
    }
    else{
        parentNode->right = newNode;
    }
    insertFix(newNode);
    return;
}

void RBTree::remove(int value) {
    RBNode* z = root;
    while (z && z->val != value) {
        if (value < z->val) z = z->left;
        else z = z->right;
    }

    if (!z) return;

    RBNode* y = z;
    Color yOriginalColor = y->color;
    RBNode* x = nullptr;

    if (!z->left) {
        x = z->right;
        transplant(z, z->right);
    }
    else if (!z->right) {
        x = z->left;
        transplant(z, z->left);
    }
    else {
        // 双孩子情况后面补
    }

    delete z;

    if (yOriginalColor == BLACK) {
        deleteFix(x);
    }
}

bool RBTree::isRBTree() const{
    if (!root) return true;
    if (root->color != BLACK) return false;
    if (!isBST(root, LLONG_MIN, LLONG_MAX)) return false;
    if (!hasNoRedRed(root)) return false;
    if (blackHeight(root) == -1) return false;
    return true;
}

// private

void RBTree::destroy(RBNode* node) {
    if (!node) return;

    destroy(node->left);
    destroy(node->right);
    delete node;
}

bool RBTree::contains(RBNode* node, int target) const {
    if (!node) return false;
    if (target == node->val) return true;

    if (target < node->val) {
        return contains(node->left, target);
    }
    return contains(node->right, target);
}

int RBTree::size(RBNode* node) const {
    if (!node) return 0;
    return 1 + size(node->left) + size(node->right);
}

int RBTree::height(RBNode* node) const {
    if (!node) return 0;
    return 1 + std::max(height(node->left), height(node->right));
}

void RBTree::inOrder(RBNode* node) const {
    if (!node) return;

    inOrder(node->left);
    std::cout << node->val << " ";
    inOrder(node->right);
}

void RBTree::preOrder(RBNode* node) const {
    if (!node) return;

    std::cout << node->val << " ";
    preOrder(node->left);
    preOrder(node->right);
}

void RBTree::postOrder(RBNode* node) const {
    if (!node) return;

    postOrder(node->left);
    postOrder(node->right);
    std::cout << node->val << " ";
}

RBTree::RBNode* RBTree::findMin(RBNode* node) const {
    if (!node) return nullptr;

    while (node->left) {
        node = node->left;
    }
    return node;
}

RBTree::RBNode* RBTree::findMax(RBNode* node) const {
    if (!node) return nullptr;

    while (node->right) {
        node = node->right;
    }
    return node;
}

void RBTree::leftRotate(RBNode* node) {
    if(!node || !node->right) return;

    RBTree::RBNode* nodeX = node->right;
    RBTree::RBNode* nodeT = nodeX->left;

    node->right = nodeT;
    if(nodeT) nodeT->parent = node;
    
    nodeX->parent = node->parent;
    if(!node->parent){
        root = nodeX;
    }
    else if(node->parent->left == node){
        node->parent->left = nodeX;
    }
    else{
        node->parent->right = nodeX;
    }

    nodeX->left = node;
    node->parent = nodeX;
}

void RBTree::rightRotate(RBNode* node) {
    if(!node || !node->left) return;

    RBTree::RBNode* nodeX = node->left;
    RBTree::RBNode* nodeT = nodeX->right;

    node->left = nodeT;
    if(nodeT) nodeT->parent = node;

    nodeX->parent = node->parent;
    if(!node->parent) root = nodeX;
    else if(node->parent->left == node) node->parent->left = nodeX;
    else node->parent->right = nodeX;

    nodeX->right = node;
    node->parent = nodeX;
}

void RBTree::insertFix(RBNode* node) {
    while(node != root && node->parent->color == RED){
        auto parentNode = node->parent;
        auto grandNode = parentNode->parent;
        if(parentNode == grandNode->left){
            auto uncleNode = grandNode->right;
            if(!uncleNode || uncleNode->color == BLACK){
                if(node == parentNode->right){
                    node = parentNode;
                    leftRotate(node);
                    parentNode = node->parent;
                    grandNode = parentNode->parent;
                }

                parentNode->color = BLACK;
                grandNode->color = RED;
                rightRotate(grandNode);
            }
            else{
                parentNode->color = BLACK;
                uncleNode->color = BLACK;
                grandNode->color = RED;
                node = grandNode;
            }
        }
        else{
            auto uncleNode = grandNode->left;
            if(!uncleNode || uncleNode->color == BLACK){
                if(node == parentNode->left){
                    node = parentNode;
                    rightRotate(node);
                    parentNode = node->parent;
                    grandNode = parentNode->parent;
                }

                parentNode->color = BLACK;
                grandNode->color = RED;
                leftRotate(grandNode);
            }
            else{
                parentNode->color = BLACK;
                uncleNode->color = BLACK;
                grandNode->color = RED;
                node = grandNode;
            }
        }
    }

    root->color = BLACK;
}

void RBTree::deleteFix(RBNode* node) {
    // TODO
}

bool RBTree::hasNoRedRed(RBNode* node) const {
    if (!node) {
        return true;
    }

    if (node->color == RED) {
        if ((node->left && node->left->color == RED) ||
            (node->right && node->right->color == RED)) {
            return false;
        }
    }

    return hasNoRedRed(node->left) && hasNoRedRed(node->right);
}

bool RBTree::isBST(RBNode* node, long long low, long long high) const {
    if(!node) return true;
    if(node->val >= high || node->val <= low){
        return false;
    }
    else{
        return isBST(node->left, low, node->val) && isBST(node->right, node->val, high);
    }
}

int RBTree::blackHeight(RBNode* node) const {
    if (!node) return 1;   // NIL 视作黑

    int leftBH = blackHeight(node->left);
    int rightBH = blackHeight(node->right);

    if (leftBH == -1 || rightBH == -1 || leftBH != rightBH)
    return -1;

    return leftBH + (node->color == BLACK ? 1 : 0);
}