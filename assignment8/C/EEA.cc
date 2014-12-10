#include <stdlib.h>
#include <gmpxx.h>
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

/* Internal Functions */

// iterative version
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


// iterative
// void mpz_eea_worker (mpz_class* d, mpz_class* s, mpz_class* t,
//                      const mpz_class a, const mpz_class b)
// {
//     mpz_class a_ = a, b_ = b;
//     mpz_class u = 0, s_ = 1, v = 1, t_ = 0;
//     mpz_class q = 0, r = 0;
//
//     mpz_class u_new, q_new, v_new;
//
//     while (cmp(b_, 0)) {
//         mpz_class_fdiv_qr(&q_new, &r, a_, b_);
//         a_ = b_;
//         b_ = r;
//         u_new = s_;
//         v_new = t_;
//         s_ = u - q * s_;
//         t_ = v - q * t_;
//         u = u_new;
//         v = v_new;
//         q = q_new;
//     }
//
//     *d = a_;
//     *s = u;
//     *t = v;
// }


// recursive
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



mpz_class mpz_class_fdiv_q(const mpz_class a, const mpz_class b) {
    mpz_class q = 0;
    mpz_fdiv_q(q.get_mpz_t(),
               a.get_mpz_t(),
               b.get_mpz_t());
    return q;
}

mpz_class mpz_class_fdiv_r(const mpz_class a, const mpz_class b) {
    mpz_class r = 0;
    mpz_fdiv_r(r.get_mpz_t(),
               a.get_mpz_t(),
               b.get_mpz_t());
    return r;
}

void mpz_class_fdiv_qr(mpz_class* q, mpz_class* r, const mpz_class a, const mpz_class b) {
    mpz_fdiv_qr((*q).get_mpz_t(),
                (*r).get_mpz_t(),
                a.get_mpz_t(),
                b.get_mpz_t());
}
