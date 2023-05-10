#define _CRT_SECURE_NO_WARNINGS 1 
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
#include <sys\stat.h>
#include "Header.h"
#include "File.h"

int Write(Table* ptab)
{
	int size, number = 0, hash, j, count = 0;
	Item* ptr;
	Item* buf;
	FILE* fp;
	fp = fopen("Table", "w+b");
	//количество элементов
	fwrite(&ptab->number, sizeof(int), 1, fp);
	//количество элементов busy=-1
	for (int i = 0; i < Length_2;i++) {
		if (ptab->ks2[i].busy == -1)
			count++;
	}
	fwrite(&count, sizeof(int), 1, fp);


	for (int i = 0; i < ptab->number; i++)
	//for (int i = 0; i < min(Length_1,Length_2); i++)//сделать так чтобы все и даже пустые смотрела
	{
		//if (ptab->ks1[i].key != 0)
		//if (ptab->ks1[i].key != 0 || ptab->ks2[find1(ptab,ptab->ks1[i].key)].busy == -1)
		//{
			//первое пространство ключей
			fwrite(&ptab->ks1[i].key, sizeof(int), 1, fp);
			fwrite(&ptab->ks1[i].par, sizeof(int), 1, fp);
			//второе пространство ключей

			//порядковый номер во втром пространстве
			hash = hash1(ptab->ks1[i].item->key2);
			j = hash;
			do
			{
				if (ptab->ks2[j].busy == 1 && strcmp(ptab->ks2[j].key, ptab->ks1[i].item->key2) == 0 && ptab->ks2[j].item->key1 == ptab->ks1[i].item->key1) {
					size = j;
					break;
				}
				hash2(&j);
				//j += hash2(key2);
				j %= Length_2;
			} while ((j != hash) && ptab->ks2[j].busy);
			//size = find2(ptab, ptab->ks1[i].item->key2);



			fwrite(&size, sizeof(int), 1, fp);//
			fwrite(&ptab->ks2[size].busy, sizeof(int), 1, fp);
			fwrite(&ptab->ks2[size].release, sizeof(int), 1, fp);
			//количество Item
			if (ptab->ks1[i].item->next != NULL) {
				ptr = ptab->ks1[i].item;
				do {
					buf = ptr;
					ptr = ptr->next;
					number++;

				} while (ptr->next != NULL);
				number++;
			}
			else
				number = 1;
			fwrite(&number, sizeof(int), 1, fp);
			//по порядку записываем элементы из одного списка
			ptr = ptab->ks1[i].item;
			for (int g = 0; g < number - 1; g++) {
				// поля Item
				fwrite(&ptr->key1, sizeof(int), 1, fp);
				size = length(ptr->key2);
				fwrite(&size, sizeof(int), 1, fp);
				fprintf(fp, "%s", ptr->key2);
				fwrite(&ptr->release, sizeof(int), 1, fp);
				fwrite(&ptr->place.length, sizeof(int), 1, fp);
				fwrite(&ptr->place.offset, sizeof(int), 1, fp);
				ptr = ptr->next;
			}
			// поля Item
			fwrite(&ptr->key1, sizeof(int), 1, fp);
			size = length(ptr->key2);
			fwrite(&size, sizeof(int), 1, fp);
			fprintf(fp, "%s", ptr->key2);
			fwrite(&ptr->release, sizeof(int), 1, fp);
			fwrite(&ptr->place.length, sizeof(int), 1, fp);
			fwrite(&ptr->place.offset, sizeof(int), 1, fp);
		//}
		//else
			//printf("%s", "Empty element");
	}
	for (int i = 0; i < Length_2; i++) {
		if (ptab->ks2[i].busy == -1)
			fwrite(&i, sizeof(int), 1, fp);
	}
	fclose(fp);
}

int Read(Table* ptab)
{
	int number, size, ks2_place, count, num;
	Item* ptr;
	Item* buf;
	FILE* fp;
	//таблица
	ptab->ks1 = (KeySpace1*)calloc(Length_1, sizeof(KeySpace1));
	ptab->ks2 = (KeySpace2*)calloc(Length_2, sizeof(KeySpace2));
	ptab->msize1 = Length_1;
	ptab->msize2 = Length_2;
	fp = fopen("Table", "r+b");
	if (!fp) {		//новая таблица
		ptab->number = 0;
		return 0;
	}
	//количество элементов
	fread(&ptab->number, sizeof(int), 1, fp);
	//количество элементов busy=-1
	fread(&count, sizeof(int), 1, fp);


	for (int i = 0; i < ptab->number; i++)
	{
		//первое пространство ключей
		fread(&ptab->ks1[i].key, sizeof(int), 1, fp);
		fread(&ptab->ks1[i].par, sizeof(int), 1, fp);
		//второе пространство ключей
		fread(&ks2_place, sizeof(int), 1, fp);
		fread(&ptab->ks2[ks2_place].busy, sizeof(int), 1, fp);
		fread(&ptab->ks2[ks2_place].release, sizeof(int), 1, fp);
		//количество Item
		fread(&number, sizeof(int), 1, fp);
		//выделение памяти
		ptab->ks1[i].item = (Item*)calloc(1, sizeof(Item));
		ptr = ptab->ks1[i].item;
		ptr->next = NULL;
		for (int p = 0; p < number - 1; p++) {
			ptr->next = (Item*)calloc(1, sizeof(Item));
			if (p == number - 2)
				ptr->next = NULL;
			ptr = ptr->next;
		}
		ptr = ptab->ks1[i].item;
		for (int p = 0; p < number - 1; p++) {
			//Item
			ptr->place.offset = ftell(fp);
			fread(&ptr->key1, sizeof(int), 1, fp);
			fread(&size, sizeof(int), 1, fp);
			ptr->key2 = (char*)calloc(size + 1, sizeof(char));
			for (int r = 0; r < size; r++)
				fread(&ptr->key2[r], sizeof(char), 1, fp);
			ptr->key2[size] = '\0';
			fread(&ptr->release, sizeof(int), 1, fp);
			fread(&ptr->place.length, sizeof(int), 1, fp);
			fread(&ptr->place.offset, sizeof(int), 1, fp);
			ptr = ptr->next;
		}
		//Item
		ptr->place.offset = ftell(fp);
		fread(&ptr->key1, sizeof(int), 1, fp);
		fread(&size, sizeof(int), 1, fp);
		ptr->key2 = (char*)calloc(size + 1, sizeof(char));
		for (int r = 0; r < size; r++)
			fread(&ptr->key2[r], sizeof(char), 1, fp);
		ptr->key2[size] = '\0';
		fread(&ptr->release, sizeof(int), 1, fp);
		fread(&ptr->place.length, sizeof(int), 1, fp);
		fread(&ptr->place.offset, sizeof(int), 1, fp);
		ptab->ks2[ks2_place].item = ptab->ks1[i].item;
		ptab->ks2[ks2_place].key = ptab->ks1[i].item->key2;
	}
	for (int i = 0; i < count; i++) {
		fread(&num, sizeof(int), 1, fp);
		ptab->ks2[num].busy = -1;
	}
	fclose(fp);
	return 1;
}

FilePlace* Write_Info(InfoType info) {
	FilePlace* ret = (FilePlace*)calloc(1, sizeof(FilePlace));
	FILE* fp;
	fp = fopen("Info", "a");

	int fd = _fileno(fp);
	struct stat buf;
	fstat(fd, &buf);
	ret->offset = buf.st_size;

	fwrite(&info.num1, sizeof(int), 1, fp);
	fwrite(&info.num2, sizeof(int), 1, fp);
	ret->length = length(info.str);
	fwrite(&ret->length, sizeof(int), 1, fp);
	fprintf(fp, "%s", info.str);
	fclose(fp);
	return ret;
}

InfoType* Read_Info(FilePlace place) {
	InfoType* ret = (InfoType*)calloc(1, sizeof(InfoType));
	FILE* fp;
	fp = fopen("Info", "r+b");
	fseek(fp, place.offset, SEEK_SET);
	fread(&ret->num1, sizeof(int), 1, fp);
	fread(&ret->num2, sizeof(int), 1, fp);
	fread(&ret->lenght, sizeof(int), 1, fp);
	ret->str = (char*)calloc(ret->lenght + 1, sizeof(char));
	for (int r = 0; r < ret->lenght; r++)
		fread(&ret->str[r], sizeof(char), 1, fp);
	ret->str[ret->lenght] = '\0';
	fclose(fp);
	return ret;
}