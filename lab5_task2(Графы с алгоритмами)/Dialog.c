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

int D_Add(List* all) {
	int x, y, choice, weight;
	char* name = NULL, * name_sub = NULL, buf1, buf2, buf3;
	unsigned int number;
	List* list = NULL, * lp;
	Graph* sub, * sub2;
	printf("%s", "Add a vertex(1) or edge(2) or fill in with random values(3)\n");
	getInt(&choice);
	switch (choice)
	{
	case 1:
		printf("%s", "Enter information:\n");
		printf("%s", "Enter coordinate x:");
		getInt(&x);
		printf("%s", "Enter coordinate y:");
		getInt(&y);
		printf("%s", "Enter name of the vertex:");
		scanf_s("%*c");
		name = get_str();
		if (all->sub == NULL || find_with_this_name(all, name) == NULL) {
			if (all->sub != NULL) {//в графе уже есть элементы
				printf("%s", "Enter number of links:");
				getNumber(&number);
				if (number > count_List(all)) {
					printf("%s", "Missing vertices\n");
					break;
				}
				if (number != 0) {
					list = (List*)calloc(1, sizeof(List));
					lp = list;
					for (int i = 0; i < number; i++) {
						printf("%s", "Enter name of the vertex:");
						scanf_s("%*c");
						name_sub = get_str();
						sub = find_with_this_name(all, name_sub);
						if (sub != NULL) {
							printf("%s", "Enter weight:");
							getInt(&weight);
							lp->sub = sub;
							lp->weight = weight;
							if (i != number - 1) {
								lp->next = (List*)calloc(1, sizeof(List));
								lp = lp->next;
							}
						}
						else {
							printf("%s", "There is no such element\n");
							number++;
						}
					}
				}
			}
			ADD(all, list, x, y, name);
		}
		else
			printf("%s", "Duplicate name\n");
		break;
	case 2:
		if (all->sub == NULL) {
			printf("%s", "The graph is empty\n");
			return -1;
		}
		if (all->next == NULL) {
			printf("%s", "There is only one element\n");
			return -1;
		}
		printf("%s", "Enter the name of the first vertex:");
		scanf_s("%*c");
		name = get_str();
		sub = find_with_this_name(all, name);
		if (sub == NULL) {
			printf("%s", "There is no such element\n");
			break;
		}
		printf("%s", "Enter the name of the second vertex:");
		//scanf_s("%*c");
		name_sub = get_str();
		sub2 = find_with_this_name(all, name_sub);
		if (sub2 == NULL){
			printf("%s", "There is no such element\n");
			break;
		}
		//проверка на дубликат
		list = sub->list;
		while (list != NULL) {
			if (list->sub == sub2) {
				printf("%s", "Duplicate edge\n");
				return -1;
			}
			list = list->next;
		}
		printf("%s", "Enter weight:");
		getInt(&weight);
		ADD_edge(sub, sub2, weight);
		break;
	case 3:
		printf("%s", "Enter number of elements:");
		getNumber(&number);
		srand(time(NULL));
		for (int i = 0; i < number; i++) {
			x = rand() % 1001;
			y = rand() % 1001;
			name = (char*)calloc(4, sizeof(char));
			buf1 = 65 + rand() % 26;
			buf2 = 65 + rand() % 26;
			buf3 = 65 + rand() % 26;
			name[0] = buf1;
			name[1] = buf2;
			name[2] = buf3;
			name[3] = '\0';
			if (find_with_this_name(all, name) == NULL)
				ADD(all, NULL, x, y, name);
		}
		for (int i = 0; i < number * 2; i++) {
			x = rand() % number + 1;//пор€дковые номера в списке
			y = rand() % number + 1;
			list = all;
			lp = all;
			for (int i = 0; i < x; i++) {
				if (list == NULL)
					break;
				list = list->next;
			}
			for (int i = 0; i < y; i++) {
				if (lp == NULL)
					break;
				lp = lp->next;
			}
			weight = rand() % 1001;
			if (list != NULL && lp != NULL && check_edge(all, list->sub, lp->sub) == 1 && list != lp)
				ADD_edge(list->sub, lp->sub, weight);

		}
		break;
	default:
		printf("%s", "There is no such option\n");
		break;
	}
	return 1;
}

int D_Find(List* all) {
	int choice, min, max, mass[30], count = 0, count_turn = 0, total = 0, buf1 = 0, number;
	char* name, * name_sub, * name_buf = NULL;
	Graph* buf = NULL, * sub, * buf2;
	List* lp, * queue, * lp2, * lp3;
	if (all->sub != NULL) {
		printf("%s", "Ordinary search(1) or breadth-first search(2) or Bellman-Ford(3) or topological sort(4)\n");
		getInt(&choice);
		switch (choice)
		{
		case 1:
			printf("%s", "Enter name of the vertex:");
			scanf_s("%*c");
			name = get_str();
			buf = find_with_this_name(all, name);
			if (buf != NULL) {
				print_graph(buf);
			}
			else {
				printf("%s", "There is no such element\n");
			}
			break;
		case 2:
			printf("%s", "Enter the name of the first vertex:");
			scanf_s("%*c");
			name = get_str();
			sub = find_with_this_name(all, name);
			while (sub == NULL) {
				if (sub == NULL)
					printf("%s", "There is no such element\n");
				printf("%s", "Enter correct name:");
				//scanf_s("%*c");
				name = get_str();
				sub = find_with_this_name(all, name);
			}
			printf("%s", "Enter the name of the second vertex:");
			name_sub = get_str();
			buf = find_with_this_name(all, name_sub);
			while (buf == NULL) {
				if (buf == NULL)
					printf("%s", "There is no such element\n");
				printf("%s", "Enter correct name:");
				//scanf_s("%*c");
				name_sub = get_str();
				buf = find_with_this_name(all, name_sub);
			}
			if (sub == buf) {
				lp = sub->list;
				while (lp != NULL) {
					if (lp->sub == buf) {
						print_graph(buf);
						return 1;
					}
					lp = lp->next;
				}
			}
			lp = all;
			while (lp != NULL) {
				lp->sub->visited = 0;
				lp = lp->next;
			}
			queue = (List*)calloc(1, sizeof(List));
			queue->sub = sub;
			queue->next = NULL;
			sub->visited = 1;
			printf("%s%c", sub->name, '\n');
			while (queue != NULL) {
				//удаление первого в очереди
				lp = queue;
				buf = queue->sub;
				queue = queue->next;
				free(lp);
				if (buf == NULL) {
					printf("%s", "There is no path between these vertexes\n");
					return -1;
				}
				//вывод очереди
				lp = queue;
				while (lp != NULL) {
					if (lp->sub != NULL)
						printf("%s%c", lp->sub->name, ' ');
					lp = lp->next;
				}
				printf("%c", '\n');
				//добавление соседних элементов
				lp = buf->list;
				if (lp != NULL) {
					while (lp->next != NULL) {
						if (lp->sub->visited == 0) {
							lp2 = queue;
							//очередь пуста€
							if (lp2 == NULL) {
								queue = (List*)calloc(1, sizeof(List));
								queue->next = NULL;
								queue->sub = lp->sub;
							}
							else {
								while (lp2->next != NULL)
									lp2 = lp2->next;
								lp2->next = (List*)calloc(1, sizeof(List));
								lp2->sub = lp->sub;
							}
							lp->sub->visited = 1;
							if (strcmp(lp->sub->name, name_sub) == 0) {
								printf("%s%c", lp->sub->name, '\n\n');
								print_graph(lp->sub);
								return 1;
							}
						}
						lp = lp->next;
					}
					//....
					if (lp->sub->visited == 0) {
						lp2 = queue;
						//очередь пуста€
						if (lp2 == NULL) {
							queue = (List*)calloc(1, sizeof(List));
							queue->next = NULL;
							queue->sub = lp->sub;
						}
						else {
							while (lp2->next != NULL)
								lp2 = lp2->next;
							lp2->next = (List*)calloc(1, sizeof(List));
							lp2->next->sub = lp->sub;
						}
						lp->sub->visited = 1;
						if (strcmp(lp->sub->name, name_sub) == 0) {
							printf("%s%c", lp->sub->name, '\n\n');
							print_graph(lp->sub);
							return 1;
						}
					}
				}
				//вывод очереди
				lp = queue;
				while (lp != NULL) {
					if (lp->sub != NULL)
						printf("%s%c", lp->sub->name, ' ');
					lp = lp->next;
				}
				printf("%c", '\n');
			}
			printf("%s", "There is no path between these vertexes\n");
			break;
		case 3:
			printf("%s", "Enter the name of the first vertex:");
			scanf_s("%*c");
			name = get_str();
			sub = find_with_this_name(all, name);
			while (sub == NULL) {
				if (sub == NULL)
					printf("%s", "There is no such element\n");
				printf("%s", "Enter correct name:");
				//scanf_s("%*c");
				name = get_str();
				sub = find_with_this_name(all, name);
			}
			printf("%s", "Enter the name of the second vertex:");
			name_sub = get_str();
			buf2 = find_with_this_name(all, name_sub);
			while (buf2 == NULL) {
				if (buf2 == NULL)
					printf("%s", "There is no such element\n");
				printf("%s", "Enter correct name:");
				//scanf_s("%*c");
				name_sub = get_str();
				buf2 = find_with_this_name(all, name_sub);
			}
			number = count_List(all);//количество всех вершин
			int* dist = (int*)calloc(number, sizeof(int));
			for (int i = 0; i < number; i++)
				dist[i] = INT_MAX;
			dist[count_number(all, sub)] = 0;
			for (int i = 0; i < number - 1; i++) {
				lp = all;
				while (lp != NULL) {
					if (dist[count_number(all, lp->sub)] != INT_MAX && lp->sub->list != NULL) {
						lp2 = lp->sub->list;
						while (lp2 != NULL) {
							if (lp2->weight + dist[count_number(all, lp->sub)] < dist[count_number(all, lp2->sub)])
								dist[count_number(all, lp2->sub)] = lp2->weight + dist[count_number(all, lp->sub)];
							lp2 = lp2->next;
						}
					}
					lp = lp->next;
				}
			}
			if (dist[count_number(all, buf2)] == INT_MAX)
				printf("%s", "There is no path between these vertexes\n");
			else
				printf("Minimum distance:%d\n", dist[count_number(all, buf2)]);
			break;
		case 4:
			lp = all;
			while (lp != NULL) {
				lp->sub->visited = 0;
				lp = lp->next;
			}
			for (int i = 0; i < count_List(all); i++) {
				lp = all;
				set_sum(all);
				while (lp != NULL) {
					if (lp->sub->visited == 0 && (source_check(all, lp->sub) == -1 || (outputs_count(lp->sub) == 0 && entry_count(lp->sub) == 0))) {
						printf("%s ", lp->sub->name);
						lp->sub->visited = 1;
					}
					lp = lp->next;
				}
				printf("%c", '\n');
			}
			lp = all;
			while (lp != NULL) {
				if (lp->sub->visited == 0) {
					printf("%s", "The graph is not acyclic\n");
					break;
				}
				lp = lp->next;
			}
			break;
		default:
			printf("%s", "There is no such option\n");
			break;
		}
	}
	else
		printf("%s", "Graph is empty\n");
	return 1;
}

int D_Delete(List* all) {
	int choice;
	char* name, * name_sub;
	Graph* buf, * sub, * sub2;
	List* lp;
	printf("%s", "Delete a vertex(1) or edge(2)\n");
	getInt(&choice);
	switch (choice)
	{
	case 1:
		printf("%s", "Enter name of the vertex:");
		scanf_s("%*c");
		name = get_str();
		buf = find_with_this_name(all, name);
		if (buf != NULL) {
			delete_mentions(all, buf);
			delete_element(all, buf->name);
		}
		else
			printf("%s", "There is no such element");
		break;
	case 2:
		printf("%s", "Enter the name of the first vertex:");
		scanf_s("%*c");
		name = get_str();
		sub = find_with_this_name(all, name);
		while (name == NULL || sub == NULL) {
			if (sub == NULL)
				printf("%s", "There is no such element\n");
			printf("%s", "Enter correct name:");
			scanf_s("%*c");
			name = get_str();
			sub = find_with_this_name(all, name);
		}
		printf("%s", "Enter the name of the second vertex:");
		name_sub = get_str();
		sub2 = find_with_this_name(all, name_sub);
		while (name_sub == NULL || sub2 == NULL) {
			if (sub2 == NULL)
				printf("%s", "There is no such element\n");
			printf("%s", "Enter correct name:");
			scanf_s("%*c");
			name_sub = get_str();
			sub2 = find_with_this_name(all, name_sub);
		}
		lp = sub->list;
		while (lp != NULL && lp->sub != sub2)
			lp = lp->next;
		if (lp == NULL) {
			printf("%s", "There is no such element\n");
			return -1;
		}
		delete_from_list(sub, lp);
		break;
	default:
		printf("%s", "There is no such option\n");
		break;
	}
	return 1;
}

int D_Show(List* all) {
	List* lp, * sub;
	lp = all;
	if (all->sub != NULL) {
		while (lp != NULL) {
			printf("%s", "x       y       name\n");
			printf("%d%s%d%s%s%c", lp->sub->x, "	", lp->sub->y, "	", lp->sub->name, '\n');
			if (lp->sub->list != NULL) {
				printf("%s", "Related vertexes with weidth:\n");
				sub = lp->sub->list;
				while (sub->next != NULL) {
					printf("%s%s%d%c", sub->sub->name, " ; ", sub->weight, '\n');
					sub = sub->next;
				}
				printf("%s%s%d%c", sub->sub->name, " ; ", sub->weight, '\n');
			}
			printf("%s", "\n\n");
			lp = lp->next;
		}
	}
	else
		printf("%s", "Graph is empty\n");
	return 1;
}

int D_Timing() {
	List* all = (List*)calloc(1, sizeof(List));
	List* list, * lp, * queue, * lp2;
	Graph* sub, * buf2, * buf_gr;
	all->next = NULL;
	all->sub = NULL;
	int key_x, key_y, number = 1000, total = 1000, count = 1, size = 5, x, y, weight, check = 0;
	char* str, * find, * find2, * key = NULL;
	char buf;
	find = (char*)calloc(size, sizeof(char));
	find2 = (char*)calloc(size, sizeof(char));
	clock_t time1, start;
	srand(time(NULL));
	for (int i = 0; i < 100; i++) {
		//добавление элементов
		for (int i = 0; i < number; i++) {
			key_x = rand() % 1001;
			key_y = rand() % 1001;
			str = (char*)calloc(size, sizeof(char));
			for (int j = 0; j < size - 1; j++) {
				buf = 65 + rand() % 26;
				str[j] = buf;
			}
			str[size - 1] = '\0';
			if (find_with_this_name(all, str) == NULL) {
				ADD(all, NULL, key_x, key_y, str);
			}
		}
		for (int i = 0; i < number * 2; i++) {
			x = rand() % total + 1;//пор€дковые номера в списке
			y = rand() % total + 1;
			list = all;
			lp = all;
			for (int i = 0; i < x; i++) {
				if (list == NULL)
					break;
				list = list->next;
			}
			for (int i = 0; i < y; i++) {
				if (lp == NULL)
					break;
				lp = lp->next;
			}
			weight = rand() % 1001;
			if (list != NULL && lp != NULL && check_edge(all, list->sub, lp->sub) == 1 && list != lp)
				ADD_edge(list->sub, lp->sub, weight);
		}
		//поиск
		start = clock();
		for (int g = 0; g < 1000; g++) {
			//if (key != NULL) {
			if (key != NULL) {
				for (int j = 0; j < size - 1; j++) {
					buf = 65 + rand() % 26;
					find[j] = buf;
				}
				find[size - 1] = '\0';
				for (int j = 0; j < size - 1; j++) {
					buf = 65 + rand() % 26;
					find2[j] = buf;
				}
				find2[size - 1] = '\0';
				sub = find_with_this_name(all, find);
				buf2 = find_with_this_name(all, find2);


				if (sub != NULL && buf2 != NULL) {
					lp = all;
					while (lp != NULL) {
						lp->sub->visited = 0;
						lp = lp->next;
					}
					queue = (List*)calloc(1, sizeof(List));
					queue->sub = sub;
					queue->next = NULL;
					sub->visited = 1;
					check = 0;
					while (queue != NULL && check == 0) {
						//удаление первого в очереди
						lp = queue;
						buf_gr = queue->sub;
						queue = queue->next;
						free(lp);
						if (buf_gr == NULL) {
							break;
						}
						//добавление соседних элементов
						lp = buf_gr->list;
						if (lp != NULL) {
							while (lp->next != NULL) {
								if (lp->sub->visited == 0) {
									lp2 = queue;
									//очередь пуста€
									if (lp2 == NULL) {
										queue = (List*)calloc(1, sizeof(List));
										queue->next = NULL;
										queue->sub = lp->sub;
									}
									else {
										while (lp2->next != NULL)
											lp2 = lp2->next;
										lp2->next = (List*)calloc(1, sizeof(List));
										lp2->sub = lp->sub;
									}
									count++;
									lp->sub->visited = 1;
									if (strcmp(lp->sub->name, find2) == 0) {
										check = 1;
										break;
									}
								}
								lp = lp->next;
							}
							count++;
						}
					}
				}
			}
			lp = all;
			for (int j = 0; j < size - 1; j++) {
				buf = 65 + rand() % 26;
				find[j] = buf;
			}
			find[size - 1] = '\0';
			if (all->sub != NULL) {
				while (lp != NULL) {
					if (strcmp(lp->sub->name, find) == 0)
						break;
					count++;
					lp = lp->next;
				}
				count++;
			}

		}
		time1 = clock();
		count = count / 1000;
		printf("%d%c%d%c%f%c", total, ';', count, ';', (double)(time1 - start) / (CLOCKS_PER_SEC * 1000) * 10000000, '\n');
		count = 1;
		total += number;
	}
	return 1;
}

int delTree(List* all) {
	List* lp, * parent, * sub, * sub_parent;
	if (all->sub != NULL) {//элементов нет
		if (all->next == NULL) {//1 элемент
			free(all->sub->name);
			free(all->sub);
		}
		else {
			parent = all;
			lp = parent->next;
			while (lp != NULL) {
				if (parent->sub->list != NULL) {//удаление рЄбер
					if (parent->sub->list->next == NULL)//1 ребро
						free(parent->sub->list);
					else {//>1 ребра
						sub_parent = parent->sub->list;
						sub = sub_parent->next;
						while (sub != NULL) {
							free(sub_parent);
							sub_parent = sub;
							sub = sub->next;
						}
						free(sub_parent);
					}
				}
				free(parent->sub->name);
				free(parent->sub);
				if (parent != all)
					free(parent);
				parent = lp;
				lp = lp->next;
			}
			if (parent->sub->list != NULL) {//удаление рЄбер
				if (parent->sub->list->next == NULL)//1 ребро
					free(parent->sub->list);
				else {//>1 ребра
					sub_parent = parent->sub->list;
					sub = sub_parent->next;
					while (sub != NULL) {
						free(sub_parent);
						sub_parent = sub;
						sub = sub->next;
					}
					free(sub_parent);
				}
			}
			free(parent->sub->name);
			free(parent->sub);
			if (parent != all)
				free(parent);
		}
	}
	return 1;
}