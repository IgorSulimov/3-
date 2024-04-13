#include <stdio.h>
#include <stdlib.h>
unsigned long long Problem_Euler8( unsigned long long number)
{
	unsigned long long* array = (unsigned long long*)calloc(number, sizeof(number));
	array[0] = 2;
	for (unsigned long long i = 2; i < number; i++)
	{
		unsigned long long k = 0;
		int fl = 0;
		for (k; array[k] != 0; k++)
		{
			if (i % array[k] == 0) {
				fl = 0;
				break;
			}
			if (i % array[k] != 0) {
				fl = 1;
			}
		}
		if (fl == 1) {
			for (unsigned long long s = 0; array[s] != 0; s++)
			{
				if (array[s + 1] == 0) {
					array[s + 1] = i;
					break;
				}
			}

			if (i % array[k] != 0) {
				for (int t = 0; array[t] != 0; t++) {
					if (array[t] == i);
				}
			}
			fl = 0;
		}
	}


	unsigned long long sum = 0;

	for (unsigned long long p = 0; array[p] != 0; p++)
	{
		sum = array[p] + sum;
	}
	return sum;
}