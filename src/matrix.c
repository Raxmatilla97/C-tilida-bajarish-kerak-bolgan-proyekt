#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Statik usul
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
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d", matrix[i][j]);
            if (j < cols - 1) printf(" ");
        }
        if (i < rows - 1) printf("\n");
    }
}

// Dinamik usul 1: Bir o'lchamli massiv
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
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d", matrix[i * cols + j]);
            if (j < cols - 1) printf(" ");
        }
        if (i < rows - 1) printf("\n");
    }
    free(matrix);
}

// Dinamik usul 2: Ko'rsatkichlar massivi
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
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d", matrix[i][j]);
            if (j < cols - 1) printf(" ");
        }
        if (i < rows - 1) printf("\n");
    }
    for (int i = 0; i < rows; i++) free(matrix[i]);
    free(matrix);
}

// Dinamik usul 3: Bir o'lchamli massiv va ko'rsatkichlar massivi
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
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d", matrix[i][j]);
            if (j < cols - 1) printf(" ");
        }
        if (i < rows - 1) printf("\n");
    }
    free(matrix);
    free(data);
}

int main() {
    int choice, rows, cols;
    printf("Choose allocation method:\n");
    printf("1. Static allocation\n");
    printf("2. Dynamic allocation (1D array)\n");
    printf("3. Dynamic allocation (array of pointers)\n");
    printf("4. Dynamic allocation (1D array + array of pointers)\n");
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