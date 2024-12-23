import qualified Data.Map as Map
import qualified Data.Set as Set
import Data.List (nub)


extendClique:: Map.Map String (Set.Set String) -> [[String]] -> [[String]]
extendClique m cliques = [y : x : l |
                            (x : l) <- cliques,
                            y <- takeWhile (<x) $ Set.toAscList (m Map.! x),
                            all (flip Set.member $ m Map.! y) l]

solve:: Map.Map String (Set.Set String) -> [String]
solve m = (last . last) (takeWhile (not . null) l)
    where
        l = iterate (extendClique m) (map (: []) vals)
        vals = map fst (Map.toList m) :: [String]


insApp:: (Ord a, Ord b) => a -> b -> Map.Map a (Set.Set b) -> Map.Map a (Set.Set b)
insApp a b m
 | Map.member a m = Map.insert a (Set.insert b (m Map.!a)) m
 | otherwise = Map.insert a (Set.fromAscList  [b]) m

parse:: String -> Map.Map String (Set.Set String)
parse s = foldl (\m x ->    let (p1,r) = span (/='-') x
                                in
                                    insApp p1 (tail r) (insApp (tail r) p1 m)) Map.empty (lines s)

customShow:: [String] -> String
customShow [] = ""
customShow [x] = x
customShow (x:lst) = x ++ ',': customShow lst

main :: IO ()
main = interact ((++"\n") . customShow . solve . parse)