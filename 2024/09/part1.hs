import Prelude hiding (readList)

first2:: [a] -> [a]
first2 (a:[]) = [a]
first2 (a:b:r) = a : first2 r 

buildList::[Int] -> Int -> Bool -> [Int]
buildList [] ind b = []
buildList (a:l1) ind b
    | a > 0 = (if b then ind else -1):buildList ((a-1):l1) ind b
    | a == 0 = buildList l1 (if b then ind+1 else ind)  (not b) 

interlace:: [Int] -> [Int] -> [Int]
interlace (a:r) (b:r2)
    | b==(-1) = interlace (a:r) r2
    | a==(-1) = b: interlace r r2
    | otherwise = a : interlace r (b:r2) 

solve::[Int]->Int
solve nums = sum $ map (uncurry (*))$ zip [0..] (take (sum$first2 nums) (interlace l (reverse l)))
    where l = buildList nums 0 True

parse:: String -> [Int]
parse (c:"") = []
parse (c:s) = (read [c]::Int) : parse s
        

main :: IO ()
main = interact ((++"\n") . show . solve . parse) 