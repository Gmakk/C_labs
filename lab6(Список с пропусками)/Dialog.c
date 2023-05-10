#include "Header.h"

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

int D_Add(List* list) {
	int	num1, num2;
	char* str, * key;
	printf("%s", "Enter key:");
	scanf_s("%*c");
	key = get_str();
	printf("%s", "Enter num1:");
	getInt(&num1);
	printf("%s", "Enter num2:");
	getInt(&num2);
	printf("%s", "Enter string:");
	scanf_s("%*c");
	str = get_str();
	if (ADD(list, key, num1, num2, str, 0) == -1)
		printf("%s", "Duplicate keys\n");
	return 1;
}

int D_Find(List* list) {
	char* key;
	Item* ip;
	int choice;
	if (list->level > 0) {
		printf("%s", "Find a specific element(1) or maximum(2)\n");
		getInt(&choice);
		switch (choice){
		case 1:
			printf("%s", "Enter key:");
			scanf_s("%*c");
			key = get_str();
			ip = find_with_this_key(list, key);
			if (ip != NULL)
				print_Item(ip);
			else
				printf("%s", "There is no such element\n");
			return 1;
			break;
		case 2:
			printf("%s", "Enter limit:");
			scanf_s("%*c");
			key = get_str();
			ip = find_max(list, key);
			if (ip != NULL) {
				print_Item(ip);
			}
			else {
				printf("%s", "There is no such element\n");
			}
			break;
		default:
			break;
		}
	}
	else {
		printf("%s", "Skip-List is empty\n");
		return -1;
	}
}

int D_Delete(List* list) {
	char* key;
	if (list->level > 0) {
		printf("%s", "Enter key:");
		scanf_s("%*c");
		key = get_str();
		if (find_with_this_key(list, key) == NULL) {
			printf("%s", "There is no such element\n");
			return -1;
		}
		DEL(list, key);
		return 1;
	}
	else {
		printf("%s", "Skip-List is empty\n");
		return -1;
	}
}

int D_Show(List* list) {
	Item* ip=list->header->forvards[0];
	if (list->level > 0) {
		while (ip != NULL) {
			if (ip->key != HighStr && ip->key != LowStr) {
				for (int i = 0; i < ip->level; i++)
					printf("%s", "- ");
				//for (int i = 0; i < MaxLevel / 2; i++)
					//printf("%s", "- ");
				printf("%s", ip->key);
				//for (int i = 0; i < MaxLevel / 2; i++)
					//printf("%s", " -");
				printf("%c", '\n');
				for (int i = 0; i < ip->level; i++) {
					if (ip->forvards[i] == NULL || ip->forvards[i]->key == HighStr)
						printf("%s", "0 ");
					else
						printf("%s%c", ip->forvards[i]->key, ' ');
				}
				printf("%s", "\n\n");
			}
			ip = ip->forvards[0];
		}
		return 1;
	}
	else {
		printf("%s", "Skip-List is empty\n");
		return -1;
	}
}

int D_Timing() {
	List* list = new_list();
	int num1, num2, size = 5, number = 1000, total = 1000, level, count = 1, number_of_el = 0;//5
	Item* ip, * parent;
	char* key, * str, * find;
	char buf;
	find = (char*)calloc(size, sizeof(char));
	clock_t time1, start;
	//srand(time(NULL));

	for (int i = 0; i < 1000; i++) {
		for (int p = 0; p < number; p++) {
			//srand(time(NULL));
			key = (char*)calloc(size, sizeof(char));
			for (int j = 0; j < size - 1; j++) {
				buf = 65 + rand() % 26;
				key[j] = buf;
			}
			key[size - 1] = '\0';
			num1 = rand() % 1001;
			num2 = rand() % 1001;
			str = (char*)calloc(2, sizeof(char));
			buf = 65 + rand() % 26;
			str[0] = buf;
			str[1] = '\0';
			//printf("%s\n", key);
			if (ADD(list, key, num1, num2, str, 0) == -1) {
				free(str);
				free(key);
			}
			else{
				//printf("%s\n", key);
				number_of_el++;
			}
		}
		start = clock();
		for (int g = 0; g < 100; g++) {
			//srand(time(NULL));
			level = MaxLevel - 1;
			ip = list->header->forvards[MaxLevel - 1];
			parent = list->header;
			//random
			for (int j = 0; j < size - 1; j++) {
				buf = 65 + rand() % 26;
				find[j] = buf;
			}
			find[size - 1] = '\0';

			while (1) {
				if (strcmp(find, ip->key) == 0) {//нашли нужный элемент
					break;
				}
				if (strcmp(find, ip->key) > 0) {//¬ставл€ема€ строка больше
					parent = ip;
					ip = ip->forvards[level];//двигаем вперед
					count++;
				}
				if (strcmp(find, ip->key) < 0) {//¬ставл€ема€ строка меньше
					if (level > 0) {//двигаем вниз
						level--;
						ip = parent->forvards[level];
						count++;
					}
					else {//дошли до низа
						break;
					}
				}
			}
		}
		time1 = clock();
		count = count / 100;
		if((double)(time1 - start) / (CLOCKS_PER_SEC * 100) * 10000000<2000)
		printf("%d%c%d%c%f%c", total, ';', count, ';', (double)(time1 - start) / (CLOCKS_PER_SEC * 100) * 10000000, '\n');
		count = 1;
		total += number;
	}
	//printf("%d\n", number_of_el);
	//printf("%d", delTree(list));
	delTree(list);
	return 1;
}

int delTree(List* list) {
	int count = 1;
	Item* parent = list->header, * ip = parent->forvards[0];
	while (ip!=NULL){
		if (parent->key != LowStr && parent->key != HighStr) {
			free(parent->key);
			free(parent->str);
		}
		free(parent);
		parent = ip;
		ip = ip->forvards[0];
		count++;
	}
	if (parent->key != LowStr && parent->key != HighStr) {
		free(parent->key);
		free(parent->str);
	}
	free(parent);
	return count;
}