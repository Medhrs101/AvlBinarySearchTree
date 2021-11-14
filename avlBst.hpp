#ifndef AVLBST_HPP
#define AVLBST_HPP
#include <iostream>

class avlBst
{
private:
	struct  Node
	{
		int		_key;
		int		_height;
		Node*   _left;
		Node*	_right;
	};
	Node *root;
	Node*	privateInsert(int key, Node* ptr);
	int		height(Node *ptr);
	int		getBalance(Node*);
	Node*	rightRotation (Node *y);
	Node*	leftRotation (Node *x);
	void	privatePrintInOrder(Node* ptr);
	void 	privatePreOrder(Node* ptr);
	Node*	privateReturnNode(int key, Node* ptr);
	
	int		privateFindSmallest(Node *ptr);
	void	removeMatch(Node *parent, Node *match, bool left);
	void	removeRootMatch();
	Node*	privateRemoveNode(int key, Node *parent);

public:
	avlBst();
	~avlBst();
	Node*   createLeaf(int key);
	void   insert(int key);
	void	removeNode(int key);
	void	printInOrder();
	void 	preOrder();
	void	printChildren(int key);
	Node*	returnNode(int key);
};

#endif /* AVLBST_HPP */
