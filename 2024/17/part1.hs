import Data.Char
import Debug.Trace
import Data.Bits ( Bits(xor) )
import qualified Data.Array as Array

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

solve:: State -> String
solve state = init (foldr ((\x s -> case x of
                         Just c -> (show c) ++ (',':s)
                         Nothing    -> s) . fst) "" relevantStates)
 where
    states =  (Nothing,state) : (map (nextStep.snd) states)
    relevantStates = takeWhile (\(r,state) -> ic state < length (program state)) states

    
parse:: String -> State
parse s = State 0 (Array.listArray (0,length program - 1) program) a b c
    where
        (a,s1) = nextInt s
        (b,s2) = nextInt s1
        (c,s3) = nextInt s2
        r = dropWhile (not.isDigit) s3
        program = foldr (\x l -> if isDigit x then read [x]:l else l) [] s3



main :: IO ()
main = interact ((++"\n") . solve . parse)