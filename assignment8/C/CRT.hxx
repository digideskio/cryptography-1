#ifndef _CRT_HXX
#define _CRT_HXX 1

#include <gmpxx.h>
#include <vector>
#include "EEA.hxx"

mpz_class mpz_crt (std::vector<mpz_class>, std::vector<mpz_class>);

#endif
