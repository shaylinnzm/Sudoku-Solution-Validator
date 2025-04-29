#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
void *check_rows(void *a)
{
    for (int i = 0; i < 9; i++)
    {
        int seen_count[9] = {0};
        for (int j = 0; j < 9; j++)
        {
            if (seen_count[sudoku[i][j] - 1] > 0){
                row_flag = true;
                break;
            }
            else {
                seen_count[sudoku[i][j] - 1]++;
            }

        }
        if (row_flag){
            break;
        }
    }
    return NULL;
}

void *check_cols(void *a)
{
    for (int j = 0; j < 9; j++)
    {
        int seen_count[9] = {0};
        for (int i = 0; i < 9; i++)
        {
            if (seen_count[sudoku[i][j] - 1] > 0){
                col_flag = true;
                break;
            }
            else {
                seen_count[sudoku[i][j] - 1]++;
            }

        }
        if (col_flag){
            break;
        }
    }
    return NULL;
}

void *check_subgrids(void *a)
{
    for (int rows = 0; rows < 9; rows += 3)
    {
        for (int cols = 0; cols < 9; cols++)
        {
            int seen_count[9] = {0};
            for (int i = rows; i < rows + 3; i++)
            {
                for (int j = cols; j < cols; j++)
                {
                    if (seen_count[sudoku[i][j] - 1] > 0){
                        subgrid_flag = true;
                        break;
                    }
                    else {
                        seen_count[sudoku[i][j] - 1]++;
                    }
                }
                if (subgrid_flag){ break; }

            }if (subgrid_flag){ break; }

        }if (subgrid_flag){ break; }

    }
    return NULL;
}
int main()
{
    printf("");
    return 0;
}
