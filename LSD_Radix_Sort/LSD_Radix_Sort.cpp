
#include <iostream>
using namespace std;
int count_of_operation = 0;


void Random(int A[], size_t n) {
	srand(unsigned(time(NULL)));
	for (int i = 0; i < n; i++) {
		A[i] = rand() % 999 + 1;
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
	int n;
	cout << "\nEnter the number of data element to be sorted: ";
	cin >> n;

	int* arr = new int[n];

	Random(arr, n);

	radixsort(arr, n);

	cout << count_of_operation;

	// Printing the sorted data.
	/*cout << "\nSorted Data ";
	for (i = 0; i < n; i++)
		cout << "->" << arr[i];*/
	return 0;
}

