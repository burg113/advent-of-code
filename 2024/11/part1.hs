import Data.Char

stones :: Int -> Integer -> Int
stones 0 num = 1 
stones d num 
    | num == 0 = stones (d-1) 1
    | mod (length s) 2 == 0 = stones (d-1) (read a) + stones (d-1) (read b)
    | otherwise = stones (d-1) (2024* num)
    where 
        s = show num
        (a,b) = splitAt (div (length s) 2) s

solve::[Integer] -> Int
solve l = sum$ map (stones 25) l 


parse:: String -> [Integer]
parse "" = []
parse s = read d : parse (drop 1 r)
    where (d,r) = span isDigit s


main :: IO ()
main = interact ((++"\n") . show . solve . parse) 