#include "./avlBst.hpp"

avlBst::avlBst(): root(nullptr)
{
    std::cout << "Default constructor called from avlBst" << std::endl;
}

avlBst::~avlBst()
{
    std::cout << "Destructor" << std::endl;
}

avlBst::Node*   avlBst::createLeaf(int key)
{
    Node*   leaf = new Node();
    leaf->_key = key;
    leaf->_right = nullptr;
    leaf->_left = nullptr;
    leaf->_height = 1;
    return leaf;
}

int     max(int x, int y)
{
    return x > y ? x: y;
}

int     avlBst::height(Node* ptr)
{
    if (ptr == nullptr)
        return 0;
    return ptr->_height;
}

int    avlBst::getBalance(Node* ptr)
{
    if (ptr == nullptr)
        return 0;
    return (height(ptr->_left) - height(ptr->_right));
}

avlBst::Node*	avlBst::rightRotation(Node* y)
{
	Node*	x = y->_left;
	Node*	T2 = x->_right;

	x->_right = y;
	y->_left = T2;
	y->_height = max(height(y->_left), height(y->_right)) + 1;
	x->_height = max(height(x->_left), height(x->_right)) + 1; 
	return x;
}

avlBst::Node*	avlBst::leftRotation(Node* x)
{
	Node*	y = x->_right;
	Node*	T2 = y->_left;

	y->_left = x;
	x->_right = T2;

	x->_height = max(height(x->_left), height(x->_right)) + 1;
	y->_height = max(height(y->_left), height(y->_right)) + 1;
	return y;
}

avlBst::Node*    avlBst::privateInsert(int key, Node*  ptr)
{
	if (ptr == nullptr)
		return createLeaf(key);
	else if (key < ptr->_key)
		ptr->_left = privateInsert(key, ptr->_left);
	else if (key > ptr->_key)
		ptr->_right = privateInsert(key, ptr->_right);
	else
    {
        // root = ptr;
		std::cout << "Key is already exist" << std::endl;
        return ptr;
    }
	ptr->_height = 1 + max(height(ptr->_left), height(ptr->_right));

    int balance = getBalance(ptr);
    
	/*	NOTE:: (key < ptr->_left->_key || inverse) it dependes where we added
		the new element in the recursion above respectively in ptr->left->left
		or ptr->left->right.
	*/

    //NOTE:: heavy on left ==> left left Case
    if (balance > 1 && key < ptr->_left->_key)
		return rightRotation(ptr);

	//NOTE:: heavy on right ==> right right Case
	if (balance < -1 && key > ptr->_right->_key)
		return leftRotation(ptr);

	//NOTE:: heavy on left ==> left right Case
	if (balance > 1 && key > ptr->_left->_key)
	{
		ptr->_left = leftRotation(ptr->_left);
		// root = rightRotation(ptr);
		return rightRotation(ptr);
	}

	//NOTE:: heavy on right ==> right left Case
	if (balance < -1 && key < ptr->_right->_key)
	{
		ptr->_right = rightRotation(ptr->_right);
		// root = leftRotation(ptr);
		return leftRotation(ptr);
	}
	// root = ptr;
	return ptr;
}

void    avlBst::insert(int key)
{
	root = privateInsert(key, root);
}


void	avlBst::privatePrintInOrder(Node* ptr)
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

void	avlBst::printInOrder()
{
	privatePrintInOrder(root);
}

void avlBst::privatePreOrder(Node* ptr)
{
    if(ptr != nullptr)
    {
        std::cout << ptr->_key << " ";
        privatePreOrder(ptr->_left);
        privatePreOrder(ptr->_right);
    }
}
void avlBst::preOrder()
{
	privatePreOrder(root);
}

void	avlBst::printChildren(int key)
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

avlBst::Node*	avlBst::privateReturnNode(int key, Node *ptr)
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

avlBst::Node*	avlBst::returnNode(int key)
{
	return (privateReturnNode(key, root));
}


int		avlBst::privateFindSmallest(Node *ptr)
{
	if (root == nullptr)
	{
		std::cout << "The tree is empty" << std::endl;
		return (-1000);
	}
	else
	{
		if (ptr->_left != nullptr)
			return privateFindSmallest(ptr->_left);
		else
			return (ptr->_key);
	}
}

void	avlBst::removeMatch(Node *parent, Node *match, bool left)
{
	if (root != nullptr)
	{
		Node*	delPtr;
		// int		matchKey = match->_key;
		int		smallestInRightSubtree;

		//NOTE:: 0 - 0 children
		if (match->_left == nullptr && match->_right == nullptr)
		{
			delPtr = match;
			left == true ? parent->_left = nullptr: parent->_right = nullptr;
			delete delPtr;
		}
		//NOTE: 1 - 0 children
		else if (match->_left != nullptr && match->_right == nullptr)
		{
			left = true ? parent->_left = match->_left: parent->_right = match->_left;
			match->_left = nullptr;
			delPtr = match;
			delete delPtr;
		}
		//NOTE: 0 - 1
		else if (match->_right != nullptr && match->_left == nullptr)
		{
			left = true ? parent->_left = match->_right: parent->_left = match->_right;
			match->_right = nullptr;
			delPtr = match;
			delete delPtr;
		}
		//NOTE: 1 -1 children
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

void	avlBst::removeRootMatch()
{
	if (root != nullptr)
	{
		Node	*delPtr = root;
		int		rootkey = root->_key;
		int		smallestInRightSubtree;

		//NOTE: 0 - 0 children
		if (root->_left == nullptr && root->_right == nullptr)
		{
			root = nullptr;
			delete delPtr;
		}
		//NOTE: 1 - 0 child
		else if (root->_left != nullptr && root->_right == nullptr)
		{
			root = root->_left;
			delPtr->_left = nullptr;
			delete delPtr;
		}
		//NOTE: 0 - 1
		else if (root->_right != nullptr && root->_left == nullptr)
		{
			root = root->_right;
			delPtr->_right = nullptr;
			delete delPtr;
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

avlBst::Node*	avlBst::privateRemoveNode(int key, Node *parent)
{
	if (root != NULL)
	{
		if (root->_key == key)
			removeRootMatch();
		else
		{
			if (key < parent->_key && parent->_left != nullptr)
			{
				if (parent->_left->_key == key)
					removeMatch(parent, parent->_left, true);
				else
					parent->_left = privateRemoveNode(key, parent->_left);
				// parent->left = (parent->_left->_key == key) ?
				// removeMatch(parent, parent->_left, true):
				// privateRemoveNode(key, parent->_left);
			}
			else if (key > parent->_key && parent->_right != nullptr)
			{
				if (parent->_right->_key == key)
					removeMatch(parent, parent->_right, false);
				else
					parent->_right = privateRemoveNode(key, parent->_right);
				// parent->_right = (parent->_right->_key == key) ?
				// removeMatch(parent, parent->_right, false):
				// privateRemoveNode(key, parent->_right);
			}
			else
				std::cout << "The key: " << key << "was not found in the tree" << std::endl;
		}
		parent->_height = 1 + max(height(parent->_right), height(parent->_left));
		int balance = getBalance(parent);
		
		if (balance > 1 && getBalance(parent->_left) >= 0)
			return rightRotation(parent);
		if (balance > 1 && getBalance(parent->_left) < 0)
		{
			parent->_left = leftRotation(parent->_left);
			return rightRotation(parent);
		}
		if (balance < -1 && getBalance(parent->_right) >= 0)
			return rightRotation(parent);
		if (balance < -1 && getBalance(parent->_left) < 0)
		{
			parent->_right = rightRotation(parent->_right);
			return leftRotation(parent);
		}
	}
	else
	{
		std::cout << "The tree is empty" << std::endl;
	}
	return parent;
}

void	avlBst::removeNode(int key)
{
	privateRemoveNode(key, root);
}

avlBst::Node*	avlBst::privateInOrderSuccessor(Node* node, Node* n)
{
	if (n->_right != nullptr)
		return (returnNode(privateFindSmallest(n->_right)));
	Node* succ = nullptr;
	while (node != nullptr)
	{
		if (n->_key < node->_key)
		{
			succ = node;
			node = node->_left;
		}
		else if (n->_key > node->_key)
			node = node->_right;
		else
			break;
	}
	// std::cout << "succ: " << succ->_key << std::endl;
	return (succ == nullptr) ? end : succ;
}

avlBst::Node*	avlBst::inOrderSuccessor(int key)
{
	return(privateInOrderSuccessor(root, returnNode(key)));
}

void	avlBst::privateMakeEndNode(Node* node)
{
	end = createLeaf(-101);
	end->_left = node;
	end->_right = nullptr;
}

void	avlBst::makeEndNode()
{
	privateMakeEndNode(root);
}