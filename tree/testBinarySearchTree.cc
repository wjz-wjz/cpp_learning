#include "BinarySearchTree.hh"

int main(){
    BST* bst = new BST();
    int array[9] = {8, 3, 10, 1, 6, 14, 4, 7, 13};
    for(int i=0; i<9; i++){
        bst->insert(array[i]);
    }

    bst->inorder();
    bst->remove(3);
    bst->inorder();
    bst->insert(-9);
    bst->inorder();

    delete bst;
    return 0;

}