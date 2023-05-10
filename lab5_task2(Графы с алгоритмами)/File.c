#include "Header.h"

int Write(List* all) {
	List* lp, * sub;
	int length1, count = 0;
	FILE* fp, * fp2;
	fp = fopen("Graph", "w+b");
	fp2 = fopen("Links", "w+b");
	lp = all;
	if (all->sub != NULL) {
		while (lp != NULL) {
			fwrite(&lp->sub->x, sizeof(int), 1, fp);
			fwrite(&lp->sub->y, sizeof(int), 1, fp);
			length1 = length(lp->sub->name);
			fwrite(&length1, sizeof(int), 1, fp);
			fprintf(fp, "%s", lp->sub->name);
			if (lp->sub->list != NULL) {
				count = 0;
				sub = lp->sub->list;
				while (sub != NULL) {
					length1 = length(lp->sub->name);
					fwrite(&length1, sizeof(int), 1, fp2);
					fprintf(fp2, "%s", lp->sub->name);
					length1 = length(sub->sub->name);
					fwrite(&length1, sizeof(int), 1, fp2);
					fprintf(fp2, "%s", sub->sub->name);
					fwrite(&sub->weight, sizeof(int), 1, fp2);
					sub = sub->next;
				}
			}
			lp = lp->next;
		}
	}
	fclose(fp);
	fclose(fp2);
	return 1;
}

int Read(List* all) {
	int num1, num2, size, x, y;
	char* name, * name2;
	Graph* gp, * gp2;
	FILE* fp, * fp2;
	fp = fopen("Graph", "r+b");
	fp2 = fopen("Links", "r+b");
	if (!fp || !fp2) {		//новое дерево
		return 0;
	}
	while (!feof(fp)) {
		fread(&x, sizeof(int), 1, fp);
		fread(&y, sizeof(int), 1, fp);
		fread(&size, sizeof(int), 1, fp);
		name = (char*)calloc(size + 1, sizeof(char));
		for (int r = 0; r < size; r++)
			fread(&name[r], sizeof(char), 1, fp);
		name[size] = '\0';
		if (!feof(fp))
			ADD(all, NULL, x, y, name);
	}
	while (!feof(fp2)) {
		fread(&size, sizeof(int), 1, fp2);
		if (feof(fp2))
			break;
		name = (char*)calloc(size + 1, sizeof(char));
		for (int r = 0; r < size; r++)
			fread(&name[r], sizeof(char), 1, fp2);
		name[size] = '\0';
		fread(&size, sizeof(int), 1, fp2);
		name2 = (char*)calloc(size + 1, sizeof(char));
		for (int r = 0; r < size; r++)
			fread(&name2[r], sizeof(char), 1, fp2);
		name2[size] = '\0';
		gp = find_with_this_name(all, name);
		gp2 = find_with_this_name(all, name2);
		fread(&size, sizeof(int), 1, fp2);
		if (!feof(fp2))
			ADD_edge(gp, gp2, size);
	}
	fclose(fp);
	fclose(fp2);
}