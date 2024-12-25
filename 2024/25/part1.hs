import qualified Data.Map as Map
import qualified Data.Set as Set
import Data.List ( sort, partition )

solve:: [[Int]] -> [[Int]] -> Int
solve keys locks = length [(k,v) | k <-keys, v<-locks, all (\(x,y) -> x+y <=7) $ zip k v] 

parse:: [String] -> ([[Int]],[[Int]])
parse [] = ([],[])
parse s
 | key = (arr:r1,r2)
 | otherwise = (r1,arr:r2)
    where
        (c,r) = span (/="") s
        (r1,r2) = parse (if null r then r else tail r)
        key = head (head c) == '.'
        arr = foldl (zipWith (\count c2 -> if c2 == '#' then count+1 else count)) (replicate (length $ head c) 0) c

main :: IO ()
main = interact ((++"\n") . show . uncurry solve . parse. lines)