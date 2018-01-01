#ifndef BTREE_H
#define BTREE_H

#include <string>
#include <vector>

using std::string;

struct Tree
{
	std::string data;
	Tree *left;
	Tree *right;
	Tree *parent;
};


class BTree{
public:
	static struct Tree *newTreeNode(string data);
	static struct Tree* insertTreeNode(struct Tree *node, string data);
	static int contains(struct Tree *root, bool found, string data);
	static Tree* deleteNode(struct Tree *node);
	static Tree* findNode(struct Tree * node, string key);
	static void printTreeInOrder(struct Tree *node);
	static Tree * vectorToTree(std::vector<string> arr);
	static int size(Tree *node);
	static Tree* addTree(Tree* node, Tree* adding);
	static Tree* clear(Tree* node);

};

#endif;