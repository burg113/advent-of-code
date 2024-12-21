import Data.Char
import qualified Data.Set as Set
import qualified Data.Map as Map
import qualified Data.Maybe as Maybe
import Data.List (sort)
import Debug.Trace (trace)

type Pos = (Int,Int)
type Board = ((Int,Int),Set.Set (Int,Int),(Int,Int))


type Keypad = (Pos,Int)
keypadA = (3,2) :: Pos
keypad = Map.fromList [ ((0,0),7),((0,1),8),((0,2),9),
                        ((1,0),4),((1,1),5),((1,2),6),
                        ((2,0),1),((2,1),2),((2,2),3),
                                  ((3,1),0), (keypadA,-1)]
keypadPos = map fst $ Map.toList keypad
invKeypad = Map.fromList (map (\(x,y) -> (y,x)) (Map.toList keypad))

type Remote = (Pos,Pos)
remoteA = (0,2) :: Pos
remote = Map.fromList [((0 ,1),(-1,0)),(remoteA,(0,0)),
        ((1,0),(0,-1)),((1,1),(1,0)),((1,2),(0,1))]
remotePos = map fst $ Map.toList remote

add:: Pos -> Pos -> Pos
add (a,b) (x,y) = (a+x,b+y)

type Node = (Pos,Pos)

transitions:: [Pos] -> Map.Map (Pos,Pos) Integer -> (Pos,Pos) -> [((Pos,Pos),Integer)]
transitions positions costs (r1,l2) = let npos = add l2 (remote Map.! r1)
        in topLayermoves ++ [((r1,npos),1) |elem npos positions]
    where
        topLayermoves = [((r1',l2),costs Map.! (r1,r1')) | r1' <-remotePos]


dijkstra:: (Node->[(Node,Integer)]) -> Set.Set (Integer,Node) -> Map.Map Node Integer -> Map.Map Node Integer
dijkstra edges pq dists
    | Set.null pq = dists
    | dists Map.! v <= cost = dijkstra edges nset dists
    | otherwise = dijkstra edges nset2 (Map.insert v cost dists)
    where
        e@(cost,v) = Maybe.fromJust (Set.lookupGE (-1,((0,0),(0,0))) pq)
        nset = Set.delete e pq
        nset2 = foldl (flip Set.insert) nset (filter (\(c,p) -> c <= dists Map.! p) (map (\(u,dc) -> (cost+dc,u)) (edges v)))

buildLayer:: Map.Map (Pos,Pos) Integer -> Map.Map (Pos,Pos) Integer
buildLayer costs = Map.fromList (concatMap (\x -> let dij = dijkstra (transitions remotePos costs) (Set.fromAscList [(0,(remoteA,x))]) (Map.fromList (zip nodes (repeat inf)))
                                 in [((x,y),dij Map.! (remoteA,y)) |y <- remotePos]) remotePos)
    where
        nodes = [(x,y) | x <- remotePos,y <- remotePos]
        inf = 1000000000000000000

buildLastLayer:: Map.Map (Pos,Pos) Integer -> Map.Map (Pos,Pos) Integer
buildLastLayer costs = Map.fromList (concatMap (\x -> let dij = dijkstra (transitions keypadPos costs) (Set.fromAscList [(0,(remoteA,x))]) (Map.fromList (zip nodes (repeat inf)))
                                 in [((x,y),dij Map.! (remoteA,y)) |y <- keypadPos]) keypadPos)
    where
        nodes = [(x,y) | x <- keypadPos,y <- keypadPos]
        inf = 1000000000000000000


dists:: Map.Map (Pos,Pos) Integer
dists = buildLastLayer (iterate buildLayer initial !! 25)
    where
        initial = Map.fromList [((x,y),0) | x<-remotePos,y<-remotePos]

pathLength::[Integer] -> Integer
pathLength keys = fromIntegral (length keys) + sum (trace (show ds) ds)
    where
        ds = zipWith (curry (dists Map.!))  (keypadA :positions) positions
        positions = map (invKeypad Map.!) keys

solve:: [([Integer],Integer)] -> Integer
solve moves = sum$ map (\(l,n) -> let p = pathLength l in trace (show (p, n)) (p * n)) moves



parse:: String -> [([Integer],Integer)]
parse s = map (\l -> (map (\x -> if isDigit x then read [x] else -1) l,read $ takeWhile isDigit l) ) (lines s)


main :: IO ()
main = interact ((++"\n") . show . solve . parse)