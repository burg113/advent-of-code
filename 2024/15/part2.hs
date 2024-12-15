import qualified Data.Set as Set
import qualified Debug.Trace as Trace

type State = ((Int,Int),(Set.Set (Int,Int),Set.Set (Int,Int)))

score:: (Int,Int) -> Int
score (x,y) = 100*y + x

line:: (Int,Int) -> (Int,Int) -> [Int] -> [(Int,Int)]
line (x,y) (dx,dy) = map (\d -> (x+dx*d,y+dy*d))

firstNotIn::Ord a => [a] -> Set.Set a -> a
firstNotIn (e:r) s
    | Set.member e s = firstNotIn r s
    | otherwise = e

add:: (Int,Int) -> (Int,Int) -> (Int,Int)
add (a,b) (c,d) = (a+c,b+d)

moveList:: [(Int,Int)] -> Set.Set (Int,Int) -> (Int,Int) -> Set.Set (Int,Int)
moveList l s d = foldl (\set p -> Set.insert (add p d) set) (foldl (flip Set.delete) s l) l

canMove:: State -> (Int,Int) -> (Int,Int) -> (Bool,[(Int,Int)])
canMove state@(pos,(boxes,walls)) d@(dx,dy) (x,y)
    | Set.member (x,y) boxes = let  (b1,l1) = if dx == 1 then (True,[]) else canMove state d (x-1+dx,y+dy)
                                    (b2,l2) = canMove state d (x+dx,y+dy)
                                    (b3,l3) = if dx == -1 then (True,[]) else canMove state d (x+1+dx,y+dy)
                            in (b1&&b2&&b3,(x,y):(l1++l2++l3))
    | Set.member (x,y) walls = (False,[])
    | otherwise = (True,[])

move:: State -> Char -> State
move state@(pos,(boxes,walls)) c
    | b = (add pos d,(moveList list boxes d,walls))
    | otherwise = state
    where
        dx
          | c == '>' = 1
          | c== '<' = -1
          | otherwise = 0
        dy
          | c == 'v' = 1
          | c== '^' = -1
          | otherwise = 0
        d = (dx,dy)
        (b1,list1) = canMove state d (add pos d)
        (b2,list2) = canMove state d (add pos (dx-1,dy))
        (b,list) = (b1&&b2,list1++list2)


draw::State -> String
draw (pos,(boxes,walls)) = (concat [ '\n': [let p = (x,y) in
                                    if pos == p then '@'
                                    else if Set.member p boxes then '['
                                    else if Set.member (add p (-1,0)) boxes then ']'
                                    else if Set.member p walls then '#'
                                    else if Set.member (add p (-1,0)) walls then '#'
                                    else ' ' | x <- [0..20]] | y<-[0..20]])


solve:: (State,String) -> Int
solve (state@(pos,(boxes,walls)),moves)
    | moves == "" = sum$ map score (Set.toList boxes)
    | otherwise = --Trace.trace (draw (move state (head moves))) 
                    (solve (move state (head moves),tail moves))



parse:: String -> (State,String)
parse s = (foldl (\curr@(p,(s1,s2)) (pos,c) -> let (x,y) = (2 * mod pos l, div pos l) in
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