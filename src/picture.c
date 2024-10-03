#include <stdio.h>

#define N 15
#define M 13

void transform(int *buf, int **matr, int n, int m);
void make_picture(int **picture, int n, int m);
void reset_picture(int **picture, int n, int m);

int main() {
    int picture_data[N][M];
    int *picture[N];
    transform((int *)picture_data, picture, N, M);
    make_picture(picture, N, M);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d", picture[i][j]);
            if (j < M - 1) printf(" ");
        }
        printf("\n");
    }
    return 0;
}

void make_picture(int **picture, int n, int m) {
    reset_picture(picture, n, m);

    // Ramkani chizish
    for (int i = 0; i < m; i++) {
        picture[0][i] = 1;      // Yuqori ramka
        picture[7][i] = 1;      // O'rta ramka
        picture[n - 1][i] = 1;  // Pastki ramka
    }
    for (int i = 0; i < n; i++) {
        picture[i][0] = 1;      // Chap ramka
        picture[i][6] = 1;      // O'rta vertikal ramka
        picture[i][m - 1] = 1;  // O'ng ramka
    }

    for (int i = 0; i < 4; i++) {
        picture[8 + i][3] = 7;
        picture[8 + i][4] = 7;
    }
    picture[10][2] = 7;
    picture[10][3] = 7;
    picture[10][4] = 7;
    picture[10][5] = 7;

    for (int i = 0; i < 4; i++) {
        picture[2][2 + i] = 3;
        picture[3][1 + i] = 3;
        picture[4][1 + i] = 3;
        picture[5][2 + i] = 3;
    }

    int sun[6][5] = {{0, 6, 6, 6, 6}, {0, 0, 6, 6, 6}, {0, 0, 6, 6, 6},
                     {0, 6, 0, 0, 6}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}};
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 5; j++) {
            picture[i + 1][j + 7] = sun[i][j];
        }
    }
}

void reset_picture(int **picture, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            picture[i][j] = 0;
        }
    }
}

void transform(int *buf, int **matr, int n, int m) {
    for (int i = 0; i < n; i++) {
        matr[i] = buf + i * m;
    }
}
