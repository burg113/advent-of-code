import Data.Char
import Data.List

solve:: [(Integer,Integer)] -> Integer
solve = (foldl (+) 0).(map (uncurry (*))) 

validl::String -> Bool
validl s = l>0 && l<=3 where l = length s

maxPrefMatch:: (String->Bool) -> String  -> (String,String)
maxPrefMatch f s = maxPrefMatchR f ("",s)

maxPrefMatchR:: (String->Bool) -> (String,String)  -> (String,String)
maxPrefMatchR f (s1, "") = (s1,"")
maxPrefMatchR f (s1, s2) = if f(s1 ++ [head s2]) then maxPrefMatchR  f (s1 ++ [head s2],tail s2) else (s1, s2)
 

parse:: [(Integer,Integer)] -> String -> [(Integer,Integer)]
parse l ""= l
parse res s = 
  if a == "mul(" && c == ","&& b == ")" && validl d1 && validl d2 then 
    (read d1,read d2):parse res r5
  else
    parse res (tail s)
  where
    (a,r1) = maxPrefMatch (flip isPrefixOf "mul(") s
    (d1,r2) = span (isDigit) r1
    (c,r3) = maxPrefMatch (== ",") r2
    (d2,r4) = span (isDigit) r3
    (b,r5) = maxPrefMatch (== ")") r4


main :: IO ()
main = interact ((++"\n") . show . solve . (parse [])) 