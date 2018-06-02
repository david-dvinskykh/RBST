#ifndef _TREE_H
#define _TREE_H
class Tree {
public:
	Tree();
	~Tree();
	bool hasKey(int key);
	void insertKey(int key);
	void deleteKey(int key);
	bool isEmpty();
//private
	class Node {
	public:
		int value;
		Tree::Node* leftNode = nullptr;
		Tree::Node* rightNode = nullptr;
		int size = 1;
		Node(int key);
		~Node();
	};
	Tree::Node* root = nullptr;
	Tree::Node** minNode(Node* root);
	Tree::Node* maxNode(Node* root);
	bool insertInRoot(Node* newNode, Node** daughterOldNode);
	void deleteRoot(Node** daughterOldNode);
	int heightUnderTree(Node* root);
	void rotateLeft(Node** node);
	void rotateRight(Node** node);
	void reduceSize(int key);
	int sizeDaughterNode(Node* node);
	Node** findNode(int key);
	void transplant(Node** node, Node* othernode);
	bool isMinElements(Node* parentNode, Node* daughterNode);
	bool isMaxElements(Node* parentNode, Node* daughterNode);
	bool checkTree(Node* node);
};
#endif // _TREE_H