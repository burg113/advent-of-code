import qualified Data.Map as Map
import qualified Data.Set as Set

import Data.List(sort)

tokenize:: String -> [String]
tokenize s =  reverse $ snd $ head $ dropWhile (not . (null . fst))$ iterate (\(s,l) -> let (a,r) = span (\x -> x/=' ' && x/='\n') s in (if null r then r else tail r, a:l)) (s,[]::[String])


main :: IO ()
main = interact ((++"\n") . foldl (\s e -> s ++ ',':e) "" . sort . tokenize)