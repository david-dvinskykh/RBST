#include "Tree.h"
#include <cassert>
#include <random>
#include <ctime>
#include "test.h"
#include<iostream>
typedef void(*TestFunctor)();

void test0();
TestFunctor g_tests[20] = { test0 };

#define STA_TEST(_TEST_NAME,_INDEX,_NEXT_TEST_NAME)	\
void _TEST_NAME (){			\
g_tests[_INDEX+1] = _NEXT_TEST_NAME; 

STA_TEST(test4, 4, nullptr)
	for (int j = 0; j < 30; j++) {
		Tree tree;

		for (int i = 0; i < 10000; i++) {

			tree.insertKey(i);
			assert(tree.hasKey(i));
		}
		for (int i = 0; i < 500; i++) {
			tree.deleteKey(i);
			assert(!tree.hasKey(i));
		}
		assert(tree.checkTree(tree.root));
	}
}
STA_TEST(test3, 3, test4)
	Tree tree;
	for (int i = 0; i < 1000; i++) {
		int num = rand();
		tree.insertKey(num);
	}
	assert(tree.checkTree(tree.root));
}

STA_TEST(test2, 2, test3)
	Tree tree;
	for (int i = 1000; i > 0; i--) {
		tree.insertKey(i);
	}
	assert(tree.checkTree(tree.root));
}

STA_TEST(test1, 1, test2)
	Tree tree;
	for (int i = 0; i < 1000; i++) {
		tree.insertKey(i);
	}
	assert(tree.checkTree(tree.root));
}

STA_TEST(test0, 0, test1)
	unsigned int start_time = clock();
	for (int j = 0; j < 30; j++) {
		Tree tree;

		for (int i = 0; i < 10000; i++) {

			tree.insertKey(i);
			assert(tree.hasKey(i));
		}
		for (int i = 0; i < 500; i++) {
			tree.deleteKey(i);
			assert(!tree.hasKey(i));
		}
	}
	double h1 = 0, count1 = 0, h2 = 0, count2 = 0, h3 = 0, count3 = 0;
	for (int j = 0; j < 500; j++) {
		Tree tree;
		for (int i = 0; i < 1000; i++) {
			tree.insertKey(i);
		}
		h1 += tree.heightUnderTree(tree.root);
		count1++;
	}
	for (int j = 0; j < 500; j++) {
		Tree tree;
		for (int i = 1000; i > 0; i--) {
			tree.insertKey(i);
		}
		h2 += tree.heightUnderTree(tree.root);
		count2++;
	}
	for (int j = 0; j < 500; j++) {
		Tree tree;
		for (int i = 0; i < 1000; i++) {
			int num = rand();
			tree.insertKey(num);
		}
		h3 += tree.heightUnderTree(tree.root);
		count3++;
	}
	std::cout << h1 / count1 <<std::endl;
	std::cout << h2 / count2 << std::endl;
	std::cout << h3 / count3 << std::endl;
}
void test() {
	srand(time(NULL));
	g_tests[0] = test0;
	for (int i = 0; i < 20 && g_tests[i]; i++) {
		g_tests[i]();
	}
}