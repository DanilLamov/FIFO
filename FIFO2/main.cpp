#include <iostream>

#include "FIFO list.h"
#include "FIFO vec.h"

int main() {
	setlocale(LC_ALL, "ru");

	fifoList<int> q1;
	std::cout << q1 << std::endl;

	fifoList<int> q2(1);
	std::cout << q2 << std::endl;

	fifoList<int> q3({ 1, 2, 3 });
	std::cout << q3 << std::endl;

	fifoList<int> q4(q2);
	std::cout << q4 << std::endl;

	q1 = q3;
	std::cout << q1 << std::endl;

	std::cout << q1[1] << std::endl;
	//std::cout << q1[3] << std::endl;

	fifoList<int> q5;
	q5.add(1);
	std::cout << q5 << std::endl;

	q3.add(4);
	std::cout << q3 << std::endl;

	q2.add(3);
	std::cout << q2 << std::endl;

	fifoList<int> q6;
	q6.add({ 2, 3, 4 });
	std::cout << q6 << std::endl;

	fifoList<int> q7(1);
	q7.add({ 2, 3, 4 });
	std::cout << q7 << std::endl;

	q1.add({ 4, 5, 6 });
	std::cout << q1 << std::endl;

	fifoList<int> q8;
	q8.del();
	std::cout << q8 << std::endl;

	fifoList<int> q9(1);
	q9.del();
	std::cout << q9 << std::endl;

	fifoList<int> q10({ 1, 2 });
	q10.del();
	std::cout << q10 << std::endl;

	std::cout << q3 << std::endl;
	std::cout << "Размер массива: " << q3.size() << std::endl;
	std::cout << "Массив пуст: " << q3.empty() << std::endl;
	q3.clear();
	std::cout << q3 << std::endl;
	std::cout << "Размер массива: " << q3.size() << std::endl;
	std::cout << "Массив пуст: " << q3.empty() << std::endl;

	std::cout << "//----------------------------------------------------------" << std::endl;

	fifoVec<int> f1;
	std::cout << f1 << std::endl;

	fifoVec<int> f2(1);
	std::cout << f2 << std::endl;

	fifoVec<int> f3({ 1, 2, 3 });
	std::cout << f3 << std::endl;

	f1.add(1);
	std::cout << f1 << std::endl;

	f1.add(2);
	std::cout << f1 << std::endl;

	f3.add(4);
	std::cout << f3 << std::endl;

	fifoVec<int> f4(f1);
	std::cout << f4 << std::endl;

	fifoVec<int> f5(f2);
	std::cout << f5 << std::endl;

	fifoVec<int> f6(f3);
	std::cout << f6 << std::endl;

	f1 = f4;
	std::cout << f1 << std::endl;

	f1 = f2;
	std::cout << f1 << std::endl;

	f1 = f3;
	std::cout << f1 << std::endl;

	std::cout << f3[2] << std::endl;
	//std::cout << f1[3] << std::endl;

	fifoVec<int> f7;
	std::cout << f7 << std::endl;
	f7.add({ 1, 2, 3 });
	std::cout << f7 << std::endl;

	fifoVec<int> f8(1);
	std::cout << f8 << std::endl;
	f8.add({ 2, 3, 4 });
	std::cout << f8 << std::endl;

	std::cout << f7 << std::endl;
	f7.add({ 4, 5, 6 });
	std::cout << f7 << std::endl;

	std::cout << "//----------------------------------------------------------" << std::endl;

	fifoVec<int> f9;
	std::cout << f9 << std::endl;
	f9.del();
	std::cout << f9 << std::endl;

	
	fifoVec<int> f10(1);
	std::cout << f10 << std::endl;
	f10.del();
	std::cout << f10 << std::endl;

	
	std::cout << f7 << std::endl;
	f7.del();
	std::cout << f7 << std::endl;

	std::cout << f7 << std::endl;
	std::cout << "Размер массива: " << f7.size() << std::endl;
	std::cout << "Массив пуст: " << f7.empty() << std::endl;
	f7.clear();
	std::cout << f7 << std::endl;
	std::cout << "Размер массива: " << f7.size() << std::endl;
	std::cout << "Массив пуст: " << f7.empty() << std::endl;

	return 0;
}