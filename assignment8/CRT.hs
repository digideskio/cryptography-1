-- | Chinese Remainder Theorem implementation
-- written by:
-- Simon Kalt
-- Clemens Ebinger

module CRT
    ( crt
--    , crtExp
    ) where
import EEA (extendedEuclidean)
import System.Random

-- | On input r_i and m_i with (gcd m_i m_j == 1) for i /= j,
--   outputs a number x that satisfies x === r_i (mod m_i) for all i.
crt :: Integral a => [a] -> [a] -> a
crt [r] [m] = r `mod` m
crt [r] (m:_) = r `mod` m
crt (r:_) [m] = r `mod` m
crt (r:rs) (m:ms) = x `mod` (m * mods)
    where previousResult = crt rs ms
          mods = product ms
          (d, s, t) = extendedEuclidean mods m
          v = s * mods
          u = t * m
          x = previousResult * u + r * v

simpleExp :: Integral a => a -> a -> a -> a
simpleExp a x m = (a ^ x) `mod` m

simpleExp2 :: Integral a => a -> a -> a -> a
simpleExp2 a 0 m = 1
simpleExp2 a x m = (a * simpleExp2 a (x - 1) m) `mod` m

crtExp :: Integral a => a -> a -> [a] -> a
crtExp a x ms = crt rs ms
    where rs = map (mod $ a^x) ms


randNBit :: (Integral a, Random a, RandomGen g) => g -> a -> (a, g)
randNBit g n = randomR (2^(n-1), 2^n - 1) g

randNBits :: (Integral a, Random a, RandomGen g) => g -> a -> [a]
randNBits g n = randomRs (2^(n-1), 2^n - 1) g

randNBitsIO :: (Integral a, Random a) => a -> IO [a]
randNBitsIO n = do
    g <- getStdGen
    return $ randomRs (2^(n-1), 2^n - 1) g

randNBitIO :: (Integral a, Random a) => a -> IO a
randNBitIO n = do
    xs <- randNBitsIO n
    return $ head xs

m1 = 381019278501297865019873560491234512
m2 = 18471059710109581029581
a = 19471049710597810498101597119857194
x = 29871098571049810249710598710490197
