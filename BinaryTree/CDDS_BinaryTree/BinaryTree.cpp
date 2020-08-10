/*----------------------------------------
Author: Richard Stern
Description: A simple binary search tree
Date: 17/4/2015
----------------------------------------*/
#include "BinaryTree.h"
#include "TreeNode.h"
#include "raylib.h"
#include <iostream>

using namespace std;

BinaryTree::BinaryTree()
{
    m_pRoot = nullptr;
}

BinaryTree::~BinaryTree()
{
	while(m_pRoot)
	{
		Remove(m_pRoot->GetData());
	}
}

// Return whether the tree is empty
bool BinaryTree::IsEmpty() const
{
	return (m_pRoot == nullptr);
}

// ----------- INSERT FUNCTIONS -----------

// Creates a new node
TreeNode* newNode(int value)
{
	TreeNode* temp = new TreeNode(value);
	temp->SetData(value);
	temp->SetLeft(NULL);
	temp->SetRight(NULL);
	return temp;
}

// Insert a new element into the tree
void BinaryTree::Insert(int a_nValue)
{
	TreeNode* t = newNode(a_nValue);
	TreeNode* parent = nullptr;

	// Checks if tree is empty
	if (IsEmpty())
	{
		m_pRoot = t;
	}

	else
	{
		// Creates and sets the current node to the root of the tree
		TreeNode* curr = m_pRoot;

		// Finds the position to place the node
		while (curr)
		{
			parent = curr;

			if (t->GetData() > curr->GetData())
			{
				curr = curr->GetRight();
			}

			else if (t->GetData() < curr->GetData())
			{
				curr = curr->GetLeft();
			}

			// Allows no duplicate values
			else
			{
				return;
			}
		}

		// Sets the parent's left or right to the new node
		if ((t->GetData()) < (parent->GetData()))
		{
			parent->SetLeft(t);
		}

		else
		{
			parent->SetRight(t);
		}
	}

}

// Inserts existing elements into the tree
void BinaryTree::InsertExisting(TreeNode* node)
{
	TreeNode* t = node;
	TreeNode* parent = nullptr;

	// Checks if tree is empty
	if (IsEmpty())
	{
		m_pRoot = t;
	}

	else
	{
		// Creates and sets the current node to the root of the tree
		TreeNode* curr = m_pRoot;

		// Finds the position to place the node
		while (curr)
		{
			parent = curr;

			if (t->GetData() > curr->GetData())
			{
				curr = curr->GetRight();
			}

			else
			{
				curr = curr->GetLeft();
			}
		}

		// Sets the parent's left or right to the node
		if ((t->GetData()) < (parent->GetData()))
		{
			parent->SetLeft(t);
		}

		else
		{
			parent->SetRight(t);
		}
	}

}

// ----------- SEARCH FUNCTIONS -----------

// Finds the searched for value for display
TreeNode* BinaryTree::Find(int a_nValue)
{
	TreeNode* pCurrent = nullptr;
	TreeNode* pParent = nullptr;

	return FindNode(a_nValue, pCurrent, pParent) ? pCurrent: nullptr;
}

// ----------- REMOVE FUNCTIONS -----------

// Finds the searched for value to remove
bool BinaryTree::FindNode(int a_nSearchValue, TreeNode*& ppOutNode, TreeNode*& ppOutParent)
{
	ppOutNode = m_pRoot;

	// While the node is not null
	while (ppOutNode != nullptr)
	{
		if (a_nSearchValue == ppOutNode->GetData())
		{
			return true;
		}

		else
		{
			ppOutParent = ppOutNode;

			if (a_nSearchValue < ppOutNode->GetData())
			{
				ppOutNode = ppOutNode->GetLeft();
			}

			else
			{
				ppOutNode = ppOutNode->GetRight();
			}
		}
	}

	// Returns false if node can't be found
	return false;
}

// Removes the searched for value
void BinaryTree::Remove(int a_nValue)
{
	// Checks if tree is empty
	if (IsEmpty())
	{
		return;
	}
	
	else
	{
		TreeNode* curr = m_pRoot;
		TreeNode* parent = nullptr;

		// Executes the remove process if the node is found
		if (FindNode(a_nValue, curr, parent))
		{
			// Creates and sets the temp nodes to each branch of the current node 
			TreeNode* left = curr->GetLeft();
			TreeNode* right = curr->GetRight();

			// If the current node is the root of the tree, root is set to null
			if (curr == m_pRoot)
			{
				m_pRoot = nullptr;
			}

			// If current is smaller than the parent, parent's left is set to null
			else if (curr->GetData() < parent->GetData())
			{ 
				parent->SetLeft(nullptr);
			}

			// If current is greater than the parent, parent's right is set to null
			else if (curr->GetData() > parent->GetData())
			{
				parent->SetRight(nullptr);
			}

			// Rearranges the children of a parent, if the parent was removed
			if (left != nullptr)
			{
				InsertExisting(left);
			}

			if (right != nullptr)
			{
				InsertExisting(right);
			}
		}

		// Removes the searched for node
		delete curr;
	}
}

// ----------- DRAW FUNCTIONS -----------

// Draws root of tree
void BinaryTree::Draw(TreeNode* selected)
{
	Draw(m_pRoot, 550, 40, 400, selected);
}

// Draws nodes in tree
void BinaryTree::Draw(TreeNode* pNode, int x, int y, int horizontalSpacing, TreeNode* selected)
{
	horizontalSpacing /= 2;

	if (pNode)
	{
		if (pNode->HasLeft())
		{
			DrawLine(x, y, x - horizontalSpacing, y + 80, RED);
			
			Draw(pNode->GetLeft(), x - horizontalSpacing, y + 80, horizontalSpacing, selected);
		}

		if (pNode->HasRight())
		{
			DrawLine(x, y, x + horizontalSpacing, y + 80, RED);

			Draw(pNode->GetRight(), x + horizontalSpacing, y + 80, horizontalSpacing, selected);
		}

		pNode->Draw(x, y, (selected == pNode));
	}
}