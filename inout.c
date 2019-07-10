#include "types.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "mats.h"
#include "inout.h"

int read_row(void)
{
	//liest die Zeilenzahl ein
	printf("Geben Sie die Zeilenanzahl ein: ");
	int m;
	do
	{
		scanf("%d", &m);
		if(m < 1)
		{
			printf("Die Zahl muss positiv sein!\n");
		}
	}
	while(m < 1);
	return m;
}

int read_col(void)
{
	//liest die Zeilenzahl ein
	printf("Geben Sie die Spaltenanzahl ein: ");
	int n;
	do
	{
		scanf("%d", &n);
		if(n < 1)
		{
			printf("Die Zahl muss positiv sein!\n");
		}
	}
	while(n < 1);
	return n;
}

int read_row_index(Matrix *A)
{
	//liest einen in die Matrix passenden Zeilenindex ein
	int i;
	printf("Geben Sie den Zeilenindex i ein:");
	do
	{
		scanf("%d", &i);
		i--;//index auf bei 0 beginnend korrigieren
		if(!index_in_range_row(A, i))
		{
			printf("Der Zeilenindex muss innerhalb der Matrix liegen!\n");
		}
	}
	while(!index_in_range_row(A, i));
	return i;
}

int read_col_index(Matrix *A)
{
	//liest einen in die Matrix passenden Spaltenindex ein
	int j;
	printf("Geben Sie den Spaltenindex ein:");
	do
	{
		scanf("%d", &j);
		j--;//index auf bei 0 beginnend korrigieren
		if(!index_in_range_row(A, j))
		{
			printf("Der Zeilenindex muss innerhalb der Matrix liegen!\n");
		}
	}
	while(!index_in_range_row(A, j));
	return j;
}

Matrix* read_mat(void)
{
	//liest eine Matrix ein über stdin
	int r = read_row();
	int c = read_col();
	Matrix *R = read_coe(r, c);
	if(R)
	{
		return R;
	}
	else
	{
		printf("Error: Matrix konnte nicht gelesen werden!\n");
		return NULL;
	}
}

Matrix* read_coe(int r, int c)
{
	//liest die Koeffizienten einer Matrix ein
	Matrix *R = create_mat(r, c);
	if(R)
	{
		printf("Geben Sie die Koeffizienten ein:\n");
		for(int i = 0; i < r; i++)
		{
			for(int j = 0; j < c; j++)
			{
				scanf("%lf", (R->mat + i * R->c + j));
			}
		}
		return R;
	}
	else
	{
		printf("Error: ungültiges Matrixformat!\n");
		return NULL;
	}
}

void print_mat(Matrix *A)
{
	//gibt eine Matrix tabellarisch aus
	if(A)//Matrix ist nicht NULL also existiert
	{
		for(int i = 0; i < A->r; i++)
		{
			for(int j = 0; j < A->c; j++)
			{
				printf("%-6.2g ", *(A->mat + i * A->c + j));
			}
			putchar('\n');
		}
	}
	else
	{
		printf("Error: Die Matrix konnte nicht ausgegeben werden!\n");
	}
}

bool check_jn(void)
{
    //true <=> Eingabe y oder j
    char in;
    scanf(" %c", &in);
    if(in == 'j' || in == 'J' || in == 'y' || in == 'Y')
    {
        return true;
    }
    return false;
}

void print_solution(Solution *S)
{
	if(S)
	{
		printf("Die Lösung lautet:\n");
		for(int i = 0; i < S->n; i++)
		{
			printf("x%d = %g\n", i + 1, *(S->sol + i));
		}
	}
	else
	{
		printf("Error: Die Lösung existiert nicht!");
	}
}