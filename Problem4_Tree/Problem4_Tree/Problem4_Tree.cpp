#include <iostream>

using namespace std;

struct treeNode {
	int element;
	treeNode* left;
	treeNode* right;
};

treeNode* initialize() {
	return NULL;
}
treeNode* find(treeNode* T, int x) {
	if (T == NULL)
		return NULL;

	if (x < T->element)
		return find(T->left, x);
	else
		if (x > T->element)
			return find(T->right, x);
		else
			return T;
}

treeNode* insert(treeNode* T, int val) {
	if (T == NULL) {
		treeNode* tmp = new treeNode;
		tmp->element = val;
		tmp->left = tmp->right = NULL;
		return tmp;
	}

	if (val <= T->element)
		T->left = insert(T->left, val);
	else
		T->right = insert(T->right, val);

	return T;
}

void insert2(treeNode* T, int val) {
	treeNode* tmp = new treeNode;
	tmp->element = val;
	tmp->left = tmp->right = NULL;
	if (T->left == NULL) {
		T->left = tmp;
	}
	if (T->right == NULL) {
		T->right = tmp;
	}
}

void insertChild(treeNode* T, int parent[], int child1[], int child2[], int N) {
	treeNode* pr = new treeNode;
	pr = initialize();
	for (int i = 0; i < N; i++) {
		pr = find(T, parent[i]);
		if (pr == NULL) {
			T = insert(T, parent[i]);
			T = insert(T, child1[i]);
			T = insert(T, child2[i]);
		}
		if (pr != NULL) {
			if (child1[i] != NULL) {
				insert2(pr, child1[i]);
			}
			if (child2[i] != NULL) {
				insert2(pr, child2[i]);
			}
		}
	}
}

void displayInorder(treeNode* T) {
	if (T == NULL)
		return;
	displayInorder(T->left);
	cout << T->element << " ";
	displayInorder(T->right);
}

int main()
{
	treeNode* t;
	t = initialize();
	int N = 15;
	int parent[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	int child1[] = { 2,4,6,8,0,10,0,12,0,13,0,14,0,0,0};
	int child2[] = { 3,5,7,9,0,11,0,0,0,0,0,15,0,0,0};

	insertChild(t, parent, child1, child2, N);
	displayInorder(t);
}