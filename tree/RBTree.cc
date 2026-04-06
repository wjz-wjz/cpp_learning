#include "RBTree.hh"
#include <algorithm>
#include <stdexcept>
#include <climits>

// public

RBTree::RBTree() {
    NIL = new RBNode(0, BLACK);
    NIL->parent = NIL;
    NIL->left = NIL;
    NIL->right = NIL;

    root = NIL;
}

RBTree::~RBTree() {
    destroy(root);
    delete NIL;
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
    if (root == NIL) {
        throw std::runtime_error("RBTree is empty");
    }
    return findMin(root)->val;
}

int RBTree::findMax() const {
    if (root == NIL) {
        throw std::runtime_error("RBTree is empty");
    }
    return findMax(root)->val;
}

void RBTree::insert(int value) {
    RBNode* parentNode = NIL;
    RBNode* currentNode = root;

    while (currentNode != NIL) {
        parentNode = currentNode;
        if (value < currentNode->val) {
            currentNode = currentNode->left;
        }
        else if (value > currentNode->val) {
            currentNode = currentNode->right;
        }
        else {
            return; // 忽略重复值
        }
    }

    RBNode* newNode = new RBNode(value, RED);
    newNode->parent = parentNode;
    newNode->left = NIL;
    newNode->right = NIL;

    if (parentNode == NIL) {
        root = newNode;
    }
    else if (value < parentNode->val) {
        parentNode->left = newNode;
    }
    else {
        parentNode->right = newNode;
    }

    insertFix(newNode);
}

void RBTree::remove(int value) {
    RBNode* z = root;
    while (z != NIL && z->val != value) {
        if (value < z->val) z = z->left;
        else z = z->right;
    }

    if (z == NIL) return;

    RBNode* y = z;
    Color yOriginalColor = y->color;
    RBNode* x = NIL;

    if (z->left == NIL) {
        x = z->right;
        transplant(z, z->right);
    }
    else if (z->right == NIL) {
        x = z->left;
        transplant(z, z->left);
    }
    else {
        y = findMin(z->right);
        yOriginalColor = y->color;
        x = y->right;

        if (y->parent == z) {
            x->parent = y;
        }
        else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    delete z;

    if (yOriginalColor == BLACK) {
        deleteFix(x);
    }
}

bool RBTree::isRBTree() const {
    if (root == NIL) return true;
    if (root->color != BLACK) return false;
    if (!isBST(root, LLONG_MIN, LLONG_MAX)) return false;
    if (!hasNoRedRed(root)) return false;
    if (blackHeight(root) == -1) return false;
    return true;
}

// private

void RBTree::transplant(RBNode* node1, RBNode* node2) {
    if (node1->parent == NIL) {
        root = node2;
    }
    else if (node1->parent->left == node1) {
        node1->parent->left = node2;
    }
    else {
        node1->parent->right = node2;
    }
    node2->parent = node1->parent;
}

void RBTree::destroy(RBNode* node) {
    if (node == NIL) return;

    destroy(node->left);
    destroy(node->right);
    delete node;
}

bool RBTree::contains(RBNode* node, int target) const {
    if (node == NIL) return false;
    if (target == node->val) return true;

    if (target < node->val) {
        return contains(node->left, target);
    }
    return contains(node->right, target);
}

int RBTree::size(RBNode* node) const {
    if (node == NIL) return 0;
    return 1 + size(node->left) + size(node->right);
}

int RBTree::height(RBNode* node) const {
    if (node == NIL) return 0;
    return 1 + std::max(height(node->left), height(node->right));
}

void RBTree::inOrder(RBNode* node) const {
    if (node == NIL) return;

    inOrder(node->left);
    std::cout << node->val << " ";
    inOrder(node->right);
}

void RBTree::preOrder(RBNode* node) const {
    if (node == NIL) return;

    std::cout << node->val << " ";
    preOrder(node->left);
    preOrder(node->right);
}

void RBTree::postOrder(RBNode* node) const {
    if (node == NIL) return;

    postOrder(node->left);
    postOrder(node->right);
    std::cout << node->val << " ";
}

RBTree::RBNode* RBTree::findMin(RBNode* node) const {
    while (node->left != NIL) {
        node = node->left;
    }
    return node;
}

RBTree::RBNode* RBTree::findMax(RBNode* node) const {
    while (node->right != NIL) {
        node = node->right;
    }
    return node;
}

void RBTree::leftRotate(RBNode* node) {
    RBNode* nodeX = node->right;
    RBNode* nodeT = nodeX->left;

    node->right = nodeT;
    nodeT->parent = node;

    nodeX->parent = node->parent;
    if (node->parent == NIL) {
        root = nodeX;
    }
    else if (node->parent->left == node) {
        node->parent->left = nodeX;
    }
    else {
        node->parent->right = nodeX;
    }

    nodeX->left = node;
    node->parent = nodeX;
}

void RBTree::rightRotate(RBNode* node) {
    RBNode* nodeX = node->left;
    RBNode* nodeT = nodeX->right;

    node->left = nodeT;
    nodeT->parent = node;

    nodeX->parent = node->parent;
    if (node->parent == NIL) {
        root = nodeX;
    }
    else if (node->parent->left == node) {
        node->parent->left = nodeX;
    }
    else {
        node->parent->right = nodeX;
    }

    nodeX->right = node;
    node->parent = nodeX;
}

void RBTree::insertFix(RBNode* node) {
    while (node != root && node->parent->color == RED) {
        auto parentNode = node->parent;
        auto grandNode = parentNode->parent;

        if (parentNode == grandNode->left) {
            auto uncleNode = grandNode->right;

            if (uncleNode->color == BLACK) {
                if (node == parentNode->right) {
                    node = parentNode;
                    leftRotate(node);
                    parentNode = node->parent;
                    grandNode = parentNode->parent;
                }

                parentNode->color = BLACK;
                grandNode->color = RED;
                rightRotate(grandNode);
            }
            else {
                parentNode->color = BLACK;
                uncleNode->color = BLACK;
                grandNode->color = RED;
                node = grandNode;
            }
        }
        else {
            auto uncleNode = grandNode->left;

            if (uncleNode->color == BLACK) {
                if (node == parentNode->left) {
                    node = parentNode;
                    rightRotate(node);
                    parentNode = node->parent;
                    grandNode = parentNode->parent;
                }

                parentNode->color = BLACK;
                grandNode->color = RED;
                leftRotate(grandNode);
            }
            else {
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
    if(node->color == RED){
        node->color = BLACK;
        return;
    }

    while(node!=root && node->color == BLACK){
        if(node->parent->left == node){
            auto parentNode = node->parent;
            auto brotherNode = parentNode->right;
            
            if(brotherNode->color == RED){
                brotherNode->color = BLACK;
                parentNode->color = RED;
                leftRotate(parentNode);
                continue;
            }

            else{
                if(brotherNode->left->color == BLACK && brotherNode->right->color == BLACK){
                    brotherNode->color = RED;
                    node = parentNode;
                    continue;
                }
                else if(brotherNode->right->color == BLACK){
                    brotherNode->left->color = BLACK;
                    brotherNode->color = RED;
                    rightRotate(brotherNode);
                    continue;
                }
                else{
                    brotherNode->color = parentNode->color;
                    brotherNode->right->color = BLACK;
                    parentNode->color = BLACK;
                    leftRotate(parentNode);
                    node = root;
                }
            }
        }
        else{
            auto parentNode = node->parent;
            auto brotherNode = parentNode->left;
            if(brotherNode->color == RED){
                brotherNode->color = BLACK;
                parentNode->color = RED;
                rightRotate(parentNode);
                continue;
            }

            else{
                if(brotherNode->left->color == BLACK && brotherNode->right->color == BLACK){
                    brotherNode->color = RED;
                    node = parentNode;
                    continue;
                }
                else if(brotherNode->left->color == BLACK){
                    brotherNode->right->color = BLACK;
                    brotherNode->color = RED;
                    leftRotate(brotherNode);
                    continue;
                }
                else{
                    brotherNode->color = parentNode->color;
                    parentNode->color = BLACK;
                    brotherNode->left->color = BLACK;
                    rightRotate(parentNode);
                    node = root;
                }
            }

        }
    }
    node->color = BLACK;
    return;
}

bool RBTree::hasNoRedRed(RBNode* node) const {
    if (node == NIL) {
        return true;
    }

    if (node->color == RED) {
        if (node->left->color == RED || node->right->color == RED) {
            return false;
        }
    }

    return hasNoRedRed(node->left) && hasNoRedRed(node->right);
}

bool RBTree::isBST(RBNode* node, long long low, long long high) const {
    if (node == NIL) return true;

    if (node->val <= low || node->val >= high) {
        return false;
    }

    return isBST(node->left, low, node->val) &&
           isBST(node->right, node->val, high);
}

int RBTree::blackHeight(RBNode* node) const {
    if (node == NIL) return 1;

    int leftBH = blackHeight(node->left);
    int rightBH = blackHeight(node->right);

    if (leftBH == -1 || rightBH == -1 || leftBH != rightBH) {
        return -1;
    }

    return leftBH + (node->color == BLACK ? 1 : 0);
}