#include "Header.h"

void find(Tree* tp, unsigned int key) {
	int cmp;
	cmp = tp->key - key;
	if (cmp == 0) {
		printf("%s", "Number1	Number2		String		Key:\n");
		while (tp->left_flag == 1 && tp->left->key == key) {
			printf("%d %s %d %s %s %s %u %s", tp->info->num1, "	", tp->info->num2, "		", tp->info->str, "		", tp->key, "\n");
			tp = tp->left;
		}
		printf("%d %s %d %s %s %s %u %s", tp->info->num1, "	", tp->info->num2, "		", tp->info->str, "		", tp->key, "\n");
		return 1;
	}
	if (cmp > 0)
		tp = tp->left;
	else
		tp = tp->right;
}

Tree* get_min(Tree* tp) {//очистить память возвращаемого значения
	//нахождение минимального в правом поддереве
	//в возвращаемом элементе есть только информация и ключ
	int length1;
	Tree* par;
	Tree* ret = (Tree*)calloc(1, sizeof(Tree));
	ret->info = (Info*)calloc(1, sizeof(Info));
	par = tp;
	tp = tp->right;
	while (tp->left_flag == 1) {
		par = tp;
		tp = tp->left;
	}
	ret->info->num1 = tp->info->num1;
	ret->info->num2 = tp->info->num2;
	length1 = length(tp->info->str) + 1;
	ret->info->str = (char*)calloc(length1, sizeof(char));
	strncpy(ret->info->str, tp->info->str, length1);
	ret->key = tp->key;
	if (tp->right_flag == 1)
		del_1sub(par, tp);
	else
		del_leaf(par, tp);
	return ret;
}

void del_leaf(Tree* par, Tree* tp) {//родительский элемент и удаляемый элемент
	if (par->left == tp) {
		par->left_flag = 0;
		//par->left = ...
	}
	else {
		par->right_flag = 0;
		//par->left = ...
	}
	free(tp->info->str);
	free(tp->info);
	free(tp);
}

void del_1sub(Tree* par, Tree* tp) {//родительский элемент и удаляемый элемент
	//перевешиваем в родительский элемент ветвь удаленного элемента
	if (par == NULL) {
		if (tp->left_flag == 1) {
			par = tp->left;
			tp->info->str = tp->left->info->str;
			tp->info->num1 = tp->left->info->num1;
			tp->info->num2 = tp->left->info->num2;
			tp->key = tp->left->key;
			tp->right_flag = tp->left->right_flag;
			tp->right = tp->left->right;
			tp->left_flag = tp->left->left_flag;
			tp->left = tp->left->right;
			//free(tp->left->info->str);
			free(par->info);
			free(par->left);
		}
		else {
			par = tp->right;
			tp->info->str = tp->right->info->str;
			tp->info->num1 = tp->right->info->num1;
			tp->info->num2 = tp->right->info->num2;
			tp->key = tp->right->key;
			tp->right_flag = tp->right->right_flag;
			tp->right = tp->right->right;
			tp->left_flag = tp->right->left_flag;
			tp->left = tp->right->right;
			//free(tp->left->info->str);
			free(par->info);
			free(par->left);
		}
	}
	else {
		if (par->left == tp) {
			if (tp->left_flag == 1) {
				par->left = tp->left;
			}
			else {
				par->left = tp->right;
			}
		}
		else {
			if (tp->left_flag == 1) {
				par->right = tp->left;
			}
			else {
				par->right = tp->right;
			}
		}
		free(tp->info->str);
		free(tp->info);
		free(tp);
	}
}

void del_2sub(Tree* par, Tree* tp) {//родительский и удаляемый
	int length1;
	Tree* buf = get_min(tp);
	tp->info->num1 = buf->info->num1;
	tp->info->num2 = buf->info->num2;
	length1 = length(buf->info->str) + 1;
	free(tp->info->str);
	tp->info->str = (char*)calloc(length1, sizeof(char));
	strncpy(tp->info->str, buf->info->str, length1);
	tp->key = buf->key;
	//free(buf->info->str);
	//free(buf->info);
	//free(buf);
}

int print(Tree* tree, int length)
{
	if (tree == NULL)
		return 1;
	if (tree->right_flag == 1)
		print(tree->right, length + 1);
	for (int i = 0; i < length; ++i)
		printf("-");
	printf("%u\n", tree->key);
	if (tree->left_flag == 1)
		print(tree->left, length + 1);
}


int print_list(Tree* tree, int size) {
	if (tree == NULL)
		return 1;
	if (number_digits(tree->key) == size)
		printf("%d %s %d %s %s %s %u %s", tree->info->num1, "	", tree->info->num2, "		", tree->info->str, "		", tree->key, "\n");
	if (tree->right_flag == 1)
		print_list(tree->right, size);
	if (tree->left_flag == 1)
		print_list(tree->left, size);
}

void set_parent(Tree* tp, Tree* parent) {
	if (tp->left_flag == 0 && tp->left != NULL && tp->left->info == NULL)
		tp->left = parent;
	if (tp->right_flag == 0 && tp->right != NULL && tp->right->info == NULL)
		tp->right = parent;
}

void free_element(Tree* tree) {
	if (tree->left_flag == 0)
		free(tree->left);
	else
		free_element(tree->left);

	if (tree->right_flag == 0)
		free(tree->right);
	else
		free_element(tree->right);
	free(tree->info->str);
	free(tree->info);
	free(tree);
}

void decimal(Tree* tree, int size) {
	Tree* tp;
	int cmp, check = 0;
	tp = tree;
	do {
		cmp = number_digits(tp->key);
		if (cmp == size) {
			if (check == 0) {
				printf("%s", "Number1	Number2		String		Key:\n");
				check = 1;
			}
			print_list(tp, size);
			return 1;
		}
		if (cmp > size)
			tp = tp->left;
		else
			tp = tp->right;
	} while ((tp->left_flag == 1 && tp->right_flag == 1) || (tp->left_flag == 1 && tp->right_flag == 0) || (tp->left_flag == 0 && tp->right_flag == 1));
	cmp = number_digits(tp->key);
	if (cmp == size) {
		if (check == 0) {
			printf("%s", "Number1	Number2		String		Key:\n");
			check = 1;
		}
		print_list(tp, size);
		return 1;
	}if (check == 0) {
		printf("%s", "There is no such element\n");
	}
}

int print_with_this_key(Tree* tp, unsigned int key, int check1) {
	//выводить результат таймирования? 1-да 0-нет
	Tree* parent = NULL;
	int timing = 1, count = 1;
	int cmp, check = 0, parent_check = 0;
	clock_t time1, start;
	start = clock();
	do {
		cmp = tp->key - key;
		if (cmp == 0) {
			if (check == 0) {
				printf("%s", "Number1	Number2		String		Key:\n");
				check = 1;
			}
			while (tp->left_flag == 1 && tp->left->key == key) {
				printf("%d %s %d %s %s %s %u %s", tp->info->num1, "	", tp->info->num2, "		", tp->info->str, "		", tp->key, "\n");
				tp = tp->left;
			}
			printf("%d %s %d %s %s %s %u %s", tp->info->num1, "	", tp->info->num2, "		", tp->info->str, "		", tp->key, "\n");
			return 1;
		}
		parent = tp;
		if (cmp > 0) {
			tp = tp->left;
		}
		else {
			tp = tp->right;
		}
		if (parent != NULL && tp->key == parent->key) {
			while (tp->left_flag == 1 && tp->left->key == tp->key)
				tp = tp->left;
			continue;
		}
		if (timing == 1 && check1 == 1) {
			time1 = clock();
			printf("%d%c%f%c%u %c", count, ';', (double)(time1 - start) / CLOCKS_PER_SEC, ';', tp->key, '\n');
			count++;
		}
	} while ((tp->left_flag == 1 && tp->right_flag == 1) || (tp->left_flag == 1 && tp->right_flag == 0) || (tp->left_flag == 0 && tp->right_flag == 1));
	cmp = tp->key - key;
	if (cmp == 0) {
		if (check == 0) {
			printf("%s", "Number1	Number2		String		Key:\n");
			check = 1;
		}
		while (tp->left_flag == 1 && tp->left->key == key) {
			printf("%d %s %d %s %s %s %u %s", tp->info->num1, "	", tp->info->num2, "		", tp->info->str, "		", tp->key, "\n");
			tp = tp->left;
		}
		printf("%d %s %d %s %s %s %u %s", tp->info->num1, "	", tp->info->num2, "		", tp->info->str, "		", tp->key, "\n");
		if (timing == 1 && check1 == 1) {
			time1 = clock();
			printf("%d%c%f %c", count, ';', (double)(time1 - start) / CLOCKS_PER_SEC, '\n');
		}
	}
}

void ADD(Tree* tree, unsigned int key, int num1, int num2, char* str) {
	int cmp, turn;
	Tree* parent = NULL;
	if (tree->info == NULL)//новое дерево
	{
		tree->info = calloc(1, sizeof(Info));
		tree->key = key;
		tree->info->num1 = num1;
		tree->info->num2 = num2;
		tree->info->str = str;
		tree->left = (Tree*)calloc(1, sizeof(Tree));
		tree->left_flag = 0;
		tree->right = (Tree*)calloc(1, sizeof(Tree));
		tree->right_flag = 0;
	}
	else
	{
		Tree* tp = tree;
		Tree* buf;
		while (1)
		{
			cmp = tp->key - key;
			if (cmp == 0) {//элемент с одинаковым ключем
				if (parent == NULL) {// ключ как в корне
					if (tree->left_flag == 1) {
						buf = (Tree*)calloc(1, sizeof(Tree));
						buf->info = (Info*)calloc(1, sizeof(Info));
						buf->left = (Tree*)calloc(1, sizeof(Tree));
						buf->right = (Tree*)calloc(1, sizeof(Tree));
						buf->info->num1 = tree->info->num1;
						buf->info->num2 = tree->info->num2;
						buf->info->str = tree->info->str;
						buf->key = tree->key;
						if (tree->left_flag == 1) {
							buf->left = tree->left;
							buf->left_flag = 1;
						}
						else
							tree->left_flag = 1;
						tree->left = buf;
						tree->info->num1 = num1;
						tree->info->num2 = num2;
						tree->info->str = str;
						tree->key = key;
					}
					else {
						tree->left_flag = 1;
						tree->left->info = calloc(1, sizeof(Info));
						tree->left->key = key;
						tree->left->info->num1 = num1;
						tree->left->info->num2 = num2;
						tree->left->info->str = str;
						tree->left->left = (Tree*)calloc(1, sizeof(Tree));
						tree->left->left_flag = 0;
						tree->left->right = (Tree*)calloc(1, sizeof(Tree));
						tree->left->right_flag = 0;
					}
				}
				else {
					buf = (Tree*)calloc(1, sizeof(Tree));
					buf->info = (Info*)calloc(1, sizeof(Info));
					buf->left_flag = 1;
					buf->right = (Tree*)calloc(1, sizeof(Tree));
					buf->right_flag = 0;
					buf->info->num1 = num1;
					buf->info->num2 = num2;
					buf->info->str = str;
					buf->key = key;
					if (turn == 0) {
						if (parent->left->right_flag == 1) {
							buf->right_flag = 1;
							buf->right = parent->left->right;
							parent->left->right = NULL;
							parent->left->right_flag = 0;
						}
						buf->left = parent->left;
						parent->left = buf;
					}
					else {
						if (parent->right->right_flag == 1) {
							buf->right_flag = 1;
							buf->right = parent->right->right;
							parent->right->right = NULL;
							parent->right->right_flag = 0;
						}
						buf->left = parent->right;
						parent->right = buf;
					}
					//set_parent(buf, parent);
				}
				return 1;
			}
			if (cmp > 0)//ключ элемента меньше
			{
				if (tp != tree && tp->left_flag == 1 && (tp->left->key == tp->key)) {
					while (tp != tree && tp->left_flag == 1 && (tp->left->key == tp->key)) {
						parent = tp;
						turn = 0;
						tp = tp->left;
					}
				}
				else {
					if (tp->left_flag == 0)
					{
						tp->left_flag = 1;
						tp->left = calloc(1, sizeof(Tree));
						tp->left->info = calloc(1, sizeof(Info));
						tp->left->key = key;
						tp->left->info->num1 = num1;
						tp->left->info->num2 = num2;
						tp->left->info->str = str;
						tp->left->left = (Tree*)calloc(1, sizeof(Tree));
						tp->left->left_flag = 0;
						tp->left->right = (Tree*)calloc(1, sizeof(Tree));
						tp->left->right_flag = 0;
						//set_parent(tp, parent);
						return 1;
					}
					else {
						parent = tp;
						turn = 0;
						tp = tp->left;
					}
				}
			}
			else// ключ элемента больше
			{
				/*while (tp != tree && tp->left_flag == 1 && (tp->left->key == tp->key)) {
					parent = tp;
					turn = 0;
					tp = tp->left;
				}*/
				if (tp->right_flag == 0)
				{
					tp->right_flag = 1;
					//tp->right = calloc(1, sizeof(Tree));
					tp->right->info = calloc(1, sizeof(Info));
					tp->right->key = key;
					tp->right->info->num1 = num1;
					tp->right->info->num2 = num2;
					tp->right->info->str = str;
					tp->right->left = (Tree*)calloc(1, sizeof(Tree));
					tp->right->left_flag = 0;
					tp->right->right = (Tree*)calloc(1, sizeof(Tree));
					tp->right->right_flag = 0;
					//set_parent(tp, parent);
					return 1;
				}
				else {
					parent = tp;
					turn = 1;
					tp = tp->right;
				}

			}
		}
	}
}