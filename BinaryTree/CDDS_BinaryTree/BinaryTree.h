/*----------------------------------------
Author: Richard Stern
Description: A simple binary search tree
Date: 17/4/2015
----------------------------------------*/
#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

class TreeNode;

class BinaryTree
{
public:
	BinaryTree();
	~BinaryTree();

	bool IsEmpty() const;

	// Inserts new nodes
	void Insert(int a_nValue);

	// Inserts existing nodes - used to rearrange tree
	void InsertExisting(TreeNode* node);

	// Removes a node
	void Remove(int a_nValue);

	// Draws the binary tree
	void Draw(TreeNode* selected = nullptr);

	// Finds a node
	TreeNode* Find(int a_nValue);

private:
	// Find the node with the specified value.
	bool FindNode(int a_nSearchValue, TreeNode*& ppOutNode, TreeNode*& ppOutParent);

	// Draws the nodes
	void Draw(TreeNode*, int x, int y, int horizontalSpacing, TreeNode* selected = nullptr);

	// The root node of the tree
	TreeNode* m_pRoot;
};

#endif //_BINARYTREE_H_