#ifndef FIFO_VEC_H
#define FIFO_VEC_H

#include <iostream>

template <typename T> class fifoVec {
public:
	fifoVec() : arr(nullptr), sizeQueue(0), maxSizeQueue(0) {}
	fifoVec(const T& data) : sizeQueue(1), maxSizeQueue(1) {
		arr = new T[1];
		*arr = data;
	}
	fifoVec(const std::initializer_list<T>& initList) : sizeQueue(initList.size()), maxSizeQueue(sizeQueue) {
		arr = new T[sizeQueue];
		T* mas = arr;
		for (const T* data = initList.begin(); data < initList.end(); ++data, ++mas)
			*mas = *data;
	}

	~fifoVec() {
		delete[] arr;
	}

	//����������� �����������
	fifoVec(const fifoVec& fifo) : sizeQueue(fifo.sizeQueue), maxSizeQueue(fifo.maxSizeQueue) {
		if (sizeQueue == 0)
			arr = nullptr;
		else {
			arr = new T[maxSizeQueue];
			T* mas1 = arr, * mas2 = fifo.arr;
			for (size_t i = 0; i < sizeQueue; ++i, ++mas1, ++mas2)
				*mas1 = *mas2;
		}
	}
	//����������� ������������
	fifoVec<T>& operator = (const fifoVec<T>& fifo) {
		//���� ������ ������������� ��� ����
		if (this == &fifo) return *this;

		clear();
		sizeQueue = fifo.sizeQueue;
		maxSizeQueue = fifo.maxSizeQueue;
		if (fifo.maxSizeQueue != 0) {
			arr = new T[maxSizeQueue];
			T* mas1 = arr, * mas2 = fifo.arr;
			for (size_t i = 0; i < sizeQueue; ++i, ++mas1, ++mas2)
				*mas1 = *mas2;
		}

		return *this;
	}
	//����������� �����������
	fifoVec(fifoVec&& fifo) : arr(fifo.arr), sizeQueue(fifo.sizeQueue), maxSizeQueue(fifo.maxSizeQueue) {
		fifo.arr = nullptr;
	}
	//�������� ������������ ������������
	fifoVec<T>& operator = (fifoVec<T>&& fifo) {
		//�������� �� ������������� ����
		if (&fifo == this) return *this;

		arr = fifo.arr;
		sizeQueue = fifo.sizeQueue;
		maxSizeQueue = fifo.maxSizeQueue;

		fifo.arr = nullptr;

		return *this;
	}

	//���������� ��������� [] ��� ��������� �������� ����������� �������� ������ 
	//�� ������� � ������������ ��������� ��� ��������
	T& operator [] (const size_t& ind) {
		if (ind < sizeQueue)
			return *(arr + ind);
		else {
			std::cerr << "����� �� ������� �������" << std::endl;
			exit(-1);
		}
	}
	//���������� ��������� [] ��� ��������� �������� ����������� �������� ������ 
	//�� ������� ��� ����������� ��������� ��� ��������
	const T& operator [] (const size_t& ind) const {
		if (ind < sizeQueue)
			return *(arr + ind);
		else {
			std::cerr << "����� �� ������� �������" << std::endl;
			exit(-1);
		}
	}

	//���������� �������� � �������
	void add(const T& data) {
		if (maxSizeQueue < sizeQueue + 1) {
			maxSizeQueue = maxSizeQueue == 0 ? 1 : maxSizeQueue * 2;

			T* temp = new T[maxSizeQueue], * mas1 = temp, * mas2 = arr;
			for (size_t i = 0; i < sizeQueue; ++i, ++mas1, ++mas2)
				*mas1 = *mas2;
			*mas1 = data;
			delete[] arr;
			arr = temp;
		}
		else
			*(arr + sizeQueue + 1) = data;

		++sizeQueue;
	}
	//���������� ���������� ��������� � �������
	void add(const std::initializer_list<T>& dataList) {
		//���� ���������� ����������� ������
		if (maxSizeQueue < sizeQueue + dataList.size()) {
			if (maxSizeQueue * 2 < sizeQueue + dataList.size())
				maxSizeQueue = sizeQueue + dataList.size() + 1;
			else
				maxSizeQueue *= 2;

			T* temp = new T[maxSizeQueue], * mas1 = temp, * mas2 = arr;
			for (size_t i = 0; i < sizeQueue; ++i, ++mas1, ++mas2)
				*mas1 = *mas2;

			for (const T* data = dataList.begin(); data < dataList.end(); ++data, ++mas1)
				*mas1 = *data;

			delete[] arr;
			arr = temp;
		}
		//���� ������ �������� ��� ��������� �������
		else {
			T* mas1 = arr + sizeQueue;
			for (const T* data = dataList.begin(); data < dataList.end(); ++data, ++mas1)
				*mas1 = *data;
		}

		sizeQueue += dataList.size();
	}

	//�������� �������� �� �������
	void del() {
		//� ������� ������ ������ ��������
		if (sizeQueue > 1) {
			//���� ������ ����� ���������
			if (maxSizeQueue > (sizeQueue - 1) * 2) {
				maxSizeQueue = (sizeQueue - 1) * 2;
				T* temp = new T[maxSizeQueue], * mas1 = temp, * mas2 = arr + 1;
				for (size_t i = 1; i < sizeQueue; ++i, ++mas1, ++mas2)
					*mas1 = *mas2;

				delete[] arr;
				arr = temp;
			}
			else {
				T* temp = arr;
				for (size_t i = 1; i < sizeQueue; ++i, ++temp)
					*temp = *(temp + 1);
			}
		}
		//� ������� ���� �������
		else {
			delete[] arr;
			arr = nullptr;
			maxSizeQueue = 0;
			sizeQueue = 1;

		}
		--sizeQueue;
	}
	//�������� �������
	void clear() {
		delete[] arr;
		arr = nullptr;
		sizeQueue = maxSizeQueue = 0;
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
	template <typename T> friend std::ostream& operator << (std::ostream& out, const fifoVec<T>& fifo);

private:
	T* arr;
	size_t sizeQueue, maxSizeQueue;

};

template <typename T> std::ostream& operator << (std::ostream& out, const fifoVec<T>& fifo) {
	T* temp = fifo.arr;
	for (size_t i = 0; i < fifo.sizeQueue; ++i, ++temp)
		out << *temp << ' ';

	return out;
}

#endif