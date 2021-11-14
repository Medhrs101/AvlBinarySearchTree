/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <moharras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 07:33:09 by moharras          #+#    #+#             */
/*   Updated: 2021/11/14 15:55:43 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./BST.hpp"

int main()
{
    BST *bst = new BST();
    // int Array[16] = {50, 76, 21, 4, 32, 64, 15, 52, 14, 100, 83, 2, 3, 70, 87, 80};
    
    //NOTE ADD leafs(nodes) in tree
    std::cout << "*****************************************************************Add Leaf" << std::endl;
    for (int i = 0; i < 49; i++)
        bst->addLeaf(i);
        bst->Createleaf(3);
    std::cout << "*****************************************************************Add Leaf" << std::endl;
    
    std::cout << "Number of Nodes: "<< bst->getcount() << std::endl;

    std::cout << "*****************************************************************Print In Order" << std::endl;
    bst->printInOrder();
    std::cout << std::endl;
    std::cout << "*****************************************************************Print In Order" << std::endl;
    
    // std::cout << "*****************************************************************Print Family " << std::endl;
    // for (int i = 0; i < 16; i++)
    // {
    //     bst->printChildren(Array[i]);
    // }
    // std::cout << "*****************************************************************Print Family " << std::endl;
    
    std::cout << "*****************************************************************Find the smallest value " << std::endl;
    std::cout << "The smallest value is: " << bst->findSmallest() << std::endl;
    std::cout << "*****************************************************************Find the samllest value " << std::endl;
    
    std::cout << "*****************************************************************remove node " << std::endl;
    std::cout << "Before remove : " ; bst->printInOrder(); std::cout << std::endl;
    bst->removeNode(52);
    std::cout << "After remove : "; bst->printInOrder(); std::cout << std::endl;    
    // std::cout << "*****************************************************************remove node " << std::endl;
    delete bst;
    // bst = nullptr;
    return 0;
}