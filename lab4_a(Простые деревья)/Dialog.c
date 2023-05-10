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
	unsigned int key, number;
	int num1, num2, choice;
	char* str;
	char buf;
	printf("%s", "Enter your information(1) or fill in random values(2):\n");
	getInt(&choice);
	switch (choice)
	{
	case 1:
		printf("%s", "Enter key:");
		getNumber(&key);
		printf("%s %s %s", "Enter information", "\n", "Number1 and Number2:\n");
		getInt(&num1);
		getInt(&num2);
		printf("%s", "Enter string:");
		scanf_s("%*c");
		str = get_str();

		ADD(tree, key, num1, num2, str);
		break;
	case 2:
		printf("%s", "Enter the number of items:");
		getNumber(&number);
		srand(time(NULL));
		for (int i = 0; i < number; i++) {
			key = rand() % 1001;
			num1 = rand() % 1001;
			num2 = rand() % 1001;
			str = (char*)calloc(2, sizeof(char));
			buf = 65 + rand() % 26;
			str[0] = buf;
			str[1] = '\0';

			ADD(tree, key, num1, num2, str);
		}
		break;
	default:
		printf("%s", "There is no such option\n");
		break;
	}


}

int D_Find(Tree* tree) {
	unsigned int key, buf_key;
	Tree* tp;
	Tree* left = NULL;
	Tree* right = NULL;
	int cmp, choice, difference = 0, check_left = 0, check_right = 0;

	if (tree->info == NULL) {
		printf("%s", "Tree is empty\n");
		return 1;
	}
	else {
		printf("%s", "Specific(1) or most different(2)\n");
		getInt(&choice);
		printf("%s", "Enter key:");
		getNumber(&key);
		switch (choice)
		{
		case 1:
			print_with_this_key(tree, key, 1);
			return 1;
			break;
		case 2:
			if (!(tree->left_flag == 0 && tree->right_flag == 0)) {
				tp = tree;
				difference = abs(tp->key - key);
				buf_key = tp->key;
				while (check_left == 0 || check_right == 0) {
					if (tp->left_flag == 1 && (abs(tp->left->key - key) > difference)) {
						difference = abs(tp->left->key - key);
						buf_key = tp->left->key;
						tp = tp->left;
						check_left = 0;
					}
					else
						check_left = 1;
					if (tp->right_flag == 1 && (abs(tp->right->key - key) > difference)) {
						difference = abs(tp->right->key - key);
						buf_key = tp->right->key;
						tp = tp->right;
						check_right = 0;
					}
					else
						check_right = 1;
				}
				print_with_this_key(tree, buf_key, 0);
				if (difference == 0) {
					printf("%s", "There is no such element\n");
					return 1;
				}
				return 1;
			}
			break;
		default:
			printf("%s", "There is no such option\n");
			return 1;
			break;
		}

	}
	printf("%s", "There is no such element\n");
	return 1;
}

int D_Delete(Tree* tree) {
	unsigned int key;
	Tree* tp;
	Tree* parent;
	int cmp;
	if (tree->info == NULL) {
		printf("%s", "Tree is empty\n");
		return 1;
	}
	else {
		printf("%s", "Enter key:");
		getNumber(&key);
		//Удаление по количеству поддеревьев
		if (tree->left_flag == 0 && tree->right_flag == 0 && tree->key == key) {
			free(tree->info->str);
			free(tree->info);
			tree->info = NULL;
			//free(tree->left);
			//free(tree->right);
			return 1;
		}
		if (((tree->left_flag == 1 && tree->right_flag == 0) || (tree->left_flag == 0 && tree->right_flag == 1)) && tree->key == key) {
			del_1sub(NULL, tree);
			return 1;
		}
		else {
			tp = tree;
			parent = NULL;
			do {
				cmp = tp->key - key;
				if (cmp == 0) {
					while (tp->left_flag == 1 && tp->left->key == key) {
						parent = tp;
						tp = tp->left;
					}
					if ((tp->left_flag == 1 && tp->right_flag == 0) || (tp->left_flag == 0 && tp->right_flag == 1)) {
						del_1sub(parent, tp);
					}
					if (tp->left_flag == 1 && tp->right_flag == 1) {
						del_2sub(parent, tp);
					}
					if (tp->left_flag == 0 && tp->right_flag == 0) {
						del_leaf(parent, tp);
					}
					//free(tp->info->str);
					//free(tp);
					return 1;
				}
				if (cmp > 0) {
					parent = tp;
					tp = tp->left;
				}
				else {
					parent = tp;
					tp = tp->right;
				}
			} while ((tp->left_flag == 1 && tp->right_flag == 1) || (tp->left_flag == 1 && tp->right_flag == 0) || (tp->left_flag == 0 && tp->right_flag == 1));
			cmp = tp->key - key;
			if (cmp == 0) {
				while (tp->left_flag == 1 && tp->left->key == key) {
					parent = tp;
					tp = tp->left;
				}
				if ((tp->left_flag && !tp->right_flag) || (!tp->left_flag && tp->right_flag)) {
					del_1sub(parent, tp);
				}
				if (tp->left_flag && tp->right_flag) {
					del_2sub(parent, tp);
				}
				if (!tp->left_flag && !tp->right_flag) {
					del_leaf(parent, tp);
				}
				return 1;
			}
			if (cmp > 0) {
				parent = tp;
				tp = tp->left;
			}
			else {
				parent = tp;
				tp = tp->right;
			}
		}
		printf("%s", "There is no such element\n");
	}
	return 1;
}

int D_Show(Tree* tree) {
	int choice, size;
	if (tree->info != NULL) {
		printf("%s", "All elements(1) or by the number of decimal(2)\n");
		getInt(&choice);
		switch (choice)
		{
		case 1:
			printf("%s", "\n\n");
			print(tree, 0);
			printf("%s", "\n\n");
			break;
		case 2:
			printf("%s", "Enter size\n");
			getInt(&size);
			decimal(tree, size);
			break;
		default:
			printf("%s", "There is no such option\n");
			break;
		}
	}
	else {
		printf("%s", "Tree is empty\n");
		return 1;
	}
}

int D_Timing() {
	Tree* tree = (Tree*)calloc(1, sizeof(Tree));
	tree->info = NULL;
	unsigned int key;
	int find, num1, num2, number = 1000, total = 1000, average = 0, count = 1;
	char* str;
	char buf;
	Tree* parent = NULL;
	Tree* tp;
	clock_t time1, start;
	srand(time(NULL));
	for (int p = 0; p < 1000; p++) {

		for (int i = 0; i < number; i++) {
			key = rand() * rand();
			num1 = rand() % 1001;
			num2 = rand() % 1001;
			str = (char*)calloc(2, sizeof(char));
			buf = 65 + rand() % 26;
			str[0] = buf;
			str[1] = '\0';

			ADD(tree, key, num1, num2, str);
		}
		start = clock();
		for (int g = 0; g < 10000; g++) {
			find = rand() * rand();
			tp = tree;
			parent = NULL;

			int cmp;
			do {
				cmp = tp->key - find;
				if (cmp == 0) {
					break;
				}
				parent = tp;
				if (cmp > 0)
					tp = tp->left;
				else
					tp = tp->right;
				if (tp->key == parent->key) {
					while (tp->left_flag == 1 && tp->left->key == tp->key)
						tp = tp->left;
					continue;
				}
				count++;
			} while ((tp->left_flag == 1 && tp->right_flag == 1) || (tp->left_flag == 1 && tp->right_flag == 0) || (tp->left_flag == 0 && tp->right_flag == 1));

			//count++;
		}
		time1 = clock();
		count = count / 10000;
		printf("%d%c%d%c%f%c", total, ';', count, ';', (double)(time1 - start) / (CLOCKS_PER_SEC * 10000) * 10000000, '\n');
		count = 1;
		total += number;
	}
}

void delTree(Tree* tree) {
	free(tree->info->str);
	free(tree->info);
	if (tree->left_flag == 0)
		free(tree->left);
	else
		free_element(tree->left);

	if (tree->right_flag == 0)
		free(tree->right);
	else
		free_element(tree->right);
}