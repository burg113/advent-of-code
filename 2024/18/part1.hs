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
dist start walkable end =  snd (until ((Set.member end).snd.fst ) (countFunc (carryinput((flip (uncurry expand)) walkable))) ((Set.fromAscList []::Set.Set (Int,Int),Set.fromAscList [start]),0))

solve::[(Int,Int)] -> Int 
solve coords = dist (0,0) walkable (70,70)
    where
        walkable = foldl (flip Set.delete) (Set.fromList [(x,y) | x<-[0..70],y<-[0..70]]) (take 1024 coords)


parseLine::String -> (Int,Int)
parseLine s = (read a,read b)
    where 
        (a,r) = span isDigit s
        b = takeWhile isDigit (tail r)

parse:: String -> [(Int,Int)]
parse s = map parseLine (lines s)

main :: IO ()
main = interact ((++"\n") . show . solve . parse)