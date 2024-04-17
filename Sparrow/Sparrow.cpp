// Sparrow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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

/*
Ordenación por burbuja : array de n elementos
Se realizan una serie de pasadas mientras indiceIntercambio > 0
*/
void ordBurbuja2(long a[], int n)
{
	int i, j;
	int indiceIntercambio;
	/* i es el índice del último elemento de la sublista */
	i = n - 1;
	/* el proceso continúa hasta que no haya intercambios */
	while (i > 0)
	{
		indiceIntercambio = 0;
		/* explorar la sublista a[0] a a[i] */
		for (j = 0; j < i; j++)
			/* intercambiar pareja y actualizar IndiceIntercambio */
			if (a[j + 1] < a[j])
			{
				long aux = a[j];
				a[j] = a[j + 1];
				a[j + 1] = aux;
				indiceIntercambio = j;
			}
		/* i se pone al valor del índice del último intercambio */
		i = indiceIntercambio;
	}
}

/*
ordenar un array de n elementos de tipo double
utilizando el algoritmo de ordenación por selección
*/
void ordSeleccion(double a[], int n)
{
	int indiceMenor, i, j;
	/* ordenar a[0]..a[n-2] y a[n-1] en cada pasada */
	for (i = 0; i < n - 1; i++)
	{
		/* comienzo de la exploración en índice i */
		indiceMenor = i;
		/* j explora la sublista a[i+1]..a[n-1] */
		for (j = i + 1; j < n; j++)
			if (a[j] < a[indiceMenor])
				indiceMenor = j;
		/* situa el elemento mas pequeño en a[i] */
		if (i != indiceMenor)
		{
			double aux = a[i];
			a[i] = a[indiceMenor];
			a[indiceMenor] = aux;
		}
	}
}

void ordInsercion(int a[], int n)
{
	int i, j;
	int aux;
	for (i = 1; i < n; i++)
	{
		/* indice j explora la sublista a[i-1]..a[0] buscando la
		posicion correcta del elemento destino, lo asigna a a[j] */
		j = i;
		aux = a[i];
		/* se localiza el punto de inserción explorando hacia abajo */
		while (j > 0 && aux < a[j - 1])
		{
			/* desplazar elementos hacia arriba para hacer espacio */
			a[j] = a[j - 1];
			j--;
		}
		a[j] = aux;
	}
}

void ordenacionShell(double a[], int n)
{
	int intervalo, i, j, k;
	intervalo = n / 2;
	while (intervalo > 0)
	{
		for (i = intervalo; i < n; i++)
		{
			j = i - intervalo;
			while (j >= 0)
			{
				k = j + intervalo;
				if (a[j] <= a[k])
					j = -1; /* así termina el bucle, par ordenado */
				else
				{
					double temp;
					temp = a[j];
					a[j] = a[k];
					a[k] = temp;
					j -= intervalo;
				}
			}
		}
		intervalo = intervalo / 2;
	}
}

int main()
{
	long a[] = { 5, 3, 4, 1, 2 };
	double b[] = { 5.0, 3.0, 4.0, 1.0, 2.0 };
	int c[] = { 5, 3, 4, 1, 2 };
	double d[] = { 5.0, 3.0, 4.0, 1.0, 2.0 };

	ordBurbuja(a, 5);
	ordBurbuja2(a, 5);
	ordSeleccion(b, 5);
	ordInsercion(c, 5);
	ordenacionShell(d, 5);

	std::cout << "Burbuja" << std::endl;
	for (int i = 0; i < 5; i++)
	{
		std::cout << a[i] << " ";
	}

	std::cout << std::endl;
	std::cout << "Seleccion" << std::endl;

	for (int i = 0; i < 5; i++)
	{
		std::cout << b[i] << " ";
	}

	std::cout << std::endl;
	std::cout << "Insercion" << std::endl;

	for (int i = 0; i < 5; i++)
	{
		std::cout << c[i] << " ";
	}

	std::cout << std::endl;
	std::cout << "Shell" << std::endl;

	for (int i = 0; i < 5; i++)
	{
		std::cout << d[i] << " ";
	}

	std::cout << std::endl;

	// Genera una lista aleatoria
	int n = 10000;
	double* lista = new double[n];
	for (int i = 0; i < n; i++)
	{
		lista[i] = rand() % 1000;
	}


	std::cout << "LISTA GRANDE: " << std::endl;

	// Inicia cronometro:
	clock_t t_ini, t_fin;
	t_ini = clock();

	// Ordena la lista:
	ordenacionShell(lista, n);

	// Detiene cronometro:
	t_fin = clock();

	// Muestra el tiempo de ejecucion:
	std::cout << "Tiempo de ejecucion: " << (double)(t_fin - t_ini) / CLOCKS_PER_SEC << " segundos" << std::endl;

	// Muestra la lista ordenada:
	for (int i = 0; i < n; i++)
	{
		std::cout << lista[i] << " ";
	}

}
