#include "Header.h"

int ADD_numbers(int number) {
	int number_add;
	FILE* fp;
	fp = fopen("Numbers", "a+b");
	for (int i = 0; i < number; i++) {
		number_add = rand() % 10;
		fwrite(&number_add, sizeof(int), 1, fp);
	}
	fclose(fp);
	return 1;
}

int first_occ(int number) {
	int number1, offset;
	char* new;
	FILE* fp;
	Item* ip;
	fp = fopen("Numbers", "r+b");
	if (!fp) {
		return -2;
	}
	Tree* tree = (Tree*)calloc(1, sizeof(Tree));
	new_tree(tree, x_low_limit, x_high_limit, y_low_limit, y_high_limit, 4);
	while (!feof(fp)) {
		offset = ftell(fp);
		fread(&number1, sizeof(int), 1, fp);
		if (find_with_this_key(tree, number1, number1, 0) == NULL) {
			new = (char*)calloc(1, sizeof(char));
			ADD(tree, number1, number1, offset, offset, new);
		}
	}
	ip = find_with_this_key(tree, number, number, 0);
	if (ip == NULL)
		return -1;
	else
		return ip->num1;
	//delTree(&tree);
	fclose(fp);
	return 1;
}

int offset() {
	int choice, number, result;
	printf("%s", "Add items(1) or find offset(2):");
	getInt(&choice);
	switch (choice) {
	case 1:
		printf("%s", "How many items to add:");
		getInt(&number);
		ADD_numbers(number);
		break;
	case 2:
		printf("%s", "Enter number:");
		getInt(&number);
		result = first_occ(number);
		switch (result)
		{
		case -2:
			printf("%s", "File is empty\n");
			break;
		case -1:
			printf("%s", "There is no such element\n");
			break;
		default:
			printf("%s%d", "Offset:", result);
			break;
		}
		break;
	default:
		printf("%s", "There is no such option\n");
		break;
	}
}