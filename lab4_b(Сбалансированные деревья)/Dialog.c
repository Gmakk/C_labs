#include "Header.h"

int dialog(const char* msgs[], int N)
{
	char* errmsg = "";
	int rc;
	int i, n;
	do {
		puts(errmsg);
		errmsg = "There is no such option";
		for (i = 0; i < N; ++i)
			puts(msgs[i]);
		puts("Make your choice:");
		n = getInt(&rc);
		if (n == 0)
			rc = 0;
	} while (rc < 0 || rc >= N);
	return rc;
}

int D_Add(Tree* tree) {
	int key_x, key_y, num1, num2, choice;
	char* str;
	printf("%s", "Enter key x:");
	getInt(&key_x);
	printf("%s", "Enter key y:");
	getInt(&key_y);
	printf("%s %s %s", "Enter information", "\n", "Number1 and Number2:\n");
	getInt(&num1);
	getInt(&num2);
	printf("%s", "Enter string:");
	scanf_s("%*c");
	str = get_str();
	if (find_with_this_key(tree, key_x, key_y, 0) != NULL) {
		printf("%s", "Duplicate keys\n");
		return -1;
	}
	ADD(tree, key_x, key_y, num1, num2, str);
	return 1;
}

int D_Find(Tree* tree) {
	int key_x, key_y, choice, buf = INT_MAX, lim_x, lim_y;
	int* dist = &buf;
	Item* ip, * min = NULL;
	printf("%s", "Search for a specific item(1) or the nearest one(2)\n");
	getInt(&choice);
	switch (choice)
	{
	case 1:
		printf("%s", "Enter key x:");
		getInt(&key_x);
		printf("%s", "Enter key y:");
		getInt(&key_y);
		ip = find_with_this_key(tree, key_x, key_y, 0);
		if (ip != NULL) {
			printf("%s", "Key x	Key y	Number1	Number2	String:\n");
			printf("%d%s%d%s%d%s%d%s%s%c", ip->key_x, "	", ip->key_y, "	", ip->num1, "	", ip->num2, "	", ip->str, '\n');
		}
		else
			printf("%s", "There is no such element\n");
		break;
	case 2:
		if (tree->sub[0] == NULL && tree->number < 2) {
			printf("%s", "Not enough elements\n");
			return -1;
		}
		printf("%s", "Enter key x:");
		getInt(&key_x);
		printf("%s", "Enter key y:");
		getInt(&key_y);
		printf("%s", "Enter limit x:");
		getInt(&lim_x);
		printf("%s", "Enter limit y:");
		getInt(&lim_y);
		ip = find_with_this_key(tree, key_x, key_y, 0);
		if (ip == NULL) {
			printf("%s", "There is no such element\n");
			return -1;
		}
		comparison(tree, ip, &min, lim_x, lim_y, &dist);
		if (min == NULL) {
			printf("%s", "There is no such element\n");
			return -1;
		}
		printf("%s", "Key x	Key y	Number1	Number2	String:\n");
		printf("%d%s%d%s%d%s%d%s%s%c", min->key_x, "	", min->key_y, "	", min->num1, "	", min->num2, "	", min->str, '\n');
		break;
	default:
		printf("%s", "There is no such option\n");
		break;
	}
	return 1;
}

int D_Delete(Tree* tree) {
	Tree* tp = tree;
	int key_x, key_y;
	printf("%s", "Enter key x:");
	getInt(&key_x);
	printf("%s", "Enter key y:");
	getInt(&key_y);

	while (tp->number == 0 && !(tp->sub[0] == NULL && tp->sub[1] == NULL && tp->sub[2] == NULL && tp->sub[3] == NULL))
		tp = tp->sub[select_sector(tp, key_x, key_y)];
	if (tp->item == NULL) {
		printf("%s", "There is no such element");
		return -1;
	}
	else {
		if (del_item(tp, key_x, key_y) == -1)
			printf("%s", "There is no such element");
		else
			clean(tree);
	}
	return -1;
}

int D_Show(Tree* tree) {
	if (tree->number == 0 && tree->sub[0] == NULL && tree->sub[1] == NULL && tree->sub[2] == NULL && tree->sub[3] == NULL) {
		printf("%s", "Tree is empty");
		return -1;
	}
	print(tree, 0);
	return 1;
}

int D_Timing() {
	Tree* tree = (Tree*)calloc(1, sizeof(Tree));
	int key_x, key_y, num1, num2, number = 1000, total = 1000, find1, find2, count = 1;
	char* str;
	char buf;
	Tree* tp = tree;
	Item* ip;
	clock_t time1, start;
	srand(time(NULL));
	new_tree(tree, x_low_limit, x_high_limit, y_low_limit, y_high_limit, 4);
	for (int i = 0; i < 1000; i++) {
		for (int p = 0; p < number; p++) {
			key_x = rand() * rand();
			key_y = rand() * rand();
			num1 = rand() % 1001;
			num2 = rand() % 1001;
			str = (char*)calloc(2, sizeof(char));
			buf = 65 + rand() % 26;
			str[0] = buf;
			str[1] = '\0';

			ADD(tree, key_x, key_y, num1, num2, str);
		}
		start = clock();
		for (int g = 0; g < 10000; g++) {
			find1 = rand() * rand();
			find2 = rand() * rand();
			tp = tree;
			while (tp->number == 0 && !(tp->sub[0] == NULL && tp->sub[1] == NULL && tp->sub[2] == NULL && tp->sub[3] == NULL)) {
				tp = tp->sub[select_sector(tp, find1, find2)];
				count++;
			}
			if (tp->item != NULL) {
				ip = tp->item;
				while (ip->next != NULL) {
					if (ip->key_x == find1 && ip->key_y == find2)
						break;
					count++;
					ip = ip->next;
				}
				count++;
			}
		}
		time1 = clock();
		count = count / 10000;
		printf("%d%c%d%c%f%c", total, ';', count, ';', (double)(time1 - start) / (CLOCKS_PER_SEC * 10000) * 10000000, '\n');
		count = 1;
		total += number;
	}
	return 1;
}

int delTree(Tree* tree) {
	Item* ip, * parent;
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
	for (int i = 0; i < 4; i++)
		del(tree->sub[i]);
	return 1;
}