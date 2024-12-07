import Data.Char
import qualified Data.Set as Set
import Data.List

dirRes:: Integer -> (Integer,Integer)
dirRes dir 
    | mod dir 4 == 0 = (1,0)
    | mod dir 4 == 1 = (0,1)
    | mod dir 4 == 2 = (-1,0)
    | mod dir 4 == 3 = (0,-1)

type Config = (Integer,(Integer,Integer))

continueWalk:: Set.Set (Integer,Integer) -> Config -> Config
continueWalk (barrier) (dir,(x,y)) 
    | Set.member npos barrier = (dir+1,(x,y)) 
    | otherwise = (dir,npos)
    where 
        npos = (x+(fst$dirRes dir),y+(snd$dirRes dir))

validConfig:: (Integer,Integer) -> Config -> Bool
validConfig (w,h) (dir,(x,y)) = x > 0 && x <= w && y > 0 && y <= h


solve:: ((Integer,Integer),(Integer,Integer),Set.Set (Integer,Integer)) -> Integer
solve ((w,h),(x,y),pos) = toInteger$length$filter (\x -> toInteger (length x) == 4*w*h) 
    [(take (fromIntegral (4*w*h)) $(takeWhile (validConfig (w,h)))$iterate (continueWalk (Set.insert (cx,cy) pos)) (3,(x,y))) | 
    cx <- [1..w],cy <- [1..h], not (cx == x && cy ==y)] 

findCords::Char -> [String] -> [(Integer,Integer)]
findCords ch s = foldl (\l (str,y) ->  l ++ [(i,y) | (i,c) <- zip [1..] str, c==ch]) 
    [] (zip s [1..])


parse:: String -> ((Integer,Integer),(Integer,Integer),Set.Set (Integer,Integer))
parse s = ((toInteger$length$lines s,toInteger$length$head$lines s), head$findCords '^' (lines s), Set.fromList$findCords '#' (lines s))
  
    

main :: IO ()
main = interact ((++"\n") . show . solve . parse) 