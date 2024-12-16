import Data.List

import qualified Data.Set as Set
import qualified Data.Map as Map
import qualified Data.Maybe as Maybe
import qualified Data.Array as Array

type PosRot = ((Int,Int),Int)
type Board = ((Int,Int),Set.Set (Int,Int),(Int,Int))
type State = (Board,Map.Map PosRot Int)

toDir::Int->(Int,Int)
toDir dir = (mod (dir+1) 2 * (2-mod (dir+1) 4),mod dir 2 * (2-mod dir 4))

add:: (Int,Int) -> (Int,Int) -> (Int,Int)
add (a,b) (c,d) = (a+c,b+d)

dijkstra:: State -> Set.Set (Int,PosRot) -> State
dijkstra state@(board@(startp,walls,endp),costs) pq
    | Set.null pq = state
    | costs Map.! p <= cost = dijkstra state nset
    | otherwise = dijkstra (board,Map.insert p cost costs) nset2
    where
        e@(cost,p@(pos,rot)) = Maybe.fromJust (Set.lookupGE (-1,((0,0),0)) pq)
        nset = Set.delete e pq
        nset2 = foldl (flip Set.insert) nset (filter (\(c,pr@(p,r)) -> if not (Map.member pr costs) then error (show pr) else not (Set.member p walls) && (costs Map.! pr > c)) [
            (cost+1,(add pos (toDir rot), rot)),
            (cost+1000,(pos, mod (rot+1) 4)),
            (cost+1000,(pos, mod (rot+3) 4))])

valid:: (Int,Int) -> Bool
valid (x,y) = x >= 0 && x <= 200 && y >= 0 && y <= 200

onShortest:: Map.Map PosRot Int -> (Int,Int) -> Int ->[PosRot]
onShortest dists finish finishdist  = (map fst . filter snd) [let p = ((x,y),r) in (p,a Array.!p)| x <- [0..200],y <- [0..200],r <- [0..3]]
    where
        a = Array.array (((0,0),0),((200,200),3)) ([(((x,y),r),
            let
                rot = r
                pos = (x,y)
                pr = (pos,rot)

                canidates = (map snd . filter (\(c,x) -> valid (fst x) && dists Map.! x == dists Map.! pr + c))  [
                    (1,(add pos (toDir rot), rot)),
                    (1000,(pos, mod (rot+1) 4)),
                    (1000,(pos, mod (rot+3) 4))]
            in
            (pos == finish && dists Map.! pr == finishdist) ||
            any (a Array.!) canidates) | x <- [0..200],y <- [0..200],r <- [0..3]])



solve:: Board -> Int
solve board@(start,s,end) = length $ nub $ map fst (onShortest endCosts end shortest)
    where
        costs = Map.fromList ([(((x,y),r),inf) | x<-[0..200],y<-[0..200], r<-[0..3]])
        ini = Set.fromList [(0,(start,0))]
        fin = [(end,r) | r<-[0..3]]
        inf = 100000000

        (_,endCosts) = dijkstra (board,costs) ini

        shortest = foldl min inf (map (endCosts Map.!) fin)


parse:: String -> Board
parse s = foldl (\curr@(ps,s1,pe) (pos,c) -> let p@(x,y) = (mod pos l, div pos l) in
                    if c == 'S' then
                        (p,s1,pe)
                    else if c == '#' then
                        (ps,Set.insert p s1,pe)
                    else if c == 'E' then
                        (ps,s1,p)
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