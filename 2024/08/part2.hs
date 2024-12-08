import Prelude hiding (readList)
import qualified Data.Map as Map
import Data.List

validPos:: (Int,Int) -> (Int,Int) -> Bool
validPos (w,h) (x,y) = x > 0 && x <= w && y > 0 && y <= h

onLine:: (Int,Int) -> (Int,Int) -> [(Int,Int)]
onLine (x,y) (x2,y2) = [(x+dx*i,y+dy*i) | i<-[(-100)..(100)]]
    where
        g = gcd (abs$ x-x2) (abs$ y-y2)
        dx = div (x2-x) g
        dy = div (y2-y) g


interference::[(Int,Int)] -> [(Int,Int)]
interference [] = []
interference (p:elements) = foldl (\l p2 -> onLine p p2 ++ l) [] elements  ++ interference elements 

solve::((Int,Int),Map.Map Char [(Int,Int)])->Int
solve (dim, m) = length $ filter (validPos dim) $ nub $ foldl (\l poss -> l ++ (interference poss)) []  m

mapp::Char -> (Int,Int)->Map.Map Char [(Int,Int)] -> Map.Map Char [(Int,Int)]
mapp k v m  = Map.insert k (v:(Map.findWithDefault [] k m)) m 
 
parse:: String -> ((Int,Int),Map.Map Char [(Int,Int)])
parse s = ((length$head$lines s,length$lines s) , 
    foldl (\m (y,l) ->  foldl (\m (x,c) -> if c == '.' then m else (mapp c (x,y) m)) m (zip [1..] l)) 
        Map.empty (zip [1..] (lines s)))
        

main :: IO ()
main = interact ((++"\n") . show . solve . parse) 