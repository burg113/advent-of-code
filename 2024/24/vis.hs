tokenize:: String -> [String]
tokenize s =  reverse $ snd $ head $ dropWhile (not . (null . fst))$ iterate (\(s,l) -> let (a,r) = span (\x -> x/=' ' && x/='\n') s in (if null r then r else tail r, a:l)) (s,[]::[String])


puml:: String -> String
puml s = "@startuml \ndigraph g {\n"++ concat rules ++ "} \n@enduml\n" 
    where
        s2 = tail $ dropWhile (/= "") $ lines s
        rules = map (\s -> let  [v1,func,v2,_,v3] = tokenize s 
                                tmp = "func"++ func ++v1++v2 in
            tmp  ++ "[label= " ++ func ++ ",color=red]\n" ++
            v1 ++ " -> " ++ tmp ++ "\n" ++ 
            v2 ++ " -> " ++ tmp ++ "\n" ++
            tmp ++ " -> " ++ v3 ++ "\n")
            s2

main :: IO ()
main = interact puml 
    --interact ((++"\n") . show . customShow . uncurry solve . parse)