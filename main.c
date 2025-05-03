#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

int sudoku[9][9] = {
    {6, 2, 4, 5, 3, 9, 1, 8, 7},
    {5, 1, 9, 7, 2, 8, 6, 3, 4},
    {8, 3, 7, 6, 1, 4, 2, 9, 5},
    {1, 4, 3, 8, 6, 5, 7, 2, 9},
    {9, 5, 8, 2, 4, 7, 3, 6, 1},
    {7, 6, 2, 3, 9, 1, 4, 5, 8},
    {3, 7, 1, 9, 5, 6, 8, 4, 2},
    {4, 9, 6, 1, 8, 2, 5, 7, 3},
    {2, 8, 5, 4, 7, 3, 9, 1, 6}
};

bool row_flag = false, col_flag = false, subgrid_flag = false;

void *check_rows(void *a) {
    for (int i = 0; i < 9; i++) {
        int seen[9] = {0};
        for (int j = 0; j < 9; j++) {
            int num = sudoku[i][j];
            if (seen[num - 1]++) {
                row_flag = true;
                return NULL;
            }
        }
    }
    return NULL;
}

void *check_cols(void *a) {
    for (int j = 0; j < 9; j++) {
        int seen[9] = {0};
        for (int i = 0; i < 9; i++) {
            int num = sudoku[i][j];
            if (seen[num - 1]++) {
                col_flag = true;
                return NULL;
            }
        }
    }
    return NULL;
}

typedef struct {
    int row;
    int col;
} parameters;

void *check_subgrid(void *param) {
    parameters *p = (parameters *)param;
    int seen[9] = {0};
    for (int i = p->row; i < p->row + 3; i++) {
        for (int j = p->col; j < p->col + 3; j++) {
            int num = sudoku[i][j];
            if (seen[num - 1]++) {
                subgrid_flag = true;
                free(p);
                return NULL;
            }
        }
    }
    free(p);
    return NULL;
}

int main() {
    pthread_t row_thread, col_thread, subgrid_threads[9];

    // Create row and column threads
    pthread_create(&row_thread, NULL, check_rows, NULL);
    pthread_create(&col_thread, NULL, check_cols, NULL);

    // Create subgrid threads
    int thread_index = 0;
    for (int i = 0; i < 9; i += 3) {
        for (int j = 0; j < 9; j += 3) {
            parameters *data = (parameters *)malloc(sizeof(parameters));
            data->row = i;
            data->col = j;
            pthread_create(&subgrid_threads[thread_index++], NULL, check_subgrid, data);
        }
    }

    // Wait for threads to finish
    pthread_join(row_thread, NULL);
    pthread_join(col_thread, NULL);
    for (int i = 0; i < 9; i++) {
        pthread_join(subgrid_threads[i], NULL);
    }

    // Final result
    if (row_flag || col_flag || subgrid_flag)
        printf("Invalid Sudoku Solution.\n");
    else
        printf("Valid Sudoku Solution.\n");

    return 0;
}
