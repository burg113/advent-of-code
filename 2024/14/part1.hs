import Data.Char



nextInt:: String -> (Int,String) 
nextInt s= (read dig * mult,r)
    where
        s1 = dropWhile (\c -> not (isDigit c || c == '-')) s
        (s2,mult) = if head s1 == '-' then (tail s1,-1) else (s1,1)
        (dig,r) = span isDigit s2

toInt:: Bool -> Int
toInt b = if b then 1 else 0

move::((Int,Int),(Int,Int)) -> (Int,Int)
move ((x,y),(dx,dy)) = ((x+100*(dx+w)) `mod` w,(y+100*(dy+h)) `mod` h)
    where
        w = 101
        h = 103

solve::[((Int,Int),(Int,Int))] -> Int
solve lst = a*b*c*d
    where
        w = 101
        h = 103
        (a,b,c,d) = foldl (\(ul,ur,dl,dr) e -> 
            let 
                (x,y) = move e
                l = toInt (x < div w 2)
                r = toInt (x > div w 2)
                u = toInt (y < div h 2)
                d = toInt (y > div h 2)
            in
                (ul + u*l ,ur + u*r,dl+ d*l,dr+ d*r)
                            ) (0,0,0,0) lst


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
main = interact ((++"\n") . show . solve . parse) 