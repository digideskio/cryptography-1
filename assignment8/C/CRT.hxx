#ifndef _CRT_HXX
#define _CRT_HXX 1

#include <gmpxx.h>
#include <vector>
#include "EEA.hxx"

// uses the chinese remainder theorem to calculate a y that satisfies:
// y = r_i (mod m_i) for all 1 <= i <= length(rs)
mpz_class mpz_crt (const std::vector<mpz_class> rs, const std::vector<mpz_class> ms);

// use the chinese remainder theorem to calculate y = a^x mod (m1 * ... * mn)
mpz_class mpz_crt_exp (mpz_class a, mpz_class x, const std::vector<mpz_class> ms);

#endif
