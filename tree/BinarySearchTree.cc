#include "BinarySearchTree.hh"
#include <stdexcept>

BST::BST() : BinaryTree() {}

// 对外接口：把 root 交给递归版本处理
void BST::insert(int value) {
    root = insert(root, value);
}

bool BST::contains(int target) const {
    return contains(root, target);
}

int BST::findMin() const {
    if (!root) {
        throw std::runtime_error("BST is empty");
    }

    return findMin(root)->val;
}

int BST::findMax() const {
    if (!root) {
        throw std::runtime_error("BST is empty");
    }

    return findMax(root)->val;
}

void BST::remove(int value) {
    root = remove(root, value);
}

// ===== 下面这些你自己写 =====

// 1. 插入
BST::Node* BST::insert(Node* node, int value) {
    if(!node){
        node = new BST::Node(value);
        return node;
    }

    if(value < node->val){
        node->left = insert(node->left, value);
    }

    else if(value > node->val){
        node->right = insert(node->right, value);
    }

    return node;
}

// 2. 查找
bool BST::contains(Node* node, int target) const {
    if(!node) return false;

    if(target == node->val) return true;

    if(target < node->val){
        return contains(node->left, target);
    }
    else if(target > node->val){
        return contains(node->right, target);
    }

    return false;
}

// 3. 找最小节点
BST::Node* BST::findMin(Node* node) const {
    if(!node) return nullptr;

    if(node->left){
        return findMin(node->left);
    }

    return node;
}

// 4. 找最大节点
BST::Node* BST::findMax(Node* node) const {
    if(!node) return nullptr;

    if(node->right){
        return findMax(node->right);
    }

    return node;
}

// 5. 删除
BST::Node* BST::remove(Node* node, int value) {
    if(!node) return nullptr;
    if(value < node->val){
        node->left = remove(node->left, value);
    }
    else if(value > node->val){
        node->right = remove(node->right, value);
    }
    else{
        if(!node->left && !node->right){
            delete node;
            return nullptr;
        }
        else if(!node->right){
            auto leftChild = node->left;
            delete node;
            return leftChild;
        }
        else if(!node->left){
            auto rightChild = node->right;
            delete node;
            return rightChild;
        }
        else{
            BST::Node* fatherNode = nullptr;
            BST::Node* childNode = node->left;
            while(childNode->right){
                fatherNode = childNode;
                childNode = childNode->right;
            }
            node->val = childNode->val;
            if(fatherNode){
                fatherNode->right = childNode->left;
            }
            else{
                node->left = childNode->left;
            }
            delete childNode;
        }
    }
    return node;
}