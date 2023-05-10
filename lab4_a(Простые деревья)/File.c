#include "Header.h"

void Write_recursion(FILE* fp, Tree* tree) {
	int length1;
	if (tree == NULL)
		return 1;

	fwrite(&tree->key, sizeof(unsigned int), 1, fp);
	fwrite(&tree->info->num1, sizeof(int), 1, fp);
	fwrite(&tree->info->num2, sizeof(int), 1, fp);
	length1 = length(tree->info->str);
	fwrite(&length1, sizeof(int), 1, fp);
	fprintf(fp, "%s", tree->info->str);

	if (tree->right_flag == 1)
		Write_recursion(fp, tree->right);

	if (tree->left_flag == 1)
		Write_recursion(fp, tree->left);
}

int Write(Tree* tree) {
	FILE* fp;
	fp = fopen("Tree", "w+b");
	Write_recursion(fp, tree);
	fclose(fp);
	return 1;
}

int Read(Tree* tree) {
	unsigned int key;
	int num1, num2, size;
	char* str;
	FILE* fp;
	fp = fopen("Tree", "r+b");
	if (!fp) {		//новое дерево
		//tree->info = NULL;
		return 0;
	}
	while (!feof(fp)) {
		fread(&key, sizeof(unsigned int), 1, fp);
		fread(&num1, sizeof(int), 1, fp);
		fread(&num2, sizeof(int), 1, fp);
		fread(&size, sizeof(int), 1, fp);
		str = (char*)calloc(size + 1, sizeof(char));
		for (int r = 0; r < size; r++)
			fread(&str[r], sizeof(char), 1, fp);
		str[size] = '\0';
		if (!feof(fp))
			ADD(tree, key, num1, num2, str);
	}
	fclose(fp);
}
