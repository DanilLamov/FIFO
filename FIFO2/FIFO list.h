#ifndef FIFO_LIST_H
#define FIFO_LIST_H

#include <iostream>

template <typename T> struct node {
	//����������� �� ���������
	node() = delete;
	//����������� ����������� ��������
	node(const T& data) : data(data), next(nullptr) {}
	//����������
	~node() = default;

	T data;
	node<T>* next;
};

template <typename T> class fifoList {
public:
	//����������� �� ���������
	fifoList() : head(nullptr), tail(nullptr), sizeQueue(0) {}
	//����������� ����������� ���� �������
	fifoList(const T& data) : head(new node<T>(data)), tail(head), sizeQueue(1) {}
	//����������� ����������� ��������� ���������
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
	//�����������
	~fifoList() {
		clear();
	}

	//����������� �����������
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
	//����������� ������������
	fifoList<T>& operator = (const fifoList<T>& fifo) {
		//���� ������ ������������� ��� ����
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
	//����������� �����������
	fifoList(fifoList&& fifo) : head(fifo.head), tail(fifo.tail), sizeQueue(fifo.sizeQueue) {
		fifo.head = fifo.tail = nullptr;
		fifo.sizeQueue = 0;
	}
	//�������� ������������ ������������
	fifoList<T>& operator = (fifoList<T>&& fifo) {
		//�������� �� ������������� ����
		if (&fifo == this) return *this;

		head = fifo.head;
		tail = fifo.tail;
		sizeQueue = fifo.sizeQueue;

		fifo.head = fifo.tail = nullptr;

		return *this;
	}

	//���������� ��������� [] ��� ��������� �������� ����������� �������� ������ 
	//�� ������� � ������������ ��������� ��� ��������
	T& operator [] (const size_t& ind) {
		if (ind < sizeQueue) {
			node<T>* temp = head;
			for (size_t i = 0; i < ind; ++i)
				temp = temp->next;
			return temp->data;
		}
		else {
			std::cerr << "����� �� ������� �������" << std::endl;
			exit(-1);
		}
	}
	//���������� ��������� [] ��� ��������� �������� ����������� �������� ������ 
	//�� ������� ��� ����������� ��������� ��� ��������
	const T& operator [] (const size_t& ind) const {
		if (ind < sizeQueue) {
			node<T>* temp = head;
			for (size_t i = 0; i < ind; ++i)
				temp = temp->next;
			return temp->data;
		}
		else {
			std::cerr << "����� �� ������� �������" << std::endl;
			exit(-1);
		}
	}

	//���������� �������� � �������
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
	//���������� ���������� ��������� � �������
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

		//������� ������ � ������� ��������
		if (head == nullptr) {
			head = newHead;
			tail = newTail;
		}
		else {
			tail->next = newHead;
			tail = newTail;
		}
	}

	//�������� �������� �� �������
	void del() {
		if (sizeQueue != 0) {
			node<T>* temp = head;
			head = head->next;
			delete temp;
			--sizeQueue;
		}
	}
	//�������� �������
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

	//������ �������
	size_t size() const {
		return sizeQueue;
	}

	//�������� �� ������� ��������� � �������
	bool empty() const {
		return sizeQueue == 0 ? true : false;
	}

	//���������� ��������� ������
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