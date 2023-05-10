#define _CRT_SECURE_NO_WARNINGS 1 
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
#include "Header.h"
#include "File.h"

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

int D_Add(Table* ptab)
{
	int num1, num2, key1, par, count_par = 0;
	char* str;
	char* key2;
	if (ptab->number < Length_1 && ptab->number < Length_2) {
		printf("%s", "Enter key1:");
		getInt(&key1);
		if (ptab->number != 0) {
			printf("%s", "key of the parent element:");
			getInt(&par);
			for (int i = 0; i < ptab->number; i++) {
				if (ptab->ks1[i].key == par)
					count_par++;
			}
			if (count_par == 0) {
				printf("%s", "Invalid key of the parent element\n");
				return -1;
			}
		}
		printf("%s", "Enter key2:");
		scanf_s("%*c");
		key2 = get_str();
		printf("%s %s %s", "Enter information", "\n", "Number1 and Number2:\n");
		getInt(&num1);
		getInt(&num2);
		printf("%s", "Enter string:");
		scanf_s("%*c");
		str = get_str();

		if (ptab->number == 0) {
			add_first(ptab, key1, key2, num1, num2, str);
		}
		else {
			add_following(ptab, key1, key2, par, num1, num2, str);
		}
	}
	else {
		printf("%s", "The table is full\n");
		return -1;
	}
	return 1;
}

int D_Find(Table* ptab)
{
	int key1, par, release, result1, result2, choice, choice1, hash, j, q = 0;
	char* key2;
	printf("%s", "1. by the key of the parent element      2. by the first key      3. by the second key     4. by two keys\n");
	getInt(&choice);
	if (ptab->number > 0) {
		switch (choice)
		{
		case 1:
			printf("%s", "Enter key of the parent element:\n");
			getInt(&par);
			for (int i = 0; i < ptab->number; i++) {
				if (ptab->ks1[i].par == par)
					list_print(ptab->ks1[i].item, ptab->ks1[i].par);
			}
			//binary_search(ptab, par);
			break;
		case 2:
			printf("%s", "Enter key1:\n");
			getInt(&key1);
			result1 = find1(ptab, key1);
			if (result1 != -1) {
				list_print(ptab->ks1[result1].item, ptab->ks1[result1].par);
			}
			else {
				printf("%s", "There is no such element\n");
				return -1;
			}
			break;
		case 3:
			printf("%s", "Find all items with this key(1) or select a release(2)\n");
			getInt(&choice1);
			printf("%s", "Enter key2:\n");
			scanf_s("%*c");
			key2 = get_str();
			result2 = find2(ptab, key2);
			if (result2 != -1) {
				switch (choice1)
				{
				case 1:
					//поиск по всем ключам через hash функции
					hash = hash1(key2);
					j = hash;
					do
					{
						if (ptab->ks2[j].busy == 1 && strcmp(ptab->ks2[j].key, key2) == 0)
							list_print(ptab->ks2[j].item, ptab->ks1[find1(ptab, ptab->ks2[j].item->key1)].par);
						hash2(&j);
						//j += hash2(key2);
						j %= Length_2;
					} while ((j != hash) && ptab->ks2[j].busy);
					break;
				case 2:
					//поиск до нужного элемента через hash функции
					hash = hash1(key2), j = hash;
					printf("%s", "Enter release:\n");
					getInt(&release);
					do
					{
						if (strcmp(ptab->ks2[j].key, key2) == 0, ptab->ks2[j].release == release) {
							list_print(ptab->ks2[j].item, ptab->ks1[find1(ptab, ptab->ks2[j].item->key1)].par);
							return 1;
						}
						hash2(&j);
						//j += hash2(key2);
						j %= Length_2;
					} while ((j != hash) && ptab->ks2[j].busy);
					//если вышел из цикла
					printf("%s", "There is no such element\n");
					return -1;
					break;
				default:
					printf("%s", "There is no such option");
					break;
				}
			}
			else {
				printf("%s", "There is no such element\n");
				return -1;
			}
			free(key2);
			break;
		case 4:
			printf("%s", "Enter key1:\n");
			getInt(&key1);
			printf("%s", "Enter key2:\n");
			scanf_s("%*c");
			key2 = get_str();
			result1 = find1(ptab, key1);
			if (result1 != -1 && ptab->ks2[find2(ptab, key2)].item == ptab->ks1[result1].item)
				list_print(ptab->ks1[result1].item, ptab->ks1[result1].par);
			else {
				printf("%s", "There is no such element\n");
				return -1;
			}
			free(key2);
			break;
		default:
			printf("%s", "There is no such option");
			break;
		}
	}
	else {
		printf("%s", "Table is empty\n");
		return -1;
	}
	return 1;
}

int D_Delete(Table* ptab)
{
	Item* ptr;
	int	key1, choice, result1, result2, key_int, choice1, release, hash_count, j, release_count, number_choice;
	char* key2;
	char* key_ch;
	printf("%s", "1. by the first key     2. by the second key     3. by two keys\n");
	getInt(&choice);
	if (ptab->number > 0) {
		switch (choice) {
		case 1:
			printf("%s", "Delete one element(1) or all of them(2)?:\n");
			getInt(&number_choice);
			switch (number_choice)
			{
			case 1:
				printf("%s", "Enter key1:");
				getInt(&key1);
				result1 = find1(ptab, key1);
				if (result1 != -1) {
					key_ch = ptab->ks1[result1].item->key2;
					result2 = find2(ptab, key_ch);
					if (ptab->ks1[result1].item->next == NULL) {
						delete_Item(ptab->ks1[result1].item);
						delete_from_key_spc(ptab, key1, result1, result2);
					}
					else {
						int rel;
						printf("%s", "Select release:\n");
						getInt(&rel);
						delete_certain(ptab, result1, result2, rel);
					}
					sort_ks1(ptab);
				}
				else
					printf("%s", "There is no such element");
				break;
			case 2:
				printf("%s", "Enter key1:");
				getInt(&key1);
				result1 = find1(ptab, key1);
				if (result1 != -1) {
					key_ch = ptab->ks1[result1].item->key2;
					result2 = find2(ptab, key_ch);
					//удаление данных
					free_list(ptab->ks1[result1].item);
					delete_from_key_spc(ptab, key1, result1, result2);
					sort_ks1(ptab);
				}
				else
					printf("%s", "There is no such element");
				break;
				break;
			default:
				printf("%s", "There is no such option");
				break;
			}
			break;
		case 2:
			printf("%s", "Delete all items with this key(1) or select a release(2)\n");
			getInt(&choice1);
			printf("%s", "Enter key2:\n");
			scanf_s("%*c");
			key2 = get_str();
			result2 = find2(ptab, key2);
			if (result2 != -1) {
				switch (choice1)
				{
				case 1:
					hash_count = hash1(key2);
					j = hash_count, release_count = 1;
					do
					{
						if (ptab->ks2[j].busy == 1 && strcmp(ptab->ks2[j].key, key2) == 0) {
							key_int = ptab->ks2[j].item->key1;
							result1 = find1(ptab, key_int);
							free_list(ptab->ks1[result1].item);
							delete_from_key_spc(ptab, key_int, result1, j);
							sort_ks1(ptab);
						}
						hash2(&j);
						j %= Length_2;
					} while ((j != hash_count) && ptab->ks2[j].busy);
					break;
				case 2:
					printf("%s", "Enter release:\n");
					getInt(&release);
					hash_count = hash1(key2);
					j = hash_count;
					do
					{
						if (ptab->ks2[j].busy == 1 && ptab->ks2[j].release == release && strcmp(ptab->ks2[j].key, key2) == 0) {
							key_int = ptab->ks2[j].item->key1;
							result1 = find1(ptab, key_int);
							if (result1 != -1) {
								//удаление данных
								free_list(ptab->ks1[result1].item);
								delete_from_key_spc(ptab, key_int, result1, j);
								sort_ks1(ptab);
							}
							else
								printf("%s", "There is no such element");
							break;
						}
						hash2(&j);
						j %= Length_2;
					} while ((j != hash_count) && ptab->ks2[j].busy);
					break;
				default:
					printf("%s", "There is no such option");
					break;
				}
			}
			else
				printf("%s", "There is no such element");
			free(key2);
			break;
		case 3:
			printf("%s", "Enter key1:");
			getInt(&key1);
			printf("%s", "Enter key2:");
			scanf_s("%*c");
			key2 = get_str();
			key_ch = key2;
			result2 = find2(ptab, key_ch);
			result1 = find1(ptab, key1);
			if (result1 != -1 && result2 != -1) {
				if (ptab->ks1[result1].item->next == NULL) {
					//удаление из 1 пространства ключей
					delete_Item(ptab->ks1[result1].item);
					delete_from_key_spc(ptab, key1, result1, result2);
				}
				else {
					int rel, count = 0;
					printf("%s", "Select release:\n");
					getInt(&rel);
					ptr = ptab->ks1[result1].item;
					delete_certain(ptab, result1, result2, rel);
				}
				sort_ks1(ptab);
			}
			else
				printf("%s", "There is no such element");
			free(key2);
			break;
		default:
			printf("%s", "There is no such option");
			break;
		}
	}
	else {
		printf("%s", "Table is empty\n");
		return -1;
	}
	return 1;
}

int D_Show(Table* ptab)
{
	FilePlace place;
	InfoType* info;
	Item* ptr;
	int choice;
	printf("%s", "Output by the first space(1) or by the second(2):\n");
	getInt(&choice);
	if (ptab->number == 0)
		printf("%s", "Table is empty");
	else {
		switch (choice)
		{
		case 1:
			printf("%s", "first number	second number		string		release		parent		key1		key2\n");
			for (int i = 0; i < ptab->number; i++)
			{
				if (ptab->ks1[i].key != 0) {
					ptr = ptab->ks1[i].item;
					while (ptr->next != NULL) {
						place.offset = ptr->place.offset;
						info = Read_Info(place);
						printf("%s %d %s %d %s %s %s %d %s %d %s %d %s %s %s", "	", info->num1, "		", info->num2,
							"		", info->str, "		", ptr->release, "		", ptab->ks1[i].par, "		", ptr->key1, "		", ptr->key2, "\n");
						ptr = ptr->next;
						free(info->str);
						free(info);
					}
					place.offset = ptr->place.offset;
					info = Read_Info(place);
					printf("%s %d %s %d %s %s %s %d %s %d %s %d %s %s %s", "	", info->num1, "		", info->num2,
						"		", info->str, "		", ptr->release, "		", ptab->ks1[i].par, "		", ptr->key1, "		", ptr->key2, "\n");
					free(info->str);
					free(info);
					printf("%s", "\n");
				}
			}
			break;
		case 2:
			printf("%s", "first number	second number		string		release		parent		key1		key2\n");
			for (int i = 0; i < Length_2; i++)
			{
				if (ptab->ks2[i].busy == 1) {
					ptr = ptab->ks2[i].item;
					while (ptr->next != NULL) {
						place.offset = ptr->place.offset;
						info = Read_Info(place);
						printf("%s %d %s %d %s %s %s %d %s %d %s %d %s %s %s", "	", info->num1, "		", info->num2,
							"		", info->str, "		", ptr->release, "		", ptab->ks1[find1(ptab, ptab->ks2[i].item->key1)].par, "		", ptr->key1, "		", ptr->key2, "\n");
						ptr = ptr->next;
						free(info->str);
						free(info);
					}
					place.offset = ptr->place.offset;
					info = Read_Info(place);
					printf("%s %d %s %d %s %s %s %d %s %d %s %d %s %s %s", "	", info->num1, "		", info->num2,
						"		", info->str, "		", ptr->release, "		", ptab->ks1[find1(ptab, ptab->ks2[i].item->key1)].par, "		", ptr->key1, "		", ptr->key2, "\n");
					free(info->str);
					free(info);
					printf("%s", "\n");
				}
				else{
					printf("%s %d %s", "\nEmpty line. Busy = ", ptab->ks2[i].busy, "\n\n");
				}
			}
			break;
		default:
			printf("%s", "There is no such option");
			break;
		}
	}
	return 1;
}

void delTable(Table* ptab)
{
	Item* ptr;
	Item* buf;
	if (ptab->number != 0) {
		for (int i = 0; i < ptab->number; i++) {
			ptr = ptab->ks1[i].item;
			if (ptr->next == NULL) {
				delete_Item(ptr);
			}
			else {
				do {
					buf = ptr;
					ptr = ptr->next;
					delete_Item(buf);

				} while (ptr->next != NULL);
				delete_Item(ptr);
			}
		}
	}
	free(ptab->ks1);
	free(ptab->ks2);
	return 1;
}