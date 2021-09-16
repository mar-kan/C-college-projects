//Kanellaki Maria Anna - 1115201400060

#include <stdio.h>
#include <stdlib.h>
#include "maxsummem.h"


int maxsummem(int i, int j, int m, int ** board, int **sums)
{
    //(i,j) = position
    // m = num of rows

    if (j == 0)
    {
        if ((sums[i-1][m-1] != -1)&&(sums[i-1][j] != -1)&&(sums[i-1][j+1] != -1))
            sums[i][j] = board[i][j] + max(sums[i-1][m-1], sums[i-1][j], sums[i-1][j+1]);
        else
            return (sums[i][j] = board[i][j] + max(maxsummem(i-1, m-1, m, board, sums),maxsummem(i-1, j, m, board, sums), maxsummem(i-1,j+1, m, board, sums)));
    }
    else if (j == m-1)
    {
        if ((sums[i-1][j-1] != -1)&&(sums[i-1][j] != -1)&&(sums[i-1][0]!= -1))
            sums[i][j] = board[i][j] + max(sums[i-1][j-1], sums[i-1][j], sums[i-1][0]);
        else
            return (sums[i][j] = board[i][j] + max(maxsummem(i-1, j-1, m, board, sums),maxsummem(i-1, j, m, board, sums), maxsummem(i-1,0, m, board, sums)));
    }

    else
    {
        if ((sums[i-1][j-1]!= -1)&&(sums[i-1][j]!= -1)&&(sums[i-1][j+1]!= -1))
            sums[i][j] = board[i][j] + max(sums[i-1][j-1], sums[i-1][j], sums[i-1][j+1]);

        else
            return (sums[i][j] = board[i][j] + max(maxsummem(i-1, j-1, m, board, sums),maxsummem(i-1, j, m, board, sums), maxsummem(i-1,j+1, m, board, sums)));
    }

    return sums[i][j];
}


void solve(int n, int m, int **board)
{
    int i, j;
    int maxSum = 0, sum = 0;

    //print values
    printf("%d  %d\n", n, m);

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
            printf("%d\t", board[i][j]);

        printf("\n");
    }

    //define new array
    int **sums = (int **) malloc(n * sizeof(int *));

    for (i = 0; i < n; i++)
        sums[i] = (int *) malloc(m * sizeof(int));

    //initialize sums
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            if (i == 0)
                sums[i][j] = board[i][j];
            else
                sums[i][j] = -1;
        }
    }

    printf("\nRunning maxsummem\n");

    for (j = 0; j < m; j++)            //for every square of last line
    {
        sum = maxsummem(n - 1, j, m, board, sums);  //starting from last square

        if (sum > maxSum)
            maxSum = sum;
    }
    printf("Max sum is %d\n", maxSum);

#if defined(PATH)

    //find row of max sum
    for (j = 0; j<m; j++)
    {
        if (sums[n-1][j] == maxSum)
            break;
    }

    //because my sums array is backwards, i created a new array to store the path and print it in order
    //the array is dynamic allocated so that it can be freed from the memory
    int * path = malloc(n * sizeof(int));

    //calculate path
    path[n-1] = board[n-1][j];

    for (i=n-1; i>0; i--)
    {
        if (j == 0)
        {
            maxSum = max(sums[i-1][m-1],sums[i-1][j],sums[i-1][j+1]);

            if (maxSum == sums[i-1][m-1])
                j = m-1;
            else if (maxSum == sums[i-1][j+1])
                j++;
        }
        else if (j == m-1)
        {
            maxSum = max(sums[i-1][j-1],sums[i-1][j],sums[i-1][0]);

            if (maxSum == sums[i-1][j-1])
                j = j-1;
            else if (maxSum == sums[i-1][0])
                j = 0;
        }
        else
        {
            maxSum = max(sums[i-1][j-1],sums[i-1][j],sums[i-1][j+1]);

            if (maxSum == sums[i-1][j-1])
                j = j-1;
            else if (maxSum == sums[i-1][j+1])
                j++;
        }

        path[i-1] = board[i-1][j];
    }

    //print path
    for (i=0; i<n; i++)
    {
        if (i == n-1)
            printf("%d\n", path[i]);
        else
            printf("%d -> ",path[i]);
    }

    free(path);
#endif

    for (i=0; i<n; i++)
        free(sums[i]);

    free(sums);
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