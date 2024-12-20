import Data.Char
import qualified Data.Set as Set
import qualified Data.Map as Map
import qualified Data.Maybe as Maybe

type Pos = (Int,Int)
type Board = ((Int,Int),Set.Set (Int,Int),(Int,Int))

dijkstra:: Set.Set Pos -> Set.Set (Int,Pos) -> Map.Map Pos Int -> Map.Map Pos Int
dijkstra walkable pq dists
    | Set.null pq = dists
    | dists Map.! p <= cost = dijkstra walkable nset dists
    | otherwise = dijkstra walkable  nset2 (Map.insert p cost dists)
    where
        e@(cost,p@(x,y)) = Maybe.fromJust (Set.lookupGE (-1,(0,0)) pq)
        nset = Set.delete e pq
        nset2 = foldl (flip Set.insert) nset (filter (\(c,p) -> Set.member p walkable && c <= dists Map.! p) [
            (cost+1,(x+1,y)),
            (cost+1,(x-1,y)),
            (cost+1,(x,y+1)),
            (cost+1,(x,y-1))])

solve::Board -> Int
solve (start,walkable,end) = length $ filter ((<=dist-100).fst) cheats
    where
        startDists = dijkstra walkable (Set.fromAscList [(0,start)]) (Map.fromList [((x,y),1000000)| x <- [0..150], y <- [0..150]])
        endDists = dijkstra walkable (Set.fromAscList [(0,end)]) (Map.fromList [((x,y),1000000)| x <- [0..150], y <- [0..150]])
        dist = startDists Map.! end 
        cheats = [(abs dx + abs dy + startDists Map.! (x,y) + endDists Map.! (x+dx,y+dy),((x,y),(x+dx,y+dy))) | x <- [0..150], y <- [0..150], dx <- [(-20)..20], dy <- [(-20)..20],
                       (x+dx) >= 0 && (x+dx) <= 150 && (y+dy) >= 0 && (y+dy) <= 150 && abs dx + abs dy <= 20]

parse:: String -> Board
parse s = foldl (\curr@(ps,s1,pe) (pos,c) -> let p@(x,y) = (mod pos l, div pos l) in
                    if c == 'S' then
                        (p,Set.insert p s1,pe)
                    else if c == '.' then
                        (ps,Set.insert p s1,pe)
                    else if c == 'E' then
                        (ps,Set.insert p s1,p)
                    else
                        curr
                    )
            ((-1,-1),Set.empty,(-1,-1)) (zip [0..] (concat $ lines s))
    where
        (p1,r) = span (/="") (lines s)
        p2 = tail r
        l = length $ head p1

main :: IO ()
main = interact ((++"\n") . show . solve . parse)