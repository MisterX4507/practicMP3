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
private:
	void merge(int nach, int kon, int* buf, int len)
	{
		n = 0;
		if (kon == nach) { n++; return; }
		if (kon - nach == 1) {
			if (buf[kon] < buf[nach])
				swap(buf[kon], buf[nach]);
			n++;
			return;
		}
		int m = (kon + nach) / 2;
		merge(nach, m, buf, len);
		merge(m + 1, kon, buf, len);
		int *temp = (int*)malloc(len * sizeof(int));
		int xl = nach;
		int xr = m + 1;
		int cur = 0;
		while (kon - nach + 1 != cur)
		{

			if (xl > m)
			{
				temp[cur++] = buf[xr++];
				n++;
			}
			else if (xr > kon)
			{
				temp[cur++] = buf[xl++];
				n++;
			}
			else if (buf[xl] > buf[xr])
			{
				temp[cur++] = buf[xr++];
				n++;
			}
			else { temp[cur++] = buf[xl++]; n++; }
		}
		for (int i = 0; i < cur; i++)
		{
			buf[i + nach] = temp[i];
			n++;
		}
	}
public:
	void operation(int* buf, int len)
	{
		int nach = 0, kon = len - 1;
		merge(nach, kon, buf, len);
	}
};
int main()
{
	setlocale(LC_ALL, "Russian");
	int size; cout << "Ââåäèòå ðàçìåðíîñòü ìàññèâîâ "; cin >> size;
	cout << "Ââåäèòå íîìåð ñîðòèðîâêè "; int nomer; cin >> nomer;
	srand((unsigned int)time(0));
	double mid = 0; COMB z; SELECTION y; MERGE x;
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
		if (nomer == 1) { x.operation(array, size); mid += x.n; }
		if (nomer == 2) { y.operation(array, size); mid += y.n; }
		if (nomer == 3) { z.operation(array, size); mid += z.n; }		
		delete[]array;
	}
	mid /= 100;
	cout << "Ñðåäíåå êîëè÷åñòâî îïåðàöèé ñðàâíåíèÿ è ïåðåñòàíîâêè ðàâíî " << mid << "\n";
	system("PAUSE"); return 0;
}