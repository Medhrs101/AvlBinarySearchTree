#include "./avlBst.hpp"

int main()
{
    int arr[7] = {40, 20, 10, 25, 30, 22, 50};
    avlBst *avl_tree = new avlBst();
    for (int i = 0; i < 7; i++)
    {
        avl_tree->insert(arr[i]);
    }
    // avl_tree->preOrder();
    // avl_tree->printInOrder();
    

    std::cout << "*****************************************************************Print Family " << std::endl;
    for (int i = 0; i < 7; i++)
    {
        avl_tree->printChildren(arr[i]);
        std::cout << std::endl;
    }
    std::cout << "*****************************************************************Print Family " << std::endl;

    // std::cout << "*****************************************************************remove Node " << std::endl;
    // avl_tree->removeNode(30);
    // avl_tree->removeNode(50);
    // avl_tree->insert(23);
    // std::cout << "*****************************************************************remove Node " << std::endl;

    std::cout << "*****************************************************************Print Family " << std::endl;
    for (int i = 0; i < 7; i++)
    {
        avl_tree->printChildren(arr[i]);
        std::cout << std::endl;
    }
    std::cout << "*****************************************************************Print Family " << std::endl;

    std::cout << "*****************************************************************inOrderSuccessor " << std::endl;
    std::cout << (avl_tree->inOrderSuccessor(50))->_key << std::endl;
    std::cout << "*****************************************************************inOrderSuccessor " << std::endl;
    std::cout << std::endl;
    delete avl_tree;
    return 0;
}