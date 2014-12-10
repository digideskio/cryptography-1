#include "CRT.hxx"
#include <iostream>

using namespace std;
int main (int argc, char const *argv[])
{
    int a = 13;
    int x = 1234;
    int m = 105;

    vector<mpz_class> rs = {1, 4, 1};
    vector<mpz_class> ms = {3, 5, 7};

    mpz_class y = mpz_crt(rs, ms);

    char* str_y = mpz_get_str(NULL, 10, y.get_mpz_t());

    printf("(%d ^ %d) %% %d = %s\n", a, x, m, str_y);

    free(str_y);

    return 0;
}
