#include "CRT.hxx"

mpz_class mpz_crt_worker (std::vector<mpz_class>, std::vector<mpz_class>, int, mpz_class);
mpz_class mpz_product(std::vector<mpz_class>, int, int);

mpz_class mpz_crt (const std::vector<mpz_class> rs, const std::vector<mpz_class> ms)
{
    int rlen = (int) rs.size();
    int mlen = (int) ms.size();
    int len = rlen <= mlen ? rlen : mlen;

    return mpz_crt_worker(rs, ms, len - 1, mpz_product(ms, 0, len));
}

mpz_class mpz_crt_worker (const std::vector<mpz_class> rs,
                          const std::vector<mpz_class> ms,
                          int index,
                          mpz_class product)
{
    if (index < 0)
    {
        return 0;
    }

    mpz_class a = rs[index];
    mpz_class b = ms[index];

    if (index == 0)
    {
        return mpz_class_fdiv_r(a, b);
    }

    product = product / b;
    mpz_class previous_result = mpz_crt_worker(rs, ms, index-1, product);

    mpz_class d = 0, s = 0, t = 0;
    mpz_eea(&d, &s, &t, product, b);

    mpz_class v = s * product;
    mpz_class u = t * b;
    mpz_class x = previous_result * u + a * v;

    return mpz_class_fdiv_r(x, b * product);
}

// end is exclusive
mpz_class mpz_product(const std::vector<mpz_class> v, int start, int end)
{
    mpz_class result = 1;
    for(int i = start; i < end; i++)
    {
        result *= v[i];
    }
    return result;
}
