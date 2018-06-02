#include "Tree.h"
#include <iostream>
#include <cassert>
#include <random>
#include <ctime>

Tree::Tree()
{
}

Tree::~Tree()
{
	delete root;
}

bool Tree::hasKey(int key)
{
	return findNode(key);
}

void Tree::insertKey(int key) {
	Node** node = &root;
	while (*node) {
		int size = (*node)->size;
		bool change = rand() % size < (double)size / (size + 1);
		if (change) {
			insertInRoot(new Node(key), node);
			return;
		}
		else {
			(*node)->size++;
			if (key < (*node)->value)
				node = &(*node)->leftNode;
			else if (key > (*node)->value)
				node = &(*node)->rightNode;
			else {
				reduceSize((*node)->value);
				return;
			}
		}
	}
	*node = new Node(key);
}

void Tree::deleteKey(int key) {
	assert(isEmpty());
	Node** node = findNode(key);
	reduceSize(key);
	if (!*node)
		return;
	if (!(*node)->leftNode)
		transplant(node, (*node)->rightNode);
	else if (!(*node)->rightNode)
		transplant(node, (*node)->leftNode);
	else {
		Node** nextNode = minNode((*node)->rightNode);
		if (nextNode == &(*node)->rightNode) {
			transplant(nextNode, (*nextNode)->rightNode);
			(*nextNode)->rightNode = (*node)->rightNode;
		}
	}
}

bool Tree::isEmpty()
{
	return root;
}

Tree::Node ** Tree::minNode(Node * root)
{
	assert(root);
	Node** node = &root;
	while ((*node)->leftNode)
		node = &(*node)->leftNode;
	return node;
}

Tree::Node * Tree::maxNode(Node * root)
{
	assert(root);
	Node* node = root;
	while (node->rightNode)
		node = node->rightNode;
	return node;
}

bool Tree::insertInRoot(Node* newNode, Node** daughterNode) {
	if (*daughterNode) {
		if (newNode->value < (*daughterNode)->value)
			if (insertInRoot(newNode, &(*daughterNode)->leftNode))
				rotateRight(daughterNode);
			else
				return false;
		else if (newNode->value > (*daughterNode)->value)
			if (insertInRoot(newNode, &(*daughterNode)->rightNode))
				rotateLeft(daughterNode);
			else
				return false;
		else
			return false;
	}
	else
		*daughterNode = newNode;
	return true;
}

void Tree::deleteRoot(Node ** daughterOldNode)
{

}

int Tree::heightUnderTree(Node* root)
{
	int left = 0;
	int right = 0;
	if (root->leftNode)
		left += heightUnderTree(root->leftNode);
	if (root->rightNode)
		right += heightUnderTree(root->rightNode);
	return (left > right ? left : right) + 1;
}

void Tree::rotateLeft(Node ** daughterNode)
{
	assert((*daughterNode)->rightNode);
	Node* newdaughterNode = (*daughterNode)->rightNode;
	(*daughterNode)->rightNode = newdaughterNode->leftNode;
	newdaughterNode->leftNode = *daughterNode;
	*daughterNode = newdaughterNode;
	(*daughterNode)->leftNode->size = sizeDaughterNode((*daughterNode)->leftNode) + 1;
	(*daughterNode)->size = sizeDaughterNode(*daughterNode) + 1;
}

void Tree::rotateRight(Node ** daughterNode)
{
	assert((*daughterNode)->leftNode);
	Node* newdaughterNode = (*daughterNode)->leftNode;
	(*daughterNode)->leftNode = newdaughterNode->rightNode;
	newdaughterNode->rightNode = *daughterNode;
	*daughterNode = newdaughterNode;
	(*daughterNode)->rightNode->size = sizeDaughterNode((*daughterNode)->rightNode) + 1;
	(*daughterNode)->size = sizeDaughterNode(*daughterNode) + 1;
}

int Tree::sizeDaughterNode(Node* node) {
	assert(node);
	int size = 0;
	if (node->leftNode)
		size += node->leftNode->size;
	if (node->rightNode)
		size += node->rightNode->size;
	return size;
}

Tree::Node** Tree::findNode(int key)
{
	for (Node** node = &root; *node;)
		if (key < (*node)->value)
			node = &(*node)->leftNode;
		else if (key > (*node)->value)
			node = &(*node)->rightNode;
		else
			return node;
	return nullptr;
}

void Tree::transplant(Node ** node, Node * otherNode)
{
	if (*node == root)
		root = otherNode;
	else
		*node = otherNode;
}

bool Tree::isMinElements(Node * parentNode, Node * daughterNode)
{
	if (daughterNode)
		if (parentNode->value > daughterNode->value &&
			isMinElements(parentNode, daughterNode->leftNode) &&
			isMinElements(parentNode, daughterNode->rightNode))
			return true;
		else {
			assert(0);
			return false;
		}
	return true;
}

bool Tree::isMaxElements(Node * parentNode, Node * daughterNode)
{
	if (daughterNode)
		if (parentNode->value < daughterNode->value &&
			isMaxElements(parentNode, daughterNode->leftNode) &&
			isMaxElements(parentNode, daughterNode->rightNode))
			return true;
		else {
			assert(0);
			return false;
		}
		return true;
}

bool Tree::checkTree(Node * node)
{
	if (node)
		return isMinElements(node, node->leftNode) && isMaxElements(node, node->rightNode) && checkTree(node->leftNode) && checkTree(node->rightNode);
	else
		true;
}

void Tree::reduceSize(int key)
{
	assert(root);
	Node** node = &root;
	while (*node) {
		(*node)->size--;
		if (key < (*node)->value) {
			node = &(*node)->leftNode;
		}
		else if (key > (*node)->value) {
			node = &(*node)->rightNode;
		}
		else
			return;
	}
}


Tree::Node::Node(int key)
{
	value = key;
}

Tree::Node::~Node()
{
	if (leftNode)
		delete leftNode;
	if (rightNode)
		delete rightNode;
}
