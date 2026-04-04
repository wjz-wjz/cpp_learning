#pragma once
#include <iostream>

class BinaryTree{
protected:
    struct Node{
        int val;
        Node* left;
        Node* right;

        Node(int value){
            val = value;
            left = nullptr;
            right = nullptr;
        }
    };
    Node* root;

public:
    BinaryTree();
    BinaryTree(int value);
    ~BinaryTree();

    void preorder() const;
    void inorder() const;
    void postorder() const;

    int size() const;
    int height() const;
    bool contains(int target) const;
    Node* getRoot() {return root;}
    void setRoot(Node* node) {root = node;}

private:
    void destroy(Node*);
    void preOrder(Node*) const;
    void inOrder(Node*) const;
    void postOrder(Node*) const;
    int size(Node*) const;
    int height(Node*) const;
    bool contains(Node*, int target) const;
};