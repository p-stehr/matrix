#ifndef INOUT_H
	#define INOUT_H

	#include "types.h"
	#include <stdio.h>
	#include <stdbool.h>
	#include <stdlib.h>
	#include <math.h>
	#include <time.h>
	#include "mats.h"
	
	int read_row(void);
	int read_col(void);
	int read_row_index(Matrix *A);
	int read_col_index(Matrix *A);
	Matrix* read_mat(void);
	Matrix* read_coe(int r, int c);
	void print_mat(Matrix *A);
	bool check_jn(void);
	void print_solution(Solution *S);

#endif