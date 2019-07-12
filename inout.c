#include "types.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
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
		if(A->r == 1)//matrix mit nur einer Zeile braucht spezielle Klammern
		{
			printf("(");
			for(int j = 0; j < A->c; j++)
			{
				printf("%g", *(A->mat + j));
				if(j != A->c - 1)
				{
					//space in der letzten Spalte wird weggelassen
					putchar(' ');
				}
			}
			printf(")\n");
		}
		else
		{	
			//breite der einzelnen spalten bestimmen	
			int col_width[A->c];
			for(int j = 0; j < A->c; j++)
			{
				col_width[j] = max_number_length(A->mat + j, A->r * A->c, A->c);
			}
			for(int i = 0; i < A->r; i++)
			{
				//richtige Klammer drucken
				if(i == 0)
				{
					printf("⎛");
				}
				else if(i == A->r - 1)
				{
					printf("⎝");
				}
				else
				{
					printf("⎜");
				}
				for(int j = 0; j < A->c; j++)
				{
					printf("%g", *(A->mat + i * A->c + j));
					fill_spaces(col_width[j] - number_length(*(A->mat + i * A->c + j)));
					if(j != A->c - 1)
					{
						//space in der letzten Spalte wird weggelassen
						putchar(' ');
					}
				}
				//richtige rechte Klammer drucken
				if(i == 0)
				{
					printf("⎞\n");
				}
				else if(i == A->r - 1)
				{
					printf("⎠\n");
				}
				else
				{
					printf("⎟\n");
				}
			}
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
		printf("Error: Die Lösung existiert nicht!\n");
	}
}

void print_vr(VectorSpace *V)
{
	if(V)
	{
		if(V->n == 1)
		{
			printf("(%g)\n", *V->bas);
		}
		for(int i = 0; i < V->n; i++)
		{
			for(int j = 0; j < V->d; j++)
			{
				printf("%g ", *(V->bas + j * V->n + i));
			}
			putchar('\n');
		}
	}
	else
	{
		printf("Error: Der Vektorraum existiert nicht!\n");
	}
}

int number_length(double x)
{
	//gibt Dezimalstellen von x mit maximal 2 nachkommastellen und bei bedarf dem punkt dazu gerechnet zurück
	char buffer[50];
	sprintf(buffer, "%.2g", x);
	return strlen(buffer);
}

int max_number_length(double *F, int n, int skip)
{
	//gibt die größte Länge einer Zahl aus dem Array F (länge n) zurück
	//mit skip wird nur jedes skip-te wort gelesn und so können zum beispiel nur spalten gelesen werden
	int max_length = 0;
	for(int i = 0; i < n / skip; i++)
	{
		int num_length = number_length(*(F + i * skip));
		if(num_length > max_length)
		{
			max_length = num_length;
		} 
	}
	return max_length;
}

void fill_spaces(int n)
{
	//füllt einen bereich mit n leerzeichen auf
	for(int i = 0; i < n; i++)
	{
		putchar(' ');
	}
}