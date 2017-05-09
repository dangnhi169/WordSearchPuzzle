#ifndef PUZZLE_H
#define PUZZLE_H

#include "FileReading.h"
#include "TrieTree.h"
#include <QString>

class Puzzle{
private:
    //store each possible words and a pair of begining position and ending position
    TrieTree< std::pair< std::pair<int,int>, std::pair<int,int> > > tree;

    QVector<QVector<QChar>> puzzleVect;

public:
    Puzzle(FileReading* file){
        puzzleVect = file->getPuzzle();
    }

    TrieTree< std::pair< std::pair<int,int>, std::pair<int,int> > >& getTree(){
        return tree;
    }

    void storeData(){

        QString str;

        for(int row = 0; row < puzzleVect.size(); row++){
            for(int col = 0; col < puzzleVect[row].size(); col++){

                goUp(str, std::make_pair(row, col), row, col);
                goDown(str, std::make_pair(row, col), row, col);
                goLeft(str, std::make_pair(row, col), row, col);
                goRight(str, std::make_pair(row, col), row, col);

                goUpRight(str, std::make_pair(row, col), row, col);
                goUpLeft(str, std::make_pair(row, col), row, col);
                goDownRight(str, std::make_pair(row, col), row, col);
                goDownLeft(str, std::make_pair(row, col), row, col);
            }
        }
    }

    void goUp(QString str, std::pair<int, int> beginPos, int endRow, int endCol){

        //if not going out of upper border
        if(endRow >= 0){

            //add next letter to str and store str with its position to tree
            str += puzzleVect[endRow][endCol];
            auto endPos = std::make_pair(endRow, endCol);
            tree.insert(str, std::make_pair(beginPos, endPos));

            //go up one row
            return goUp(str, beginPos, endRow - 1, endCol);
        }
    }

    void goDown(QString str, std::pair<int, int> beginPos, int endRow, int endCol){

        //if not going out of lower border
        if(endRow < puzzleVect.size()){

            //add next letter to str and store str with its position to tree
            str += puzzleVect[endRow][endCol];
            auto endPos = std::make_pair(endRow, endCol);
            tree.insert(str, std::make_pair(beginPos, endPos));

            //go down one row
            return goDown(str, beginPos, endRow + 1, endCol);
        }
    }

    void goLeft(QString str, std::pair<int, int> beginPos, int endRow, int endCol){

        //if not going out of left border
        if(endCol >= 0){

            //add next letter to str and store str with its position to tree
            str += puzzleVect[endRow][endCol];
            auto endPos = std::make_pair(endRow, endCol);
            tree.insert(str, std::make_pair(beginPos, endPos));

            //go down one row
            return goLeft(str, beginPos, endRow, endCol - 1);
        }
    }

    void goRight(QString str, std::pair<int, int> beginPos, int endRow, int endCol){

        //if not going out of right border
        if(endCol < puzzleVect[endRow].size()){

            //add next letter to str and store str with its position to tree
            str += puzzleVect[endRow][endCol];
            auto endPos = std::make_pair(endRow, endCol);
            tree.insert(str, std::make_pair(beginPos, endPos));

            //go down one row
            return goRight(str, beginPos, endRow, endCol + 1);
        }
    }

    void goUpRight(QString str, std::pair<int, int> beginPos, int endRow, int endCol){

        //if not going out of upper border
        if(endRow >= 0 && endCol < puzzleVect[endRow].size()){

            //add next letter to str and store str with its position to tree
            str += puzzleVect[endRow][endCol];
            auto endPos = std::make_pair(endRow, endCol);
            tree.insert(str, std::make_pair(beginPos, endPos));

            //go up one row
            return goUpRight(str, beginPos, endRow - 1, endCol + 1);
        }
    }

    void goUpLeft(QString str, std::pair<int, int> beginPos, int endRow, int endCol){

        //if not going out of upper border
        if(endRow >= 0 && endCol >= 0){

            //add next letter to str and store str with its position to tree
            str += puzzleVect[endRow][endCol];
            auto endPos = std::make_pair(endRow, endCol);
            tree.insert(str, std::make_pair(beginPos, endPos));

            //go up one row
            return goUpLeft(str, beginPos, endRow - 1, endCol - 1);
        }
    }

    void goDownRight(QString str, std::pair<int, int> beginPos, int endRow, int endCol){

        //if not going out of upper border
        if(endRow < puzzleVect.size() && endCol < puzzleVect[endRow].size()){

            //add next letter to str and store str with its position to tree
            str += puzzleVect[endRow][endCol];
            auto endPos = std::make_pair(endRow, endCol);
            tree.insert(str, std::make_pair(beginPos, endPos));

            //go up one row
            return goDownRight(str, beginPos, endRow + 1, endCol + 1);
        }
    }

    void goDownLeft(QString str, std::pair<int, int> beginPos, int endRow, int endCol){

        //if not going out of upper border
        if(endRow < puzzleVect.size() && endCol >= 0){

            //add next letter to str and store str with its position to tree
            str += puzzleVect[endRow][endCol];
            auto endPos = std::make_pair(endRow, endCol);
            tree.insert(str, std::make_pair(beginPos, endPos));

            //go up one row
            return goDownLeft(str, beginPos, endRow + 1, endCol - 1);
        }
    }
};

#endif // PUZZLE_H
