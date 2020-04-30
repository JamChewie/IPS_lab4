#include "task_1.h"
#include "task_2.h"
#include "task_3.h"
#include "vector_var.h"
#include "cilk_for_plus_threads.h"
/*
* "task_1.h" - ����������� ������ ���������
* "task_2.h" - ������ � �������������� ������ cilk_for, ��� std::thread
* "vector_var.h" - ������ � ������� ����������� �������� �� std::vector
* "cilk_for_plus_threads.h" - ������ � �������������� cilk_for � std::thread ��� ������� ������
* "task_3.h" - ������ � ������������� cilk_for � std::thread � �������� ������
*/
int main()
{
	std::cout << "Base variant of programm" << std::endl;
	TASK1::run();
	std::cout << "===========================================" << std::endl;

	std::cout << "Cilk_for variant without std::trheads" << std::endl;
	TASK2::run();
	std::cout << "===========================================" << std::endl;

	std::cout << "Vector variant of programm" << std::endl;
	VectorVar::run();
	std::cout << "===========================================" << std::endl;

	std::cout << "Cilk_for and threads with memory cleaning" << std::endl;
	TASK3::run();
	std::cout << "===========================================" << std::endl;


	system("pause");
	return 0;
}