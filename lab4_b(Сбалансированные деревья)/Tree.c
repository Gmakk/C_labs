#include "Header.h"
int new_tree(Tree* tree, int low_x, int high_x, int low_y, int high_y, int choice) {

	switch (choice)
	{
	case 0:
		tree->sub[choice] = (Tree*)calloc(1, sizeof(Tree));
		tree->sub[choice]->low_limit_x = low_x;
		tree->sub[choice]->high_limit_x = low_x + (high_x - low_x) / 2;
		tree->sub[choice]->low_limit_y = high_y - (high_y - low_y) / 2;//+ 1
		tree->sub[choice]->high_limit_y = high_y;
		for (int i = 0; i < 4; i++)
			tree->sub[choice]->sub[i] = NULL;
		break;
	case 1:
		tree->sub[choice] = (Tree*)calloc(1, sizeof(Tree));
		tree->sub[choice]->low_limit_x = high_x - (high_x - low_x) / 2;//+ 1
		tree->sub[choice]->high_limit_x = high_x;
		tree->sub[choice]->low_limit_y = high_y - (high_y - low_y) / 2;//+ 1
		tree->sub[choice]->high_limit_y = high_y;
		for (int i = 0; i < 4; i++)
			tree->sub[choice]->sub[i] = NULL;
		break;
	case 2:
		tree->sub[choice] = (Tree*)calloc(1, sizeof(Tree));
		tree->sub[choice]->low_limit_x = low_x;
		tree->sub[choice]->high_limit_x = low_x + (high_x - low_x) / 2;
		tree->sub[choice]->low_limit_y = low_y;
		tree->sub[choice]->high_limit_y = low_y + (high_y - low_y) / 2;
		for (int i = 0; i < 4; i++)
			tree->sub[choice]->sub[i] = NULL;
		break;
	case 3:
		tree->sub[choice] = (Tree*)calloc(1, sizeof(Tree));
		tree->sub[choice]->low_limit_x = high_x - (high_x - low_x) / 2;//+ 1
		tree->sub[choice]->high_limit_x = high_x;
		tree->sub[choice]->low_limit_y = low_y;
		tree->sub[choice]->high_limit_y = low_y + (high_y - low_y) / 2;
		for (int i = 0; i < 4; i++)
			tree->sub[choice]->sub[i] = NULL;
		break;
	case 4:
		tree->low_limit_x = low_x;
		tree->high_limit_x = high_x;
		tree->low_limit_y = low_y;
		tree->high_limit_y = high_y;
		for (int i = 0; i < 4; i++)
			tree->sub[i] = NULL;
		break;
	default:
		break;
	}
	tree->item = NULL;
	tree->number = 0;
}

int select_sector(Tree* tree, int key_x, int key_y) {
	if (key_x <= tree->low_limit_x + (tree->high_limit_x - tree->low_limit_x) / 2 && key_y >= tree->high_limit_y - (tree->high_limit_y - tree->low_limit_y) / 2)// <= >
		return 0;
	if (key_x >= tree->high_limit_x - (tree->high_limit_x - tree->low_limit_x) / 2 && key_y >= tree->high_limit_y - (tree->high_limit_y - tree->low_limit_y) / 2)// > >
		return 1;
	if (key_x <= tree->low_limit_x + (tree->high_limit_x - tree->low_limit_x) / 2 && key_y <= tree->low_limit_y + (tree->high_limit_y - tree->low_limit_y) / 2)// <= <=
		return 2;
	if (key_x >= tree->high_limit_x - (tree->high_limit_x - tree->low_limit_x) / 2 && key_y <= tree->low_limit_y + (tree->high_limit_y - tree->low_limit_y) / 2)// > <=
		return 3;
}
int add_item(Tree* tree, int key_x, int key_y, int num1, int num2, char* str, int choice) {
	Item* ip, * parent, * buf;
	Tree* tp;
	if (choice == 4)
		tp = tree;
	else
		tp = tree->sub[choice];
	ip = (Item*)calloc(1, sizeof(Item));
	ip->key_x = key_x;
	ip->key_y = key_y;
	ip->num1 = num1;
	ip->num2 = num2;
	ip->str = str;
	//вставка в список элементов
	if (tp->item == NULL) {
		tp->item = ip;
		ip->next = NULL;
	}
	else {
		if (tp->item->key_x >= ip->key_x) {
			buf = tp->item;
			tp->item = ip;
			ip->next = buf;
		}
		else {
			parent = tp->item;
			if (parent->next == NULL) {
				tp->item->next = ip;
				ip->next = NULL;
			}
			else {
				while (parent->next != NULL && ip->key_x > parent->next->key_x)
					parent = parent->next;
				buf = parent->next;
				parent->next = ip;
				ip->next = buf;
			}
		}
	}
	tp->number++;
}

int overflow(Tree* tree, int key_x, int key_y, int num1, int num2, char* str) {
	Item* ip = tree->item, * parent;
	//создание дочерних элементов
	for (int i = 0; i < 4; i++) {
		//tree->sub[i] = (Tree*)calloc(1, sizeof(Tree));
		new_tree(tree, tree->low_limit_x, tree->high_limit_x, tree->low_limit_y, tree->high_limit_y, i);
	}
	//перенос Item в дочерние элементы
	while (ip->next != NULL) {
		add_item(tree, ip->key_x, ip->key_y, ip->num1, ip->num2, ip->str, select_sector(tree, ip->key_x, ip->key_y));
		parent = ip;
		ip = ip->next;
		free(parent);
	}
	add_item(tree, ip->key_x, ip->key_y, ip->num1, ip->num2, ip->str, select_sector(tree, ip->key_x, ip->key_y));
	free(ip);
	tree->number = 0;
	tree->item = NULL;
	//новая попытка добавить элемент после внесения изменений
	ADD(tree, key_x, key_y, num1, num2, str);
}

int ADD(Tree* tree, int key_x, int key_y, int num1, int num2, char* str) {
	Tree* tp = tree;
	if (key_x < x_low_limit || key_x>x_high_limit || key_y<y_low_limit || key_y > y_high_limit) {
		printf("%s", "Values are out of bounds\n");
		return 1;
	}
	while (1)
	{
		if (tp->number < one_square_range && tp->sub[0] == NULL && tp->sub[1] == NULL && tp->sub[2] == NULL && tp->sub[3] == NULL) {
			add_item(tp, key_x, key_y, num1, num2, str, 4);
			return 1;
		}
		if (tp->number == one_square_range && tp->sub[0] == NULL && tp->sub[1] == NULL && tp->sub[2] == NULL && tp->sub[3] == NULL) {
			overflow(tp, key_x, key_y, num1, num2, str);
			return 1;
		}
		tp = tp->sub[select_sector(tp, key_x, key_y)];
	}
}

Item* find_with_this_key(Tree* tree, int key_x, int key_y, int print1) {//1-печатать 0-нет
	Tree* tp = tree;
	Item* ip;
	while (tp->number == 0 && !(tp->sub[0] == NULL && tp->sub[1] == NULL && tp->sub[2] == NULL && tp->sub[3] == NULL))
		tp = tp->sub[select_sector(tp, key_x, key_y)];
	if (tp->item == NULL)
		return NULL;
	else {
		ip = tp->item;
		while (ip->next != NULL) {
			if (ip->key_x == key_x && ip->key_y == key_y) {
				if (print1 == 1) {
					printf("%s", "Key x	Key y	Number1	Number2	String:\n");
					printf("%d%s%d%s%d%s%d%s%s%c", ip->key_x, "	", ip->key_y, "	", ip->num1, "	", ip->num2, "	", ip->str, '\n');
				}
				return ip;
			}
			ip = ip->next;
		}
		if (ip->key_x == key_x && ip->key_y == key_y) {
			if (print1 == 1) {
				printf("%s", "Key x	Key y	Number1	Number2	String:\n");
				printf("%d%s%d%s%d%s%d%s%s%c", ip->key_x, "	", ip->key_y, "	", ip->num1, "	", ip->num2, "	", ip->str, '\n');
			}
			return ip;
		}
	}
	if (print1 == 1)
		printf("%s", "There is no such element");
	return NULL;
}

del_item(Tree* tree, int key_x, int key_y) {
	Tree* tp = tree;
	Item* ip, * parent;
	if (tree->item == NULL)
		return -1;
	ip = tree->item;
	//один элемент
	if (ip->next == NULL) {
		if (ip->key_x == key_x && ip->key_y == key_y) {
			free(tree->item);
			tree->item = NULL;
			tree->number = 0;
			return 1;
		}
		else
			return -1;
	}
	parent = tree->item;
	ip = parent->next;
	//первый элемент
	if (parent->key_x == key_x && parent->key_y == key_y) {
		free(parent);
		tree->item = ip;
		tree->number--;
		return 1;
	}
	while (ip->next != NULL && !(ip->key_x == key_x && ip->key_y == key_y)) {
		parent = parent->next;
		ip = ip->next;
	}
	//последний элмент
	if (ip->next == NULL && ip->key_x == key_x && ip->key_y == key_y) {
		free(ip);
		parent->next = NULL;
		tree->number--;
		return 1;
	}
	//элемент из середины
	if (ip->key_x == key_x && ip->key_y == key_y) {
		parent->next = ip->next;
		free(ip);
		tree->number--;
		return 1;
	}
	return -1;
}

int print(Tree* tree, int length)
{
	Item* ip;
	if (tree == NULL)
		return 1;
	for (int i = 0; i < length; ++i)
		printf(" ");
	printf("%s%d%c%d%s%d%c%d%s", "(x:", tree->low_limit_x, '-', tree->high_limit_x, "   y:", tree->low_limit_y, '-', tree->high_limit_y, ")\n");
	//for (int i = 0; i < length; ++i)
		//printf(" ");
	//printf("%c%s%d%c%d%s","(y:",tree->low_limit_y,'-',tree->high_limit_y,")\n");
	if (tree->number > 0) {
		ip = tree->item;
		for (int i = 0; i < length; ++i)
			printf("-");
		printf("{");
		while (ip != NULL) {
			printf("%d%c%d", ip->key_x, ';', ip->key_y);
			if (ip->next != NULL)
				printf("%c", '	');
			ip = ip->next;
		}
		printf("}");
		printf("%c", '\n');
	}
	if (tree->number == 0 && tree->sub[0] != NULL && tree->sub[1] != NULL && tree->sub[2] != NULL && tree->sub[3] != NULL) {
		for (int p = 0; p < 4; p++)
			print(tree->sub[p], length + 1);
	}
}

int comparison(Tree* tree, Item* comp, Item** min, int lim_x, int lim_y, int** dist) {
	Item* ip;
	if (tree == NULL)
		return 1;
	if (tree->number > 0) {
		ip = tree->item;
		while (ip != NULL) {
			if (distance(comp, ip) < **dist && ip != comp && ip->key_x <= lim_x && ip->key_y <= lim_y) {
				**dist = distance(comp, ip);
				*min = ip;
			}
			ip = ip->next;
		}
	}
	if (tree->number == 0 && tree->sub[0] != NULL && tree->sub[1] != NULL && tree->sub[2] != NULL && tree->sub[3] != NULL) {
		for (int p = 0; p < 4; p++)
			comparison(tree->sub[p], comp, min, lim_x, lim_y, dist);
	}
}

int clean(Tree* tree) {
	Tree* tp = tree;
	Item* ip, * buf;
	int count = 0;
	if (tree != NULL) {
		for (int p = 0; p < 4; p++)
			clean(tree->sub[p]);
		if (tree->sub[0] != NULL && (tree->sub[0]->number > 0 || tree->sub[1]->number > 0 || tree->sub[2]->number > 0 || tree->sub[3]->number > 0)) {
			//if ( (tree->sub[0]->number == 0 && tree->sub[1]->number > 0 && tree->sub[2]->number > 0 && tree->sub[3]->number > 0)) {
			for (int i = 0; i < 4; i++) {
				count += tree->sub[i]->number;
				if (tree->sub[i]->sub[0] != NULL)
					return 1;
			}
			if (count == one_square_range) {
				for (int t = 0; t < 4; t++) {
					ip = tree->sub[t]->item;
					while (ip != NULL) {
						buf = ip;
						add_item(tree, ip->key_x, ip->key_y, ip->num1, ip->num2, ip->str, 4);
						ip = ip->next;
						free(buf);
					}
					free(tree->sub[t]);
					tree->sub[t] = NULL;
				}
				tree->number = count;
			}
		}
	}
	return 1;
}

int del(Tree* tree) {
	Item* ip, * parent;
	if (tree == NULL)
		return 1;
	if (tree->sub[0] == NULL) {
		if (tree->number > 0) {
			parent = tree->item;
			ip = parent->next;
			while (ip != NULL) {
				free(parent->str);
				free(parent);
				parent = ip;
				ip = ip->next;
			}
			free(parent->str);
			free(parent);
		}
		free(tree);
	}
	else {
		for (int i = 0; i < 4; i++)
			del(tree->sub[i]);
		free(tree);
	}

	return 1;
}