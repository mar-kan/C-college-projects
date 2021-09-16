//Kanellaki Maria Anna - 1115201400060


#include <stdio.h>
#include "maxsumrec.h"

int maxsumrec(int i, int j, int m, int ** board)
{
//(i,j) = position
// m = num of rows
    if (i == 0)                         //no more valid moves
        return board[i][j];

    else if (j == 0)
        return board[i][j] + max(maxsumrec(i-1, m-1, m, board),maxsumrec(i-1, j, m, board), maxsumrec(i-1,j+1, m, board));

    else if (j == m-1)
        return board[i][j] + max(maxsumrec(i-1, j-1, m, board),maxsumrec(i-1, j, m, board), maxsumrec(i-1,0, m, board));

    else
        return board[i][j] + max(maxsumrec(i-1, j-1, m, board),maxsumrec(i-1, j, m, board), maxsumrec(i-1,j+1, m, board));
}


void solve(int n, int m, int **board)
{
    int i, j;
    int max = 0, sum = 0;

    //print values
    printf("%d  %d\n", n, m);

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            printf("%d\t", board[i][j]);
        }
        printf("\n");
    }

    printf("\nRunning maxsumrec\n");

    for (j = 0; j < m; j++)            //for every square of last line
    {
        sum = maxsumrec(n-1, j, m, board);

        if (sum > max)
            max = sum;
    }
    printf("Max sum is %d\n", max);
}


int max(int a, int b, int c)
{
    int max = 0;

    if (a > max)
        max = a;

    if (b > max)
        max = b;

    if (c > max)
        max = c;

    return max;
}