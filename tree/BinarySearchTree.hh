#pragma once
#include "BinaryTree.hh"

class BST : public BinaryTree {
public:
    BST();

    void insert(int value);
    bool contains(int target) const;

    int findMin() const;
    int findMax() const;

    void remove(int value);

private:
    Node* insert(Node* node, int value);
    bool contains(Node* node, int target) const;

    Node* findMin(Node* node) const;
    Node* findMax(Node* node) const;

    Node* remove(Node* node, int value);
};