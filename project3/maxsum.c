//Kanellaki Maria Anna - 1115201400060


#include <stdio.h>
#include <stdlib.h>
#include "maxsumrec.h"
#include "maxsummem.h"
#include "maxsumdp.h"

int main()
{
    int n, m, i, j;

    //input number of rows
    scanf("%d", &n);
    if (n < 1)              //invalid num
        return -1;

    //input number of columns
    scanf("%d", &m);
    if (m < 1)              //invalid num
        return -1;

    //define array
    int **board = (int **) malloc(n * sizeof(int*));

    for (i = 0; i < n; i++)
    {
        board[i] = (int *) malloc(m * sizeof(int));
    }

    //input board
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            scanf("%d", &board[i][j]);
        }
    }
    solve(n, m, board);

    for (i = 0; i < n; i++)
        free(board[i]);

    free(board);
    return 0;
}