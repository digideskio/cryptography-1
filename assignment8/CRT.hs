-- Simon Kalt
-- Clemens Ebinger

module Main where

-- | On input a, b, calculates the greatest common 
-- divisor d and integers s and t that satisfy
-- > d = a*s + b*t
-- > extendedEuclidean a b = (d, s, t)
extendedEuclidean :: Integral a => a -> a -> (a, a, a)
extendedEuclidean a b = (d, s, t)
    where (d, s', t') = worker (abs a) (abs b)
          s = if a < 0 then (-s') else s'
          t = if b < 0 then (-t') else t'
          worker a 0 = (a, 1, 0)
          worker a b = (gcd, t, s - q * t)
            where (q, r) = quotRem a b
                  (gcd, s, t) = worker b r

