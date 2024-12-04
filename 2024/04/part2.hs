import Data.Array

valid::([Char],[Char])->Bool
valid (s1,s2) = (s1 == "MAS" || s1 == "SAM") && (s2 == "MAS" || s2 == "SAM")

solve:: ((Integer,Integer), Array Integer Char) -> Integer
solve ((w,h),field) = toInteger$ length$ filter valid [([field!((y-1)*w+x-1),field!(y*w+x),field!((y+1)*w+x+1)],[field!((y-1)*w+x+1),field!(y*w+x),field!((y+1)*w+x-1)]) | x <- [1..(w-2)], y <- [1..(h-2)]]



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