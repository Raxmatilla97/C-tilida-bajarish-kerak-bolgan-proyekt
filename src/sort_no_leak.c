#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 1000

void bubble_sort(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    char input[MAX_INPUT_LENGTH];
    int n;
    int *arr = NULL;
    int count = 0;

    if (!fgets(input, sizeof(input), stdin)) {
        printf("n/a");
        return 1;
    }

    char *token = strtok(input, " \n");
    if (token == NULL || sscanf(token, "%d", &n) != 1 || n <= 0) {
        printf("n/a");
        return 1;
    }

    arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("n/a");
        return 1;
    }

    while (token != NULL && count < n) {
        token = strtok(NULL, " \n");
        if (token != NULL) {
            if (sscanf(token, "%d", &arr[count]) != 1) {
                printf("n/a");
                free(arr);
                return 1;
            }
            count++;
        }
    }

    // Agar barcha elementlar birinchi qatorda bo'lmasa, qo'shimcha qatorlarni o'qish
    while (count < n && fgets(input, sizeof(input), stdin)) {
        token = strtok(input, " \n");
        while (token != NULL && count < n) {
            if (sscanf(token, "%d", &arr[count]) != 1) {
                printf("n/a");
                free(arr);
                return 1;
            }
            count++;
            token = strtok(NULL, " \n");
        }
    }

    if (count != n) {
        printf("n/a");
        free(arr);
        return 1;
    }

    bubble_sort(arr, n);

    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(" ");
    }

    free(arr);
    return 0;
}