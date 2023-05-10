#include "Header.h"

int Write(List* list) {
	Item* ip = list->header;
	int length1;
	FILE* fp;
	fp = fopen("Tree", "w+b");
	while (ip != NULL) {
		if (ip->key != LowStr && ip->key != HighStr) {//запись одного элемента
			length1 = length(ip->key);
			fwrite(&length1, sizeof(int), 1, fp);
			fprintf(fp, "%s", ip->key);
			fwrite(&ip->num1, sizeof(int), 1, fp);
			fwrite(&ip->num2, sizeof(int), 1, fp);
			length1 = length(ip->str);
			fwrite(&length1, sizeof(int), 1, fp);
			fprintf(fp, "%s", ip->str);
			fwrite(&ip->level, sizeof(int), 1, fp);
		}
		ip = ip->forvards[0];
	}
	fclose(fp);
}

int Read(List* list) {
	int num1, num2, size, level;
	char* key, * str;
	FILE* fp;
	fp = fopen("Tree", "r+b");
	if (!fp) {		//новое дерево
		return 0;
	}
	while (!feof(fp)) {
		fread(&size, sizeof(int), 1, fp);
		if (feof(fp))
			break;
		key = (char*)calloc(size + 1, sizeof(char));
		for (int r = 0; r < size; r++)
			fread(&key[r], sizeof(char), 1, fp);
		key[size] = '\0';
		fread(&num1, sizeof(int), 1, fp);
		fread(&num2, sizeof(int), 1, fp);
		fread(&size, sizeof(int), 1, fp);
		if (feof(fp))
			break;
		str = (char*)calloc(size + 1, sizeof(char));
		for (int r = 0; r < size; r++)
			fread(&str[r], sizeof(char), 1, fp);
		str[size] = '\0';
		fread(&level, sizeof(int), 1, fp);
		if (!feof(fp))
			ADD(list, key, num1, num2, str, level);
	}
	fclose(fp);
}