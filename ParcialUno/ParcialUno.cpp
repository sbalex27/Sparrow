#include <iostream>

void ordBurbuja(long a[], int n)
{
	int interruptor = 1;
	int pasada, j;
	for (pasada = 0; pasada < n - 1 && interruptor; pasada++)
	{
		/* bucle externo controla la cantidad de pasadas */
		interruptor = 0;
		for (j = 0; j < n - pasada - 1; j++)
			if (a[j] > a[j + 1])
			{
				/* elementos desordenados, es necesario intercambio */
				long aux;
				interruptor = 1;
				aux = a[j];
				a[j] = a[j + 1];
				a[j + 1] = aux;
			}
	}
}

int main()
{
	int n = 30;
	long* lista = new long[n];
	for (int i = 0; i < n; i++)
	{
		lista[i] = rand() % 1000;
	}
	ordBurbuja(lista, n);
	
	for (int i = 0; i < n; i++)
	{
		std::cout << lista[i] << " ";
	}
}
