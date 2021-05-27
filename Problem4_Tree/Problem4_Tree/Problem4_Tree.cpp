#include <iostream>
#include <fstream>
#include <sstream>

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
	treeNode* tmp = T;
	if (T == NULL)
		return NULL;

	if (T->element == x) {
		return T;
	}
	tmp = find(T->left,x);
	if (tmp) {
		return tmp;
	}
	else {
		return find(T->right, x);
	}
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

treeNode* insert2(treeNode* T, int val) {
	treeNode* tmp = new treeNode;
	tmp->element = val;
	tmp->left = tmp->right = NULL;
	if (T->left == NULL) {
		T->left = tmp;
		return T;
	}
	if (T->right == NULL) {
		T->right = tmp;
		return T;
	}
}

treeNode* insertChild(treeNode* T, int parent[], int child1[], int child2[], int N) {
	treeNode* pr = new treeNode;
	pr = initialize();
	for (int i = 0; i < N; i++) {
		pr = find(T, parent[i]);
		if (pr == NULL) {
			T = insert(T, parent[i]);
			T = insert2(T, child1[i]);
			T = insert2(T, child2[i]);
		}
		if (pr != NULL) {
			if (child1[i] != NULL) {
				pr = insert2(pr, child1[i]);
			}
			if (child2[i] != NULL) {
				pr = insert2(pr, child2[i]);
			}
		}
	}
	return T;
}

void displayInorder(treeNode* T) {
	if (T == NULL)
		return;
	cout << T->element << " ";
	displayInorder(T->left);
	displayInorder(T->right);
}

int GetLevel(treeNode* T, int x, int level) { // Returns level of element x if it is present in tree,otherwise returns -1.
	if (T == NULL) {
		return -1;
	}
	// If key is present in T, or in left subtree or right subtree, return true.
	if (T->element == x) {
		return level;
	}
	int l = GetLevel(T->left, x, level + 1);
	return (l != -1) ? l : GetLevel(T->right, x, level + 1);
}

treeNode* GetDistanceH(treeNode* T, int x, int y, int& d1, int& d2, int& dist, int lvl) {
	if (T == NULL) 
		return NULL;
	// If either x or y matches with root's element, report the presence by returning root (Note that if a key is ancestor of other, then the ancestor key becomes LCA (lowest common ancestor).
	if (T->element == x){
		d1 = lvl;
		return T;
	}
	if (T->element == y){
		d2 = lvl;
		return T;
	}
	// Look for x and y in left and right subtrees
	treeNode* left_lca = GetDistanceH(T->left, x, y, d1, d2, dist, lvl + 1);
	treeNode* right_lca = GetDistanceH(T->right, x, y, d1, d2, dist, lvl + 1);

	// If both of the above calls return Non-NULL, then one key is present in once subtree and other is present in other. So this node is the LCA
	if (left_lca && right_lca){
		dist = d1 + d2 - 2 * lvl;
		return T;
	}

	// Otherwise check if left subtree or right subtree is LCA
	return (left_lca != NULL) ? left_lca : right_lca;
}

int GetDistance(treeNode* T, int x, int y){
	int d1 = -1, d2 = -1, dist;
	treeNode* lca = GetDistanceH(T, x, y, d1, d2, dist, 1);

	// If both x and y were present in Tree, return dist
	if (d1 != -1 && d2 != -1)
		return dist;

	// If x is ancestor of y, consider x as root and find level of y in subtree rooted with x
	if (d1 != -1){
		dist = GetLevel(lca, y, 0);
		return dist;
	}

	// If y is ancestor of x, consider y as root and find level of x in subtree rooted with y
	if (d2 != -1){
		dist = GetLevel(lca, x, 0);
		return dist;
	}
	return -1;
}

treeNode* GetLCA(treeNode* T, treeNode* x, treeNode* y) { //get lowest comon ancestor.
	if (T == nullptr) {
		return nullptr;
	}
	if (T == x || T == y) {
		return T;
	}

	// recursively check if x or y exists in the left subtree
	treeNode* left = GetLCA(T->left, x, y);

	// recursively check if x or y exists in the right subtree
	treeNode* right = GetLCA(T->right, x, y);

	// if x is found in one subtree and y is found in the other subtree, update lca to the current node
	if (left && right) {
		return T;
	}

	// if x and y exist in the left subtree
	if (left) {
		return left;
	}

	// if x and y exist in the right subtree
	if (right) {
		return right;
	}
}

void relation(treeNode* T, int x, int y) {
	string rel;
	int dist1 = 0;
	int dist2 = 0;
	if (T == NULL){
		cout << "Empty tree." << endl;
		return;
	}
	if (find(find(T, x), y) == NULL && find(find(T, y), x) == NULL) { // if y is not in subtree x and if x is not in subtree y then they are cousins.
		rel = "cousin";
		dist1 = GetDistance(T, GetLCA(T,find(T,x), find(T,y))->element , x);
		dist2 = GetDistance(T, GetLCA(T, find(T, x), find(T, y))->element, y);
		cout << x << " and " << y << " are " << rel << "-" << dist1 << "-" << dist2 << "-" << GetLCA(T, find(T, x), find(T, y))->element << endl;
	}
	else { // if y is found in subtree x then they are cousins.
		rel = "descendant";
		dist1 = GetDistance(T, x, y);
		cout << x << " and " << y << " are " << rel << "-" << dist1 << endl;
	}
}

int main()
{
	string line;
	string x;

	int N = 15;
	int parent[15];
	int child1[15];
	int child2[15];

	int person1[7];
	int person2[7];

	ifstream myReadFile;
	myReadFile.open("Input.txt");
	if (myReadFile){
		myReadFile >> x;
		for (int i = 0; i < 15; i++) {
			myReadFile >> x;
			parent[i] = stoi(x);
		}
		myReadFile >> x;
		for (int i = 0; i < 15; i++) {
			myReadFile >> x;
			if (x == "-") {
				x = "0";
			}
			child1[i] = stoi(x);
		}
		myReadFile >> x;
		for (int i = 0; i < 15; i++) {
			myReadFile >> x;
			if (x == "-") {
				x = "0";
			}
			child2[i] = stoi(x);
		}
	}
	myReadFile.close();

	myReadFile.open("Request.txt");
	if (myReadFile) {
		myReadFile >> x;
		for (int i = 0; i < 7; i++) {
			myReadFile >> x;
			person1[i] = stoi(x);
		}
		myReadFile >> x;
		for (int i = 0; i < 7; i++) {
			myReadFile >> x;
			person2[i] = stoi(x);
		}
	}
	myReadFile.close();

	treeNode* t;
	t = initialize();

	t = insertChild(t, parent, child1, child2, N);
	cout << "Display tree in order:" << endl;
	displayInorder(t);
	cout << endl << endl;
	cout << "Output:" << endl;
	for (int i= 0; i < 7; i++) {
		relation(t, person1[i], person2[i]);
	}
}