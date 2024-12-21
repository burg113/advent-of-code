import Data.Char
import qualified Data.Set as Set
import qualified Data.Map as Map
import qualified Data.Maybe as Maybe
import Data.List (sort)
import Debug.Trace (trace)

type Pos = (Int,Int)
type Board = ((Int,Int),Set.Set (Int,Int),(Int,Int))


type Keypad = (Pos,Int)
keypadA = (3,2)
keypad = Map.fromList [ ((0,0),7),((0,1),8),((0,2),9),
                        ((1,0),4),((1,1),5),((1,2),6),
                        ((2,0),1),((2,1),2),((2,2),3),
                                  ((3,1),0), (keypadA,-1)]
keypadPos = map fst $ Map.toList keypad
invKeypad = Map.fromList (map (\(x,y) -> (y,x)) (Map.toList keypad))

type Remote = (Pos,Pos)
remoteA = (0,2)
remote = Map.fromList [((0 ,1),(-1,0)),(remoteA,(0,0)),
        ((1,0),(0,-1)),((1,1),(1,0)),((1,2),(0,1))]
remotePos = map fst $ Map.toList remote


type Node = (Pos,Pos,Pos)
nodes = [(r1,r2,k) | r1 <- remotePos,r2 <- remotePos, k <- keypadPos]

add:: Pos -> Pos -> Pos
add (a,b) (x,y) = (a+x,b+y)

transitions:: Node -> [Node]
transitions (r1,r2,k) = let npos = add r2 (remote Map.! r1)
                            npos2 = add k (remote Map.! r2) 
        in topLayermoves ++ [(r1,npos,k)|Map.member npos remote] ++ [(r1,r2,npos2)|r1 ==remoteA && Map.member npos2 keypad]
    where
        options = [(1,0),(-1,0),(0,1),(0,-1)]
        topLayermoves = [(add r1 d,r2,k) | d <- options, Map.member (add r1 d) remote]

dijkstra:: Set.Set (Int,Node) -> Map.Map Node Int -> Map.Map Node Int
dijkstra pq dists
    | Set.null pq = dists
    | dists Map.! v <= cost = dijkstra nset dists
    | otherwise = dijkstra nset2 (Map.insert v cost dists)
    where
        e@(cost,v) = Maybe.fromJust (Set.lookupGE (-1,head nodes) pq)
        nset = Set.delete e pq
        nset2 = foldl (flip Set.insert) nset (filter (\(c,p) -> c <= dists Map.! p) (zip (repeat (cost+1)) (transitions v)))

dist:: Node -> Node -> Int
dist n1 n2 = dijkstra (Set.fromAscList [(0,n1)]) (Map.fromList (zip nodes (repeat inf))) Map.! n2
    where 
        inf = 1000000

pathLength::[Int] -> Int
pathLength keys = length keys + sum (trace (show ds) ds)
    where
        ds = zipWith dist ((remoteA,remoteA,keypadA) :positions) positions 
        positions = map (\x -> (remoteA,remoteA,invKeypad Map.! x)) keys

solve:: [([Int],Int)] -> Int
solve moves = sum$ map (\(l,n) -> let p = pathLength l in trace (show (p, n)) (p * n)) moves
    


parse:: String -> [([(Int)],Int)]
parse s = map (\l -> (map (\x -> if isDigit x then read [x] else -1) l,read $ takeWhile isDigit l) ) (lines s)


main :: IO ()
main = interact ((++"\n") . show . solve . parse)