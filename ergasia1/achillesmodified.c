#include <stdio.h>
#include <time.h>
#define MAXNUM 8575

int main()
{
    int i, j, primes, num, exp, exp2, MKD, newMKD, count_achilles = 0;
    clock_t start, end;

    start = clock();

    /*y = rand(
     *z = rand(
     *x= ((ymod 32768) + 1)·((zmod 32768) + 1) + 1
     */

    for (i = 1; i <= MAXNUM; i++) {
        printf("num = %d\n", i);
        num = i;
        exp = 0;
        while (num % 2 == 0) {
            num = num / 2;
            exp++;
        }
        printf("2^%d\n", exp);
        if (exp == 1)
            continue;

        exp2 = exp;
        exp = 0;
        while (num % 3 == 0) {
            num = num / 3;
            exp++;
        }
        printf("3^%d\n", exp);
        if (exp == 1)
            continue;

        if (exp != 0 && exp2 != 0) {
            for (j = 1; j <= exp && j <= exp2; j++) {
                if (exp % j == 0 && exp2 % j == 0)
                    MKD = j;
            }
        } else {
            if (exp > exp2)
                MKD = exp;
            else
                MKD = exp2;
        }

        newMKD = MKD;

        for (primes = 5; primes * primes <= i * 2; primes = primes + 6) {
            printf("%d %d \n\n", primes, i);
            exp = 0;
            while (num % primes == 0) {
                num = num / primes;
                exp++;
            }
            printf("%d^%d\n", primes, exp);
            if (exp == 1)
                break;

            exp2 = 0;
            while (num % (primes + 2) == 0) {
                num = num / (primes + 2);
                exp2++;
            }
            printf("%d^%d\n", primes + 2, exp2);
            if (exp2 == 1)
                break;

            if (exp != 0 && exp2 != 0) {
                if (MKD) {
                    for (j = 1; j <= exp && j <= exp2 && j <= MKD; j++) {
                        if (exp % j == 0 && exp2 % j == 0 && (MKD % j == 0 || newMKD % j == 0))
                            newMKD = j;
                    }
                } else if (exp == 0) {
                    if (MKD) {
                        for (j = 1; j <= exp2 && j <= MKD; j++) {
                            {
                                if (exp2 % j == 0 && MKD % j == 0 || newMKD % j == 0)
                                    newMKD = j;
                            }
                        }
                    } else {
                        for (j = 1; j <= exp2; j++) {
                            if (exp2 % j == 0)
                                newMKD = j;
                        }
                    }
                } else if (exp2 == 0) {
                    for (j = 1; j <= exp && j <= MKD; j++) {
                        if (exp % j == 0 && MKD % j == 0 || newMKD % j == 0)
                            newMKD = j;
                    }
                }
            }
            printf("%d %d %d %d %d\n\n", newMKD, primes, i, exp, exp2);
            if (newMKD == 1 && (primes + 6) * (primes + 6) > i && exp != 1 && exp2 != 1) {
                printf("%d is achilles number\n", i);
                count_achilles++;
            }
        }
    }
    end = clock();
    printf("Found %d achilles numbers up to %d\n", count_achilles, MAXNUM);
    printf("Current time is %ld\n", (end - start) / CLOCKS_PER_SEC);
    return 0;
}