#include "Header.h"
#include "File.h"

int hash1(char* c)
{
	int i = 0;
	for (int j = 0; j < strlen(c); ++j)
		i += c[j];
	return (i % Length_2);
}

int hash2(int* i)
{
	*i += (Length_2 / 2) + 1;
}

int find1(Table* ptab, int key)
{
	for (int i = 0; i < Length_1; ++i)
	{
		if (ptab->ks1[i].key == key)
			return i;
	}
	return -1;
}

int find2(Table* ptab, char* key)
{
	int i = hash1(key), j = i;
	do
	{
		if (ptab->ks2[j].busy == 1 && strcmp(ptab->ks2[j].key, key) == 0)
			return j;
		hash2(&j);
		j %= Length_2;
	} while ((j != i) && ptab->ks2[j].busy);

	return -1;
}

void list_print(Item* ptr, int par) {
	FilePlace place;
	InfoType* info;
	printf("%s", "first number	second number		string		release		parent		key1		key2\n");
	while (ptr->next != NULL) {
		place.offset = ptr->place.offset;
		info = Read_Info(place);
		printf("%s %d %s %d %s %s %s %d %s %d %s %d %s %s %s", "	", info->num1, "		", info->num2,
			"		", info->str, "		", ptr->release, "		", par, "		", ptr->key1, "		", ptr->key2, "\n");
		ptr = ptr->next;
		free(info->str);
		free(info);
	}
	place.offset = ptr->place.offset;
	info = Read_Info(place);
	printf("%s %d %s %d %s %s %s %d %s %d %s %d %s %s %s", "	", info->num1, "		", info->num2,
		"		", info->str, "		", ptr->release, "		", par, "		", ptr->key1, "		", ptr->key2, "\n");
	free(info->str);
	free(info);
}

void add_first(Table* ptab, int key1, char* key2, int num1, int num2, char* str) {
	FilePlace* place;
	InfoType info;
	//1 пространство ключей и данные
	//выделение Item
	ptab->ks1[0].item = (Item*)calloc(1, sizeof(Item));
	ptab->ks1[0].item->next = NULL;

	ptab->ks1[0].item->key1 = key1;
	ptab->ks1[0].item->key2 = key2;
	ptab->ks1[0].item->release = 1;
	ptab->ks1[0].key = key1;
	ptab->ks1[0].par = 0;
	//выделение места под данные
	info.lenght = length(str);
	info.num1 = num1;
	info.num2 = num2;
	info.str = str;
	place = Write_Info(info);
	ptab->ks1[0].item->place.length = place->length;
	ptab->ks1[0].item->place.offset = place->offset;
	/*ptab->ks1[0].item->info = (InfoType*)calloc(1, sizeof(InfoType));
	ptab->ks1->item[0].info->num1 = num1;
	ptab->ks1->item[0].info->num2 = num2;
	ptab->ks1->item[0].info->str = str;*/
	//присваивание указателей первого пространства ключей второму
	//работа hash функции
	ptab->ks2[hash1(key2)].item = ptab->ks1->item;
	ptab->ks2[hash1(key2)].key = key2;
	ptab->ks2[hash1(key2)].busy = 1;
	ptab->ks2[hash1(key2)].release = 1;
	ptab->number = 1;
	free(place);
}

void add_following(Table* ptab, int key1, char* key2, int par, int num1, int num2, char* str) {
	FilePlace* place;
	InfoType info;
	int check;
	if ((check = find1(ptab, key1)) != -1) {//добавление элемента с одинаковым составным ключем
		if (strcmp(ptab->ks1[check].item->key2, key2) == 0) {
			Item* ptr = ptab->ks1[check].item;
			int release = ptab->ks1[check].item->release + 1;
			ptab->ks1[check].item = (Item*)calloc(1, sizeof(Item));
			ptab->ks2[find2(ptab, key2)].item = ptab->ks1[check].item;
			ptab->ks1[check].item->next = ptr;
			ptab->ks1[check].item->release = release;
			ptab->ks1[check].item->key1 = key1;
			ptab->ks1[check].item->key2 = key2;

			info.lenght = length(str);
			info.num1 = num1;
			info.num2 = num2;
			info.str = str;
			place = Write_Info(info);
			ptab->ks1[check].item->place.length = place->length;
			ptab->ks1[check].item->place.offset = place->offset;

			/*ptab->ks1[check].item->info = (InfoType*)calloc(1, sizeof(InfoType));
			ptab->ks1[check].item->info->num1 = num1;
			ptab->ks1[check].item->info->num2 = num2;
			ptab->ks1[check].item->info->str = str;*/
			free(place);
			return 1;
		}
		else {
			printf("%s", "An element with this key already exists");
			return -1;
		}
	}
	if (ptab->number < ptab->msize1 && ptab->number < ptab->msize2) {
		//добавление в первое пространство ключей
		int count = 0, hash = hash1(key2);
		while ((ptab->ks1[count].par <= par && ptab->ks1[count].key != 0) && count < ptab->number)
			count++;
		if (ptab->ks1[count].key != 0) {
			for (int g = Length_1 - 2; g >= count; g--)
				swap_ks1(&ptab->ks1[g], &ptab->ks1[g + 1]);
		}
		ptab->ks1[count].item = (Item*)calloc(1, sizeof(Item));
		ptab->ks1[count].item->next = NULL;
		ptab->ks1[count].item->key1 = key1;
		ptab->ks1[count].item->key2 = key2;
		ptab->ks1[count].item->release = 1;
		ptab->ks1[count].key = key1;
		ptab->ks1[count].par = par;
		//printf("%d\n", ptab->ks1[count].par);
		//выделение места под данные

		info.lenght = length(str);
		info.num1 = num1;
		info.num2 = num2;
		info.str = str;
		place = Write_Info(info);
		ptab->ks1[count].item->place.length = place->length;
		ptab->ks1[count].item->place.offset = place->offset;
		free(place);
		/*ptab->ks1[count].item->info = (InfoType*)calloc(1, sizeof(InfoType));
		ptab->ks1[count].item->info->num1 = num1;
		ptab->ks1[count].item->info->num2 = num2;
		ptab->ks1[count].item->info->str = str;*/

		//добавление во второе пространство ключей
		//рассчет версии элемента
		int hash_count = hash1(key2);
		int j = hash_count, release_count = 1;
		do
		{
			if (ptab->ks2[j].busy == 1 && strcmp(ptab->ks2[j].key, key2) == 0)
				release_count++;
			hash2(&j);
			//j += hash2(key2);
			j %= Length_2;
		} while ((j != hash_count) && ptab->ks2[j].busy);
		//заполнение полей
		int p = hash;
		if (ptab->ks2[hash].busy != 0) {
			do {
				hash2(&p);
				//p += hash2(key2);
				p %= Length_2;
			} while (hash != p && ptab->ks2[p].busy == 1);
		}
		ptab->ks2[p].item = ptab->ks1[count].item;
		ptab->ks2[p].key = key2;
		ptab->ks2[p].busy = 1;
		ptab->ks2[p].release = release_count;
		//удаление из первого пространства в случае неудачи
		ptab->number++;
	}
}

void correct_par_key(Table* ptab, int key1) {
	for (int h = 0; h < Length_1; h++) {
		if (ptab->ks1[h].par == key1)
			ptab->ks1[h].par = 0;
	}
}

int swap_ks1(KeySpace1* el1, KeySpace1* el2) {
	KeySpace1 buf;
	buf.item = el1->item;
	buf.key = el1->key;
	buf.par = el1->par;
	el1->item = el2->item;
	el1->key = el2->key;
	el1->par = el2->par;
	el2->item = buf.item;
	el2->key = buf.key;
	el2->par = buf.par;
	return 1;
}

void free_list(Item* ptr) {
	Item* buf;
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

void delete_from_key_spc(Table* ptab, int par, int result1, int result2) {
	ptab->ks1[result1].key = 0;
	ptab->ks1[result1].par = 0;
	for (int g = result1; g <= Length_1 - 2; g++)
		swap_ks1(&ptab->ks1[g], &ptab->ks1[g + 1]);
	//выставление ключа родительского элемента в 0
	correct_par_key(ptab, par);
	//удаление из 2 пространства ключей
	ptab->ks2[result2].busy = -1;
	ptab->ks2[result2].key = NULL;
	ptab->ks2[result2].release = 0;
	ptab->number--;
}

void delete_certain(Table* ptab, int result1, int result2, int rel) {
	int count = 0;
	Item* buf;
	Item* ptr = ptab->ks1[result1].item;
	while (ptr->release != rel) {
		ptr = ptr->next;
		count++;
		if (ptr->next == NULL && ptr->release != rel) {
			printf("%s", "There is no such element:\n");
			return -1;
		}
	}
	if (ptr->next == NULL) {//удаляем последний
		delete_Item(ptr);
		ptr = ptab->ks1[result1].item;
		for (int i = 0; i < count - 1; i++)
			ptr = ptr->next;
		ptr->next = NULL;
	}
	else {
		if (count == 0) {//удаляем первый
			buf = ptab->ks1[result1].item->next;
			delete_Item(ptab->ks1[result1].item);
			ptab->ks1[result1].item = buf;
			ptab->ks2[result2].item = buf;
		}
		else {//удаляем из середины
			buf = ptr->next;
			delete_Item(ptr);
			ptr = ptab->ks1[result1].item;
			for (int i = 0; i < count - 1; i++)
				ptr = ptr->next;
			ptr->next = buf;
		}
	}
}

void delete_Item(Item* ptr) {
	free(ptr->key2);
	free(ptr);
}

void sort_ks1(Table* ptab) {
	for (int i = 0; i < ptab->number - 1; i++)
	{
		for (int j = (ptab->number - 1); j > i; j--) // для всех элементов после i-ого
		{
			if (ptab->ks1[j - 1].par > ptab->ks1[j].par) // если текущий элемент меньше предыдущего
				swap_ks1(&ptab->ks1[j - 1], &ptab->ks1[j]);
		}
	}
}

void binary_search(Table* ptab, int par) {
	int key, i;
	int left = 0;
	int right = ptab->number - 1;
	int search = -1;
	while (left <= right)
	{
		int mid = (left + right) / 2; 
		if (par == ptab->ks1[mid].par) { 
			search = mid;
			//вывести список
			list_print(ptab->ks1[mid].item, par);
			break;
		}
		if (par < ptab->ks1[mid].par)
			right = mid - 1; 
		else 
			left = mid + 1;
	}
	if (search == -1)
		printf("%s", "There is no such element\n");
	return 0;
}