{-# OPTIONS_GHC -Wno-incomplete-patterns #-}
import qualified Data.Set as Set

type State = ((Int,Int),(Set.Set (Int,Int),Set.Set (Int,Int)))

score:: (Int,Int) -> Int
score (x,y) = 100*y + x

line:: (Int,Int) -> (Int,Int) -> [Int] -> [(Int,Int)]
line (x,y) (dx,dy) = map (\d -> (x+dx*d,y+dy*d))

firstNotIn::Ord a => [a] -> Set.Set a -> a
firstNotIn (e:r) s
    | Set.member e s = firstNotIn r s
    | otherwise = e

move:: State -> Char -> State
move state@(pos,(boxes,walls)) c
    | Set.member pushTo walls = state
    | otherwise = (npos,(Set.delete npos (Set.insert pushTo boxes),walls) )
    where
        dx
          | c == '>' = 1
          | c== '<' = -1
          | otherwise = 0
        dy
          | c == 'v' = 1
          | c== '^' = -1
          | otherwise = 0
        l = line pos (dx,dy) [1..]
        npos = (fst pos + dx,snd pos + dy)
        pushTo = firstNotIn l boxes

solve:: (State,String) -> Int
solve (state@(pos,(boxes,walls)),moves)
    | moves == "" = sum$ map score (Set.toList boxes)
    | otherwise = solve (move state (head moves),tail moves)



parse:: String -> (((Int,Int),(Set.Set (Int,Int),Set.Set (Int,Int))),String)
parse s = (foldl (\curr@(p,(s1,s2)) (pos,c) -> let (x,y) = (mod pos l, div pos l) in
                    if c == '@' then
                        ((x,y),(s1,s2))
                    else if c == 'O' then
                        (p,(Set.insert (x,y) s1,s2))
                    else if c == '#' then
                        (p,(s1,Set.insert (x,y) s2))
                    else
                        curr
                    )
            ((-1,-1),(Set.empty,Set.empty)) (zip [0..] (concat $ lines s))
            , concat p2)
    where
        (p1,r) = span (/="") (lines s)
        p2 = tail r
        l = length $ head p1


main :: IO ()
main = interact ((++"\n") . show . solve . parse)