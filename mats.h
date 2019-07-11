#ifndef MATS_H
	#define MATS_H

	#include "types.h"
	#include <stdio.h>
	#include <stdbool.h>
	#include <stdlib.h>
	#include <math.h>
	#include <time.h>
	#include "inout.h"

	Matrix* create_mat(int r, int c);
	VectorSpace* create_vr(int d, int n);
	Solution* create_solution(int n);
	Matrix* create_En(int n);
	Matrix *create_zero(int r, int c);
	Matrix* copy_mat(Matrix *A);
	void free_mat(Matrix *A);
	bool mat_is_quad(Matrix *A);
	bool mat_same_row_size(Matrix *A, Matrix *B);
	bool mat_same_col_size(Matrix *A, Matrix *B);
	bool mat_same_size(Matrix *A, Matrix *B);
	bool mat_multable(Matrix *A, Matrix *B);
	bool index_in_range_row(Matrix *A, int i);
	bool index_in_range_col(Matrix *A, int j);
	bool mat_invertable(Matrix *A);
	bool mat_equal(Matrix *A, Matrix *B);
	bool mat_is_En(Matrix *A);
	bool mat_is_zero(Matrix *A);
	bool is_zero_row(Matrix *A, int n);
	int is_nilpotent(Matrix *A);
	bool is_idempotent(Matrix *A);
	Matrix* mat_add(Matrix *A, Matrix *B);
	Matrix* mat_mul(Matrix *A, Matrix *B);
	Matrix* mat_pow(Matrix *A, int p);
	Matrix* mat_skal_mul(Matrix *A, double a);
	double mat_diagmult(Matrix *A);
	double mat_spur(Matrix *A);
	void mat_row_add(Matrix *A, int s1, int s2, double a);
	void mat_row_switch(Matrix *A, int s1, int s2);
	Matrix* mat_gauss(Matrix *A);
	Matrix* mat_step_order(Matrix *A);
	Matrix* mat_step_norm(Matrix *A);
	Matrix* mat_spez_step(Matrix *A);
	Matrix* mat_gauss_jordan(Matrix *A, Matrix *B);
	Solution* mat_spez_solution(Matrix *A, Matrix *B);
	VectorSpace* mat_core(Matrix *A);
	double determinant(Matrix *A);
	Matrix* mat_ij(Matrix *A, int i, int j);
	Matrix* mat_ij_(Matrix *A, int i, int j);
	Matrix* mat_adj(Matrix *A);
	Matrix* mat_inverse(Matrix *A);
	int mat_rang(Matrix *A);
	Matrix* mat_trans(Matrix *A);
	Matrix* mat_main_minor(Matrix *A, int n);

#endif