/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BST.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <moharras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 09:43:22 by moharras          #+#    #+#             */
/*   Updated: 2021/11/14 11:47:58 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BST.hpp"

BST::BST(): count(0), root(nullptr)
{
	std::cout << "Default Constructor called from Bst" << std::endl;
	root = NULL;
}

BST::~BST()
{
	std::cout << "Destructor called from Bst" << std::endl;
}

BST::Node*  BST::Createleaf(int key)
{
	Node*   leaf = new Node();
	
	leaf->_key = key;
	leaf->_left = nullptr;
	leaf->_right = nullptr;
	return (leaf);
}

void    BST::privateAddLeaf(int key, Node*  ptr)
{
	if (root == nullptr)
	{
		root = Createleaf(key);
		count++;
	}
	else if (key < ptr->_key)
	{
		if (ptr->_left != nullptr)
			privateAddLeaf(key, ptr->_left);
		else
		{
			ptr->_left = Createleaf(key);
			count++;
		}
	}
	else if (key > ptr->_key)
	{
		if (ptr->_right != nullptr)
			privateAddLeaf(key, ptr->_right);
		else
		{
			ptr->_right = Createleaf(key);
			count++;
		}
	}
	else
		std::cout << "Key is already exist" << std::endl;
	return ;
}


void    BST::addLeaf(int key)
{
	privateAddLeaf(key, root);
}


void	BST::privatePrintInOrder(Node* ptr)
{
	if (root != nullptr)
	{
		if (ptr->_left != nullptr)
			privatePrintInOrder(ptr->_left);
		std::cout << ptr->_key << "|";
		if (ptr->_right != nullptr)
			privatePrintInOrder(ptr->_right);
	}
	else
		std::cout << "Tree is empty" << std::endl;
}

void	BST::printInOrder()
{
	privatePrintInOrder(root);
}

BST::Node*	BST::privateReturnNode(int key, Node *ptr)
{
	if (ptr != nullptr)
	{
		if (key == ptr->_key)
			return ptr;
		else
		{
			if (key < ptr->_key)
				return privateReturnNode(key, ptr->_left);
			else
				return privateReturnNode(key, ptr->_right);
		}
	}
	else
		return nullptr;
}

BST::Node*	BST::returnNode(int key)
{
	return (privateReturnNode(key, root));
}

int		BST::returnRootKey()
{
	if (root != nullptr)
		return root->_key;
	else
	{
		std::cout << "Tree is empty" << std::endl;
		return (-1000);
	}
}

void	BST::printChildren(int key)
{
	Node*	ptr = returnNode(key);
	if (ptr != nullptr)
	{
		std::cout << "Parent Node: " << ptr->_key << std::endl;
		(ptr->_left == nullptr) ?
		std::cout << "Left child = NULL" << std::endl :
		std::cout << "left child = " << ptr->_left->_key << std::endl;
		(ptr->_right == nullptr) ?
		std::cout << "right child = NULL" << std::endl :
		std::cout << "right child = " << ptr->_right->_key << std::endl;
	}
	else
		std::cout << "Key: " << key << "is not in the tree" << std::endl; 
}

int		BST::privateFindSmallest(Node *ptr)
{
	if (root == nullptr)
	{
		std::cout << "The tree is empty" <<  std::endl;
		return (-1000);  
	}
	else
	{
		if (ptr->_left != nullptr)
			return (privateFindSmallest(ptr->_left));
		else
			return ptr->_key;
	}
}

int		BST::findSmallest()
{
	return (privateFindSmallest(root));
}

void	BST::privateRemoveNode(int key, Node *parent)
{
	if (root != nullptr)
	{
		if (root->_key == key)
			removeRootMatch();
		else
		{
			if (key < parent->_key && parent->_left != nullptr)
			{
				parent->_left->_key == key ?
				removeMatch(parent, parent->_left, true):
				privateRemoveNode(key, parent->_left);
			}
			else if (key > parent->_key && parent->_right != nullptr)
			{
				parent->_right->_key == key ?
				removeMatch(parent, parent->_right, false):
				privateRemoveNode(key, parent->_right);
			}
			else
				std::cout << "The key: " << key << " was not found in the tree" << std::endl;
 		}
	}
	else
		std::cout << "The tree is empty" << std::endl;
}

void	BST::removeNode(int key)
{
	privateRemoveNode(key, root);
}

void	BST::removeRootMatch()
{
	if (root != NULL)
	{
		Node *delPtr = root;
		int rootkey = root->_key;
		int smallestInRightSubtree;
		
		//NOTE : 0 - 0 child
		if (root->_left == nullptr && root->_left == nullptr)
		{
			root = nullptr;
			delete delPtr;
		}
		//NOTE : 1 - 0 child
		else if (root->_left != nullptr && root->_right == nullptr)
		{
			root = root->_left;
			delPtr->_left = nullptr;
			delete delPtr;
			std::cout << "The root node with key " << rootkey << " was deleted. " \
			<< "the new root contains key " << root->_key << std::endl; 
		}
		//NOTE: 0 - 1
		else if (root->_right != nullptr && root->_left == nullptr)
		{
			root = root->_right;
			delPtr->_right = nullptr;
			delete delPtr;
			std::cout << "The root node with key " << rootkey << " was deleted. " \
			<< "the new root contains key " << root->_key << std::endl;
		}
		//NOTE: 1 - 1
		else
		{
			smallestInRightSubtree = privateFindSmallest(root->_right);
			privateRemoveNode(smallestInRightSubtree, root);
			root->_key = smallestInRightSubtree;
			std::cout << "The root key containing key: " << rootkey << \
			" was overwritten with key: " << root->_key << std::endl;	
		}
	}
	else
	{
		std::cout << "can not remove root. The tree is empty" << std::endl;
	}
}

void	BST::removeMatch(Node* parent, Node* match, bool left)
{
	if (root != nullptr)
	{
		Node*	delPtr;
		int		matchKey = match->_key;
		int		smallestInRightSubtree;
		
		//NOTE: 0 - 0 children
		if (match->_left == nullptr && match->_right == nullptr)
		{
			delPtr = match;
			left = true ? parent->_left = nullptr : parent->_right = nullptr;
			delete delPtr;
			std::cout << "The node containing key " << matchKey << " was removed" << std::endl;
		}
		//NOTE: 1 - 0 children
		else if (match->_left != nullptr && match->_right == nullptr)
		{
			left == true ? parent->_left = match->_left : parent->_right = match->_left;
			match->_left = nullptr;
			delPtr = match;
			delete delPtr;
		}
		//NOTE: 0 - 1 children
		else if (match->_right != nullptr && match->_left == nullptr)
		{
			left == true ? parent->_left = match->_right : parent->_right = match->_right;
			match->_right = nullptr;
			delPtr = match;
			delete delPtr;
		}
		//NOTE:: 1 - 1 children
		else
		{
			smallestInRightSubtree = privateFindSmallest(match->_right);
			privateRemoveNode(smallestInRightSubtree, match);
			match->_key = smallestInRightSubtree;
		}
	}
	else
	{
		std::cout << "Can not remove match, The tree is empty." << std::endl;
	}
}