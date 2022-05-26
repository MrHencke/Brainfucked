-- I'm sorry for what you're about to read

module Main where

import Data.Char (chr, ord)
import System.Directory.Internal.Prelude (getArgs)
import System.IO (IOMode (ReadMode), hGetContents, openFile)

main :: IO ()
main = do
  args <- getArgs
  fileHandle <- openFile (head args) ReadMode
  bf <- hGetContents fileHandle
  parser [] bf [0] (replicate 30000 0) 0 False

inc :: Int -> Int
inc 255 = 0
inc x = x + 1

dec :: Int -> Int
dec 0 = 255
dec x = x -1

parser :: [Char] -> String -> [Int] -> [Int] -> Int -> Bool -> IO ()
parser _ [] _ _ _ _ = putStrLn ""
parser pbf bf pt t c True = if head bf == ']' then parser (head bf : pbf) (tail bf) pt t c False else parser (head bf : pbf) (tail bf) pt t c True
parser pbf bf pt t c ign = do
  case head bf of
    '+' -> parser (head bf : pbf) (tail bf) pt (inc (head t) : tail t) (c + 1) ign
    '-' -> parser (head bf : pbf) (tail bf) pt (dec (head t) : tail t) (c + 1) ign
    '>' -> parser (head bf : pbf) (tail bf) (head t : pt) (tail t) (c + 1) ign
    '<' -> parser (head bf : pbf) (tail bf) (tail pt) (head pt : t) (c + 1) ign
    '[' -> if head t == 0 then parser (head bf : pbf) (tail bf) pt t c True else parser (head bf : pbf) (tail bf) pt t 1 ign
    ']' -> parser (drop c pbf) (foldr (:) bf (reverse (take c pbf))) pt t c ign
    '.' -> do
      putChar (chr (head t))
      parser (head bf : pbf) (tail bf) pt t (c + 1) ign
    ',' -> do
      new <- getChar
      parser (head bf : pbf) (tail bf) pt (ord new : tail t) (c + 1) ign
    _ -> parser (head bf : pbf) (tail bf) pt t c ign