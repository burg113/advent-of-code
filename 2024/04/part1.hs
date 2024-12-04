import Data.Array

solve:: ((Integer,Integer), Array Integer Char) -> Integer
solve ((w,h),field) = foldl (+) 0 (map (occurences "XMAS") options)
  where 
    options = optionsOne ++ map (foldl (\l x->x:l) []) optionsOne 
    optionsOne = [conc i w h field | i <- [0..(w-1)]] ++ [conc (i*w) 1 w field | i <- [0..(h-1)]]
      ++ [conc i (w+1) (min h (w-i)) field | i <- [0..(w-1)]] ++ [conc (i*w) (w+1) (min w (h-i)) field | i <- [1..(h-1)]]
      ++ [conc i (w-1) (min h (i+1)) field | i <- [0..(w-1)]] ++ [conc (i*w+w-1) (w-1) (min w (h-i)) field | i <- [1..(h-1)]]



conc:: Integer -> Integer -> Integer -> Array Integer Char -> [Char]
conc start dif n field = [ field ! (start + dif * i) | i <- [0..(n-1)]] 

occurences::[Char] -> [Char] -> Integer
occurences s1 s = toInteger $ length $ filter (==s1) (substrs s (toInteger$ length s1))

substrs:: [Char] ->Integer -> [[Char]]
substrs [] am = []
substrs s am = take (fromIntegral am) s : (substrs (tail s) am)
 


toArray:: [a] -> Array Integer a
toArray l = listArray (0,(toInteger $ length l) - 1) l

parse:: String -> ((Integer,Integer), Array Integer Char)
parse s = ((toInteger $ length (head l), toInteger $ length l), toArray  (foldl (++) [] l))
  where l = lines s

main :: IO ()
main = interact ((++"\n") . show . solve . parse) 