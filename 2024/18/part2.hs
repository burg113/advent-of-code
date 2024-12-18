import Data.Char
import qualified Data.Set as Set


toDir::Int->(Int,Int)
toDir dir = (mod (dir+1) 2 * (2-mod (dir+1) 4),mod dir 2 * (2-mod dir 4))

add:: (Int,Int) -> (Int,Int) -> (Int,Int)
add (a,b) (c,d) = (a+c,b+d)

expand:: Set.Set (Int,Int) -> Set.Set (Int,Int) -> Set.Set (Int,Int) -> Set.Set (Int,Int)
expand prev positions walkable = Set.fromList (filter (\x -> Set.member x walkable && not (Set.member x prev)) [add pos (toDir r) | r<-[0..3], pos <-Set.toList positions])

carryinput:: ((a,a)->a) -> (a,a)->(a,a)
carryinput f (i1,i2) = (i2,f (i1,i2))

countFunc:: (a->b) -> (a,Int) -> (b,Int)
countFunc f (inp,i) = (f inp,i+1) 

dist:: (Int,Int) -> Set.Set (Int,Int)-> (Int,Int) -> Int
dist start walkable end =  snd (until (\((s1,s2),i) -> Set.member end s2 || i >= 10000) (countFunc (carryinput((flip (uncurry expand)) walkable))) ((Set.fromAscList []::Set.Set (Int,Int),Set.fromAscList [start]),0))

solve::[(Int,Int)] -> (Int,Int) 
solve coords = last (take (until (\x -> dist (0,0) (walkable x) (size,size) >=10000) (+1) 1) coords) 
    where
        walkable = \n -> foldl (flip Set.delete) (Set.fromList [(x,y) | x<-[0..size],y<-[0..size]]) (take n coords)
        size = 70


parseLine::String -> (Int,Int)
parseLine s = (read a,read b)
    where 
        (a,r) = span isDigit s
        b = takeWhile isDigit (tail r)

parse:: String -> [(Int,Int)]
parse s = map parseLine (lines s)

render::(Int,Int) -> String
render (a,b) = show a ++ "," ++ show b

main :: IO ()
main = interact ((++"\n") . render . solve . parse)