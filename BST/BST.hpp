#ifndef BST_HPP
#define BST_HPP
#include <iostream>

class BST
{
private:
	struct Node
	{
		int     _key;
		Node*   _right;
		Node*   _left;
	};
	int count;
	Node    *root;
	void    privateAddLeaf(int key, Node* ptr);
	void	privatePrintInOrder(Node *ptr);
	Node*	privateReturnNode(int key, Node* ptr);
	int		privateFindSmallest(Node* ptr);
	void	privateRemoveNode(int key, Node *parent	);
	void	removeRootMatch();
	void	removeMatch(Node *parent, Node* match, bool left);
public:
	BST();
	~BST();
	Node*   Createleaf(int key);
	void    addLeaf(int key);
	void	printInOrder();
	Node*	returnNode(int key);
	int		returnRootKey();
	void	printChildren(int key);
	int		findSmallest();
	void	removeNode(int key);
	const int& getcount() const {return (count);}
	const int& getkey(Node *ptr) const {return ptr->_key;};

};

#endif /* BST_HPP */
