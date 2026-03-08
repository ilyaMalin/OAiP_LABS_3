#include <iostream>

struct Spisok {
	int data;
	Spisok* next;
	Spisok* prev;
}*begin, *end;

static void creat(Spisok** b, Spisok** e, int info) {
	Spisok* t = new Spisok;
	t->data = info;
	t->next = t->prev = nullptr;
	*b = *e = t;
}

static void add_front(Spisok** b, Spisok** e, int info) {
	Spisok* t = new Spisok;
	t->data = info;
	t->prev = nullptr;
	t->next = *b;
	(*b)->prev = t;
	*b = t;
}

static void add_back(Spisok** b, Spisok** e, int info) {
	Spisok* t = new Spisok;
	t->data = info;
	t->next = nullptr;
	t->prev = *e;
	(*e)->next = t;
	*e = t;
}

static void view_front(Spisok** b, Spisok** e) {
	if (*b == nullptr) {
		std::cout << "Очередь пуста!" << std::endl;
		return;
	}
	Spisok* t = *b;
	while (t != nullptr) {
		std::cout << t->data << " ";
		t = t->next;
	}
}

static void view_back(Spisok** b, Spisok** e) {
	if (*e == nullptr) {
		std::cout << "Очередь пуста!" << std::endl;
		return;
	}
	Spisok* t = *e;
	while (t != nullptr) {
		std::cout << t->data << " ";
		t = t->prev;
	}
}

static void dell_all(Spisok** b, Spisok** e){
	Spisok* t;
	while (*b != nullptr) {
		t = *b;
		*b = (*b)->next;
		delete t;
	}
	*e = nullptr;
}

/*static void sort(Spisok** b, Spisok** e) {
	if (*b == nullptr) {
		std::cout << "Очередь пуста!";
		return;
	}
	Spisok* t1 = *b;
	Spisok* t2 = *e;
	while (*b != *e) {

	}
}*/

static float average(Spisok* b, Spisok* e) {
	if (b == nullptr) return 0;
	float sum = 0;
	int count = 0;
	Spisok* t1 = b;
	Spisok* t2 = e;
	while (t1 != t2) {
		sum += t1->data + t2->data;
		count += 2;
		t1 = t1->next;
		t2 = t2->prev;
	}
	if (t1 != nullptr && t1 == t2) {
		sum += t1->data;
		count++;
	}
	return sum / count;
}

static int count_delete(Spisok** b, Spisok** e) {
	if (b == nullptr && (*b)->next != nullptr) return 0;
	int count = 0;
	float av = average(*b, *e);
	Spisok* t = *b, *key = nullptr;
	while (t != nullptr) {
		Spisok* tnext = t->next;
		if (t->data < av) {
			key = t;
			count++;
		}
		if (key != nullptr) {
			if (key == *b) {
				*b = (*b)->next;
				(*b)->prev = nullptr;
			}
			else if (key == *e) {
				*e = (*e)->prev;
				(*e)->next = nullptr;
			}
			else {
				(key->prev)->next = key->next;
				(key->next)->prev = key->prev;
			}
			delete t;
			key = nullptr;
		}
		t = tnext;
	}
	return count;
}

int main() {
	setlocale(LC_ALL, "RU");
	srand(time(NULL));
	begin = end = nullptr;
	std::cout << "Добавьте первый элемент в очередь: ";
	int first;
	std::cin >> first;
	creat(&begin, &end, first);
	int n, m;
	do {
		std::cout
			<< "\n1. Просмотр очереди с начала.\n"
			<< "2. Просмотр очереди с конца.\n"
			<< "3. Добавление элемента в начало.\n"
			<< "4. Добавление элемента в конец.\n"
			<< "5. Заполнение очередь случайными числами с начала.\n"
			<< "6. Заполнение очередь случайными числами с конца.\n"
			<< "7. Сортировка по значению.\n"
			<< "8. Среднее значение от всех элементов.\n"
			<< "9. Задание.\n"
			<< "10. Выход.\n";
		std::cout << "Выберите действие: ";
		std::cin >> n;
		switch (n) {
		case 1: {
			view_front(&begin, &end);
			break;
		}
		case 2: {
			view_back(&begin, &end);
			break;
		}
		case 3: {
			std::cout << "Добавить элемент: ";
			std::cin >> m;
			add_front(&begin, &end, m);
			break;
		}
		case 4: {
			std::cout << "Добавить элемент: ";
			std::cin >> m;
			add_back(&begin, &end, m);
			break;
		}
		case 5: {
			std::cout << "Сколько элементов добавить?: ";
			std::cin >> m;
			for (int i = 0; i < m; i++) add_front(&begin, &end, rand() % 100);
			break;
		}
		case 6: {
			std::cout << "Сколько элементов добавить?: ";
			std::cin >> m;
			for (int i = 0; i < m; i++) add_back(&begin, &end, rand() % 100);
			break;
		}
		case 8: {
			std::cout << "Среднее значение от всех элементов: " << average(begin, end);
			break;
		}
		case 9: {
			std::cout << "Удалено элементов: " << count_delete(&begin, &end);
			break;
		}
		case 10: {
			dell_all(&begin, &end);
			std::cout << "Очередь очищена.\nВыход из программы....";
		}
		}
	} while (n != 10);
}