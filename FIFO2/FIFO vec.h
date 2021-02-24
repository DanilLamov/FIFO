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

	//конструктор копирования
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
	//конструктор присваивания
	fifoVec<T>& operator = (const fifoVec<T>& fifo) {
		//если объект присваивается сам себе
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
	//конструктор перемещения
	fifoVec(fifoVec&& fifo) : arr(fifo.arr), sizeQueue(fifo.sizeQueue), maxSizeQueue(fifo.maxSizeQueue) {
		fifo.arr = nullptr;
	}
	//оператор присваивания перемещением
	fifoVec<T>& operator = (fifoVec<T>&& fifo) {
		//проверка на приссваивание себе
		if (&fifo == this) return *this;

		arr = fifo.arr;
		sizeQueue = fifo.sizeQueue;
		maxSizeQueue = fifo.maxSizeQueue;

		fifo.arr = nullptr;

		return *this;
	}

	//перегрузка оператора [] для получения значения конкретного элемента списка 
	//по индексу с возможностью изменения его значения
	T& operator [] (const size_t& ind) {
		if (ind < sizeQueue)
			return *(arr + ind);
		else {
			std::cerr << "Выход за границы очереди" << std::endl;
			exit(-1);
		}
	}
	//перегрузка оператора [] для получения значения конкретного элемента списка 
	//по индексу без возможности изменения его значения
	const T& operator [] (const size_t& ind) const {
		if (ind < sizeQueue)
			return *(arr + ind);
		else {
			std::cerr << "Выход за границы очереди" << std::endl;
			exit(-1);
		}
	}

	//добавление элемента в очередь
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
	//добавление нескольких элементов в очередь
	void add(const std::initializer_list<T>& dataList) {
		//если необходимо увеличивать массив
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
		//если массив отсается без изменения размера
		else {
			T* mas1 = arr + sizeQueue;
			for (const T* data = dataList.begin(); data < dataList.end(); ++data, ++mas1)
				*mas1 = *data;
		}

		sizeQueue += dataList.size();
	}

	//удаление элемента из очереди
	void del() {
		//в очереди больше одного элемента
		if (sizeQueue > 1) {
			//если массив нужно уменьшить
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
		//в очереди один элемент
		else {
			delete[] arr;
			arr = nullptr;
			maxSizeQueue = 0;
			sizeQueue = 1;

		}
		--sizeQueue;
	}
	//отчистка очереди
	void clear() {
		delete[] arr;
		arr = nullptr;
		sizeQueue = maxSizeQueue = 0;
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