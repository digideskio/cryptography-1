#include "CRT.hxx"
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

// throws a compile time error if used since somehow gmp_randclass is private
// gets random numbers in the range {2^(n-1), 2^n - 1}
mpz_class get_z_bits1(gmp_randclass rand, mp_bitcnt_t n)
{
    mpz_class lower_bits = rand.get_z_bits(n - 1);
    mpz_setbit(lower_bits.get_mpz_t(), n-1);
    return lower_bits;
}

void test(int, int);

int main (int argc, char const *argv[])
{
    test(1024, 100);
    test(2048, 50);
    test(4096, 20);
    return 0;
}

void test(int bits, int test_count)
{
    // initialize random
    gmp_randclass rand (gmp_randinit_mt);

    ifstream f("/dev/urandom");
    unsigned int seed;
    f.read(reinterpret_cast<char*>(&seed), sizeof(seed));

    rand.seed(seed);
    clock_t times1 = 0, times2 = 0;

    printf("Running %d tests for N = %d\n", test_count, bits);

    for(int i = 0; i < test_count; i++)
    {
        mpz_class m1, m2, a, x, prod;
        clock_t begin, end;

        do {
            m1 = rand.get_z_bits(bits - 1);
            mpz_setbit(m1.get_mpz_t(), bits-1);

            m2 = rand.get_z_bits(bits - 1);
            mpz_setbit(m2.get_mpz_t(), bits-1);

            a = rand.get_z_bits(bits);
            mpz_setbit(a.get_mpz_t(), bits);

            x = rand.get_z_bits(bits);
            mpz_setbit(x.get_mpz_t(), bits);

            prod = m1 * m2;
        } while(cmp(mpz_gcd(m1, m2), 1) || (cmp(a, prod) > 0) || (cmp(x, prod) > 0));


        vector<mpz_class> ms = {m1, m2};

        begin = clock();
        mpz_class result = mpz_crt_exp(a, x, ms);
        end = clock();
        times1 += end - begin;


        mpz_class expected = 0;
        begin = clock();
        mpz_powm(expected.get_mpz_t(), a.get_mpz_t(), x.get_mpz_t(), prod.get_mpz_t());
        end = clock();
        times2 += end - begin;

        if(cmp(result, expected))
        {
            printf("Results not equal!");
            cout << result.get_str() << endl;
            cout << expected.get_str() << endl;
        }
    }


    printf("Time spent using own algorithm: %f\n", ((double) times1) / CLOCKS_PER_SEC);
    printf("Time spent using GMP algorithm: %f\n", ((double) times2) / CLOCKS_PER_SEC);
    printf("Speed-up: %f\n", ((double) times2) / ((double) times1));
}
