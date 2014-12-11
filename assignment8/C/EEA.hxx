#ifndef _EEA_HXX
#define _EEA_HXX 1

#include <gmpxx.h>

// Calculates the greatest common divisor of (a, b) into `gcd`
mpz_class mpz_gcd (const mpz_class a, const mpz_class b);

// Calculates d, s, t s.t.:
// (a, b) =: d = a*s + b*t
void mpz_eea (mpz_class* d, mpz_class* s, mpz_class* t,
                const mpz_class a, const mpz_class b);

// wrapper for mpz_fdiv_q
mpz_class mpz_class_fdiv_q(const mpz_class, const mpz_class);

// wrapper for mpz_fdiv_r
mpz_class mpz_class_fdiv_r(const mpz_class, const mpz_class);

// wrapper for mpz_fdiv_qr
void mpz_class_fdiv_qr(mpz_class*, mpz_class*, const mpz_class, const mpz_class);

#endif
