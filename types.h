#ifndef TYPES_H
	#define TYPES_H
	
	typedef struct
	{
		int r; //Zeilenanzahl
		int c; //Spaltenanzahl
		double *mat; //Koeffizientenmatrix
	} Matrix;

	typedef struct
	{
		int d; //Dimension also anzahl der Basisvektoren
		int n; //Dimension der Einzelnen Basisvektoren
		double *bas; //Array mit Basisvektorkoeffizienten
	} VectorSpace;

	typedef struct
	{
		int n; //Diemension der Lösung
		double *sol; //Koeffizienten, also x1 = sol[0] ... xn = sol[n-1]
	} Solution;

#endif