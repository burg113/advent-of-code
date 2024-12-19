import Data.Char
import qualified Data.Array as Array

matchSuff:: Eq a => [a] -> [a] -> Bool
matchSuff l1 l2 = all (uncurry (==)) (zip (reverse l1) (reverse l2)) 

canConstruct:: [String] -> String -> Integer
canConstruct strs s = possible Array.! length s
    where
        possible = Array.listArray (0,length s) 
            (1 : [  let str = take i s
                        opts = filter (\x -> length x <= i && matchSuff str x) strs
                    in
                sum$ map (\opt -> possible Array.! (i-length opt)) opts
                | i <- [1..(length s)]])

solve::([String],[String]) -> Integer 
solve (towels, goals) = sum$ map(canConstruct towels) goals

parseList:: Char -> String -> [String]
parseList c "" = []
parseList c s = a : parseList c (drop 2 r)
    where 
        (a,r) = span (/=c) s

parse:: String -> ([String],[String])
parse s = (parseList ',' (head $ lines s),drop 2 (lines s))

main :: IO ()
main = interact ((++"\n") . show . solve . parse)