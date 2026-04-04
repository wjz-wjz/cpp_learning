#pragma once
#include <iostream>

class AVLTree {
private:
    struct Node {
        int val;
        int height;
        Node* left;
        Node* right;

        Node(int value) : val(value), height(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

public:
    AVLTree();
    ~AVLTree();

    void insert(int value);
    void remove(int target);

    bool contains(int target) const;

    void inorder() const;
    void preorder() const;
    void postorder() const;

    int height() const;
    int size() const;

private:
    void destroy(Node* node);

    Node* insert(Node* node, int value);
    Node* remove(Node* node, int target);
    bool contains(Node* node, int target) const;

    void inOrder(Node* node) const;
    void preOrder(Node* node) const;
    void postOrder(Node* node) const;

    int size(Node* node) const;

    int getHeight(Node* node) const;
    int getBalance(Node* node) const;

    Node* leftRotate(Node* node);
    Node* rightRotate(Node* node);
};