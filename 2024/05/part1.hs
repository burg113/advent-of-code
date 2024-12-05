import Data.Char

respectsOrder:: (Integer,Integer) -> [Integer] ->  Bool
respectsOrder (a,b) [] = True
respectsOrder (a,b) (c:r) 
  | (c == b) = not (any (==a) r)
  | otherwise = respectsOrder (a,b) r


solve:: ([(Integer,Integer)],[[Integer]]) -> Integer
solve (pairs,lists) = foldl (\n x-> n + x !! (fromIntegral $ div (toInteger (length x)) 2)) 0 (filter (\list -> all (\pair -> respectsOrder pair list) pairs) lists)

numList:: String -> [Integer]
numList "" = []
numList s = (read d) : numList r
  where
    (d,r1) = span isDigit s
    r = if r1 == "" then r1 else tail r1 
  
listToPair:: [Integer] -> (Integer,Integer)
listToPair [] = error "not good"
listToPair l = (head l, last l)


parse:: String -> ([(Integer,Integer)],[[Integer]])
parse s = (map (listToPair.numList) p1, map (numList) p2)
  where
    (p1,pt) = span (/="") (lines s)
    p2 = tail pt

main :: IO ()
main = interact ((++"\n") . show . solve . parse) 