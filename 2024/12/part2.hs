import Data.Char
import qualified Data.Set as Set
import qualified Data.Array as Array

dif = [(1,0),(-1,0),(0,-1),(0,1)]

orth::(Int,Int) -> (Int,Int)
orth (x,y) = (y,-x)


valid:: Array.Array (Int,Int) Int -> (Int,Int) -> Int -> Bool
valid field (x,y) val = x >= 0 && y >= 0 && x <= w && y <= h && field Array.! (x,y) == val
    where
        w = fst $ snd $ Array.bounds field
        h = snd $ snd $ Array.bounds field 


fill:: Array.Array (Int,Int) Int -> Set.Set (Int,Int) -> (Int,Int) -> (Set.Set (Int,Int),Integer,Integer)
fill field visited (x,y) 
    | Set.member (x,y) visited = (visited,0,0)
    | otherwise = foldl 
        (\(visited,area,border) (dx,dy)-> 
            if valid field (x+dx,y+dy) val && not (Set.member (x+dx,y+dy) visited)  then 
                let (newVis,a2,b2) = fill field visited (x+dx,y+dy) in (newVis,area+a2,border+b2)
            else if not$ valid field (x+dx,y+dy) val then
                let (odx,ody) = orth (dx,dy) 
                    corner = not ((valid field (x+odx,y+ody) val) && 
                                (not$ valid field (x+dx+odx,y+dy+ody) val)) in
                (visited,area,border+ if corner then 1 else 0)
            else
                (visited,area,border)
        ) 
            (Set.insert (x,y) visited,1,0) dif
    where
        val = field Array.! (x,y)


solve :: Array.Array (Int,Int) Int -> Integer
solve field = fst $ foldl 
    (\(curr,visited) (x,y)-> 
        let (nvisited,area,border) = fill field visited (x,y) in 
            (curr+area*border,nvisited) ) 
    (0,Set.empty) [(x,y) | x <-[0..w], y<-[0..h]]
    where
        w = fst $ snd $ Array.bounds field
        h = snd $ snd $ Array.bounds field 

parse:: String -> Array.Array (Int,Int) Int
parse s = Array.listArray ((0,0),(w-1,h-1)) ((map ord) $ concat $ lines s)
    where 
        h = length$lines s
        w = length$head$lines s

main :: IO ()
main = interact ((++"\n") . show . solve . parse) 