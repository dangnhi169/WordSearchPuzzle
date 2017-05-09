#ifndef FILEREADING_H
#define FILEREADING_H

#define NUMBERS_OF_FILES 2

#include <time.h>
#include <stdlib.h>
#include <QString>
#include <QVector>
#include <algorithm>
#include <QFile>
#include <QTextStream>

#include "TrieTree.h"

class FileReading{
private:
    //create 2D array to store puzzle
    QVector<QVector<QChar>> puzzle;

    //trie tree storing dictionary
    TrieTree<int> dictTree;

    //file number (pick randomly, 1,2,3...)
    int fileNumber;
public:
    FileReading(){
        //pick a random file
        srand(time(NULL));
        fileNumber = 1 + std::rand() % (NUMBERS_OF_FILES);

    }

    void readPuzzleFile(int size){
        //initialize file to read in data
        QFile inFile(QString::number(size) + "Small" + QString::number(fileNumber) + ".in");
        if(inFile.open(QIODevice::ReadOnly | QIODevice::Text)){
            QTextStream file(&inFile);
            QString row;

            //read in puzzle file word by word
            while (!file.atEnd()) {

                //read in each line until end of file
                row = file.readLine().toUpper();

                //store string
                QVector<QChar> vect;
                for(int i = 0; i < row.size(); i++){
                    vect.push_back(row[i]);
                }
                puzzle.push_back(vect);

            }
        }
    }

    void readDictionary(){
        //initialize file to read in data and size to store dimension of word array
        QFile inFile("dictionary.txt");
        if(inFile.open(QIODevice::ReadOnly | QIODevice::Text)){
            QTextStream file(&inFile);
            QString row;

            //read in puzzle file word by word
            while (!file.atEnd()) {

                //read in each line until end of file
                row = file.readLine().toUpper();

                //store string
                dictTree.insert(row, 0);
            }
        }
    }

     QVector<QVector<QChar>>& getPuzzle(){
         return puzzle;
     }

     TrieTree<int>& getDictTree(){
         return dictTree;
     }

};

#endif // FILEREADING_H
