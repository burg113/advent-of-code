import Data.Char



moves:: Int -> ((Int,Int),(Int,Int),(Int,Int)) -> Int
moves (-1) a = inf
    where inf = 1000000

moves d v@((dx1,dy1),(dx2,dy2),(dx,dy)) 
    | d*dx1 + d2*dx2 == dx && d*dy1 + d2*dy2 == dy = min (3*d+d2) (moves (d-1) v)
    | otherwise = moves (d-1) v
    where 
        d2 = div (dx-d*dx1) dx2 
    
solve :: [((Int,Int),(Int,Int),(Int,Int))] -> Int
solve = sum . (filter (<inf)) . (map (moves 100)) 
    where inf = 1000000

readafter:: Char -> String -> (Int,String) 
readafter c s= (read num, r)
    where
        s1 = tail$ dropWhile (/=c) s
        (num,r) = span isDigit s1

parse:: String -> [((Int,Int),(Int,Int),(Int,Int))]
parse s 
    | dropWhile (/='+') s == "" = []
    | otherwise =  ((dx1,dy1),(dx2,dy2),(dx,dy)) : parse r6 
    where 
        (dx1,r1) = readafter '+' s
        (dy1,r2) = readafter '+' r1
        (dx2,r3) = readafter '+' r2
        (dy2,r4) = readafter '+' r3
        (dx,r5) = readafter '=' r4
        (dy,r6) = readafter '=' r5

main :: IO ()
main = interact ((++"\n") . show . solve . parse) 