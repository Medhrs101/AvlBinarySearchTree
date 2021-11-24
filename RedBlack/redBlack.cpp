/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redBlack.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <moharras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 02:57:40 by moharras          #+#    #+#             */
/*   Updated: 2021/11/24 01:17:03 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./redBlack.hpp"

redBlack::redBlack(/* args */)
{
	std::cout << "Default constructor from redBlack" << std::endl;
	end = new Node;
	end->left = nullptr;
	end->right = nullptr;
	end->data = -101;
	end->color = BLACK;
	root = end;
}

redBlack::~redBlack()
{
	std::cout << "Destructor from redBlack" << std::endl;
}

redBlack::nodePtr redBlack::privateInsert(nodePtr node, nodePtr x)
{
	if (node == end)
		return x;
	if (x->data < node->data)
	{
		node->left = privateInsert(node->left, x);
		node->left->parent = node;
	}
	else if (x->data > node->data)
	{
		node->right = privateInsert(node->right, x);
		node->right->parent = node;
	}
	return node;
}

void redBlack::leftRotation(nodePtr x)
{
	nodePtr y = x->right;
	x->right = y->left;
	if (y->left != end) {
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == nullptr) {
		root = y;
	} else if (x == x->parent->left) {
		x->parent->left = y;
	} else {
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

	// rotate right at node x
void redBlack::rightRotation(nodePtr x)
{
	nodePtr y = x->left;
	x->left = y->right;
	if (y->right != end) {
		y->right->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == nullptr) {
		root = y;
	} else if (x == x->parent->right) {
		x->parent->right = y;
	} else {
		x->parent->left = y;
	}
	y->right = x;
	x->parent = y;
}

template <class T>
void	swap(T& a, T& b)
{
	T temp;
	temp = a;
	a = b;
	b = temp;
}

void redBlack::fixViolation(nodePtr& node, nodePtr& x)
{
	nodePtr xParent = nullptr;
	nodePtr xGrandPa = nullptr;
	
	/*NOTE: just Notation for simplification:
			granpa has two children, oldest and youngest
	*/
	/*NOTE:: chain greater or equal than three nodes black-->red-->red
			at leat
	*/ 
	while((x != node) && (x->color != BLACK ) && (x->parent->color == RED))
	{
		xParent = x->parent;
		xGrandPa = x->parent->parent;
		/*NOTE:: there is two cases:
				1. x child of youngest (x->parent == xGrandpa->left)
				2. x child of oldest (x->parent == xGrandpa->rightt)		
		*/ 
		
		if (xParent == xGrandPa->left)
		{
			nodePtr xUncle = xGrandPa->right;
		/*NOTE: x Uncle exist and he is a red color*/
			if (xUncle != end && xUncle->color == RED)
			{
				xGrandPa->color = RED;
				xParent->color = BLACK;
				xUncle->color = BLACK;
				x = xGrandPa;
			}
		/*NOTE: x Uncle black or nullptr*/
			else
			{
				if (x == xParent->right)
				{
					leftRotation(xParent);
					x = xParent;
					xParent = x->parent;
				}
				rightRotation(xGrandPa);
				swap(xParent->color, xGrandPa->color);
				x = xParent;
			}
		}
		else
		{
			nodePtr xUncle = xGrandPa->left;
			if (xUncle != end && xUncle->color == RED)
			{
				xGrandPa->color = RED;
				xParent->color = BLACK;
				xUncle->color = BLACK;
				x = xGrandPa;
			}
			else
			{
				if (x == xParent->left)
				{
					rightRotation(xParent);
					x = xParent;
					xParent = x->parent;
				}
				leftRotation(xGrandPa);
				swap(xParent->color, xGrandPa->color);
				x = xParent;
			}
		}
	}
	node->color = BLACK;
}

redBlack::nodePtr	redBlack::createLeaf(const int& data)
{
	nodePtr	leaf = new Node;
	leaf->parent = nullptr;
	leaf->right = end;
	leaf->left = end;
	leaf->color = RED;
	leaf->data = data;
	return leaf;
}
void    redBlack::insert(const int& data)
{
	nodePtr x = createLeaf(data);
	root = privateInsert(root, x);
	root ->parent = end;
	end->left = root;
	fixViolation(root, x);
	// std::cout << "here: " << data << std::endl;
}

redBlack::nodePtr	redBlack::privateReturnNode(int key, nodePtr ptr)
{
	if (ptr != end)
	{
		if (key == ptr->data)
			return ptr;
		else
		{
			if (key < ptr->data)
				return privateReturnNode(key, ptr->left);
			else
				return privateReturnNode(key, ptr->right);
		}
	}
	else
		return end;
}

redBlack::nodePtr	redBlack::returnNode(int key)
{
	return (privateReturnNode(key, root));
}

void	redBlack::printChildren(int key)
{
	Node*	ptr = returnNode(key);
	if (ptr != nullptr)
	{
		std::cout << "Parent Node: " << ptr->data << std::endl;
		(ptr->left == nullptr) ?
		std::cout << "Left child = NULL" << std::endl :
		std::cout << "left child = " << ptr->left->data << std::endl;
		(ptr->right == nullptr) ?
		std::cout << "right child = NULL" << std::endl :
		std::cout << "right child = " << ptr->right->data << std::endl;
	}
	else
		std::cout << "Key: " << key << "is not in the tree" << std::endl; 
}
#define COUNT 10
#define RESET   "\033[0m"
#define REDD     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
void redBlack::print2DUtil(nodePtr root, int space)
{
    // Base case
    if (root == end)
        return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    print2DUtil(root->right, space);
 
    // Print current node after space
    // count
    std::cout << std::endl;
    for (int i = COUNT; i < space; i++)
        std::cout<<" ";
	if(root->color == RED)
    std::cout << REDD << root->data << RESET << "\n";
	else
    std::cout << root->data << "\n";

    // Process left child
    print2DUtil(root->left, space);
}
 
// Wrapper over print2DUtil()
void redBlack::privateprint2D(nodePtr root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}
void	redBlack::print2D()
{
	privateprint2D(root);
}

void	redBlack::link2Nodes(nodePtr first, nodePtr second)
{
	if (first->parent == nullptr)
	{
		root = second;
	}
	else if (first == first->parent->left)
	{
		first->parent->left = second;
	}
	else
	{
		first->parent->right = second;
		
	}
	second->parent = first->parent;
}

redBlack::nodePtr		redBlack::findSmallest(nodePtr ptr)
{
	while (ptr->left != end)
		ptr = ptr->left;
	return ptr;
}

void	redBlack::fixDB(nodePtr x)
{
	nodePtr sib;
	// std::cout << x->parent->data << std::endl;
	while(x != root && x->color == BLACK)
	{
			// std::cout << "hellllo" << std::endl;
			// std::cout << x->data << std::endl;
			// exit (0);
		if (x == x->parent->left)
		{
			sib = x->parent->right;
			// Case: 4
			if (sib->color == RED)
			{
				sib->color = BLACK;
				x->parent->color = RED;
				leftRotation(x->parent);
				sib = x->parent->right; 
			}

			if (sib->left->color == BLACK && sib->right->color == BLACK)
			{
				// Case 3
				sib->color = RED;
				x = x->parent;
			}
			else 
			{
				// Case 5
				if (sib->right->color == BLACK)
				{
					sib->color = RED;
					sib->right->color = BLACK;
					rightRotation(sib);
					sib = x->parent->right;
				}
				// Case 6:
				sib->color = x->parent->color;
				x->parent->color = BLACK;
				sib->right->color = BLACK;
				leftRotation(x->parent);
				x = root;
			}
		}
		else
		{
			sib = x->parent->left;
			if (sib->color == RED)
			{
				sib->color = BLACK;
				x->parent->color = RED;
				rightRotation(x->parent);
				sib = x->parent->left;
			}
			
			if (sib->right->color == BLACK && sib->right->color == BLACK)
			{
				sib->color = RED;
				x = x->parent;
			}
			else
			{
				if (sib->left->color == BLACK)
				{
					// case 3.3
					sib->right->color = BLACK;
					sib->color = RED;
					leftRotation(sib);
					sib = x->parent->left;
				}	
				sib->color = x->parent->color;
				x->parent->color = BLACK;
				sib->left->color = BLACK;
				rightRotation(x->parent);
				x = root;
			}
		}
	}
	x->color = BLACK;
}

void	redBlack::deleteNodeHelper(nodePtr node, const int& data)
{
	nodePtr	z = returnNode(data);
	nodePtr x, y = z;
	bool yColor = y->color;
	// if the node has one child on the right side
	if (z->left == end)
	{
		x = z->right;
		link2Nodes(z, z->right);
	}
	else if (z->right == end)
	{
		
		x = z->left;
		link2Nodes(z, z->left);
	}
	else
	{
		y = findSmallest(z->right);
		yColor = y->color;
		x = y->right; // x is right from the node will be deleted
		if (y->parent == z)
			x->parent = y;
		else
		{
			link2Nodes(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		link2Nodes(z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	delete z;
	// if yColor is black its a DB(double black) and its one of DB cases
	if (yColor == BLACK)
	{
		fixDB(x);
	}
}

void	redBlack::deleteNode(const int& data)
{
	deleteNodeHelper(root, data);
}


redBlack::nodePtr redBlack::getRoot() const
{
	return this->root;
}

void	redBlack::printHelper(nodePtr root, std::string indent, bool last)
{
	// print the tree structure on the screen
   	if (root != end)
	{
		std::cout << indent;
		if (last)
		{
	    	std::cout << "R----";
			indent += "     ";
		}
		else
		{
			std::cout<<"L----";
	    	indent += "|    ";
		}
		
       std::string sColor = root->color?"RED":"BLACK";
	   std::cout<<root->data<<"("<<sColor<<")"<< std:: endl;
	   printHelper(root->left, indent, false);
	   printHelper(root->right, indent, true);
	}
	// cout<<root->left->data<<endl;
}

void redBlack::prettyPrint()
{
	if (root)
	{
		printHelper(this->root, "", true);
    }
}

redBlack::nodePtr	redBlack::successor(nodePtr x)
{
	if (x->right != end)
		return(findSmallest(x->right));

	nodePtr y = x->parent;
	while (y != end && x == y->right)
	{
		x = y;
		y = y->parent;
	}
	return y;
}

redBlack::nodePtr redBlack::succ(const int& data)
{
	return successor(returnNode(data));
}