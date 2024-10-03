#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 100
#define MAX_COLS 100
#define REQUIRED_LINES 5

int global_cols;

// Satrlar yig'indisini hisoblash funksiyasi
int row_sum(int *row, int cols) {
    int sum = 0;
    for (int i = 0; i < cols; i++) {
        sum += row[i];
    }
    return sum;
}

// Satrlarni taqqoslash funksiyasi (qsort uchun)
int compare_rows(const void *a, const void *b) {
    int sum_a = row_sum(*(int **)a, global_cols);
    int sum_b = row_sum(*(int **)b, global_cols);
    return sum_b - sum_a;  // Kamayish tartibida tartiblash
}

int main() {
    int rows = 3, cols = 3;
    int matrix[MAX_ROWS][MAX_COLS];
    int *matrix_ptrs[MAX_ROWS];
    char buffer[1000];

    // 5 qator kiritishni o'qish
    for (int i = 0; i < REQUIRED_LINES; i++) {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("n/a");
            return 1;
        }

        // Faqat 3-5 qatorlarni matritsa sifatida o'qiymiz
        if (i >= 2 && i < 5) {
            char *token = strtok(buffer, " \n");
            for (int j = 0; j < cols; j++) {
                if (token == NULL || sscanf(token, "%d", &matrix[i - 2][j]) != 1) {
                    printf("n/a");
                    return 1;
                }
                token = strtok(NULL, " \n");
            }
            matrix_ptrs[i - 2] = matrix[i - 2];
        }
    }

    global_cols = cols;

    // Satrlarni tartiblash
    qsort(matrix_ptrs, rows, sizeof(int *), compare_rows);

    // Barcha satrlarni chiqarish
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d", matrix_ptrs[i][j]);
            if (j < cols - 1) printf(" ");
        }
        if (i < rows - 1) printf("\n");
    }

    return 0;
}