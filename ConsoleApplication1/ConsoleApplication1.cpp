#include <iostream>
#include <string>
#include "Windows.h"
using namespace std;

struct avltree //создаем структуру для представления узлов
{
	int balance;
	int info; //высота
	avltree* l; //ссылка на левое поддерево
	avltree* r; //ссылка на правое поддерево
};

int h(avltree* root) //вычисляем высоту дерева
{
	if (root == NULL) return 0; //если дерево пустое то возвращаем 0
	int hleft = h(root->l), hright = h(root->r); // считаем высоту левого и правого поддерева
	if (hleft > hright) // если высота слева больше
		return hleft + 1; // добавляем узел
	else // иначе
		return hright + 1; // возвращаем высоту правого поддерева
}
void setbalance(avltree* (&root)) //находим баланс текущего узла
{
	if (root != NULL)
		root->balance = h(root->r) - h(root->l);
}

void turnright(avltree* (&root))
{
	avltree *lefttree, * lefttreerighttree;
	lefttree = root->l;
	lefttreerighttree = lefttree->r;

	lefttree->r = root;
	root->l = lefttreerighttree;
	root = lefttree;
	setbalance(root->r);
	setbalance(root);
}

void turnleft(avltree* (&root))
{
	avltree *righttree, * righttreelefttree;
	righttree = root->r;
	righttreelefttree = righttree->l;
	
	righttree->l = root;
	root->r = righttreelefttree;
	root = righttree;
	setbalance(root->l);
	setbalance(root);
}

void insert(avltree* (&root), int d) // добавление узла в дерево поиска
{
	if (root == NULL)
	{
		root = new avltree;
		root->info = d;
		root->balance = 0;
		root->l = NULL;
		root->r = NULL;
	}
	else
	{
		if (d > root->info)
		{
			insert(root->r, d);
			if (h(root->r) - h(root->l) > 1)
			{
			    if (h(root->r->r) < h(root->r->l))
				    turnright(root->r);
				turnleft(root);
			}
		}
		else
			if (d < root->info)
			{
				insert(root->l, d);
				if (h(root->l) - h(root->r) > 1)
				{
					if (h(root->l->l) < h(root->l->r))
						turnleft(root->l);
					turnright(root);
				}
			}
		setbalance(root);
	}
}

void output(avltree* p) // рапспечатка дерева в симметричном порядке
{
	if (p != NULL)
	{
		output(p->l);
		cout << p->info << " ";
		output(p->r);
	}
}

void print_n(const avltree* p, int n, int level, int prob)
{
	if (p)
	{
		if (level == n)
		{
			for (int i = 1; i <= prob; i++) cout << " ";
			cout << p->info;
		}
		else
		{
			print_n(p->l, n, level + 1, prob);
			print_n(p->r, n, level + 1, prob);
		}
	} 
}

void clear(avltree** p)
{
	if ((*p) != NULL)
	{
		clear(&(*p)->l);
		clear(&(*p)->r);

		delete* p;
	    *p = NULL;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int d;
	char ch;
	avltree* root;
	root = NULL;
	do
	{
		cout << "Введите число" << endl;
		cin >> d;
		insert(root, d);
		cout << "Ввести еще одно число? (y/n)" << endl;
		cin >> ch;
	} 
	while (ch != 'n');
	cout << "Вывод дерева в симметричном порядке: " << endl;
	output(root);
	cout << endl;
	cout << "Вывод дерева" << endl;
	clear(&root);
	if (!root)
	{
		cout << "Дерево очищено!" << endl;
	}
	else
	{
		cout << "Ошибка удаления!" << endl;
	}
	system("pause");
}
