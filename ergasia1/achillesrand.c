#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define MAXNUM 10000000
#define COMPUTATIONS 1000

int main()
{
    int i, j, primes, num, number, exp, exp2, GCD, calcGCD, count = 0;
    clock_t start, end;
    long primesl;
    int overflow;                                                        //flag to check if there is overflow
    start = clock();
    srand(time(0));

    for (i = 1; i <= COMPUTATIONS; i++)
    {
        int y = rand() % 32768 + 1;                                     //calculate num
        int z = rand() % 32768 + 1;
        number = y*z + 1;
        num = number;
printf("%d\n", number);
        exp = 0;
        while (num % 2 == 0)                                            //find exponent of number 2
        {
            num = num / 2;
            exp++;
        }

        if (exp == 1)
            continue;

        exp2 = 0;
        while (num % 3 == 0)                                            //find exponent of number 3
        {
            num = num / 3;
            exp2++;
        }
        if (exp2 == 1)
            continue;

        if (!exp && !exp2)                                              //find greater common divider for exponents of 2, 3
            GCD = 0;
        else if (!exp)
            GCD = exp2;
        else if (!exp2)
            GCD = exp;
        else
        {
            for(j = 1; j <= exp && j <= exp2; j++)
            {
                if(exp % j == 0 && exp2 % j == 0)
                    GCD = j;
            }
        }
        calcGCD = GCD;

        for (primes = 5; primes/1000 <= number/primes; primes = primes + 6)   //find prime dividers and exponents
        {                                                                     //added /1000 in primes*primes because otherwise it left out large prime dividers

            if (primes/1000000 > INT_MAX / primes)                             //checking overflow
            {                                                                 //same implementation as below but with long numbers
                primesl = primes;

                exp = 0;
                while (num % primesl == 0)
                {
                    num = num / primesl;
                    exp++;
                }
                if (exp == 1)
                    break;

                exp2 = 0;
                while (num % (primesl + 2) == 0)
                {
                    num = num / (primesl + 2);
                    exp2++;
                }
                if (exp2 == 1)
                    break;
            }
            else
            {
                exp = 0;
                while (num % primes == 0)
                {
                    num = num / primes;
                    exp++;
                }
                if (exp == 1)
                    break;

                exp2 = 0;
                while (num % (primes + 2) == 0)
                {
                    num = num / (primes + 2);
                    exp2++;
                }
                if (exp2 == 1)
                    break;
            }

            if (!exp && !exp2)                                              //find greater common divider for all exponents
                continue;

            else if (!exp)
            {
                if (GCD)
                {
                    for (j = 1; j <= GCD && j <= exp2; j++)
                    {
                        if (GCD % j == 0 && exp2 % j == 0)
                            calcGCD = j;
                    }
                    GCD = calcGCD;
                }
                else
                {
                    if (calcGCD)
                    {
                        GCD = calcGCD;
                        for (j = 1; j <= GCD && j <= exp2; j++)
                        {
                            if (GCD % j == 0 && exp2 % j == 0)
                                calcGCD = j;
                        }
                        GCD = calcGCD;
                    }
                    else
                        calcGCD = exp2;
                }
            }
            else if (!exp2)
            {
                if (GCD)
                {
                    for (j = 1; j <= GCD && j <= exp; j++)
                    {
                        if (GCD % j == 0 && exp % j == 0)
                            calcGCD = j;
                    }
                    GCD = calcGCD;
                }
                else
                {
                    if (calcGCD)
                    {
                        GCD = calcGCD;
                        for (j = 1; j <= GCD && j <= exp; j++)
                        {
                            if (GCD % j == 0 && exp % j == 0)
                                calcGCD = j;
                        }
                        GCD = calcGCD;
                    }
                    else
                        calcGCD = exp;
                }
            }
            else
            {
                if (GCD)
                {
                    for (j = 1; j <= exp && j <= exp2 && j <= GCD; j++)
                    {
                        if (exp % j == 0 && exp2 % j == 0 && GCD % j == 0)
                            calcGCD = j;
                    }
                    GCD = calcGCD;
                }
                else
                {
                    if (calcGCD)
                    {
                        GCD = calcGCD;
                        for (j = 1; j <= GCD && j <= exp && j <= exp2; j++)
                        {
                            if (GCD % j == 0 && exp % j == 0 && exp2 % j == 0)
                                calcGCD = j;
                        }
                        GCD = calcGCD;
                    } else
                    {
                        for (j = 1; j <= exp && j <= exp2; j++)
                        {
                            if (exp % j == 0 && exp2 % j == 0)
                                calcGCD = j;
                        }
                        GCD = calcGCD;
                    }
                }
            }
            if (num == 1)
                break;

        }
//printf ("Num = %d and Last prime = %d\n", num, primes);
        if (calcGCD == 1 && exp != 1 && exp2 != 1)
        {
            printf("%d is Αchilles number\n", num);
            count++;
        }
    }
    end = clock();
    printf("Found %d Αchilles numbers out of %d tested numbers\n", count, COMPUTATIONS);
    printf("Current time is %ld\n", (end - start) / CLOCKS_PER_SEC);
    return 0;
}