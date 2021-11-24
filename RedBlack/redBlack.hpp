#ifndef REDBLACK_HPP
#define REDBLACK_HPP
#include <iostream>

enum Color {RED, BLACK};
class redBlack
{
private:
    struct Node
    {
        int data;
        bool color;
        Node *left, *right, *parent;
    };
public:
private:
    typedef Node*   nodePtr;
    nodePtr root;
    nodePtr end;
    
    nodePtr privateInsert (nodePtr node, nodePtr x);
    void    rightRotation(nodePtr x);
    void    leftRotation(nodePtr x);
    void    fixViolation (nodePtr& node, nodePtr& x);
    nodePtr createLeaf(const int& data);
	
    //Deletetion
    nodePtr	privateReturnNode(int key, nodePtr ptr);
    nodePtr findSmallest(nodePtr);
    void    link2Nodes(nodePtr, nodePtr);
    void    deleteNodeHelper(nodePtr node , const int &data);
    void    fixDB(nodePtr);
    nodePtr successor(nodePtr x);
    //print
    void    print2DUtil(nodePtr root, int space);
    void    privateprint2D(nodePtr root);
    void    printHelper(nodePtr root, std::string indent, bool last);

public:
    redBlack();
    ~redBlack();
    void    insert(const int& data);
    void    deleteNode(const int& data);
    nodePtr	returnNode(int key);
    void	printChildren(int key);
    void    print2D();
    nodePtr getRoot() const ;
    void    prettyPrint();
    nodePtr succ(const int& data);
};

#endif /* REDBLACK_HPP */
