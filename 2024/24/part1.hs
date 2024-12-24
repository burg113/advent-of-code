import qualified Data.Map as Map
import qualified Data.Set as Set
import Data.List ( sort, partition )

customShow::Map.Map String Bool -> Integer
customShow vars = foldl (\n (name,val) -> if val then n+ 2^read (tail name) else n) 0 relevant
    where
        relevant = sort $ filter ((=='z').head.fst) $ Map.toList vars

solve:: Map.Map String Bool -> [((String,String,String), Bool -> Bool -> Bool)] -> Map.Map String Bool
solve vars rules
    | null r1 = vars
    | otherwise = solve nvars r2
    where
        (r1,r2) = partition ((\(x,y,z) -> Map.member x vars && Map.member y vars).fst) rules
        nvars = foldl (\vars ((x,y,z),f)-> Map.insert z (f (vars Map.! x) (vars Map.! y)) vars) vars r1

tokenize:: String -> [String]
tokenize s =  reverse $ snd $ head $ dropWhile (not . (null . fst))$ iterate (\(s,l) -> let (a,r) = span (\x -> x/=' ' && x/='\n') s in (if null r then r else tail r, a:l)) (s,[]::[String])

parse:: String -> (Map.Map String Bool,[((String,String,String),Bool -> Bool -> Bool)])
parse s = (vars,rules)
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
main = interact ((++"\n") . show . customShow . uncurry solve . parse)