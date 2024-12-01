
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



solve:: [(Integer,Integer)] -> Integer
solve l = foldl (\sum x -> toInteger (length (filter (==x) l2))* x + sum) 0 l1
    where
        l1 = sort (map fst l)
        l2 = sort (map snd l)


tmp x = filter (==x) l2
    where l2 = []

toTuple :: [a] -> (a,a)
toTuple [] = error "recieved empty list"
toTuple l = (head l, last l)

parse :: String -> [(Integer,Integer)]
parse iput =
    map (toTuple . map (\x -> read x ::Integer) . splitOn " ") (lines iput)


main :: IO ()
main = interact $ (show . solve . parse)