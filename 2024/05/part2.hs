import Data.Char
import qualified  Data.Set as Set

transitiveHullRec:: Integer -> Set.Set (Integer,Integer) -> Set.Set (Integer,Integer)
transitiveHullRec 0 comp = comp
transitiveHullRec n comp = foldl (\x y-> Set.insert y x) comp [(x,y) | (x,y) <- Set.toList comp, (w,z) <- Set.toList comp, w==y]

transitiveHull:: Set.Set (Integer,Integer) -> Set.Set (Integer,Integer)
transitiveHull order = transitiveHullRec (toInteger$ Set.size order) order

insertOrdered:: Set.Set (Integer,Integer) -> Integer -> [Integer] -> [Integer]
insertOrdered order x [] = [x]
insertOrdered order x (y:r) 
  | Set.member (x,y) order = x:y:r  
  | otherwise = y:(insertOrdered order x r)

sortList:: Set.Set (Integer,Integer) -> [Integer] -> [Integer]
sortList order list = foldl (flip$insertOrdered order) [] list

respectsOrder:: (Integer,Integer) -> [Integer] ->  Bool
respectsOrder (a,b) [] = True
respectsOrder (a,b) (c:r) 
  | (c == b) = not (any (==a) r)
  | otherwise = respectsOrder (a,b) r

solve:: ([(Integer,Integer)],[[Integer]]) -> Integer
solve (pairs,lists) = foldl (\n x-> n + x !! (fromIntegral $ div (toInteger (length x)) 2)) 0 
                      (map (sortList order) (filter (\list -> not$ all (\pair -> respectsOrder pair list) pairs) lists))
  where
    order = transitiveHull$ Set.fromList pairs

numList:: String -> [Integer]
numList "" = []
numList s = (read d) : numList r
  where
    (d,r1) = span isDigit s
    r = if r1 == "" then r1 else tail r1 
  
listToPair:: [Integer] -> (Integer,Integer)
listToPair l = (head l, last l)

parse:: String -> ([(Integer,Integer)],[[Integer]])
parse s = (map (listToPair.numList) p1, map (numList) p2)
  where
    (p1,pt) = span (/="") (lines s)
    p2 = tail pt

main :: IO ()
main = interact ((++"\n") . show . solve . parse) 