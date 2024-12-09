import Prelude hiding (readList)
import qualified Debug.Trace as Deb
toFirst:: (Int,Int) -> [(Int,Int)] -> [(Int,Int)]
toFirst (len,l2) (a:(b1,b2):r)  
    | len <= b1 && fst a == 0 = (len,l2) : (b1-len,b2) : r
    | len <= b1 = a : (0,0) : (len,l2) : (b1-len,b2) : r     
    | otherwise = a : (b1,b2) : toFirst (len,l2) r

-- Deb.trace ("len" ++ (show$length lst)) $ 

moveRec:: [(Int,Int)] -> [(Int,Int)] -> [(Int,Int)]
moveRec res [] = res
moveRec res l  =  moveRec ((head$ tail lst):(head lst) :res) (reverse$tail$ tail lst)
    where 
        p = init$ init l
        len = last$ init l
        b = last l
        lst = reverse$ if fst len == 0 then
                l
            else
                toFirst len (p ++ [(0,0), (fst len + fst b,0)])


buildList::[(Int,Int)] -> [Int]
buildList [] = []
buildList ((a,v):l1)
    | a > 0 = v : buildList ((a-1,v) : l1)
    | a == 0 = buildList l1 

solve::[Int]->Int
solve nums = sum $ map (uncurry (*))$ zip [0..] (buildList$ moveRec [] l)
    where l = zip (nums++[0]) [if mod i 2 == 0 then div i 2 else 0 | i <- [0..]]

parse:: String -> [Int]
parse (c:"") = []
parse (c:s) = (read [c]::Int) : parse s
        

main :: IO ()
main = interact ((++"\n") . show . solve . parse) 