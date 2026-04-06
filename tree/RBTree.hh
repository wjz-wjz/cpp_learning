#pragma once
#include <iostream>

class RBTree {
private:
    enum Color { BLACK, RED };

    struct RBNode {
        int val;
        Color color;
        RBNode* parent;
        RBNode* left;
        RBNode* right;

        RBNode(int v = 0, Color c = BLACK)
            : val(v), color(c), parent(nullptr), left(nullptr), right(nullptr) {}
    };

    RBNode* root;
    RBNode* NIL;

public:
    RBTree();
    ~RBTree();

    bool contains(int target) const;
    int size() const;
    int height() const;

    void inorder() const;
    void preorder() const;
    void postorder() const;

    int findMin() const;
    int findMax() const;

    void insert(int value);
    void remove(int value);

    bool isRBTree() const;

private:
    void destroy(RBNode* node);

    void transplant(RBNode* node1, RBNode* node2);

    bool contains(RBNode* node, int target) const;
    int size(RBNode* node) const;
    int height(RBNode* node) const;

    void inOrder(RBNode* node) const;
    void preOrder(RBNode* node) const;
    void postOrder(RBNode* node) const;

    RBNode* findMin(RBNode* node) const;
    RBNode* findMax(RBNode* node) const;

    void leftRotate(RBNode* node);
    void rightRotate(RBNode* node);

    void insertFix(RBNode* node);
    void deleteFix(RBNode* node);

    bool isBST(RBNode* node, long long low, long long high) const;
    bool hasNoRedRed(RBNode* node) const;
    int blackHeight(RBNode* node) const;
};