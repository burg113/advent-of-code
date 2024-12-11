import Data.Array

valid:: ((Int,Int), Array Int Int) -> Int -> Int -> Bool
valid ((w,h),field) pos1 pos2 = pos2 >= 0 && pos2 < (w*h) -- in bounds
                        && field!pos2 == field!pos1 - 1  -- only go -1
                        && (div pos1 w == div pos2 w -- same y
                        || mod pos1 w == mod pos2 w) -- same x 

neightbours:: ((Int,Int), Array Int Int) -> Int -> [Int]
neightbours ((w,h),field) pos = filter (valid ((w,h),field) pos) [pos+1,pos-1,pos+w,pos - w]


reachable:: ((Int,Int), Array Int Int) -> Int -> Int
reachable ((w,h),field) pos = sum$ map (\p -> if field!p == 9 && reach!p then 1 else 0) [0..len]
    where 
        len = (snd $ bounds field)
        reach = array (0,len) (
            [(i,if i == pos then True else any (reach!) (neightbours ((w,h),field) i))  | i <- [0..len]])
        
solve::((Int,Int),Array Int Int) -> Int
solve ((w,h),field) = sum $ map (reachable ((w,h),field)) (filter (\x -> 0==field!x) [0..(snd$bounds field)])


parse:: String -> ((Int,Int),Array Int Int)
parse s = ((length (head$ lines s),length (lines s)), listArray (0,length l - 1) l )
 where l = map (\c -> read [c]) $concat (lines s)
        

main :: IO ()
main = interact ((++"\n") . show . solve . parse) 