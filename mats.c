#include "types.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "mats.h"
#include "inout.h"

Matrix* create_mat(int r, int c)
{
	//initialisiert eine Matrix und reserviert Speicher für die Einträge
	if(r > 0 && c > 0)
	{
		Matrix *A = (Matrix*)malloc(sizeof(Matrix));
		A->r = r;
		A->c = c;
		A->mat = (double*)malloc(r * c * sizeof(double));
		return A;
	}
	else
	{
		printf("Error: Matrix hat kein gültiges Format!\n");
		return NULL;
	}
}

VectorSpace* create_vr(int d, int n)
{
	//initialisiert einen Vr und reserviert Speicher für die Einträge
	if(d >= 0 && n > 0)
	{
		VectorSpace *V = (VectorSpace*)malloc(sizeof(VectorSpace));
		V->d = d;
		V->n = n;
		V->bas = (double*)malloc(d * n * sizeof(double));
		return V;
	}
	else
	{
		printf("Error: Ungültiger Vektorraum!\n");
		return NULL;
	}
}

Solution* create_solution(int n)
{
	if(n >= 0)
	{
		Solution* S = (Solution*)malloc(sizeof(Solution));
		S->n = n;
		S->sol = (double*)malloc(n * sizeof(double));
		return S;
	}
	else
	{
		printf("Error: Lösung hat ungültiges Format\n");
		return NULL;
	}
}

Matrix* create_En(int n)
{
	//erstellt die Einheitsmatrix mit größe n
	Matrix *R = create_mat(n, n);
	if(R)
	{
		for(int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if(i == j)
				{
					*(R->mat + i * R->c + j) = 1;
				}
				else
				{
					*(R->mat + i * R->c + j) = 0;
				}
			}
		}
		return R;
	}
	else
	{
		printf("Error: Matrix hat kein gültiges Format!\n");
		return NULL;
	}
}

Matrix* copy_mat(Matrix *A)
{
	Matrix *R = create_mat(A->r, A->c);
	for(int i = 0; i < A->r * A->c; i++)
	{
		*(R->mat + i) = *(A->mat + i);
	}
	return R;
}

double correct_zero(double x)
{
	//ersetzt -0 durch 0
	return (x == -0) ? 0 : x;
}

void free_mat(Matrix *A)
{
	//gibt den Speicher der Matrix wieder frei
	free(A->mat);
	free(A);
}

bool mat_is_quad(Matrix *A)
{
	//true <=> Zeilenzahl == Spaltenzahl
	return (A->r == A->c);
}

bool mat_same_row_size(Matrix *A, Matrix *B)
{
	//true <=> Gleiche Zeilenzahl
	return (A->r == B->r);
}

bool mat_same_col_size(Matrix *A, Matrix *B)
{
	//true <=> Gleiche Spaltenzahl
	return (A->c == B->c);
}

bool mat_same_size(Matrix *A, Matrix *B)
{
	//true <=> Zwei Matrizen haben das selbe Format
	return ((A->r == B->r) && (A->c == B->c));
}

bool mat_multable(Matrix *A, Matrix *B)
{
	//true <=> Matrizen sind multiplizierbar also Spaltenzahl1 = Zeilenzahl2
	return (A->c == B->r);
}

bool index_in_range_row(Matrix *A, int i)
{
	//true <=> Reihe i liegt in Matrix A
	return (i >= 0 && i < A->r);
}

bool index_in_range_col(Matrix *A, int j)
{
	//true <=> Reihe i liegt in Matrix A
	return (j >= 0 && j < A->c);
}

bool mat_invertable(Matrix *A)
{
	//true <=> Matrix ist invertierbar
	return (determinant(A) != 0);
}

bool mat_equal(Matrix *A, Matrix *B)
{
	//true <=> beide Matrizen sind gleich
	if(mat_same_size(A, B))
	{
		for(int i = 0; i < A->r * A->c; i++)
		{
			if(*(A->mat + i) != *(B->mat + i))
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool is_zero_row(Matrix *A, int n)
{
	//true <=> Zeile n ist Nullzeile
	for(int i = 0; i < A->c; i++)
	{
		if(*(A->mat + n * A->c + i) != 0)
		{
			return false;
		}
	}
	return true;
}

bool mat_is_zero(Matrix *A)
{
	//true <=> Matrix ist Nullmatrix
	for(int i = 0; i < A->r; i++)
	{
		for(int j = 0; j < A->c; j++)
		{
			if(*(A->mat + i * A->c + j) != 0)
			{
				return false;
			}
		}
	}
	return true;
}

int is_nilpotent(Matrix *A)
{
	//gibt die potenz an, ab der A nilpotent ist, sonst 0
	int r = 0;
	if(mat_is_quad(A))
	{
		Matrix *B = copy_mat(A);
		for(int i = 1; i <= A->r && r == 0; i++) //r != damit sobald eine potenz gefunden wurde für die nilpotent ist, aufgehört wird
		{
			if(mat_is_zero(B))
			{
				r = i;
			}
			B = mat_mul(B, A);
		}
		free_mat(B);
	}
	return r;
}

bool is_idempotent(Matrix *A)
{
	//true <=> Matrix ist idempotent also A = A²
	bool r = false;
	if(mat_is_quad(A))
	{
		Matrix *B = mat_pow(A, 2);
		if(mat_equal(A, B))
		{
			r = true;
		}
		free_mat(B);
	}
	return r;
}

bool is_symmetric(Matrix *A)
{
    //true <=> Matrix ist symmetrisch
    Matrix *B = mat_trans(A);
    bool r = mat_equal(A, B);
    free_mat(B);
    return r;
}

bool is_orthogonal(Matrix *A)
{
    // true <=> Matrix ist orthogonal
    Matrix *B = mat_trans(A);
    Matrix *C = mat_inverse(A);
    bool r = mat_equal(B, C);
    free_mat(B);
    free_mat(C);
    return r;
}

Matrix* mat_add(Matrix *A, Matrix *B)
{
	//addiert Matrizen A und B
	if(mat_same_size(A, B))
	{
		Matrix *R = create_mat(A->r, A->c);
		for(int i = 0; i < A->r; i++)
		{
			for(int j = 0; j < A->c; j++)
			{
				*(R->mat + i * R->c + j) = *(A->mat + i * A->c + j) + *(B->mat + i * B->c + j);
			}
		}
		return R;
	}
	else 
	{
		printf("Error: Matrizen nicht addierbar!\n");
		return NULL;
	}
}

Matrix* mat_mul(Matrix *A, Matrix *B)
{
	//multipliziert Matrizen A und B
	if(mat_multable(A, B))
	{
		Matrix *R = create_mat(A->r, B->c); //Zeilenzahl von A Spaltenzahl von B
		for(int i = 0; i < A->r; i++)
		{			
			for(int j = 0; j < B->c; j++)
			{
				double sum = 0;
				for(int k = 0; k < A->c; k++)
				{
					sum += *(A->mat + i * A->c + k) * *(B->mat + k * B->c + j);
				}
				*(R->mat + i * R->c + j) = sum;
			}
		}
		return R;
	}
	else 
	{
		printf("Error: Matrizen nicht multiplizierbar!\n");
		return NULL;
	}
}

Matrix* mat_pow(Matrix *A, int p)
{
	if(mat_is_quad(A))
	{
		if(p > 0)
		{
			Matrix *R = copy_mat(A);
			for(int i = 0; i < p; i++)
			{
				R = mat_mul(R, A);
			}
			return R;
		}
		else if(p == 0)
		{
			if(mat_invertable(A))
			{
				Matrix *R = create_En(A->r);
				return R;
			}
			else
			{
				printf("Error: Matrix nicht invertierbar, also nicht mit 0 potenzierbar!\n");
				return NULL;
			}
		}
		else
		{
			printf("Error: Matrix nicht zur negativen potenzierbar!");
			return NULL;
		}
	}
	else
	{
		printf("Error: Nur quadratische Matrizen sind potenzierbar!");
		return NULL;
	}
}

Matrix* mat_skal_mul(Matrix *A, double a)
{
	Matrix *R = create_mat(A->r, A->c);
	for(int i = 0; i < A->r; i++)
	{
		for(int j = 0; j < A->c; j++)
		{
			*(R->mat + i * R->c + j) = correct_zero(*(A->mat + i * A->c + j) * a);
		}
	}
	return R;
}

double mat_spur(Matrix *A)
{
	if(mat_is_quad(A))
	{
		double spur = 0;
		for(int i = 0; i < A->r; i++)
		{
			spur += *(A->mat + i * A->c + i);
		}
		return spur;
	}
	else
	{
		printf("Error: Spur nur für quadratische Matrizen bestimmbar!\n");
		return NAN;
	}
}

double mat_diagmult(Matrix *A)
{
	//Gibt die Einträge der Hauptdiagonale multipliziert zurück
	double r = 1;
	for(int i = 0; i < A->r; i++)
	{
		r *= *(A->mat + i * A->c + i);
	}
	return r;
}

void mat_row_add(Matrix *A, int s1, int s2, double a)
{
	//Macht Gaußform 3 durch Addition von a * s2-te Zeile auf s1-te Zeile
	for(int j = 0; j < A->c; j++)
	{
		*(A->mat + s1 * A->c + j) = correct_zero(*(A->mat + s1 * A->c + j) + a * *(A->mat + s2 * A->c + j));
	}
}

void mat_row_switch(Matrix *A, int s1, int s2)
{
	//Tauscht die Zeilen s1 und s2 in der Matrix
	double tmp;
	for(int j = 0; j < A->c; j++)
	{
		tmp = *(A->mat + s1 * A->c + j);
		*(A->mat + s1 * A->c + j) = *(A->mat + s2 * A->c + j);
		*(A->mat + s2 * A->c + j) = tmp;
	}
}

void mat_row_skal(Matrix *A, int s, double a)
{
	//multipliziert zeile s mit skalar a
	for(int j = 0; j < A->c; j++)
	{
		*(A->mat + s * A->c + j) = correct_zero(a * *(A->mat + s * A->c + j));
	}
}

Matrix* mat_gauss(Matrix *A)
{
	//bringt eine Matrix auf obere Dreiecksform ohne die Determinante zu ändern
	Matrix *R = copy_mat(A);
	for(int i = 0; i < R->c; i++)
	{
		int pivot = i; //pivot ist index der Zeile die zum Eliminieren genutzt wird
		if(*(R->mat + i * R->c + i) == 0) //Hauptdiagonaleintrag ist Null
		{
			double best_pivot_val = 0; //Wert der Zeile, die zum eliminieren genutzt wird
			for(int j = i + 1; j < R->r; j++) //Maximum nehmen um Rundungsfehler klein zu halten
			{
				if(fabs(*(R->mat + j * R->c + i)) > best_pivot_val)
				{
					best_pivot_val = fabs(*(R->mat + j * R->c + i));
					pivot = j;
				}
			}
		}
		double pivot_coe = *(R->mat + pivot * R->c + i); //Eintrag mit dem elimiert wird
		if(pivot_coe != 0) //Bei pivot_coe ist die Spalte bereits in korrekter form
		{
			for(int j = 0; j < R->r; j++)
			{
				if(j != pivot) //Zeile darf sich nicht selbst eliminieren
				{
					mat_row_add(R, j, pivot, -(*(R->mat + j * R->c + i) / pivot_coe));
				}
			}
			if(pivot != i) //Zeilen müssen getauscht werden da in eigentlicher Pivotzeile eine 0 steht
			{	//Tauschen als verschachtelung von Zeilenadditionen um die determinante nicht zu ändern
				mat_row_add(R, i, pivot, 1.0 / pivot_coe); 
				mat_row_add(R, pivot, i, -pivot_coe);
			}
		}
	}
	return R;
}

Matrix* mat_step_order(Matrix *A)
{
	//bringt Stufen in der Matrix auf die richtige Position
	Matrix *R = copy_mat(A);
	int already_sorted = -1;
	for(int j = 0; j < R->c && already_sorted < R->r - 2; j++)
	{
		for(int i = R->r - 1; i > already_sorted; i--)
		{
			if(*(R->mat + i * R->c + j) != 0)
			{
				already_sorted++;
				mat_row_switch(R, i, already_sorted);				
				if(*(R->mat + i * R->c + j) != 0 && i > already_sorted) //Getauschtes Element extra überprüfen, da es sonst übersprungen wird
				{
					already_sorted++;
					mat_row_switch(R, i, already_sorted);					
				}
			}
		}
	}
	return R;
}

Matrix* mat_step_norm(Matrix *A)
{
	//normiert die Stufen einer Matrix
	Matrix *R = copy_mat(A);
	for(int i = 0; i < R->r; i++)
	{
		int j = 0;
		while(j < R->c - 1 && *(R->mat + i * R->c + j) == 0)
		{
			j++;
		}
		if(*(R->mat + i * R->c + j) != 0)
		{
			mat_row_skal(R, i, 1.0 / *(R->mat + i * R->c + j));
		}
	}
	return R;
}

Matrix* mat_spez_step(Matrix *A)
{
	//bring A auf spezielle Zeilenstufenform
	Matrix *R = mat_gauss(A);
	R = mat_step_order(R);
	R = mat_step_norm(R);
	return R;
}

Matrix* mat_gauss_jordan(Matrix *A, Matrix *B)
{
	//bringt A auf Zeilenstufenform und macht die gleichen Operationen mit B
	if(!mat_same_row_size(A, B))
	{
		printf("Error: Matrizen nicht von geeignetem Format für Gauss-Jordan\n");
		return NULL;
	}
	Matrix *A2 = copy_mat(A);
	Matrix *B2 = copy_mat(B);
	for(int i = 0; i < A2->c; i++)
	{
		int pivot = i; //pivot ist index der Zeile die zum Eliminieren genutzt wird
		if(*(A2->mat + i * A2->c + i) == 0) //Hauptdiagonaleintrag ist Null
		{
			double best_pivot_val = 0; //Wert der Zeile, die zum eliminieren genutzt wird
			for(int j = i + 1; j < A2->r; j++) //Maximum nehmen um Rundungsfehler klein zu halten
			{
				if(fabs(*(A2->mat + j * A2->c + i)) > best_pivot_val)
				{
					best_pivot_val = fabs(*(A2->mat + j * A2->c + i));
					pivot = j;
				}
			}
		}
		double pivot_coe = *(A2->mat + pivot * A2->c + i); //Eintrag mit dem elimiert wird
		if(pivot_coe != 0) //Bei pivot_coe ist die Spalte bereits in korrekter form
		{
			for(int j = 0; j < A2->r; j++)
			{
				if(j != pivot) //Zeile darf sich nicht selbst eliminieren
				{
					mat_row_add(B2, j, pivot, -(*(A2->mat + j * A2->c + i) / pivot_coe));
					mat_row_add(A2, j, pivot, -(*(A2->mat + j * A2->c + i) / pivot_coe));					
				}
			}
			if(pivot != i) //Zeilen müssen getauscht werden da in eigentlicher Pivotzeile eine 0 steht
			{	//Tauschen als verschachtelung von Zeilenadditionen um die determinante nicht zu ändern
				mat_row_add(B2, i, pivot, 1.0 / pivot_coe); 
				mat_row_add(B2, pivot, i, -pivot_coe);
				mat_row_add(A2, i, pivot, 1.0 / pivot_coe); 
				mat_row_add(A2, pivot, i, -pivot_coe);
			}
		}
	}
	//Beide jetzt auf Zeilenstufenform
	int already_sorted = -1;
	for(int j = 0; j < A2->c && already_sorted < A2->r - 2; j++)
	{
		for(int i = A2->r - 1; i > already_sorted; i--)
		{
			if(*(A2->mat + i * A2->c + j) != 0)
			{
				already_sorted++;
				mat_row_switch(A2, i, already_sorted);
				mat_row_switch(B2, i, already_sorted);				
				if(*(A2->mat + i * A2->c + j) != 0 && i > already_sorted) //Getauschtes Element extra überprüfen, da es sonst übersprungen wird
				{
					already_sorted++;
					mat_row_switch(A2, i, already_sorted);	
					mat_row_switch(B2, i, already_sorted);					
				}
			}
		}
	}
	//jetzt mit Stufen in richtiger Reihenfolge
	for(int i = 0; i < A2->r && !is_zero_row(A2, i); i++)
	{
		int j = 0;
		while(j < A2->c - 1 && *(A2->mat + i * A2->c + j) == 0)
		{
			j++;
		}
		if(*(A2->mat + i * A2->c + j) != 0)
		{
			mat_row_skal(B2, i, 1.0 / *(A2->mat + i * A2->c + j));
			mat_row_skal(A2, i, 1.0 / *(A2->mat + i * A2->c + j));			
		}
	}
	//jetzt in Endform
	free_mat(A2);
	return B2;
}

Solution* mat_spez_solution(Matrix *A, Matrix *B)
{
	//gibt die spezielle Lösung von A = B wieder (B ist Vektor)
	if(mat_same_row_size(A, B) && B->c == 1)
	{
		Solution *S = create_solution(B->r);
		Matrix* B2 = mat_gauss_jordan(A, B);
		for(int i = 0; i < B2->r; i++)
		{
			*(S->sol + i) = *(B2->mat + i);
		}
		free_mat(B2);
		return S;
	}
	else
	{
		printf("Error: Ungültiges Format für spezielle Lösung!\n");
		return NULL;
	}
}

VectorSpace* mat_core(Matrix *A)
{
	//bestimmt den Kern einer Matrix A
	Matrix *B = mat_spez_step(A);
	int rang = mat_rang(B);
	VectorSpace *V = create_vr(B->r - rang, B->c);
	int steps[rang];
	int J[V->d];
	for(int i = 0; i < rang; i++)
	{
		int j = 0;
		while(j < B->c - 1 && *(B->mat + i * B->c + j) == 0)
		{
			j++;
		}
		//j ist jetzt die Stufenposition
		steps[i] = j;
	}
	//J_ bestimmen
	int J_pos = 0;
	for(int i = 0; i < B->r; i++)
	{
		bool is_in_j_ = true;
		for(int j = 0; j < rang && is_in_j_; j++)
		{
			if(steps[j] == i)
			{
				is_in_j_ = false;
			}
		}
		if(is_in_j_)
		{
			J[J_pos] = i;
			J_pos++;
		}
	}
	for(int i = 0; i < V->d; i++)
	{
		for(int j = 0; j < rang; j++)
		{
			*(V->bas + i * V->n + steps[j]) = correct_zero(-(*(B->mat + steps[j] * B->c + J[i])));
		}
		for(int j = 0; j < V->d; j++)
		{
			if(i == j)//nur eine Eins pro Vektor verteilen und zwar an unterschiedliche Stellen
			{
				*(V->bas + i * V->n + J[j]) = 1;
			}
			else
			{
				*(V->bas + i * V->n + J[j]) = 0;
			}			
		}
	}
	free_mat(B);
	return V;
}

double determinant(Matrix *A)
{
	//betsimmt die Determinante einer Matrix mithilfe der oberen Dreiecksform
	if(mat_is_quad(A))
	{
		Matrix *B = mat_gauss(A);
		double det = mat_diagmult(B);
		free_mat(B);
		return det;
	}
	else
	{
		printf("Error: Determinante nur für quadratische Matrizen bestimmbar!\n");
		return NAN;
	}
}

Matrix* mat_ij(Matrix *A, int i, int j)
{
	//gibt Aij zurück also 1 bei aij und sonst in Zeile i und Spalte j Nullen
	if(index_in_range_row(A, i) && index_in_range_col(A, j))
	{
		Matrix *R = copy_mat(A);
		//Nullen eintragen
		for(int z = 0; z < i; z++)
		{
			*(R->mat + z * R->c + j) = 0;
		}
		for(int z = i + 1; z < A->r; z++)
		{
			*(R->mat + z * R->c + j) = 0;
		}
		for(int s = 0; s < j; s++)
		{
			*(R->mat + i * R->c + s) = 0;
		}
		for(int s = j + 1; s < A->c; s++)
		{
			*(R->mat + i * R->c + s) = 0;
		}
		//1 auf aij eintragen
		*(R->mat + i * R->c + j) = 1;
		return R;
	}
	else
	{
		printf("Error: Index außerhalb der Matrix!\n");
		return NULL;
	}
}

Matrix* mat_ij_(Matrix *A, int i, int j)
{
	//gibt Aij' zurück also A mit Zeile i und Spalte j gestrichen
	if(index_in_range_row(A, i) && index_in_range_col(A, j))
	{
		Matrix *R = create_mat(A->r - 1, A->c - 1);
		int s = 0; //index des im neuen Array zu belgenden Feldes
		for(int k = 0; k < A->r * A->c; k++)
		{
			if(!(k % A->c == j || (k >= i * A->r && k < (i + 1) * A->r)))
			{
				*(R->mat + s) = *(A->mat + k);
				s++;
			}
		}
		return R;
	}
	else
	{
		printf("Error: Index außerhalb der Matrix!\n");
		return NULL;
	}
}

Matrix* mat_adj(Matrix *A)
{
	if(mat_is_quad(A))
	{
		Matrix *R = create_mat(A->r, A->c);
		for(int i = 0; i < R->r; i++)
		{
			for(int j = 0; j < R->c; j++)
			{
				*(R->mat + i * R->c + j) = correct_zero(determinant(mat_ij_(A, j, i)) * pow(-1, i + j));
			}
		}
		return R;
	}
	else
	{
		printf("Error: Für Adjunkte muss Matrix quadratisch sein!");
		return NULL;
	}
}

Matrix* mat_inverse(Matrix *A)
{
	//berechnet inverses mithilfe der cramerschen Regel
	double det = determinant(A);
	if(det != 0)
	{
		Matrix *R = mat_adj(A);
		mat_skal_mul(A, 1.0 / det);
		return R;
	}
	else
	{
		printf("Error: Kein Inverses bei Determinante = 0!\n");
		return NULL;
	}
}

int mat_rang(Matrix *A)
{
	//Gibt den Rang der Matrix zurück
	int rang = A->r;
	Matrix *B = mat_spez_step(A);
	for(int i = B->r - 1; i >= 0; i--)
	{
		if(is_zero_row(B, i))
		{
			rang--;
		}
	}
	free_mat(B);
	return rang;
}

Matrix* mat_trans(Matrix *A)
{
	//gibt die transponierte Matrix zurück
	Matrix *R = create_mat(A->c, A->r);
	for(int i = 0; i < A->r; i++)
	{
		for(int j = 0; j < A->c; j++)
		{
			*(R->mat + j * R->c + i) = *(A->mat + i * R->c + j);
		}
	}
	return R;
}

Matrix* mat_main_minor(Matrix *A, int n)
{
	//gibt den n-ten hauptminor zurück der also nxn groß ist
	if(mat_is_quad(A))
	{
		if(n <= A->r)
		{
			Matrix *R = create_mat(n, n);
			for(int i = 0; i < n; i++)
			{
				for(int j = 0; j < n; j++)
				{
					*(R->mat + i * n + j) = *(A->mat + i * A->c + j);
				}
			}
			return R;
		}
		else
		{
			printf("Error: Minore kann maximal so groß wie Matrix sein!\n");
			return NULL;
		}
	}
	else
	{
		printf("Error: Matrix muss für Minoren quadratisch sein!\n");
		return NULL;
	}
}

int mat_definitheit_sylvester(Matrix *A)
{
	//bestimmt dei Definitheit mit sylvester-kriterium
	//0 <=> indefinit
	//1 <=> positiv definit
	//2 <=> positiv semidefinit
	//-1 <=> negativ definit
	//-2 <=> negativ semidefinit
	int r = 0;
	if(mat_is_quad(A))
	{
		double main_minors[A->r];
		bool semi = false;
		for(int i = 0; i < A->r; i++)
		{
			main_minors[i] = determinant(mat_main_minor(A, i + 1));
		}
		if(main_minors[0] > 0)
		{
			r = 1;
			for(int i = 1; i < A->r && r == 1; i++)
			{
				if(main_minors[i] < 0)
				{
					r = 0;
				}
				else if(main_minors[i] == 0)
                {
				    semi = true;
                }
			}
		}
		else if(main_minors[0] < 0)
		{
			r = -1;
			for(int i = 1; i < A->r && r == -1; i++)
			{
				if(i % 2)
				{
					if(main_minors[i] < 0)
					{
						r = 0;
					}
					else if(main_minors[i] == 0)
                    {
                        semi = true;
                    }
				}
				else
				{
				    if(main_minors[i] > 0)
					{
						r = 0;
					}
				    else if(main_minors[i] == 0)
                    {
                        semi = true;
                    }
				}
			}
		}
		if(semi)
        {
		    if(r == 1)
            {
		        r = 2;
            }
		    else if(r == -1)
            {
		        r = -2;
            }
        }
	}
	return r;
}

Matrix* mat_trafo_formel(Matrix *A, Matrix *S)
{
	//Wendet die Trafo formel auf A mit Wechselmatrix S an
	if(mat_invertable(S) && mat_same_size(A, S))
	{
		Matrix *Si = mat_inverse(S);
		Matrix *R = mat_mul(Si, A);
		R = mat_mul(R, S);
		free_mat(Si);
		return R;
	}
	else
	{
		printf("Error: Wechselmatrix nicht invertierbar oder nicht gleiches Format wie A!\n");
		return NULL;
	}	
}