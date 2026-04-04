#include "AVL.hh"
#include <algorithm>

// public

AVLTree::AVLTree() : root(nullptr) {}

AVLTree::~AVLTree() {
    destroy(root);
}

void AVLTree::insert(int value) {
    root = insert(root, value);
}

void AVLTree::remove(int target) {
    root = remove(root, target);
}

bool AVLTree::contains(int target) const {
    return contains(root, target);
}

void AVLTree::inorder() const {
    inOrder(root);
}

void AVLTree::preorder() const {
    preOrder(root);
}

void AVLTree::postorder() const {
    postOrder(root);
}

int AVLTree::height() const {
    return getHeight(root);
}

int AVLTree::size() const {
    return size(root);
}

// private

void AVLTree::destroy(Node* node) {
    if (!node) return;

    destroy(node->left);
    destroy(node->right);
    delete node;
}

bool AVLTree::contains(Node* node, int target) const {
    if (!node) return false;
    if (target == node->val) return true;

    if (target < node->val) {
        return contains(node->left, target);
    }
    return contains(node->right, target);
}

void AVLTree::inOrder(Node* node) const {
    if (!node) return;

    inOrder(node->left);
    std::cout << node->val << " ";
    inOrder(node->right);
}

void AVLTree::preOrder(Node* node) const {
    if (!node) return;

    std::cout << node->val << " ";
    preOrder(node->left);
    preOrder(node->right);
}

void AVLTree::postOrder(Node* node) const {
    if (!node) return;

    postOrder(node->left);
    postOrder(node->right);
    std::cout << node->val << " ";
}

int AVLTree::size(Node* node) const {
    if (!node) return 0;
    return 1 + size(node->left) + size(node->right);
}

// ===== 下面这些你自己写 =====

// 1. 返回节点高度
int AVLTree::getHeight(Node* node) const {
    if(node) return node->height;

    return 0;
}

// 2. 平衡因子 = 左高 - 右高
int AVLTree::getBalance(Node* node) const {
    if(node) return getHeight(node->left) - getHeight(node->right);

    return 0;
}

// 3. 右旋
AVLTree::Node* AVLTree::rightRotate(Node* node) {
    Node* nodeX = node->left;
    Node* nodeT = nodeX->right;

    nodeX->right = node;
    node->left = nodeT;

    node->height = 1+std::max(getHeight(node->left), getHeight(node->right));
    nodeX->height = 1+std::max(getHeight(nodeX->left), getHeight(nodeX->right));

    return nodeX;
}

// 4. 左旋
AVLTree::Node* AVLTree::leftRotate(Node* node) {
    Node* nodeX = node->right;
    Node* nodeT = nodeX->left;

    nodeX->left = node;
    node->right = nodeT;

    node->height = 1+std::max(getHeight(node->left), getHeight(node->right));
    nodeX->height = 1+std::max(getHeight(nodeX->left), getHeight(nodeX->right));

    return nodeX;
}

// 5. AVL 插入
AVLTree::Node* AVLTree::insert(Node* node, int value) {
    // TODO 第一步：先按 BST 方式插入
    // 1. node 为空 -> 新建节点
    if(!node) return new Node(value);
    // 2. value < node->val -> 插左边
    if(value < node->val){
        node->left = insert(node->left, value);
    }
    // 3. value > node->val -> 插右边
    else if(value > node->val){
        node->right = insert(node->right, value);
    }
    // 4. value == node->val -> 忽略重复值
    else{
        return node;
    }

    // TODO 第二步：更新当前节点高度
    // node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    // TODO 第三步：计算平衡因子
    // int balance = getBalance(node);
    int balance = getBalance(node);

    // TODO 第四步：判断 4 种失衡
    //
    // LL: balance > 1 && value < node->left->val
    //     return rightRotate(node);
    if(balance > 1 && value < node->left->val)
        node = rightRotate(node);
    // RR: balance < -1 && value > node->right->val
    //     return leftRotate(node);
    else if(balance < -1 && value > node->right->val)
        node = leftRotate(node);
    // LR: balance > 1 && value > node->left->val
    //     node->left = leftRotate(node->left);
    //     return rightRotate(node);
    else if(balance > 1 && value > node->left->val){
        node->left = leftRotate(node->left);
        node = rightRotate(node);
    }
    // RL: balance < -1 && value < node->right->val
    //     node->right = rightRotate(node->right);
    //     return leftRotate(node);
    else if(balance < -1 && value < node->right->val){
        node->right = rightRotate(node->right);
        node = leftRotate(node);
    }

    return node;
}

AVLTree::Node* AVLTree::remove(Node* node, int value) {
    // 1. 标准 BST 删除
    if (!node) return nullptr;

    if (value < node->val) {
        node->left = remove(node->left, value);
    }
    else if (value > node->val) {
        node->right = remove(node->right, value);
    }
    else {
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
            Node* minNode = node->right;
            while (minNode->left) {
                minNode = minNode->left;
            }

            node->val = minNode->val;
            node->right = remove(node->right, minNode->val);
        }
    }

    // 2. 如果当前节点已经为空，直接返回
    if (!node) return nullptr;

    // 3. 更新高度
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    // 4. 计算平衡因子
    int balance = getBalance(node);

    // 5. 四种失衡修复

    // LL
    if (balance > 1 && getBalance(node->left) >= 0)
        return rightRotate(node);

    // LR
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RR
    if (balance < -1 && getBalance(node->right) <= 0)
        return leftRotate(node);

    // RL
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}