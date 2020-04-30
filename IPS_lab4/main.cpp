#include "task_1.h"
#include "task_2.h"
#include "task_3.h"
#include "vector_var.h"
#include "cilk_for_plus_threads.h"
/*
* "task_1.h" - стандартная версия программы
* "task_2.h" - версия с использованием только cilk_for, без std::thread
* "vector_var.h" - версия с заменой стандартных массивов на std::vector
* "cilk_for_plus_threads.h" - версия с использованием cilk_for и std::thread без очистки памяти
* "task_3.h" - версия с использование cilk_for и std::thread с очисткой памяти
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