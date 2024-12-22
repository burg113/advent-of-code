import Data.Char
import qualified Data.Set as Set
import qualified Data.Map as Map
import qualified Data.Maybe as Maybe
import Data.List (sort)
import Debug.Trace (trace)
import Data.Bits (Bits(xor))

simulate:: Int -> Int -> Int 
simulate 0 num = num
simulate steps num = simulate (steps-1) num3
    where 
        num1  = xor num (num*64) `mod` 16777216 
        num2 = xor num1 (div num1 32) `mod` 16777216 
        num3  = xor num2 (num2*2048) `mod` 16777216 
        

solve:: [Int] -> Int
solve nums = sum $ map (simulate 2000) nums 

parse:: String -> [Int]
parse s = map read (lines s)


main :: IO ()
main = interact ((++"\n") . show . solve . parse)