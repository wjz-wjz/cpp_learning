#include "AVL.hh"
#include <iostream>

void testCase(const char* name, const int arr[], int n) {
    AVLTree tree;

    for (int i = 0; i < n; ++i) {
        tree.insert(arr[i]);
    }

    std::cout << "===== " << name << " =====\n";

    std::cout << "Preorder: ";
    tree.preorder();
    std::cout << '\n';

    std::cout << "Inorder: ";
    tree.inorder();
    std::cout << '\n';

    std::cout << "Height: " << tree.height() << '\n';
    std::cout << "Size: " << tree.size() << '\n';
    std::cout << '\n';
}

void testRemove() {
    AVLTree tree;
    int arr[] = {20, 10, 30, 5, 15, 25, 40, 3, 8, 13, 18};
    int n = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < n; ++i) {
        tree.insert(arr[i]);
    }

    std::cout << "===== Remove Test =====\n";

    std::cout << "Initial inorder: ";
    tree.inorder();
    std::cout << '\n';

    std::cout << "Initial preorder: ";
    tree.preorder();
    std::cout << '\n';

    std::cout << "Initial height: " << tree.height() << '\n';
    std::cout << "Initial size: " << tree.size() << '\n';
    std::cout << '\n';

    tree.remove(3);   // 叶子
    std::cout << "After remove 3:\n";
    std::cout << "Inorder: ";
    tree.inorder();
    std::cout << '\n';
    std::cout << "Preorder: ";
    tree.preorder();
    std::cout << '\n';
    std::cout << "Height: " << tree.height() << '\n';
    std::cout << "Size: " << tree.size() << '\n';
    std::cout << '\n';

    tree.remove(5);   // 单孩子或接近单孩子
    std::cout << "After remove 5:\n";
    std::cout << "Inorder: ";
    tree.inorder();
    std::cout << '\n';
    std::cout << "Preorder: ";
    tree.preorder();
    std::cout << '\n';
    std::cout << "Height: " << tree.height() << '\n';
    std::cout << "Size: " << tree.size() << '\n';
    std::cout << '\n';

    tree.remove(20);  // 删除根，双孩子
    std::cout << "After remove 20:\n";
    std::cout << "Inorder: ";
    tree.inorder();
    std::cout << '\n';
    std::cout << "Preorder: ";
    tree.preorder();
    std::cout << '\n';
    std::cout << "Height: " << tree.height() << '\n';
    std::cout << "Size: " << tree.size() << '\n';
    std::cout << '\n';
}

int main() {
    int ll[] = {30, 20, 10};
    int rr[] = {10, 20, 30};
    int lr[] = {30, 10, 20};
    int rl[] = {10, 30, 20};

    testCase("LL", ll, 3);
    testCase("RR", rr, 3);
    testCase("LR", lr, 3);
    testCase("RL", rl, 3);

    testRemove();

    return 0;
}