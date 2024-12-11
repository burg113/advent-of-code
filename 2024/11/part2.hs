import Data.Char
import qualified Data.Map as Map

stones :: Int -> Map.Map (Int,Integer) Integer -> Integer -> (Integer,Map.Map (Int,Integer) Integer)
stones 0 c num = (1,c) 
stones d cache num 
    | Map.member (d,num) cache = (cache Map.! (d,num), cache)
    | num == 0 = let (ans,newCache) = stones (d-1) cache 1 in 
        (ans, Map.insert (d,num) ans newCache)
    | mod (length s) 2 == 0 = let (ans1,c1) = stones (d-1) cache (read a) 
                                  (ans2,c2) = stones (d-1) c1 (read b) in 
        (ans1+ans2, Map.insert (d,num) (ans1+ans2) c2)
    | otherwise = let (ans,newCache) = stones (d-1) cache (2024* num) in 
        (ans, Map.insert (d,num) ans newCache)
    where 
        s = show num
        (a,b) = splitAt (div (length s) 2) s

solve::[Integer] -> Integer
solve l = sum$ map (\x -> fst$stones 75 (Map.empty) x) l 


parse:: String -> [Integer]
parse "" = []
parse s = read d : parse (drop 1 r)
    where (d,r) = span isDigit s


main :: IO ()
main = interact ((++"\n") . show . solve . parse) 