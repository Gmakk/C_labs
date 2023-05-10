#include "Header.h"

int Write_recursion(FILE* fp, Tree* tree) {
	Item* ip;
	int length1;
	if (tree == NULL)
		return 1;
	if (tree->number > 0 && tree->sub[0] == NULL) {
		ip = tree->item;
		while (ip != NULL) {
			fwrite(&ip->key_x, sizeof(int), 1, fp);
			fwrite(&ip->key_y, sizeof(int), 1, fp);
			fwrite(&ip->num1, sizeof(int), 1, fp);
			fwrite(&ip->num2, sizeof(int), 1, fp);
			length1 = length(ip->str);
			fwrite(&length1, sizeof(int), 1, fp);
			fprintf(fp, "%s", ip->str);
			ip = ip->next;
		}
	}
	else {
		for (int i = 0; i < 4; i++)
			Write_recursion(fp, tree->sub[i]);
	}
}

int Write(Tree* tree) {
	FILE* fp;
	fp = fopen("Tree", "w+b");
	Write_recursion(fp, tree);
	fclose(fp);
	return 1;
}

int Read(Tree* tree) {
	int num1, num2, size, key_x, key_y;
	char* str;
	FILE* fp;
	fp = fopen("Tree", "r+b");
	if (!fp) {		//новое дерево
		return 0;
	}
	while (!feof(fp)) {
		fread(&key_x, sizeof(int), 1, fp);
		fread(&key_y, sizeof(int), 1, fp);
		fread(&num1, sizeof(int), 1, fp);
		fread(&num2, sizeof(int), 1, fp);
		fread(&size, sizeof(int), 1, fp);
		if (feof(fp))
			break;
		str = (char*)calloc(size + 1, sizeof(char));
		for (int r = 0; r < size; r++)
			fread(&str[r], sizeof(char), 1, fp);
		str[size] = '\0';
		if (!feof(fp))
			ADD(tree, key_x, key_y, num1, num2, str);
	}
	fclose(fp);
}