#include "EEA.hxx"

// internal function declarations
mpz_class mpz_gcd_worker (const mpz_class, const mpz_class);
void mpz_eea_worker (mpz_class*, mpz_class*, mpz_class*, const mpz_class, const mpz_class);

/* Exported Functions */

// Calculates the greatest common divisor of (a, b) into `gcd`
mpz_class mpz_gcd (const mpz_class a, const mpz_class b)
{
    mpz_class a_abs, b_abs;
    a_abs = abs(a);
    b_abs = abs(b);
    return mpz_gcd_worker(a_abs, b_abs);
}

// | On input a, b, calculates the greatest common
// divisor d and integers s and t that satisfy
// > d = a*s + b*t
// > extendedEuclidean a b = (d, s, t)
void mpz_eea (mpz_class* d, mpz_class* s, mpz_class* t, const mpz_class a, const mpz_class b)
{
    mpz_class a_abs, b_abs;
    a_abs = abs(a);
    b_abs = abs(b);
    mpz_eea_worker(d, s, t, a_abs, b_abs);

    // TODO:
    // s = if a < 0 then (-s') else s'
    // t = if b < 0 then (-t') else t'
}

// wrapper for mpz_fdiv_q
mpz_class mpz_class_fdiv_q(const mpz_class a, const mpz_class b) {
    mpz_class q = 0;
    mpz_fdiv_q(q.get_mpz_t(),
    a.get_mpz_t(),
    b.get_mpz_t());
    return q;
}

// wrapper for mpz_fdiv_r
mpz_class mpz_class_fdiv_r(const mpz_class a, const mpz_class b) {
    mpz_class r = 0;
    mpz_fdiv_r(r.get_mpz_t(),
    a.get_mpz_t(),
    b.get_mpz_t());
    return r;
}

// wrapper for mpz_fdiv_qr
void mpz_class_fdiv_qr(mpz_class* q, mpz_class* r, const mpz_class a, const mpz_class b) {
    mpz_fdiv_qr((*q).get_mpz_t(),
    (*r).get_mpz_t(),
    a.get_mpz_t(),
    b.get_mpz_t());
}

/* Internal Functions */

// worker for gcd, iterative
mpz_class mpz_gcd_worker (const mpz_class a, const mpz_class b)
{
    mpz_class r = 0;
    mpz_class a_ = a;
    mpz_class b_ = b;

    while(cmp(b_, 0)) { // b_ != 0
        r = mpz_class_fdiv_r(a_, b_);
        a_ = b_;
        b_ = r;
    }
    // is this necessary?
    mpz_class gcd = a_;
    return gcd;
}

// worker for eea, recursive, TODO: make iterative
void mpz_eea_worker (mpz_class* d, mpz_class* s, mpz_class* t,
                     const mpz_class a, const mpz_class b)
{
    if(!cmp(b, 0)) {
        *d = a;
        *s = 1;
        *t = 0;
        return;
    }

    mpz_class q = 0, r = 0;
    mpz_class_fdiv_qr(&q, &r, a, b);

    // recursive call
    mpz_eea_worker(d, s, t, b, r);

    mpz_class old_s = *s;
    *s = *t;
    *t = old_s - q * (*t);
}
