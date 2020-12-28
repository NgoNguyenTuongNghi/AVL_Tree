//AVL TREE
//T-LAN

#include <bits/stdc++.h>

using namespace std;

struct node {
	int giatri;
	node *left, *right, *top;

	node(int x) {
		left = right = top = NULL;
		giatri = x;
	}
};

node * root = NULL;

// Đo chiều cao của cây con gốc a

int ChieuCao(node* a) {
	if (a == NULL)
		return 0;
	return max(ChieuCao(a->left) + 1, ChieuCao(a->right) + 1);
}

int ChenhLech(node* a) {
	if (a == NULL)
		return 0;
	return abs(ChieuCao(a->left) - ChieuCao(a->right));
}

// Nối a vào b, a là cây con trái của b

void LeftJoin(node* a, node* b) {
	if (a != NULL)
		a->top = b;
	if (b != NULL)
		b->left = a;
	else root = a;
}

// Nối a vào b, a là cây con phải của b

void RightJoin(node* a, node* b) {
	if (a != NULL)
		a->top = b;
	if (b != NULL)
		b->right = a;
	else root = a;
}

// Hàm xoay trái, a là con phải trực tiếp của b, sau xoay, b thành con trái trực tiếp của a

void XoayTrai(node* a, node* b) {
	if (b == NULL) {
		RightJoin(a, b);
		return;
	}

	node* c = b->top;
	RightJoin(a->left, b);
	LeftJoin(b, a);

	if (c == NULL)
		RightJoin(a, c);
	else
		if (c->right == b)
			RightJoin(a, c);
		else
			LeftJoin(a, c);
}

// Hàm xoay phải, a là con trái trực tiếp của b, sau xoay, b thành con phải trực tiếp của a

void XoayPhai(node* a, node* b) {
	if (b == NULL) {
		RightJoin(a, b);
		return;
	}

	node* c = b->top;
	LeftJoin(a->right, b);
	RightJoin(b, a);

	if (c == NULL)
		RightJoin(a, c);
	else
		if (c->left == b)
			LeftJoin(a, c);
		else
			RightJoin(a, c);
}

// Cân bằng cây

void CanBang(node* a) {
	if (a == NULL)
		return;

	if (ChenhLech(a) <= 1)
		return;

	if (ChieuCao(a->left) > ChieuCao(a->right)) {
		// Xoay kép trái phải
		if (ChieuCao(a->left->left) < ChieuCao(a->left->right))
			XoayTrai(a->left->right, a->left);
		XoayPhai(a->left, a);
	}
	else
		if (ChieuCao(a->right) > ChieuCao(a->left)) {
			// Xoay kép phải trái
			if (ChieuCao(a->right->right) < ChieuCao(a->right->left))
				XoayPhai(a->right->left, a->right);
			XoayTrai(a->right, a);
		}
}

// Chèn nút a vào cây con nút b

void Chen(node *a, node *b) {
	if (b == NULL) {
		RightJoin(a, b);
		return;
	}

	if (a->giatri == b->giatri) {
		return;
	}

	if (a->giatri < b->giatri)
		if (b->left != NULL)
			Chen(a, b->left);
		else
			LeftJoin(a, b);

	if (a->giatri > b->giatri)
		if (b->right != NULL)
			Chen(a, b->right);
		else
			RightJoin(a, b);

	CanBang(b);
}

// In cây con gốc a

void In(string x, node * a, bool Trai)
{
	if (a == NULL)
		return;
	else {
		cout << x;
		cout << (Trai ? "|---" : "'___");

		cout << "[" << a->giatri << "]" << endl;

		In(x + (Trai ? "|   " : "    "), a->left, true);
		In(x + (Trai ? "|   " : "    "), a->right, false);
	}
}

void In(node* a)
{
	In("", a, false);
}

int main () {
	int z;
	cout << "----CAY AVL -- CAY NHI PHAN TIM KIEM CAN BANG----";
	cout << endl << "Nhap khoa (-99: ket thuc): ";
	cin >> z;
	while (z != -99) {
		Chen(new node(z), root);
		cout << "Cay AVL hien tai: " << endl;
		In(root);
		cout << endl << "-----------------------------------------------------------------" << endl;
		cout << "----CAY AVL -- CAY NHI PHAN TIM KIEM CAN BANG----" << endl;
		cout << endl << "Nhap them khoa (-99: ket thuc): ";
		cin >> z;
	}

	cout << endl << "-----------------------------------------------------------------" << endl;
	system("pause");

	return 0;
}