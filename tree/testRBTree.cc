#include "RBTree.hh"
#include <iostream>

int main() {
    RBTree tree;

    int arr[] = {10, 20, 30, 15, 25, 5, 1, 50, 60, 55};
    int n = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < n; ++i) {
        tree.insert(arr[i]);
    }

    std::cout << "Inorder: ";
    tree.inorder();
    std::cout << '\n';

    std::cout << "Preorder: ";
    tree.preorder();
    std::cout << '\n';

    std::cout << "Size: " << tree.size() << '\n';
    std::cout << "Height: " << tree.height() << '\n';

    std::cout << "Contains 25: " << tree.contains(25) << '\n';
    std::cout << "Contains 100: " << tree.contains(100) << '\n';

    std::cout << "Min: " << tree.findMin() << '\n';
    std::cout << "Max: " << tree.findMax() << '\n';

    std::cout << tree.isRBTree() << '\n';

    return 0;
}