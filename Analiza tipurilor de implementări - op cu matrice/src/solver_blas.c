/*
 * Tema 2 ASC
 * 2024 Spring
 */
#include "utils.h"
#include <cblas.h>

/*
 * Add your BLAS implementation here
 */
double *my_solver(int N, double *A, double *B)
{
	printf("BLAS SOLVER\n");
    // C = (At * B + B * A) * Bt
	double *C = (double *)malloc(N * N * sizeof(double));
    double *D = (double *)malloc(N * N * sizeof(double));
    double *E = (double *)malloc(N * N * sizeof(double));

    // consider D o copie pentru B
	cblas_dcopy(N * N, B, 1, D, 1);
    // calculez At * D si retin rezultatul in D
	cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasTrans, CblasNonUnit, N, N, 1, A, N, D, N);
	
    // consider E o copie pentru B
	cblas_dcopy(N * N, B, 1, E, 1);
    // calculez E * A si retin rezultatul in E
	cblas_dtrmm(CblasRowMajor, CblasRight, CblasUpper, CblasNoTrans, CblasNonUnit, N, N, 1, A, N, E, N);

	// adun matricile D si E si retin rezultatul in E
	cblas_daxpy(N * N, 1, D, 1, E, 1);
    // calculez E * Bt si retin rezultatul in C
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasTrans, N, N, N, 1.0, E, N, B, N, 0.0, C, N);

	free(D);
	free(E);
	return C;
}
