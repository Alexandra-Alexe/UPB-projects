/*
 * Tema 2 ASC
 * 2024 Spring
 */
#include "utils.h"

// functie ce transpune o matrice
double* transpose(int N, double* A) {
    double* At = malloc(N * N * sizeof(double));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            At[j * N + i] = A[i * N + j];
        }
    }
    return At;
}

// functie ce inmulteste eficient o matrice inferior triunghiulara cu una oarecare
double* multiply_efficient_lower_triangular(double* A, double* B, int N) {
    double* result = malloc(N * N * sizeof(double));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) { 
            double sum = 0.0;
            for (int k = 0; k <= i; k++) {
                sum += A[i * N + k] * B[k * N + j]; 
            }
            result[i * N + j] = sum;
        }
    }
    return result;
}

// functie ce inmulteste eficient o matrice oarecare cu una superior triunghiulara
double* multiply_efficient_upper_triangular(double* A, double* B, int N) {
    double* result = malloc(N * N * sizeof(double));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            double sum = 0.0;
            for (int k = 0; k <= j; k++) {
                sum += A[i * N + k] * B[k * N + j];
            }
            result[i * N + j] = sum;
        }
    }
    return result;
}

// functie ce inmulteste doua matrici oarecare
double* multiply(int N, double* A, double* B) {
    double* result = malloc(N * N * sizeof(double));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            double sum = 0.0;
            for (int k = 0; k < N; k++) {
                sum += A[i * N + k] * B[k * N + j];
            }
            result[i * N + j] = sum;
        }
    }
    return result;
}

// functie care aduna doua matrici
double* add(int N, double* A, double* B) {
    double* result = malloc(N * N * sizeof(double));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            result[i * N + j] = A[i * N + j] + B[i * N + j];
        }
    }
    return result;
}

/*
 * Add your unoptimized implementation here
 */
double* my_solver(int N, double *A, double* B) {
    // Calculul de efectuat: (At * B + B * A) * Bt
	printf("NEOPT SOLVER\n");

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
