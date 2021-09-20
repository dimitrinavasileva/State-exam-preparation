-- Prelude> :l C:\ghc\ghc-7.4.2\bin\Haskell - preparation.hs
-- [1 of 1] Compiling Main             ( C:\ghc\ghc-7.4.2\bin\Haskell - preparation.hs, interpreted )
-- Ok, modules loaded: Main.
-- *Main> main
-- [0,1,3,4,8,11,18,23]

--Sept 2016
filterByChar c ls = filter (\x -> (c `elem` x)) ls
--main = print (filterByChar 'o' ["cat", "cow", "dog"])
--let (x:y):z = ["Curry"] in (x,y,z) 

--July 2016
--[​ x : [x] | x <- [ [1,2], [3,4] ] ​] -- -> [[[1,2], [[1,2]]], [[3,4], [[3,4]]]
--[​ map (f 5) [1,2,3] | f <­ [ (+), (­), (*) ] ​]
--"a" : ​[​ ['b', 'c'], "d" ​]  -- -> ["a","bc","d"]

--Sept 2015 Задача 3
mergeDI x [] = x
mergeDI [] x = x
mergeDI (x:xs) (y:ys) = if x < y
                         then x : mergeDI xs (y:ys) 
			             else y : mergeDI (x:xs) ys
--main = print(mergeDI [1,3,5,7] [2,2,6,10])
						
--July 2015
--map ​(​head [(\couple­>fst couple + snd couple)]​)   
--(​foldr1 (++) [[(1,2)],[(3,4)]]​)

--[zip [x] [x] | x <­ [1..5]

--map (\(x:y:z)­>x:z) [[1,2,3],[2,3,1],[3,1,2]

--Task1 DI
quickSort :: (Ord a) => [a] -> [a]
quickSort []     = []
quickSort (x:xs) = quickSort smaller ++ [x] ++ quickSort larger
    where 
		smaller = filter (< x) xs
		larger = filter (>= x) xs
		
--[3,2,5,4,1]
-- x = 3
-- quickSort [2,1] --> quickSort [1] ++ [2] ++ [] ++ [3] ++ quickSort [5,4] --> quickSort [4] ++ [5] ++ []

--main = print (quickSort [3,1,4,5,2])

merge :: (Ord a) => [a] -> [a] -> [a]
merge xs [] = xs
merge [] ys = ys
merge (x:xs) (y:ys) | x <= y    = x : (merge xs (y:ys))
                    | otherwise = y : (merge (x:xs) ys)

-- 5 `div` 2 --> 2
-- take 2 [1,2,3,4,5] --> [1,2]
-- drop 2 [1,2,3,4,5] --> [3,4,5]  
					
mergeSort :: (Ord a) => [a] -> [a]
mergeSort [] = []
mergeSort [a] = [a]
mergeSort a = merge (mergeSort lastFew)(mergeSort firstFew) 
    where firstFew = take ((length a) `div` 2) a -- In racket (take list position)
          lastFew = drop ((length a) `div` 2) a
--mergeSort [3,2,1]
--merge mergeSort [3] -- 3 mergeSort [2,1] -- mergeSort [2] mergeSort [1]
--merge mergeSort [ ] 

msort :: Ord a => [a] -> [a]
msort [] = []
msort [a] = [a]
msort xs = merge (msort (firstHalf xs)) (msort (secondHalf xs))
	where
		firstHalf  xs = let { n = length xs } in take (div n 2) xs
		secondHalf xs = let { n = length xs } in drop (div n 2) xs
--main = print(mergeSort [3,1,4,5,2])

insertionSort :: Ord a => [a] -> [a]
insertionSort xs = inserts xs []

-- Insert given elements in an emerging result
inserts :: Ord a => [a] -> [a] -> [a]
inserts [] r = r
inserts (x:xs) r = inserts xs (insert x r)

-- Insert a given element in a list
insert :: Ord a => a -> [a] -> [a]
insert x [] = [x]
insert x (y:ys) = if x <= y then x : y : ys
                  else y : insert x ys
--main = print(insertionSort [3,1,4,5,2])

-- Polymorphic sorting
selectionSort :: Ord a => [a] -> [a]
selectionSort xs = selects xs

-- Repeat selection of smallest element
selects :: Ord a => [a] -> [a]
selects [] = []
selects xs = x : selects xs'
  where
    x = smallest (head xs) (tail xs)
    xs' = remove x xs

-- Find smallest element
smallest :: Ord a => a -> [a] -> a
smallest x [] = x
smallest x (y:ys) = smallest (min x y) ys

-- Remove a given element
remove :: Eq a => a -> [a] -> [a]
remove _ [] = error "Element not found for removal."
remove x (y:ys) =
  if x==y
    then ys
    else y : remove x ys
--main = print(selectionSort [3,1,4,5,2])

bubbleUp :: (Ord a) => [a] -> [a]
bubbleUp [] = []
bubbleUp [x] = [x]
bubbleUp (x:y:xs) = smaller : bubbleUp (larger : xs)
  where
    smaller = min x y
    larger = max x y

bubbleSort :: (Ord a) => [a] -> [a]
bubbleSort l = foldl (\acc _ -> bubbleUp acc) l [0 .. length l]
--main = print(bubbleSort [3,1,4,5,2])

data Tree a = EmptyTree | Node {
                            value :: a,
                            left  :: Tree a,
                            right :: Tree a
                          } deriving (Show,Read)
						  

{-- sampleInt tree from the exam
    1
   / \
  2   6
 / \   \
3   5   7
 \
  4
--}
sampleInt = Node 1 (Node 2 (Node 3 EmptyTree
                                       (Node 4 EmptyTree EmptyTree))
                             (Node 5 EmptyTree EmptyTree))
                   (Node 6 EmptyTree
                             (Node 7 EmptyTree EmptyTree))
						  
height :: Tree Int -> Int
height EmptyTree = 0
height (Node v EmptyTree EmptyTree) = 1
height (Node v l r) = 1 + max (height l) (height r)
--main = print(height sampleInt)

sumTree :: Tree Int -> Int
sumTree EmptyTree = 0
sumTree (Node v EmptyTree EmptyTree) = v
sumTree (Node v l r) = v + (sumTree l) + (sumTree r)
--main = print(sumTree sampleInt)

-- even
sumOddTreeValues:: Tree Int -> Int
sumOddTreeValues EmptyTree = 0
sumOddTreeValues (Node v EmptyTree EmptyTree) = if(odd v) then v else 0
sumOddTreeValues (Node v l r) = if(odd v) then v + (sumOddTreeValues l) + (sumOddTreeValues r)
								else (sumOddTreeValues l) + (sumOddTreeValues r)
--main = print(sumOddTreeValues sampleInt)

maxSumPath :: Tree Int -> Int
maxSumPath EmptyTree = 0
maxSumPath (Node v EmptyTree EmptyTree) = v
maxSumPath (Node v l r) = v + max (maxSumPath l)(maxSumPath r)
--main = print(maxSumPath sampleInt)

findMin :: Tree Int -> Int
findMin EmptyTree = maxBound
findMin (Node v EmptyTree EmptyTree) = v
findMin (Node v l r) = min v (min (findMin l) (findMin r))
--main = print(findMin sampleInt)

findMax :: Tree Int -> Int
findMax EmptyTree = minBound
findMax (Node v EmptyTree EmptyTree) = v
findMax (Node v l r) = max v (max (findMax l) (findMax r))
--main = print(findMax sampleInt)

elementExistance :: Tree Int -> Int -> Bool
elementExistance EmptyTree _ = False
elementExistance (Node v l r) x = if v == x then True
				  else (elementExistance l x) || (elementExistance r x)
--main = print(elementExistance sampleInt 5)

countOccurance :: Tree Int -> Int -> Int
countOccurance EmptyTree _ = 0
countOccurance (Node v l r) x = if v == x then 1 + (countOccurance l x) + (countOccurance r x)
				else (countOccurance l x) + (countOccurance r x)
--main = print(countOccurance sampleInt 5)

--Var2
--countOccurance :: Tree Int -> Int -> Int
--countOccurance EmptyTree _ = 0
--countOccurance (Node v l r) x 
--	|v == x = 1 + countOccurance l x + countOccurance r x
--	|otherwise = countOccurance l x + countOccurance r x

countLeaves :: Tree Int -> Int
countLeaves EmptyTree = 0
countLeaves (Node _ EmptyTree EmptyTree) = 1
countLeaves (Node _ l r) = countLeaves l + countLeaves r
--main = print(countLeaves sampleInt)

onKLevel :: Tree Int -> Int -> [Int]
onKLevel EmptyTree _ = []
onKLevel (Node v l r) 1 = [v]
onKLevel (Node _ l r) k = (onKLevel l (k-1)) ++ (onKLevel r (k-1))
--main = print(onKLevel sampleInt 3)
--[3,5,7]

countElements :: Tree Int -> Int
countElements EmptyTree = 0
countElements (Node _ l r) = 1 + (countElements l) + (countElements r)
--main = print(countElements sampleInt)

{-- sample tree from the homework
    a
   / \
  b   c
 / \   \
d   e   f
 \
  g
--}

sample = Node 'a' (Node 'b' (Node 'd' EmptyTree
                                      (Node 'g' EmptyTree EmptyTree))
                            (Node 'e' EmptyTree EmptyTree))
                  (Node 'c' EmptyTree
                            (Node 'f' EmptyTree EmptyTree))

-- Variant1 
-- Task1 - списък от всички думи, които могат да се образуват по път от корена, до някое от листата на дървото. 
--Ако дървото е празно, да се връща празният списък.

-- Функцията е : това е добавянето на елемент към началото на списъка
-- например 1 : [2,3] [1,2,3]
-- В хаскел за операторите има т.нар. операторно сечение, 
-- при което оператора частично се прилага към 1 аргумент и 
-- се получава нова функция само на един аргумент.
-- Така (v:) е все едно функцията, която получава само 1 аргумент-списък, и добавя към началото му.
-- виж упр 9 -> ФП-Тери
treeWords :: Tree Char -> [String]
treeWords EmptyTree = []
treeWords (Node v EmptyTree EmptyTree) = [[v]]
treeWords (Node v l r)  = map (v:) (wl ++ wr)
    where wl = treeWords l
          wr = treeWords r		  
--main = print(treeWords sample)
-- ["abdg","abe","acf"]

-- Variant2
--Task2 - проверява дали str се съдържа в някой път от корена на дървото към негово листо. 
-- Символите трябва да се срещат точно в реда им от str. Не е задължително да се срещат непосредствено един след друг.
treeContains:: Tree Char -> String -> Bool
treeContains _ "" = True
treeContains EmptyTree str = False
treeContains (Node v l r) str@(c:cs) | c == v    = treeContains l cs  || treeContains r cs
                                     | otherwise = treeContains l str || treeContains r str


--main = print(map (treeContains sample) ["", "a", "b", "abdg", "bd", "ae"])
--[True,True,True,True,True,True]
--main = print(map (treeContains sample) ["ea", "zx", "abb"])
--[False,False,False]

--Variant3
--Task1 - връща списък от всички нива в дървото. Нивата да се представят като думи 
-- символни низове образувани от елементите в нивото, подредени от най-левия към най-десния. 
--Ако дървото е празно, да се връща празният списък.
combine:: [String] -> [String] -> [String]
combine xs [] = xs
combine [] ys = ys
combine (x:xs) (y:ys) = (x ++ y) : combine xs ys
--main = print(combine ["a","abc"] ["defg"])
--["adefg","abc"]

treeLevels :: Tree Char -> [String]
treeLevels EmptyTree = []
treeLevels (Node v l r) = [v] : combine ll lr
    where ll = treeLevels l
          lr = treeLevels r
--main = print(treeLevels sample)
--["a","bc","def","g"]		  

-- Втори вариант за рекурсивна дефиниция на дърво

data Tree1 a = EmptyTree1
			   |Leaf a
			   |Tree1 {root::a,
					  left1::Tree1 a,
					  right1::Tree1 a}
			   deriving(Show)
			   
t1 = Tree1 1 (Tree1 2 EmptyTree1 (Leaf 3)) (Leaf 4)

heightTree1 :: Tree1 Int -> Int
heightTree1 EmptyTree1 = 0
heightTree1 (Leaf _)  = 1
heightTree1 (Tree1 _ l r)  = 1 + max (heightTree1 l) (heightTree1 r)
--main = print(heightTree1 t1)

data NTree = NilT | TNode Int NTree NTree

nT = TNode 17 (TNode 14 NilT NilT) (TNode 20 NilT NilT)

sumNTree,depthNTree :: NTree -> Int

sumNTree NilT = 0
sumNTree (TNode n t1 t2) = n + sumNTree t1 + sumNTree t2
--main = print(sumNTree nT)

depthNTree NilT = 0
depthNTree (TNode n t1 t2) = 1 + max (depthNTree t1) (depthNTree t2)

occursNTree :: NTree -> Int -> Int
occursNTree NilT p = 0
occursNTree (TNode n t1 t2) p
 | n==p = 1 + occursNTree t1 p + occursNTree t2 p
 | otherwise = occursNTree t1 p + occursNTree t2 p

data BST a = Nil | BSTNode a (BST a) (BST a)
			deriving (Eq,Ord,Show,Read)

depthBST :: BST a -> Int
depthBST Nil = 0
depthBST (BSTNode n t1 t2) = 1 + max (depthBST t1) (depthBST t2)

numberOfElements :: BST a -> Int
numberOfElements Nil = 0
numberOfElements (BSTNode _ leftTree rightTree) = 1 + numberOfElements leftTree + numberOfElements rightTree

sumOfElements :: BST Int -> Int
sumOfElements Nil = 0
sumOfElements (BSTNode n leftTree rightTree) = n + sumOfElements leftTree + sumOfElements rightTree

countLeavesBST :: BST a -> Int
countLeavesBST Nil = 0
countLeavesBST (BSTNode _ Nil Nil) = 1
countLeavesBST (BSTNode _ leftTree rightTree) = countLeavesBST leftTree + countLeavesBST rightTree

--Трансформиране на двоично дърво (прилагане на дадена 
--функция към всеки от върховете на дървото):
mapTree :: (a -> b) -> BST a -> BST b
mapTree f Nil = Nil
mapTree f (BSTNode x tl t2) = BSTNode (f x) (mapTree f tl) (mapTree f t2)

onKLevelBST :: BST a -> Int -> [a]
onKLevelBST Nil _ = []
onKLevelBST (BSTNode n lt rt) 1 = [n]
onKLevelBST (BSTNode _ lt rt) k = (onKLevelBST lt (k-1)) ++ (onKLevelBST rt (k-1))

kLevelLeavesBST :: BST a -> Int -> Int
kLevelLeavesBST Nil _ = 0
kLevelLeavesBST (BSTNode _ Nil Nil) 1 = 1
kLevelLeavesBST (BSTNode _ lt rt) k = (kLevelLeavesBST lt (k-1)) + (kLevelLeavesBST rt (k-1))

--Трансформиране на списък в двоично дърво:
createTree :: [a] -> BST a
createTree [] = Nil
createTree list = BSTNode root (createTree leftList) (createTree rightList)
 where
	mid = div (length list) 2
	secondPart = drop mid list
	leftList = take mid list
	root = head secondPart
	rightList = tail secondPart


--Haskell - Функции от по-висок ред

applyTo5 :: (Int -> Int) -> Int -- Задължители скоби
applyTo5 f = f 5
--applyTo5 (+1) --> 6 -- (+1) Едноместна функция

zipWith' :: (a->b->c) -> [a] -> [b] -> [c]
zipWith' _ _ [] = []
zipWith' _ [] _ = []
zipWith' op (x:xs) (y:ys) = op x y : zipWith' op xs ys

--zipWith' (+) [1..10] [1..10] --> [2,4,6,8,10,12,14,16,18,20]

map' :: (a->b) -> [a] -> [b]
map' _ [] = []
map' op (x:xs) = op x : map' op xs
--map' (+1) [1..10]

filter' :: (a->Bool) -> [a] -> [a]
filter' _ [] = []
filter' pred (x:xs)
	| pred x = x : filter' pred xs
	| otherwise = filter' pred xs
--filter' odd [1..10]
--filter' (>5) [1..10]

quicksort [] = []
quicksort (x:xs) = quicksort less ++ [x] ++ quicksort more
	where
		less = filter (<x) xs
		more = filter (>=x) xs

--Lambda ex.: \x y ->x + y*10

--HASKELL
--foldl (-) 0 [1,2,3,4] --> 0-(1-(2-(3-4))) --> -10
--scanl (-) 0 [1,2,3,4] --> [0,-1,-3,-6,-10] 
--foldr (-) 0 [1,2,3,4] --> 1-(2-(3-(4-0))) --> -2
--scanr (-) 0 [1,2,3,4] --> [-2,3,-1,4,0]

--SCHEME
--foldl - 0 '(1,2,3,4) --> 4-(3-(2-(1-0))) --> 2
--foldr - 0 '(1,2,3,4) --> 1-(2-(3-(4-0))) --> -2

take' :: Int -> [a] -> [a]
take' n _ | n <= 0 = []
take' _ []         = []
take' n (x:xs)     = x : take' (n-1) xs

-- Прилагане на функция $
--foldl (+) $ filter even $ map (*10) [1..10]
--foldl (+) (filter even (map (*10) [1..10]))

--От списък да вземем първо елементите по модул и след това по корен
--map sqrt (map abs [-5..5])
--map sqrt $ map abs [-5..5]
--map (\x -> sqrt (abs x)) [-5..5]
--map (sqrt.abs) [-5..5]

--findLast :: [Int] -> Int
--findLast [] = error "Empty list!"
--findLast [x] = x
--findLast l = head $ reverse l 
--main = print(findLast [1..4])