#include <iostream>
#include "./redBlack.hpp"

int main()
{
    int arr[8] = {50, 35, 70, 80, 15, 65, 68, 90};
    redBlack *avl_tree = new redBlack();
    for (int i = 0; i < 8; i++)
    {
        avl_tree->insert(arr[i]);
    }
    // avl_tree->preOrder();
    // avl_tree->printInOrder();
    avl_tree->print2D();
    // avl_tree->prettyPrint();

    std::cout  << "Successor: " << (avl_tree->succ(70))->data << std::endl;


    // std::cout << "*****************************************************************Print Family " << std::endl;
    // for (int i = 0; i < 12; i++)
    // {
    //     avl_tree->printChildren(arr[i]);
    //     std::cout << std::endl;
    // }
    // std::cout << "*****************************************************************Print Family " << std::endl;

    // std::cout << "*****************************************************************remove TEST " << std::endl;
    // avl_tree->print2D();
    // std::cout << "*****************************************************************Print Family " << std::endl;
    // avl_tree->deleteNode(90);
    // avl_tree->print2D();
    // std::cout << "*****************************************************************Print Family " << std::endl;
    // avl_tree->deleteNode(80);
    // avl_tree->print2D();
    // std::cout << "*****************************************************************Print Family " << std::endl;
    // avl_tree->deleteNode(50);
    // avl_tree->print2D();
    // std::cout << "*****************************************************************Print Family " << std::endl;
    // avl_tree->deleteNode(15);
    // avl_tree->print2D();
    // std::cout << "*****************************************************************Print Family " << std::endl;
    // avl_tree->deleteNode(35);
    // avl_tree->print2D();
    // std::cout << "*****************************************************************Print Family " << std::endl;
    // avl_tree->deleteNode(65);
    // avl_tree->print2D();
    // std::cout << "*****************************************************************Print Family " << std::endl;
    // avl_tree->deleteNode(70);
    // avl_tree->print2D();
    // std::cout << "*****************************************************************Print Family " << std::endl;
    // avl_tree->deleteNode(68);
    // avl_tree->print2D();
    // std::cout << "*****************************************************************Print Family " << std::endl;
    // std::cout << avl_tree->getRoot()->parent << std::endl;
    // std::cout << "*****************************************************************remove TEST " << std::endl;

    // std::cout << "*****************************************************************remove Node " << std::endl;
    // avl_tree->removeNode(30);
    // avl_tree->removeNode(50);
    // avl_tree->insert(23);
    // std::cout << "*****************************************************************remove Node " << std::endl;

    // std::cout << "*****************************************************************Print Family " << std::endl;
    // for (int i = 0; i < 7; i++)
    // {
    //     avl_tree->printChildren(arr[i]);
    //     std::cout << std::endl;
    // }
    // std::cout << "*****************************************************************Print Family " << std::endl;

    // std::cout << "*****************************************************************inOrderSuccessor " << std::endl;
    // std::cout << (avl_tree->inOrderSuccessor(50))->_key << std::endl;
    // std::cout << "*****************************************************************inOrderSuccessor " << std::endl;
    // std::cout << std::endl;
    delete avl_tree;
    return 0;
}
// int main()
// {
//     int p = 5;
//     std::cout << "&p: " << &p << std::endl;
//     int *ptr = &p;
//     std::cout << "ptr: " << ptr << std::endl;
//     std::cout << "&ptr: " << &ptr << std::endl;
//     int **pptr = &ptr;
//     std::cout << "**ptr: " << pptr << std::endl;

//     return 0;
// }
