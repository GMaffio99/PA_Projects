
isInt :: Float -> Bool
isInt x = x == fromInteger ( round x )

isSquare :: [Float] -> Bool
isSquare m = isInt ( sqrt ( fromIntegral ( length m ) ) )

toString :: [Float] -> Int -> String
toString [] l = "  |  "
toString m l | length m `mod` n == 0 = "  |  " ++ show (head m) ++ toString (tail m) l
             | otherwise             = "  " ++ show (head m) ++ toString (tail m) l
             where n = round ( sqrt ( fromIntegral l ) )

rowIndexes :: Int -> Int -> [Int]
rowIndexes n 0 = []
rowIndexes n x = rowIndexes n (x-1) ++ replicate n x

rowIndexesTail :: [Int] -> Int -> Int -> [Int]
rowIndexesTail l n 0 = l
rowIndexesTail l n x = rowIndexesTail (replicate n x ++ l) n (x-1)

columnIndexes :: Int -> Int -> [Int]
columnIndexes n 0 = []
columnIndexes n x = [1..n] ++ columnIndexes n (x-1)

columnIndexesTail :: [Int] -> Int -> Int -> [Int]
columnIndexesTail l n 0 = l
columnIndexesTail l n x = columnIndexesTail (l ++ [1..n]) n (x-1)

getMatrixWithIndexes :: [Float] -> [(Float,Int,Int)]
getMatrixWithIndexes m = zip3 m (rowIndexesTail [] n n) (columnIndexesTail [] n n)
                         where n = round ( sqrt ( fromIntegral ( length m ) ) )

filterMatrix :: ((Float, Int, Int) -> Bool) -> [(Float, Int, Int)] -> [Float]
filterMatrix p mt = [(\(x,y,z) -> x) e | e <- mt, p e]

removeRowAndColumn :: [(Float,Int,Int)] -> Int -> Int -> [Float]
removeRowAndColumn mt r c = filterMatrix (\(x,y,z) -> y/=r && z/=c) mt

det :: [Float] -> Float
det m | length m == 1  = head m
      | length m == 4  = detM2 m
      | length m == 9  = detM3 m
      | isTriangular m = detMT m
      | otherwise      = detMN m

detM2 :: [Float] -> Float
detM2 [a,b,c,d] = a * d - b * c

detM3 :: [Float] -> Float
detM3 [m11,m12,m13,m21,m22,m23,m31,m32,m33] = m11*m22*m33 + m12*m23*m31 + m13*m21*m32 - (m13*m22*m31 + m11*m23*m32 + m12*m21*m33)

isTriangular :: [Float] -> Bool
isTriangular m = sum (filterMatrix (\(x,y,z) -> y<z) mt) == 0.0 || sum (filterMatrix (\(x,y,z) -> y>z) mt) == 0.0
                 where mt = getMatrixWithIndexes m

detMT :: [Float] -> Float
detMT m = product ( filterMatrix (\(x,y,z) -> y==z) mt )
          where mt = getMatrixWithIndexes m

detMN :: [Float] -> Float
detMN m | length m == 1 = head m
        | otherwise     = sum [x * (-1)^(y+z) * detMN (removeRowAndColumn mt y z) | (x,y,z) <- mt, y == 1]
                          where mt = getMatrixWithIndexes m

main = do

  putStrLn "\nInserisci una matrice (in forma di lista): "
  let matrix = [1,2,3]
  print matrix
  if isSquare matrix
  then putStrLn ( toString matrix (length matrix) ++ "\nIl determinante della matrice inserita è: " ++ show(det matrix) )
  else putStrLn "La matrice inserita non è quadrata"

  putStrLn "\nInserisci una matrice (in forma di lista): "
  let matrix = [1,2,3,4]
  print matrix
  if isSquare matrix
  then putStrLn ( toString matrix (length matrix) ++ "\nIl determinante della matrice inserita è: " ++ show(det matrix) )
  else putStrLn "La matrice inserita non è quadrata"

  putStrLn "\nInserisci una matrice (in forma di lista): "
  let matrix = [2,3,4,5,6,7,8,9,0]
  print matrix
  if isSquare matrix
  then putStrLn ( toString matrix (length matrix) ++ "\nIl determinante della matrice inserita è: " ++ show(det matrix) )
  else putStrLn "La matrice inserita non è quadrata"

  putStrLn "\nInserisci una matrice (in forma di lista): "
  let matrix = [1,0,0,0,2,3,0,0,4,5,6,0,7,8,9,10]
  print matrix
  if isSquare matrix
  then putStrLn ( toString matrix (length matrix) ++ "\nIl determinante della matrice inserita è: " ++ show(det matrix) )
  else putStrLn "La matrice inserita non è quadrata"
  
  putStrLn "\nInserisci una matrice (in forma di lista): "
  let matrix = [3,5,7,11,13,17,19,23,29,31,37,39,41,43,47,53]
  print matrix
  if isSquare matrix
  then putStrLn ( toString matrix (length matrix) ++ "\nIl determinante della matrice inserita è: " ++ show(det matrix) )
  else putStrLn "La matrice inserita non è quadrata"
  
  putStrLn "\nInserisci una matrice (in forma di lista): "
  input <- getLine
  let matrix = read input :: [Float]
  if isSquare matrix
  then putStrLn ( toString matrix (length matrix) ++
                  "\nIl determinante della matrice inserita è: " 
                  ++ show(det matrix) )
  else putStrLn "La matrice inserita non è quadrata"

