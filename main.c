#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

// Function prototypes
void fib_fast_doubling(int n, mpz_t result);
void fib_fast_doubling_recursive(int n, mpz_t Fn, mpz_t FnPlus1);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        printf("Please enter a positive integer greater than zero.\n");
        return 1;
    }

    mpz_t result;
    mpz_init(result);

    // Calculate Fibonacci using fast doubling
    fib_fast_doubling(n, result);

    // Print result
    printf("Fibonacci number at position %d is: ", n);
    gmp_printf("%Zd\n", result);

    mpz_clear(result);

    return 0;
}

void fib_fast_doubling(int n, mpz_t result) {
    mpz_t FnPlus1;
    mpz_init(result);
    mpz_init(FnPlus1);
    fib_fast_doubling_recursive(n, result, FnPlus1);
    mpz_clear(FnPlus1);
}

void fib_fast_doubling_recursive(int n, mpz_t Fn, mpz_t FnPlus1) {
    if (n == 0) {
        mpz_set_ui(Fn, 0);
        mpz_set_ui(FnPlus1, 1);
        return;
    }

    mpz_t Fk, FkPlus1, temp, temp2;
    mpz_init(Fk);
    mpz_init(FkPlus1);
    mpz_init(temp);
    mpz_init(temp2);

    fib_fast_doubling_recursive(n / 2, Fk, FkPlus1);

    // F(2k) = Fk * [2Fk+1 − Fk]
    mpz_mul_ui(temp, FkPlus1, 2);       // temp = 2*Fk+1
    mpz_sub(temp, temp, Fk);            // temp = 2*Fk+1 - Fk
    mpz_mul(Fn, Fk, temp);              // Fn = Fk * temp

    // F(2k+1) = Fk+1^2 + Fk^2
    mpz_mul(temp, FkPlus1, FkPlus1);    // temp = Fk+1^2
    mpz_mul(temp2, Fk, Fk);             // temp2 = Fk^2
    mpz_add(FnPlus1, temp, temp2);      // FnPlus1 = temp + temp2

    if (n & 1) {
        // For odd n, adjust the result
        mpz_set(temp, FnPlus1);
        mpz_set(FnPlus1, Fn);
        mpz_add(FnPlus1, FnPlus1, temp);
        mpz_set(Fn, temp);
    }

    mpz_clear(Fk);
    mpz_clear(FkPlus1);
    mpz_clear(temp);
    mpz_clear(temp2);
}
