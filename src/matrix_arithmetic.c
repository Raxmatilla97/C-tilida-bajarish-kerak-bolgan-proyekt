#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

int input(int **matrix, int *n, int *m);
void output(int **matrix, int n, int m);
int sum(int **matrix_first, int n_first, int m_first, int **matrix_second, int n_second, int m_second,
        int **matrix_result, int *n_result, int *m_result);
int transpose(int **matrix, int n, int m);
int mul(int **matrix_first, int n_first, int m_first, int **matrix_second, int n_second, int m_second,
        int **matrix_result, int *n_result, int *m_result);

int main() {
    int operation;
    if (scanf("%d", &operation) != 1 || operation < 1 || operation > 3) {
        printf("n/a\n");
        return 1;
    }

    int **matrix1 = (int **)malloc(MAX_SIZE * sizeof(int *));
    int **matrix2 = (int **)malloc(MAX_SIZE * sizeof(int *));
    int **result = (int **)malloc(MAX_SIZE * sizeof(int *));
    for (int i = 0; i < MAX_SIZE; i++) {
        matrix1[i] = (int *)malloc(MAX_SIZE * sizeof(int));
        matrix2[i] = (int *)malloc(MAX_SIZE * sizeof(int));
        result[i] = (int *)malloc(MAX_SIZE * sizeof(int));
    }

    int n1, m1, n2, m2, n_result, m_result;

    if (input(matrix1, &n1, &m1) == 0) {
        if (operation == 1 || operation == 2) {
            if (input(matrix2, &n2, &m2) == 0) {
                if (operation == 1) {
                    if (sum(matrix1, n1, m1, matrix2, n2, m2, result, &n_result, &m_result) == 0) {
                        output(result, n_result, m_result);
                    } else {
                        printf("n/a\n");
                    }
                } else {  // operation == 2
                    if (mul(matrix1, n1, m1, matrix2, n2, m2, result, &n_result, &m_result) == 0) {
                        output(result, n_result, m_result);
                    } else {
                        printf("n/a\n");
                    }
                }
            } else {
                printf("n/a\n");
            }
        } else {  // operation == 3
            if (transpose(matrix1, n1, m1) == 0) {
                output(matrix1, m1, n1);
            } else {
                printf("n/a\n");
            }
        }
    } else {
        printf("n/a\n");
    }

    for (int i = 0; i < MAX_SIZE; i++) {
        free(matrix1[i]);
        free(matrix2[i]);
        free(result[i]);
    }
    free(matrix1);
    free(matrix2);
    free(result);

    return 0;
}

int input(int **matrix, int *n, int *m) {
    if (scanf("%d %d", n, m) != 2 || *n <= 0 || *m <= 0 || *n > MAX_SIZE || *m > MAX_SIZE) {
        return 1;
    }
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *m; j++) {
            if (scanf("%d", &matrix[i][j]) != 1) {
                return 1;
            }
        }
    }
    return 0;
}

void output(int **matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d", matrix[i][j]);
            if (j < m - 1) printf(" ");
        }
        if (i < n - 1) printf("\n");
    }
}

int sum(int **matrix_first, int n_first, int m_first, int **matrix_second, int n_second, int m_second,
        int **matrix_result, int *n_result, int *m_result) {
    if (n_first != n_second || m_first != m_second) {
        return 1;
    }
    *n_result = n_first;
    *m_result = m_first;
    for (int i = 0; i < *n_result; i++) {
        for (int j = 0; j < *m_result; j++) {
            matrix_result[i][j] = matrix_first[i][j] + matrix_second[i][j];
        }
    }
    return 0;
}

int transpose(int **matrix, int n, int m) {
    int **temp = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++) {
        temp[i] = (int *)malloc(n * sizeof(int));
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            temp[j][i] = matrix[i][j];
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = temp[i][j];
        }
    }
    for (int i = 0; i < m; i++) {
        free(temp[i]);
    }
    free(temp);
    return 0;
}

int mul(int **matrix_first, int n_first, int m_first, int **matrix_second, int n_second, int m_second,
        int **matrix_result, int *n_result, int *m_result) {
    if (m_first != n_second) {
        return 1;
    }
    *n_result = n_first;
    *m_result = m_second;
    for (int i = 0; i < *n_result; i++) {
        for (int j = 0; j < *m_result; j++) {
            matrix_result[i][j] = 0;
            for (int k = 0; k < m_first; k++) {
                matrix_result[i][j] += matrix_first[i][k] * matrix_second[k][j];
            }
        }
    }
    return 0;
}