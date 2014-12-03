module Main where

-- | Returns the gcd of a and b
simpleEuclidean :: Integral a => a -> a -> a
simpleEuclidean a b = worker (abs a) (abs b)
    where worker a 0 = a
          worker a b = worker b (a `rem` b)


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

-- | Asks the user for two integers and runs the extended euclidean algorithm on them
main = do
    putStrLn "Enter two integers a, b to calculate gcd(a, b) = s * a + t * b"
    putStr "a: "
    first <- getLine
    putStr "b: "
    second <- getLine
    let a = read first :: Integer
        b = read second :: Integer
        (gcd', s, t) = extendedEuclidean a b
        showWithParen x = if x >= 0 then show x else "(" ++ show x ++ ")"
    putStrLn $ (show gcd') ++ " = "
        ++ (showWithParen s) ++ " * " ++ (showWithParen a) ++ " + "
        ++ (showWithParen t) ++ " * " ++ (showWithParen b)
    putStrLn $ "Haskells gcd function returns: " ++ (show (gcd a b))
