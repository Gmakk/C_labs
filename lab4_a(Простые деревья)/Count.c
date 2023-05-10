#include "Header.h"

int ADD_numbers(int number) {
	unsigned int number_add;
	FILE* fp;
	fp = fopen("Count", "a+b");
	for (int i = 0; i < number; i++) {
		number_add = rand() % 10;
		fwrite(&number_add, sizeof(unsigned int), 1, fp);
	}
	fclose(fp);
	return 1;
}

int recursive_count(Tree* tree,FILE* fc) {
	
	int count = 1;
	if (tree == NULL)
		return 1;
	if (tree->right_flag == 1)
		recursive_count(tree->right,fc);
	while (tree->left_flag==1 && tree->key==tree->left->key){
		tree = tree->left;
		count++;
	}
	fprintf(fc,"%u%c%d\n", tree->key, ' ', count);
	
	if (tree->left_flag == 1)
		recursive_count(tree->left,fc);
}

int count_numbers() {
	unsigned int number;
	char* new;
	FILE* fp;
	fp = fopen("Count", "r+b");
	FILE* fc;
	fc = fopen("Result.txt", "w");
	if (!fp) {
		return -1;
	}
	Tree* tree = (Tree*)calloc(1, sizeof(Tree));
	tree->info = NULL;
	while (!feof(fp)) {
		fread(&number, sizeof(unsigned int), 1, fp);
		new = (char*)calloc(1, sizeof(char));
		if(!feof(fp))
			ADD(tree, number, 0, 0, new);
	}
	recursive_count(tree,fc);
	//delTree(&tree);
	fclose(fp);
	fclose(fc);
	return 1;
}

int Counting() {
	int choice, number;
	printf("%s", "Add items(2) or count the number(2):");
	getInt(&choice);
	switch (choice){
	case 1:
		printf("%s", "How many items to add:");
		getInt(&number);
		ADD_numbers(number);
		break;
	case 2:
		if(count_numbers() == -1)
			printf("%s", "File is empty\n");
		break;
	default:
		printf("%s", "There is no such option\n");
		break;
	}
}