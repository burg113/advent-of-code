import Data.Char
import qualified Data.Set as Set


nextInt:: String -> (Int,String) 
nextInt s= (read dig * mult,r)
    where
        s1 = dropWhile (\c -> not (isDigit c || c == '-')) s
        (s2,mult) = if head s1 == '-' then (tail s1,-1) else (s1,1)
        (dig,r) = span isDigit s2

toInt:: Bool -> Int
toInt b = if b then 1 else 0

move::Int -> ((Int,Int),(Int,Int)) -> (Int,Int)
move d ((x,y),(dx,dy)) = ((x+d*(dx+w)) `mod` w,(y+d*(dy+h)) `mod` h)
    where
        w = 101
        h = 103

visualize:: [(Int,Int)] -> (String,Int)
visualize lst = (concat ['\n' : [if Set.member (x,y) set then '#' else ' ' | x<-[0..(w-1)]] | y<-[0..(h-1)] ], score)
    where
        set = Set.fromList lst
        score = sum (map (\(x,y) -> abs ((div w 2 - x)*(div h 2 - y))) (Set.toList set))
        w = 101
        h = 103

solve::[((Int,Int),(Int,Int))] -> String
solve lst = concat [let (img,score) = visualize (map (move d) lst) in 
    if score < 250000 then "\n" ++ devide ++ (show d) ++ " " ++ (show score) ++ devide ++ img else ""| d <- [0..(101*103)]]
    where devide = take 60 (repeat '-')

parseLine:: String -> ((Int,Int),(Int,Int))
parseLine s = ((x,y),(dx,dy))
    where 
        (x,r1) = nextInt s
        (y,r2) = nextInt r1
        (dx,r3) = nextInt r2
        (dy,r4) = nextInt r3

parse:: String -> [((Int,Int),(Int,Int))]
parse s =  map parseLine (lines s)


main :: IO ()
main = interact ((++"\n")  . solve . parse) 