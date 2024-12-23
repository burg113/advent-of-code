import qualified Data.Map as Map
import qualified Data.Set as Set
import Debug.Trace



solve:: Map.Map String (Set.Set String) -> Int
solve m = length $ filter (\(a,b,c) -> any (\(x:r) -> x =='t') [a,b,c]) l
    where 
        l = [(x,y,z) | x <- vals,
                        y <- Set.toList (m Map.! x),
                        z <- Set.toList (m Map.! x), 
                        x < y && y < z && Set.member z (m Map.! y)] :: [(String,String,String)]
        vals = map fst (Map.toList m) :: [String]
        

insApp:: (Ord a, Ord b) => a -> b -> Map.Map a (Set.Set b) -> Map.Map a (Set.Set b)
insApp a b m
 | Map.member a m = Map.insert a (Set.insert b (m Map.!a)) m
 | otherwise = Map.insert a (Set.fromAscList  [b]) m

parse:: String -> Map.Map String (Set.Set String)
parse s = foldl (\m x ->    let (p1,r) = span (/='-') x
                                in 
                                    insApp p1 (tail r) (insApp (tail r) p1 m)) Map.empty (lines s)


main :: IO ()
main = interact ((++"\n") . show . solve . parse)