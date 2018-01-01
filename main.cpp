#include <string>
#include <algorithm>
#include <chrono>
#include <vector>
#include "BTree.h"
#include "InputTree.h"

using std::string;

int main(){
	
	
	string key;
	

	std::cout << "Search for word in file.txt \nEnter word:";
	std::cin >> key;

	Tree *root = BTree::newTreeNode("\0");
	root = InputTree::readFile(root);
	
	Tree *node = BTree::findNode(root, key);
	if (node != nullptr){
		std::cout << "found and deleted key: " << node->data << std::endl << std::endl;
		node = BTree::deleteNode(node);
	}

	

	//record time for search
	std::cout << "\nloaded file into memory \nStarting search for '" << key << "'..." << std::endl;


	//cout duplicates of key and time it
	auto start_time = std::chrono::high_resolution_clock::now();
	int res = BTree::contains(root, false, key);
	auto end_time = std::chrono::high_resolution_clock::now();
	auto time = end_time - start_time;
	std::cout << "Search completed in: " << std::chrono::duration_cast<std::chrono::microseconds>(time).count() << "micro secs";

	std::cout << std::endl << "\ncounts of '" +key + "' Using binary tree find:" << res;

	//tree example
	std::cout << std::endl << std::endl;
	std::vector<string> arr;
	arr.push_back("hi");
	arr.push_back("are");
	arr.push_back("ssare");
	arr.push_back("zare");
	Tree *tree = BTree::vectorToTree(arr);
	tree = BTree::deleteNode(BTree::findNode(tree, "hi"));
	tree = BTree::insertTreeNode(tree, "example");
	tree = BTree::insertTreeNode(tree, "hid");
	tree = BTree::insertTreeNode(tree, "hipe");
	
	std::cout << "tree size:" << BTree::size(tree) << std::endl;
	BTree::addTree(tree, BTree::vectorToTree(arr));
	std::cout << "tree size:" << BTree::size(tree) << std::endl;


	BTree::printTreeInOrder(tree);
	std::cout << "\nsize: " << BTree::size(root) << std::endl;

	std::cout << "\n\ntype to quit:";
	int a; std::cin >> a;
}

Tree* InputTree::readFile(Tree * node){//read file
	std::ifstream infile;
	infile.open("file.txt");
	int readCount = 0, totalRead = 0;
	char word[256];
	std::cout << "\nloading file into memory...\n";
	infile.getline(word, 128, ' ');
	node = BTree::newTreeNode(word);
	while (infile)
	{
		//counting reading
		readCount++;
		if (readCount > 1000){
			totalRead++;
			readCount = 0;
			std::cout << "read words: " << totalRead * 1000 << std::endl;
		}

		infile.getline(word, 128, ' ');
		
		//replace no alphabethic characters
		if (word != "" && word != " " && word != nullptr){
			string str = word;
			str.erase(std::remove_if(str.begin(), str.end(), [](char c) {
				if (c > 255 || c < 0){
					return false;
				}

				return !isalpha(c);
			}), str.end());

			//add word to tree
			BTree::insertTreeNode(node, str);
		}
	}
	infile.close();
	return node;
}