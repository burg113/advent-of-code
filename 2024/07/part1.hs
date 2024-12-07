import Data.Char
import Prelude hiding (readList)
import qualified Data.Set as Set
import Data.List

poss:: [Integer] -> [Integer]
poss (x:[]) = x:[]
poss (x:lst) = (map (+x) rest) ++ (map (*x) rest) 
    where rest = poss lst



solve::[(Integer,[Integer])]->Integer
solve list = foldl (+) 0 (map fst $ filter (\(n,lst) -> not $ null $ (filter (==n) (poss$reverse lst))) list)

readList::String -> [Integer]
readList "" = []
readList (' ':s) = readList s
readList s = read d : readList r
    where (d,r) = span isDigit s

p::String -> (Integer,[Integer])
p s = (read n,readList (tail$tail r))
    where
        (n,r) = span isDigit s

parse:: String -> [(Integer,[Integer])]
parse s = map p (lines s)
  
    

main :: IO ()
main = interact ((++"\n") . show . solve . parse) 