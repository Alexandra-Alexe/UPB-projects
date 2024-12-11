/*
 * Tema 2 ASC
 * 2024 Spring
 */
#include "utils.h"

// functie ce transpune eficient o matrice data
double* transpose(int N, double* A) {
    register double* At = malloc(N * N * sizeof(double));
    if (At == NULL) {
        exit(EXIT_FAILURE); 
    }

	// pointer pt parcurgerea matricei A
    register double* A_ptr = A;   
	// pointer pt parcurgerea matricei At
    register double* At_ptr;      

    for (register int i = 0; i < N; i++) {
        At_ptr = At + i;          
        for (register int j = 0; j < N; j++, A_ptr++) {
            *At_ptr = *A_ptr;
            At_ptr += N;          
        }
    }

    return At;
}


// functie ce inmulteste eficient o matrice inferior triunghiulara cu una oarecare
double* multiply_efficient_lower_triangular(double* A, double* B, int N) {
    register double* result = malloc(N * N * sizeof(double));
    if (result == NULL) {
        exit(EXIT_FAILURE); 
    }

    for (register int i = 0; i < N; i++) {
        for (register int j = 0; j < N; j++) { 
            register double sum = 0.0;
			// pointer pt parcurgerea liniei i a matricei A
            register double* A_ptr = A + i * N;
			// pointer pt parcurgerea coloanei j a matricei B 
            register double* B_ptr = B + j;    

            for (register int k = 0; k <= i; k++, A_ptr++, B_ptr += N) {
                sum += *A_ptr * *B_ptr;
            }
            result[i * N + j] = sum;
        }
    }
    return result;
}

// functie ce inmulteste eficient o matrice oarecare cu una superior triunghiulara
double* multiply_efficient_upper_triangular(double* A, double* B, int N) {
    register double* result = malloc(N * N * sizeof(double));
    if (result == NULL) {
        exit(EXIT_FAILURE); 
    }

    for (register int i = 0; i < N; i++) {
        for (register int j = 0; j < N; j++) {
            register double sum = 0.0;
			// pointer pt parcurgerea liniei i a matricei A
            register double* A_ptr = A + i * N;  
			// pointer pt parcurgerea coloanei j a matricei B
            register double* B_ptr = B + j;         

            for (register int k = 0; k <= j; k++, A_ptr++, B_ptr += N) {
                sum += *A_ptr * *B_ptr;
            }
            result[i * N + j] = sum;
        }
    }
    return result;
}

// functie ce inmulteste eficient doua matrici oarecare
double* multiply(int N, double* A, double* B) {
    register double* result = malloc(N * N * sizeof(double));
    if (result == NULL) {
        exit(EXIT_FAILURE); 
    }

    for (register int i = 0; i < N; i++) {
        for (register int j = 0; j < N; j++) {
            register double sum = 0.0;
			// pointer pt parcurgerea liniei i a matricei A
            register double* A_ptr = A + i * N; 
			// pointer pt parcurgerea coloanei j a matricei B 
            register double* B_ptr = B + j;     

            for (register int k = 0; k < N; k++, A_ptr++, B_ptr += N) {
                sum += *A_ptr * *B_ptr;
            }
            result[i * N + j] = sum;
        }
    }
    return result;
}


// functie care aduna eficient doua matrici
double* add(int N, double* A, double* B) {
    register double* result = malloc(N * N * sizeof(double));
    if (result == NULL) {
        exit(EXIT_FAILURE); 
    }

    for (register int i = 0; i < N; i++) {
		// pointeri pt parcurgerea liniilor i ale matricilor A si B
        register double* A_ptr = A + i * N;  
        register double* B_ptr = B + i * N;  
		// pointer pt parcurgerea liniilor i ale matricei rezultat
        register double* result_ptr = result + i * N;  

        for (register int j = 0; j < N; j++, A_ptr++, B_ptr++, result_ptr++) {
            *result_ptr = *A_ptr + *B_ptr;
        }
    }
    return result;
}

/*
 * Add your optimized implementation here
 */
double* my_solver(int N, double *A, double* B) {
	printf("OPT SOLVER\n");
	// Calculul de efectuat: (At * B + B * A) * Bt

    // calculez transpusele matricilor A si B
    double* At = transpose(N, A);
    double* Bt = transpose(N, B);
    // realizez inmultirile din paranteza
    double *AB = multiply_efficient_lower_triangular(At, B, N);
    double *BA = multiply_efficient_upper_triangular(B, A, N);
    // obtin matricea finala facand suma si inmultirea finala
    double* C = add(N, AB, BA);
    double* result = multiply(N, C, Bt);
    
    free(At);
    free(Bt);
    free(AB);
    free(BA);
    free(C);
    return result;
}
