
import Data.List

splitOnRec :: [Char] -> [Char]->[Char] ->[Char]-> [[Char]]
splitOnRec delim "" buff buff2 = [buff2 ++ buff]
splitOnRec delim str buff buff2
    | length buff == length delim =
        if buff == delim then
            buff2 : (splitOnRec delim str "" "")
        else
            splitOnRec delim (tail str) (tail buff ++ [head str]) (buff2 ++ [head buff])

    | otherwise = splitOnRec delim (tail str) (buff ++ [head str]) buff2

splitOn :: [Char] -> [Char] -> [[Char]]
splitOn delim str = splitOnRec delim str "" ""


valid:: [Integer] -> Integer -> Bool
valid [a] df = True
valid (a:b:rest) df =  v && valid (b:rest) df
    where 
        v = (a*df < b*df) && ((a)*df + 4 > b * df)

val:: [Integer] -> Bool
val (a:b:rest) = 
    if a > b then 
        valid (a:(b:rest)) (-1) 
    else 
        valid (a:(b:rest)) 1

solve:: [[Integer]] -> Integer
solve l = toInteger (length (filter (\x -> any (val) (x:withoutSingleRec [] (head x) (tail x))) l))


toTuple :: [a] -> (a,a)
toTuple [] = error "recieved empty list"
toTuple l = (head l, last l)


withoutSingleRec::[Integer] -> Integer -> [Integer]-> [[Integer]]
withoutSingleRec b1 e []  = [b1]
withoutSingleRec b1 e b2  = (b1 ++ b2) : withoutSingleRec (b1 ++ [e]) (head b2) (tail b2)




parse :: String -> [[Integer]]
parse iput =
    map (map (\x -> read x ::Integer) . splitOn " ") (lines iput)


main :: IO ()
main = interact $ (show . solve . parse)