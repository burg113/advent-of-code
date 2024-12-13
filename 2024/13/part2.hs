import Data.Char

moves:: ((Integer,Integer),(Integer,Integer),(Integer,Integer)) -> Integer
moves ((dx1,dy1),(dx2,dy2),(dx,dy)) 
    | d1*det >= 0 && d2*det >=0 && mod d1 det == 0 && mod d2 det == 0 = div (3*d1+d2) det
    | otherwise = 0
    where 
        d1 = dy2 * dx - dx2 * dy
        d2 = dx1 * dy - dy1 * dx
        det = dx1*dy2 - dx2 * dy1 
        
solve :: [((Integer,Integer),(Integer,Integer),(Integer,Integer))] -> Integer
solve = sum . (map moves) 


readafter:: Char -> String -> (Integer,String) 
readafter c s= (read num, r)
    where
        s1 = tail$ dropWhile (/=c) s
        (num,r) = span isDigit s1

parse:: String -> [((Integer,Integer),(Integer,Integer),(Integer,Integer))]
parse s 
    | dropWhile (/='+') s == "" = []
    | otherwise =  ((dx1,dy1),(dx2,dy2),(dx+10000000000000,dy+10000000000000)) : parse r6 
    where 
        (dx1,r1) = readafter '+' s
        (dy1,r2) = readafter '+' r1
        (dx2,r3) = readafter '+' r2
        (dy2,r4) = readafter '+' r3
        (dx,r5) = readafter '=' r4
        (dy,r6) = readafter '=' r5

main :: IO ()
main = interact ((++"\n") . show . solve . parse) 