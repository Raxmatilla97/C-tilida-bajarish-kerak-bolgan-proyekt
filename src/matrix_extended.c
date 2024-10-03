#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

void find_max_min(int *data, int rows, int cols, int *max_rows, int *min_cols) {
    for (int i = 0; i < rows; i++) {
        max_rows[i] = INT_MIN;
        for (int j = 0; j < cols; j++) {
            if (i == 0 || data[i * cols + j] < min_cols[j]) {
                min_cols[j] = data[i * cols + j];
            }
            if (data[i * cols + j] > max_rows[i]) {
                max_rows[i] = data[i * cols + j];
            }
        }
    }
}

void print_matrix_and_stats(int *data, int rows, int cols) {
    int max_rows[MAX_SIZE], min_cols[MAX_SIZE];
    for (int j = 0; j < cols; j++) min_cols[j] = INT_MAX;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d", data[i * cols + j]);
            if (j < cols - 1) printf(" ");
        }
        if (i < rows - 1) printf("\n");
    }
    printf("\n");

    find_max_min(data, rows, cols, max_rows, min_cols);

    for (int i = 0; i < rows; i++) {
        printf("%d", max_rows[i]);
        if (i < rows - 1) printf(" ");
    }
    printf("\n");
    for (int j = 0; j < cols; j++) {
        printf("%d", min_cols[j]);
        if (j < cols - 1) printf(" ");
    }
}

void static_alloc(int rows, int cols) {
    static int matrix[MAX_SIZE][MAX_SIZE];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (scanf("%d", &matrix[i][j]) != 1) {
                printf("n/a");
                return;
            }
        }
    }
    print_matrix_and_stats((int *)matrix, rows, cols);
}

void dynamic_alloc_1(int rows, int cols) {
    int *matrix = (int *)malloc(rows * cols * sizeof(int));
    if (matrix == NULL) {
        printf("n/a");
        return;
    }
    for (int i = 0; i < rows * cols; i++) {
        if (scanf("%d", &matrix[i]) != 1) {
            printf("n/a");
            free(matrix);
            return;
        }
    }
    print_matrix_and_stats(matrix, rows, cols);
    free(matrix);
}

void dynamic_alloc_2(int rows, int cols) {
    int **matrix = (int **)malloc(rows * sizeof(int *));
    if (matrix == NULL) {
        printf("n/a");
        return;
    }
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            for (int j = 0; j < i; j++) free(matrix[j]);
            free(matrix);
            printf("n/a");
            return;
        }
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (scanf("%d", &matrix[i][j]) != 1) {
                for (int k = 0; k < rows; k++) free(matrix[k]);
                free(matrix);
                printf("n/a");
                return;
            }
        }
    }
    print_matrix_and_stats((int *)matrix[0], rows, cols);
    for (int i = 0; i < rows; i++) free(matrix[i]);
    free(matrix);
}

void dynamic_alloc_3(int rows, int cols) {
    int **matrix = (int **)malloc(rows * sizeof(int *));
    int *data = (int *)malloc(rows * cols * sizeof(int));
    if (matrix == NULL || data == NULL) {
        free(matrix);
        free(data);
        printf("n/a");
        return;
    }
    for (int i = 0; i < rows; i++) {
        matrix[i] = &data[i * cols];
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (scanf("%d", &matrix[i][j]) != 1) {
                free(matrix);
                free(data);
                printf("n/a");
                return;
            }
        }
    }
    print_matrix_and_stats(data, rows, cols);
    free(matrix);
    free(data);
}

int main() {
    int choice, rows, cols;
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > 4) {
        printf("n/a");
        return 1;
    }
    if (scanf("%d %d", &rows, &cols) != 2 || rows <= 0 || cols <= 0 ||
        (choice == 1 && (rows > MAX_SIZE || cols > MAX_SIZE))) {
        printf("n/a");
        return 1;
    }
    switch (choice) {
        case 1:
            static_alloc(rows, cols);
            break;
        case 2:
            dynamic_alloc_1(rows, cols);
            break;
        case 3:
            dynamic_alloc_2(rows, cols);
            break;
        case 4:
            dynamic_alloc_3(rows, cols);
            break;
    }
    return 0;
}
