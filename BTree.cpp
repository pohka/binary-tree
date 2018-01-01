
#include "BTree.h"
#include <iostream>

	struct Tree * BTree::newTreeNode(string data)
{
	Tree *node = new Tree;
	node->data = data;
	node->left = nullptr;
	node->right = nullptr;
	node->parent = nullptr;

	return node;
}

struct Tree* BTree::insertTreeNode(struct Tree *node, string data)
{
	static Tree *p;
	Tree *retNode;

	if (node == nullptr)  {
		retNode = BTree::newTreeNode(data);
		retNode->parent = p;
		return retNode;
	}
	if (data <= node->data) {
		p = node;
		node->left = BTree::insertTreeNode(node->left, data);
	}
	else {
		p = node;
		node->right = BTree::insertTreeNode(node->right, data);
	}
	return node;
}

//returns count of data in tree
int BTree::contains(struct Tree *root, bool found, string data){
	if (root == nullptr || root->data == "\0") return 0;

	int dups = 0;
	if (data > root->data && root->right!=nullptr){ //go right
		dups += BTree::contains(root->right, found, data);
	}
	else{ //go left
		if (data == root->data){
			dups++;
			found = true;
		}
		//go left again if this node is duplicate or, 
		//if not found yet
		//otherwise stop searching
		if ((found && dups==1 && root->left != nullptr) ||
			(!found && root->left != nullptr)) {
			dups += contains(root->left, found, data);
		}
	}
	return dups;
}

Tree* BTree::deleteNode(struct Tree *node){
	if (node == nullptr || node->data == "\0") return nullptr;
	
	//3 cases: 
	//leaf
	if (node->left == nullptr && node->right == nullptr){
		Tree *p=node->parent;

		if(p != nullptr){ //not root node
			if (p->left == node) p->left = nullptr;
			else p->right = nullptr;
		}
		if (p == nullptr){
			return nullptr;
		}
		else{
			delete node;
			node = nullptr;
		}
	}
	//1 child
	else if (node->left == nullptr || node->right == nullptr){
		Tree *p = node->parent;
		Tree *child;

		//if deleting root node
		//if (p == nullptr) p = node;

		//child on left
		if (node->left != nullptr)
			child = node->left;
		else //child on right
			child = node->right;

		if (node->parent == nullptr){ // todo deleting root node
			
			//replace node with child
			node->data = child->data;
			node->left = child->left;
			node->right = child->right;
			
			delete child; 
		}
		else{ //not root node
			if (p->left == node){ //node left of parent
				p->left = child;
			}
			else{ //node right of parent
				p->right = child;
			}

			node = nullptr;
			delete node;
		}
	}
	//2 children
	else{
		//std::cout << "delete case 3 \n";

		//find child to replace
		Tree *child = node->right;
		Tree* childsParent=node;

		//find min value on right side of node
		while (child->left != nullptr){
			childsParent = child;
			child = child->left;
		}

		//swap data from child to the node requesting deleted
		node->data = child->data;

		//fix possible dangling tree to the right of the child
		if (childsParent->right == child){ //when deleting root node
			childsParent->right = child->right;
		}
		else{ //any other node
			childsParent->left = child->right;
		}

		delete child;
	}
	return node;
}

Tree* BTree::findNode(struct Tree * node, string key){
	if (node == nullptr || node->data == "\0") return nullptr;

	if (node->data == key)
		return node;
	else if(node->data >= key && node->left!=nullptr){
		return findNode(node->left, key);
	}
	else if (node->data < key && node->right != nullptr){
		return findNode(node->right, key);
	}
	//return nullptr if not found
	return nullptr;
}

//disply tree in order

void BTree::printTreeInOrder(struct Tree *node)
{
	if (node == nullptr || node->data == "\0") return;

	printTreeInOrder(node->left);
	std::cout << node->data << " ";
	printTreeInOrder(node->right);
}


Tree * BTree::vectorToTree(std::vector<string> arr){
	if(arr.size() == 0) return nullptr;

	Tree *tree = newTreeNode(arr.at(0));
	for (int i = 1; i < arr.size(); i++){
		insertTreeNode(tree, arr.at(i));
	}
	return tree;
}

int BTree::size(Tree* node){
	int count = 0;
	if (node == nullptr || node->data == "\0") return 0;

	count = 1;
	count += size(node->left);
	count += size(node->right);
	return count;
	
}

Tree* BTree::addTree(Tree* node, Tree* addingTree){
	if (addingTree == nullptr || addingTree->data == "\0") return node;

	node = insertTreeNode(node, addingTree->data);
	if (addingTree->left)
		node = addTree(node, addingTree->left);
	if (addingTree->right)
			node = addTree(node, addingTree->right);
	

	return node;
}

//deletes all tree and its node, returns nullptr
Tree* BTree::clear(Tree *tree){
	if (tree->left)
		clear(tree->left);
	if (tree->right)
		clear(tree->right);

	//set parents child ptr to nullptr
	if (tree->parent != nullptr){
		if (tree->parent->left == tree){
			tree->parent->left = nullptr;
		}
		else{
			tree->parent->right = nullptr;
		}
	}
	delete tree;
	return nullptr;
}