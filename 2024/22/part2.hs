import qualified Data.Map as Map
import Data.Bits (Bits(xor))

simulate:: Int -> Int -> [(Int,Int)]
simulate 0 num = []
simulate steps num = (mod num3 10,mod num3 10 - mod num 10): simulate (steps-1) num3
    where
        num1  = xor num (num*64) `mod` 16777216
        num2 = xor num1 (div num1 32) `mod` 16777216
        num3  = xor num2 (num2*2048) `mod` 16777216

sellPrice:: [Int] -> [(Int,Int)] -> Map.Map [Int] Int
sellPrice buff rem
    | length buff >= 4 = sellPrice (tail buff) rem
    | null rem = Map.empty
    | otherwise = Map.insert nbuff (fst $ head rem) (sellPrice nbuff (tail rem))
    where
        nbuff = buff ++ [snd $ head rem]

solve:: [Int] -> Int
solve nums = foldl max 0 [ sum $ map (\m -> if Map.member [x,y,z,w] m then m Map.! [x,y,z,w] else 0) simulates | x<-[(-9)..9],y<-[(-9)..9],z<-[(-9)..9],w<-[(-9)..9]]
    where simulates = map (sellPrice [] . simulate 2000) nums :: [Map.Map [Int] Int]

parse:: String -> [Int]
parse s = map read (lines s)

main :: IO ()
main = interact ((++"\n") . show . solve . parse)