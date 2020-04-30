#include <vector>
#include <thread>
#include <stdio.h>
#include <iostream>
#include <exception>
#include <locale.h>
#include <algorithm>
#include <cilk/cilk.h>
#include <cilk/reducer_opadd.h>
namespace VectorVar
{
	/// ������������, ������������ ��� ����� ����������� ����������
	/// ������� �������� �������: �� ������� ��� �� ��������
	enum class eprocess_type
	{
		by_rows = 0,
		by_cols
	};

	void InitMatrix(std::vector <std::vector <double>> &matrix)
	{
		for (size_t i = 0; i < matrix.size(); ++i)
		{
			for (size_t j = 0; j < matrix[i].size(); ++j)
			{
				matrix[i][j] = rand() % 5 + 1;
			}
		}
	}

	/// ������� PrintMatrix() �������� �������� ������� <i>matrix</i> �� �������;
	void PrintMatrix(std::vector <std::vector <double>> &matrix)
	{
		printf("Generated matrix:\n");
		for (size_t i = 0; i < matrix.size(); ++i)
		{
			for (size_t j = 0; j < matrix[i].size(); ++j)
			{
				printf("%lf ", matrix[i][j]);
			}
			printf("\n");
		}
	}

	/// ������� FindAverageValues() ������� ������� �������� � ������� <i>matrix</i>
	/// �� �������, ���� �� �������� � ����������� �� �������� ��������� <i>proc_type</i>;
	/// proc_type - �������, � ����������� �� �������� ������� �������� ����������� 
	/// ���� �� �������, ���� �� ������� �������� ������� <i>matrix</i>
	/// matrix - �������� �������
	/// average_vals - ������, ���� ����������� ����������� ������� ��������
	void FindAverageValues(eprocess_type proc_type, std::vector <std::vector <double>> &matrix, std::vector <double> &average_vals)
	{
		switch (proc_type)
		{
		case eprocess_type::by_rows:
		{
			for (size_t i = 0; i < matrix.size(); ++i)
			{
				double sum(0.0);
				for (size_t j = 0; j < matrix[0].size(); ++j)
				{
					sum += matrix[i][j];
				}
				average_vals[i] = sum / matrix[0].size();
			}
			break;
		}
		case eprocess_type::by_cols:
		{
			for (size_t j = 0; j < matrix[0].size(); ++j)
			{
				double sum(0.0);
				for (size_t i = 0; i < matrix.size(); ++i)
				{
					sum += matrix[i][j];
				}
				average_vals[j] = sum / matrix.size();
			}
			break;
		}
		default:
		{
			throw("Incorrect value for parameter 'proc_type' in function FindAverageValues() call!");
		}
		}
	}

	/// ������� PrintAverageVals() �������� �������� ������� <i>average_vals</i> �� �������;
	/// proc_type - �������, ���������� �� ��, ��� ���� ��������� 
	/// ������� �������� �������� ������� �� ������� ��� �� ��������
	/// average_vals - ������, �������� ������� �������� �������� �������,
	/// ����������� �� ������� ��� �� ��������
	void PrintAverageVals(eprocess_type proc_type, std::vector <double> &average_vals)
	{
		switch (proc_type)
		{
		case eprocess_type::by_rows:
		{
			printf("\nAverage values in rows:\n");
			int i = 0;
			std::for_each(average_vals.begin(), average_vals.end(), [&](double avg)
			{
				printf("Row %u: %lf\n", i, avg);
				i++;
			}
			);
			break;
		}
		case eprocess_type::by_cols:
		{
			printf("\nAverage values in columns:\n");
			int i = 0;
			std::for_each(average_vals.begin(), average_vals.end(), [&](double avg)
			{
				printf("Column %u: %lf\n", i, avg);
				i++;
			}
			);
			break;
		}
		default:
		{
			throw("Incorrect value for parameter 'proc_type' in function PrintAverageVals() call!");
		}
		}
	}


	void run()
	{
		const unsigned ERROR_STATUS = -1;
		const unsigned OK_STATUS = 0;

		unsigned status = OK_STATUS;

		try
		{
			srand((unsigned)time(0));

			const size_t numb_rows = 2;
			const size_t numb_cols = 3;
			//�������� ������� �� �������� � ������������� ���������� ���������
			std::vector <std::vector <double>> matrix(numb_rows, std::vector <double>(numb_cols));
			//�������� �������� ��� �������� ������� ��������
			std::vector <double> average_vals_in_rows(numb_rows);
			std::vector <double> average_vals_in_cols(numb_cols);
			InitMatrix(matrix);

			PrintMatrix(matrix);
			auto start = clock() / 1000.0;
			std::thread first_thr(FindAverageValues, eprocess_type::by_rows, std::ref(matrix), std::ref(average_vals_in_rows));
			std::thread second_thr(FindAverageValues, eprocess_type::by_cols, std::ref(matrix), std::ref(average_vals_in_cols));

			first_thr.join();
			second_thr.join();
			auto end = clock() / 1000.0;
			std::cout << "Duration = " << end - start << std::endl;
			PrintAverageVals(eprocess_type::by_rows, average_vals_in_rows);
			PrintAverageVals(eprocess_type::by_cols, average_vals_in_cols);
		}
		catch (std::exception& except)
		{
			printf("Error occured!\n");
			except.what();
			status = ERROR_STATUS;
		}
	}
}
