
#include <iostream>
#include <fstream>
#include<iomanip>
#include <random>

using namespace std;
int count_of_operation = 0;

std::random_device rd; // Источник энтропии.
std::mt19937 generator(rd()); // Генератор случайных чисел.


void Random(int A[], int n, int min, int max) {
	
	// (Здесь берется одно инициализирующее значение, можно брать больше)

	std::uniform_int_distribution<> distribution(min, max); // Равномерное распределение
	for (int i = 0; i < n; i++) {
		A[i] = distribution(generator);
	}
}

// Получение максимального элемента из массива
int getMax(int arr[], int n)
{
	int max = arr[0];
	for (int i = 1; i < n; i++)
		if (arr[i] > max)
			max = arr[i];

	count_of_operation += n;
	return max;
}

// Сортировка подсчетом массива arr[].
void countSort(int arr[], int n, int exp)
{
	// Count[i] массив будет считать число значений массива, имеющих цифру 'i' на их (exp)-м месте.
	int i, count[10] = { 0 };
	
	
	int* output = new int[n];
	for (int i = 0; i < n; i++) 
	{
		// Заполнение массива 
		output[i] = 0;
	}
	// Подсчет количества раз, которые каждый разряд появился в (exp)-м месте в каждом в input
	for (i = 0; i < n; i++)
		count[(arr[i] / exp) % 10]++;
	count_of_operation += n;

	// Подсчет их кумулятивной суммы.
	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];
	count_of_operation += 9;
	// Вставка значений в соответствии с цифрой '(arr[i] / exp) % 10' попавшего в count[(arr[i] / exp) % 10].
	for (i = n - 1; i >= 0; i--)
	{
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}
	count_of_operation += n + (n-1);

	// Назначение результата указателю arr main().
	for (i = 0; i < n; i++)
		arr[i] = output[i];
	count_of_operation += n;
}

// Сортировка arr[] размера n с помощью Radix Sort.
void radixsort(int arr[], int n)
{
	int exp, m;
	m = getMax(arr, n);

	// Вызов countSort() для цифры на (exp)-м месте в каждом входе.
	for (exp = 1; m / exp > 0; exp *= 10)
		countSort(arr, n, exp);
}

int main()
{
	int n = 10000;


	fstream outFile1;
	outFile1.open("result_change_n.txt", std::ios::out);
	fstream outFile2;
	outFile2.open("result_change_m.txt", std::ios::out);
	
	// Изменяем количество входных данных и фиксируем длину чисел
	for (int i = 2; i <= 10000; i++)
	{
		int* arr = new int[i];
		Random(arr, i, 100, 999);
		radixsort(arr, i);

		outFile1 << count_of_operation << " ";
		count_of_operation = 0;
		delete[] arr;
	}

	// Изменяем максимальное количетсво разрядов

	int* arr = new int[n];
	for (int i = 1; i <= 8; i++)
	{
		
		Random(arr, n, int(pow(10, i-1)), int(pow(10,i)-1));
		radixsort(arr, n);
		
		outFile2 << count_of_operation << " ";
		count_of_operation = 0;
	}
	delete[] arr;
	outFile1.close();
	outFile2.close();
	return 0;
}

