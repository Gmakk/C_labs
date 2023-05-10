#include "Header.h"

List* new_list() {
	Item* last = (Item*)calloc(1, sizeof(Item));
	Item* first = (Item*)calloc(1, sizeof(Item));
	List* list = (List*)calloc(1, sizeof(List));
	list->level = 0;
	list->header = first;
	first->key = LowStr;
	last->key = HighStr;
	first->level = MaxLevel;
	last->level = MaxLevel;
	for (int i = 0; i < MaxLevel; i++) {
		first->forvards[i] = last;
		last->forvards[i] = NULL;
	}
	return list;
}

int ADD(List* list, char* key, int num1, int num2, char* str, int certain_lvl) {
	int count = MaxLevel - 1, rand1 = 0, level, buf = 1;
	Item** update[MaxLevel], * ip = list->header->forvards[MaxLevel - 1], * parent;
	//srand(time(NULL));
	Item* new = (Item*)calloc(1, sizeof(Item));
	new->key = key;
	new->num1 = num1;
	new->num2 = num2;
	new->str = str;
	if (certain_lvl == 0){
		rand1 = 1 + rand() % MaxLevel;
		/*while (buf == 1 && rand1 < MaxLevel){
			rand1 += buf;
			buf = rand() % 2;
		}*/
	}
	else
		rand1 = certain_lvl;
	new->level = rand1;
	if (list->level == 0) {
		for (int i = 0; i < rand1; i++) {
			new->forvards[i] = list->header->forvards[i];
			list->header->forvards[i] = new;
		}
		list->level = rand1;
	}
	else {
		level = MaxLevel - 1;
		parent = list->header;
		while (1) {
			if (strcmp(key, ip->key) > 0) {//¬ставл€ема€ строка больше
				parent = ip;
				ip = ip->forvards[level];//двигаем вперед
			}
			if (strcmp(key, ip->key) < 0) {//¬ставл€ема€ строка меньше
				if (level > 0) {//двигаем вниз
					update[count] = &parent->forvards[level];
					count--;
					level--;
					ip = parent->forvards[level];
				}
				else {//вставл€ем
					update[count] = &parent->forvards[level];
					for (int i = 0; i < rand1; i++) {
						new->forvards[i] = *update[i];//ok
						*update[i] = new;
					}
					if (rand1 > list->level)
						list->level = rand1;
					return 1;
				}
			}
			if (strcmp(key, ip->key) == 0) {
				return -1;
			}
		}
	}
	return 1;
}

int DEL(List* list, char* key) {
	int count = MaxLevel - 1, level, max = 0;
	Item** update[MaxLevel], * ip = list->header->forvards[MaxLevel - 1], * parent;

	level = MaxLevel - 1;
	parent = list->header;
	while (level>0) {
		if (strcmp(key, ip->key) > 0) {//¬ставл€ема€ строка больше
			parent = ip;
			ip = ip->forvards[level];//двигаем вперед
		}
		if (strcmp(key, ip->key) <= 0) {//¬ставл€ема€ строка меньше
			if (level > 0) {//двигаем вниз
				update[count] = &parent->forvards[level];
				count--;
				level--;
				ip = parent->forvards[level];
			}
		}
	}
	if (strcmp(key, ip->key) == 0) {//нашли нужный элемент
		update[count] = &parent->forvards[level];
		for (int i = 0; i < ip->level; i++) {
			//new->forvards[i] = *update[i];//ok
			*update[i] = ip->forvards[i];
		}
		free(ip);
		ip = list->header->forvards[0];
		while (ip->key != HighStr) {
			if (ip->level > max)
				max = ip->level;
			ip = ip->forvards[0];
		}
		list->level = max;
		return 1;
	}
	return -1;
}

Item* find_with_this_key(List* list, char* key) {
	Item* ip = list->header->forvards[MaxLevel - 1], * parent = list->header;
	int level = MaxLevel - 1;
	if (strcmp(key, HighStr) == 0)
		return NULL;
	while (1){
		if (strcmp(key, ip->key) == 0) {//нашли нужный элемент
			return ip;
		}
		if (strcmp(key, ip->key) > 0) {//¬ставл€ема€ строка больше
			parent = ip;
			ip = ip->forvards[level];//двигаем вперед
		}
		if (strcmp(key, ip->key) < 0) {//¬ставл€ема€ строка меньше
			if (level > 0) {//двигаем вниз
				level--;
				ip = parent->forvards[level];
			}
			else {//дошли до низа
				return NULL;
			}
		}
	}
	return NULL;
}

int print_Item(Item* ip) {
	printf("%s", "\nKey	level	num1	num2	str\n");
	printf("%s%c%d%c%d%c%d%c%s", ip->key, '	', ip->level, '	', ip->num1, '	', ip->num2, '	', ip->str);
	printf("%s", "\n\nLinks:\n");
	for (int i = 0; i < ip->level; i++) {
		if (ip->forvards[i]->key != HighStr)
			printf("%s%c", ip->forvards[i]->key,'	');
		else
			printf("%s", "0	");
	}
	printf("%c", '\n');
	return 1;
}

Item* find_max(List* list, char* key) {
	Item* ip = list->header->forvards[MaxLevel - 1], * parent = list->header;
	int level = MaxLevel - 1;
	if (strcmp(key, HighStr) == 0)
		return NULL;
	while (1) {
		if (strcmp(key, ip->key) >= 0) {//¬ставл€ема€ строка больше
			parent = ip;
			ip = ip->forvards[level];//двигаем вперед
		}
		if (strcmp(key, ip->key) < 0) {//¬ставл€ема€ строка меньше
			if (level > 0) {//двигаем вниз
				level--;
				ip = parent->forvards[level];
			}
			else {//дошли до низа
				if (parent->key != LowStr)
					return parent;
				else
					return NULL;
			}
		}
	}
}