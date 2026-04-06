#include "RBTree.hh"
#include <iostream>

int main() {
    RBTree tree;

    int arr[] = {20, 10, 30, 5, 15, 25, 40, 3, 8, 13, 18};
    int n = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < n; ++i) {
        tree.insert(arr[i]);
    }

    std::cout << "Initial inorder: ";
    tree.inorder();
    std::cout << '\n';
    std::cout << "Valid: " << tree.isRBTree() << '\n';
    std::cout << "Size: " << tree.size() << '\n';
    std::cout << "Height: " << tree.height() << '\n';
    std::cout << '\n';

    int delArr[] = {3, 5, 20, 30, 10, 15};
    int m = sizeof(delArr) / sizeof(delArr[0]);

    for (int i = 0; i < m; ++i) {
        tree.remove(delArr[i]);
        std::cout << "After remove " << delArr[i] << ":\n";
        std::cout << "Inorder: ";
        tree.inorder();
        std::cout << '\n';
        std::cout << "Valid: " << tree.isRBTree() << '\n';
        std::cout << "Size: " << tree.size() << '\n';
        std::cout << "Height: " << tree.height() << '\n';
        std::cout << '\n';
    }

    return 0;
}