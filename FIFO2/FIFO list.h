#ifndef FIFO_LIST_H
#define FIFO_LIST_H

#include <iostream>

template <typename T> struct node {
	//конструктор по умолчанию
	node() = delete;
	//конструктор принимающий значение
	node(const T& data) : data(data), next(nullptr) {}
	//деструктор
	~node() = default;

	T data;
	node<T>* next;
};

template <typename T> class fifoList {
public:
	//конструктор по умолчнаию
	fifoList() : head(nullptr), tail(nullptr), sizeQueue(0) {}
	//конструктор добавляющий один элемент
	fifoList(const T& data) : head(new node<T>(data)), tail(head), sizeQueue(1) {}
	//конструктор добавляющий несколько элементов
	fifoList(const std::initializer_list<T>& dataList) : sizeQueue(dataList.size()) {
		head = new node<T>(*dataList.begin());
		node<T>* temp1 = head;

		for (const T* data = dataList.begin() + 1; data < dataList.end(); ++data) {
			tail = new node<T>(*data);
			temp1->next = tail;
			temp1 = tail;
		}

		tail->next = nullptr;
	}
	//декструктор
	~fifoList() {
		clear();
	}

	//конструктор копирования
	fifoList(const fifoList& fifo) : sizeQueue(fifo.sizeQueue) {
		if (fifo.sizeQueue == 0)
			head = tail = nullptr;
		else {
			head = new node<T>(fifo.head->data);
			node<T>* temp1 = head, * temp2 = fifo.head->next;
			tail = head;

			for (size_t i = 1; i < sizeQueue; ++i, temp2 = temp2->next) {
				tail = new node<T>(temp2->data);
				temp1->next = tail;
				temp1 = tail;
			}

			tail->next = nullptr;
		}
	}
	//конструктор присваивания
	fifoList<T>& operator = (const fifoList<T>& fifo) {
		//если объект присваивается сам себе
		if (this == &fifo) return *this;

		clear();
		if (fifo.sizeQueue != 0) {
			head = new node<T>(fifo.head->data);
			node<T>* temp1 = head, * temp2 = fifo.head->next;

			for (size_t i = 1; i < fifo.sizeQueue; ++i, temp2 = temp2->next) {
				tail = new node<T>(temp2->data);
				temp1->next = tail;
				temp1 = tail;
			}

			sizeQueue = fifo.sizeQueue;
		}

		return *this;
	}
	//конструктор перемещения
	fifoList(fifoList&& fifo) : head(fifo.head), tail(fifo.tail), sizeQueue(fifo.sizeQueue) {
		fifo.head = fifo.tail = nullptr;
		fifo.sizeQueue = 0;
	}
	//оператор присваивания перемещением
	fifoList<T>& operator = (fifoList<T>&& fifo) {
		//проверка на приссваивание себе
		if (&fifo == this) return *this;

		head = fifo.head;
		tail = fifo.tail;
		sizeQueue = fifo.sizeQueue;

		fifo.head = fifo.tail = nullptr;

		return *this;
	}

	//перегрузка оператора [] для получения значения конкретного элемента списка 
	//по индексу с возможностью изменения его значения
	T& operator [] (const size_t& ind) {
		if (ind < sizeQueue) {
			node<T>* temp = head;
			for (size_t i = 0; i < ind; ++i)
				temp = temp->next;
			return temp->data;
		}
		else {
			std::cerr << "Выход за границы очереди" << std::endl;
			exit(-1);
		}
	}
	//перегрузка оператора [] для получения значения конкретного элемента списка 
	//по индексу без возможности изменения его значения
	const T& operator [] (const size_t& ind) const {
		if (ind < sizeQueue) {
			node<T>* temp = head;
			for (size_t i = 0; i < ind; ++i)
				temp = temp->next;
			return temp->data;
		}
		else {
			std::cerr << "Выход за границы очереди" << std::endl;
			exit(-1);
		}
	}

	//добавление элемента в очередь
	void add(const T& data) {
		node<T>* temp = new node<T>(data);
		temp->next = nullptr;
		if (head == nullptr)
			head = tail = temp;
		else {
			tail->next = temp;
			tail = temp;
		}
		++sizeQueue;
	}
	//добавление нескольких элементов в очередь
	void add(const std::initializer_list<T>& dataList) {
		sizeQueue += dataList.size();

		node<T>* newHead;
		newHead = new node<T>(*dataList.begin());
		node<T>* temp1 = newHead, * newTail = newHead;

		for (const T* data = dataList.begin() + 1; data < dataList.end(); ++data) {
			newTail = new node<T>(*data);
			temp1->next = newTail;
			temp1 = newTail;
		}

		newTail->next = nullptr;

		//склейка нового и старого участков
		if (head == nullptr) {
			head = newHead;
			tail = newTail;
		}
		else {
			tail->next = newHead;
			tail = newTail;
		}
	}

	//удаление элемента из очереди
	void del() {
		if (sizeQueue != 0) {
			node<T>* temp = head;
			head = head->next;
			delete temp;
			--sizeQueue;
		}
	}
	//отчистка очереди
	void clear() {
		node<T>* temp;
		for (size_t i = 0; i < sizeQueue; ++i) {
			temp = head->next;
			delete head;
			head = temp;
		}

		head = tail = nullptr;
		sizeQueue = 0;
	}

	//размер очереди
	size_t size() const {
		return sizeQueue;
	}

	//проверка на наличие элементов в массиве
	bool empty() const {
		return sizeQueue == 0 ? true : false;
	}

	//перегрузка оператора вывода
	template <typename T> friend std::ostream& operator << (std::ostream& out, const fifoList<T>& fifo);

private:
	node<T>* head, * tail;
	size_t sizeQueue;

};

template <typename T> std::ostream& operator << (std::ostream& out, const fifoList<T>& fifo) {
	node<T>* temp = fifo.head;
	for (size_t i = 0; i < fifo.sizeQueue; ++i, temp = temp->next)
		out << temp->data << ' ';

	return out;
}

#endif