-- 
{-
dont ask me why this works i am not 100% sure either

my notes contain 
Program: 

while (a != 0)
5,5	out << ((A)^ 6 ^ (A / (2^(A%8 ^3))))%8
0,3	A = A / 8

bit correspondence
bit in A    digits in output
0 - 3 		last
0 - 6 		2nd last
0 - 9 		3rd last
1 - 12 		4th last
4 - 15		5th last 
...

-}
import Data.Char
import Data.Bits ( Bits(xor) )
import qualified Data.Array as Array

import Debug.Trace

data State = State {
    ic :: Int,
    program :: Array.Array Int Int,
    a :: Int,
    b :: Int,
    c :: Int
} deriving Show

nextInt:: String -> (Int,String)
nextInt s= (read dig * mult,r)
    where
        s1 = dropWhile (\c -> not (isDigit c || c == '-')) s
        (s2,mult) = if head s1 == '-' then (tail s1,-1) else (s1,1)
        (dig,r) = span isDigit s2

toBase:: Int -> Int -> [Int]
toBase b num 
    | num == 0 = []
    | otherwise = mod num b : toBase b (div num b)

fromBase:: Int -> [Int] -> Int
fromBase b [] = 0
fromBase b (x:r) = x + b * fromBase b r

nextStep:: State -> (Maybe Int, State)
nextStep state
    | inst == 0 = (Nothing,State nic (program state) (div aval (2^comboOp)) bval cval)
    | inst == 1 = (Nothing,State nic (program state) aval (xor bval op) cval)
    | inst == 2 = (Nothing,State nic (program state) aval (mod comboOp 8) cval)
    | inst == 3 = if aval == 0 then
                    (Nothing,State nic (program state) aval bval cval)
                else
                    (Nothing,State op (program state) aval bval cval)
    | inst == 4 = (Nothing,State nic (program state) aval (xor bval cval) cval)
    | inst == 5 = (Just (mod comboOp 8),State nic (program state) aval bval cval)
    | inst == 6 = (Nothing,State nic (program state) aval (div aval (2^comboOp)) cval)
    | inst == 7 = (Nothing,State nic (program state) aval bval (div aval (2^comboOp)))
    where
        inst = program state Array.! ic state
        op = program state Array.! (ic state + 1)
        comboOp
            | op <= 3 = op
            | op == 4 = aval
            | op == 5 = bval
            | op == 6 = cval
            | otherwise = error ("this should not happen, op:" ++ (show op))
        aval = a state
        bval = b state
        cval = c state
        nic = ic state + 2

solven:: State -> Int -> [Int]
solven state' aval= foldr ((\x s -> case x of
                         Just c -> c:s
                         Nothing    -> s) . fst) [] relevantStates
 where
    state = (State (ic state') (program state') aval (b state') (c state'))
    states =  (Nothing,state) : (map (nextStep.snd) states)
    relevantStates = takeWhile (\(r,state) -> ic state < length (program state)) states


finda:: State -> Int -> Int
finda state aval
    | l == Array.elems (program state) = aval
    | otherwise = (if aval < 1000 then trace ((show aval)++ "\n" ++ show l) else id)
                (finda state (aval+1))
        where
            l = solven state aval

matchSuff:: [Int] -> [Int] -> Bool
matchSuff l1 l2 = all (uncurry (==)) (zip (reverse l1) (reverse l2))

solveRec:: State -> [Int]-> [Int]
solveRec state prev
    | not (null solutions) = trace (show goal) solutions
    | otherwise = solveRec state newCanidates
    where
        goal = Array.elems (program state)
        canidates = [fromBase 8 (d:(toBase 8 p)) | p <- prev, d <-[0..7]]
        solutions = filter (\canidate -> let ans = solven state canidate in length goal == length ans && goal == ans) canidates
        newCanidates = filter (\canidate -> matchSuff goal (solven state canidate)) canidates


solve:: State -> Int
solve state = foldl min 100000000000000000 solutions
    where
        solutions = solveRec state [1..7]


parse:: String -> State
parse s = State 0 (Array.listArray (0,length program - 1) program) 1 b c
    where
        (a,s1) = nextInt s
        (b,s2) = nextInt s1
        (c,s3) = nextInt s2
        r = dropWhile (not.isDigit) s3
        program = foldr (\x l -> if isDigit x then read [x]:l else l) [] s3



main :: IO ()
main = interact ((++"\n") . show . solve . parse)