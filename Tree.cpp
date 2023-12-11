#include "Tree.h"


struct result { 
	int k;
	bool cond;	// ����� ��� ����������� ��������� ����� � ������ ����� ��������. True, ���� ������ ����� �������� ����, �� �� ����� �� ��������.
				// ��������, ���� ��������� {a1, a2,.., an} -- ���� �� ������ ��������� ���� a_n+1, � a_i -- ����, ������� ����� �������, �� ��������� 
				// �� "����������" �� a_n+1, ���������� ����� ����� �� 1 ����� ����������� � ���� ����� � ������� �� ������ i
};


void add(Tree** t, int k) { // ��� ������ ����� ����� � ����� � ������ �����������, ����� ����� ����� ������� ���������
	if (*t == nullptr) {
		*t = new Tree;
		(*t)->key = k;
		(*t)->left = nullptr;
		(*t)->right = nullptr;
		(*t)->N = 1;
	}
	else {
		if ((*t)->left == nullptr) {
			add(&(*t)->left, k);
		}
		else if ((*t)->right == nullptr) {
			add(&(*t)->right, k);
		}
		else {
			if ((*t)->left->N <= (*t)->right->N) {
				add(&(*t)->left, k);
			}
			else {
				add(&(*t)->right, k);
			}
		}
		(*t)->N += 1;
	}
}


result find_replacement(Tree* t, int search_key) { // ����� ������ ��������� ����, �������� ��� �� ������ � �������� ����� ����� � �����������
	result res;
	res.cond = false;
	if (t->right != nullptr) {
		if (t->left->N <= t->right->N) {
			if (t->right->N == 1) {
				res.k = t->key;
				res.cond = true;
				delete t->right;
				t->right = nullptr;
				t->N = t->N - 1;
				return res;
			}
			if (!res.cond) {
				res = find_replacement(t->right, search_key);
			}
		}
		else {
			if (t->left->N == 1) {
				res.k = t->left->key;
				res.cond = true;
				delete t->left;
				t->left = nullptr;
				t->N = t->N - 1;
				return res;
			}
			if (!res.cond) {
				res = find_replacement(t->left, search_key);
			}
		}
	}
	else {
		if (t->left->N == 1) {
			res.k = t->left->key;
			res.cond = true;
			delete t->left;
			t->left = nullptr;
			t->N = t->N - 1;
			return res;
		}
		if (!res.cond) {
			res = find_replacement(t->left, search_key);
		}
	}
	if (res.cond) {
		t->N = t->N - 1;
		if (search_key == t->key) {
			res.cond = false;
		}
	}
	return res;
}


bool del(Tree* t, int k, Tree* root) { // ����� �������� ���� � ��� �������� (������ �� ����� ��������)
	if (t->key == k) {
		result res = find_replacement(root, k);
		if (res.k != k) {
			t->key = res.k;
		}
		return true;
	}
	bool found = false;
	if (t->left != nullptr) {
		found |= del(t->left, k, root);
	}
	if ((!found) && (t->right != nullptr)) {
		found |= del(t->right, k, root);
	}
	return found;
}


void print_tree(Tree* t, int* x, int y) {
	if (t != nullptr) {
		print_tree(t->left, x, y + 1);
		COORD coord;
		coord.X = *x;
		coord.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		printf("%d", t->key);
		(*x)++;
		print_tree(t->right, x, y + 1);
	}
}

void print_nodes(Tree* t) {
	if (t != nullptr) {
		std::cout << "���� " << t->key << ", ���������� ����� � ���������: " << t->N << std::endl;
		print_nodes(t->left);
		print_nodes(t->right);
	}
}