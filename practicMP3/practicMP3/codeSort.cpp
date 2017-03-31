#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
int i, j;
class SORTING {
public:
	int n;
	virtual void operation(int *buf, int len) = 0;
};
class SELECTION : public SORTING {
public:
	void operation(int* buf, int len)
	{
		n = 0;
		for (i = 0; i < len - 1; i++)
		{
			int i_min = i;
			for (j = i + 1; j < len; j++)
			{
				n++;
				if (buf[j] < buf[i_min]) i_min = j;
			}
			 if (i != i_min) {
				int temp; n++;
				temp = buf[i]; buf[i] = buf[i_min]; buf[i_min] = temp;
			}
		}
	}
};
class COMB : public SORTING {
public:
	void operation(int* buf, int len)
	{
		n = 0;
		const double A = 1.3;
		int step, temp; step = len / A;
		while (step > 1)
		{
			for (i = 0; (i + step) < len; i++)
			{
				n++;
				if (buf[i] > buf[i + step]) {
					temp = buf[i]; buf[i] = buf[i + step];
					buf[i + step] = temp; n++;
				}
			}
			step /= A;
		}
		for (i = 0; i < len - 1; i++) {
			for (j = 0; j < len - i - 1; j++) {
				n++;
				if (buf[j] > buf[j + 1]) {
					temp = buf[j]; buf[j] = buf[j + 1];
					buf[j + 1] = buf[j]; n++;
				}
			}
		}
	}
};
class MERGE : public SORTING {
public:
	void operation(int* buf, int size)
	{
		n = 0;
		int mid = size / 2;
		if (size % 2 == 1)
			mid++;
		int h = 1;
		int *c = (int*)malloc(size * sizeof(int));
		int step;
		while (h < size)
		{
			step = h;
			int i = 0;
			int j = mid;
			int k = 0;
			while (step <= mid)
			{
				while ((i < step) && (j < size) && (j < (mid + step)))
				{
					if (buf[i] < buf[j])
					{
						c[k] = buf[i];
						i++; k++; n++;
					}
					else {
						c[k] = buf[j];
						j++; k++; n++; 
					}
				}
				while (i < step)
				{
					c[k] = buf[i];
					i++; k++; n++;
				}
				while ((j < (mid + step)) && (j<size))
				{
					c[k] = buf[j];
					j++; k++; n++;
				}
				step = step + h;
			}
			h = h * 2;
			for (i = 0; i < size; i++)
			{
				buf[i] = c[i]; n++;
			}
		}
	}
};
int main()
{
	setlocale(LC_ALL, "Russian");
	int size; cout << "¬ведите размерность массивов "; cin >> size;
	cout << "¬ведите номер сортировки "; int nomer; cin >> nomer;
	srand((unsigned int)time(0));
	double mid = 0; COMB z; SELECTION y; MERGE q;
	for (int S = 1; S <= 100; S++)
	{
		int *array = new int[size];
		for (int k = 0; k < size; k++)
		{
			if (S == 1) array[k] = k; else
				if (S == 2) {
					if (nomer == 2) {
						if (k == 0)  array[k] = size - 1; else array[k] = k - 1;
					}
					else array[k] = size - 1 - k;
				} else
					array[k] = rand() % 1000;
		}
		if (nomer == 2) { y.operation(array, size); mid += y.n; }
		if (nomer == 3) { z.operation(array, size); mid += z.n; }
		if (nomer == 4) { q.operation(array, size); mid += q.n;}
		delete[]array;
	}
	mid /= 100;
	cout << "—реднее количество операций сравнени€ и перестановки равно " << mid << "\n";
	system("PAUSE"); return 0;
}