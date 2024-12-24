{-# OPTIONS_GHC -Wno-incomplete-patterns #-}
{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Redundant bracket" #-}
import qualified Data.Map as Map
import qualified Data.Set as Set
import Data.Bits
import Data.List(sort)
import Data.List(partition)

res::Map.Map String Bool -> Int
res vars = foldl (\n (name,val) -> if val then n+ 2^read (tail name) else n) 0 relevant
    where
        relevant = sort $ filter ((=='z').head.fst) $ Map.toList vars

lpad:: Int -> String -> Char -> String
lpad len str c
 | length str >= len = str
 | otherwise = lpad len (c:str) c

w:: Int -> Int -> Map.Map String Bool
w n1 n2 = foldl (\m i -> let n = 2^i in
                        Map.insert ("x"++lpad 2 (show i) '0') ((.&.) n n1 > 0) $
                        Map.insert ("y"++lpad 2 (show i) '0') ((.&.) n n2 > 0) m) Map.empty [0..99]

solve:: [((String,String,String), Bool -> Bool -> Bool)] -> [(Int,[Bool])]
solve rules = filter (not . and .snd) 
                    [let    n = 2^i
                            b1 = i == 44 || (calc n n == 2*n)
                            b2 = calc n 0 == n
                            b3 = calc 0 n == n
                            b4 = i == 0 || calc (2^(i-1)) (n-(2^(i-1))) == n
                    in
                        (i,[b1,b2,b3,b4])
                          | i <- [0..44]
                    ]
    where
        calc x y = res $ (solve1) (w x y) rules
        calc :: Int -> Int -> Int
        
solve1:: Map.Map String Bool -> [((String,String,String), Bool -> Bool -> Bool)] -> Map.Map String Bool
solve1 vars rules
    | null r1 = vars
    | otherwise = solve1 nvars r2
    where
        (r1,r2) = partition ((\(x,y,z) -> Map.member x vars && Map.member y vars).fst) rules
        nvars = foldl (\vars ((x,y,z),f)-> Map.insert z (f (vars Map.! x) (vars Map.! y)) vars) vars r1

tokenize:: String -> [String]
tokenize s =  reverse $ snd $ head $ dropWhile (not . (null . fst))$ iterate (\(s,l) -> let (a,r) = span (\x -> x/=' ' && x/='\n') s in (if null r then r else tail r, a:l)) (s,[]::[String])

parse:: String -> [((String,String,String),Bool -> Bool -> Bool)]
parse s = rules
    where
        s1 = takeWhile (/= "") $ lines s
        vars = foldl (\m s -> let [var,val] = tokenize s in Map.insert (init var) (val=="1") m) Map.empty s1
        s2 = tail $ dropWhile (/= "") $ lines s
        rules = map (\s -> let [v1,func,v2,_,v3] = tokenize s in
            ((v1,v2,v3),case func of
                "AND" -> (&&)
                "OR" -> (||)
                "XOR" -> (\x y -> (x || y) && not (x && y))
                ))
            s2


main :: IO ()
main = interact ((++"\n") . show . solve . parse)