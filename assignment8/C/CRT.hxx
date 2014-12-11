#ifndef _CRT_HXX
#define _CRT_HXX 1

#include <gmpxx.h>
#include <vector>
#include "EEA.hxx"

mpz_class mpz_crt (const std::vector<mpz_class>, const std::vector<mpz_class>);
mpz_class mpz_crt_exp (mpz_class a, mpz_class x, const std::vector<mpz_class> ms);

#endif
