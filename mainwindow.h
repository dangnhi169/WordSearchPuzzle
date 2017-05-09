#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QLabel>
#include <QFontDialog>
#include <QMessageBox>
#include <QTextEdit>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

#include "Puzzle.h"
#include "FileReading.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void play();
    void displayPuzzle(QVector<QVector<QChar>> puzzle2D);
    void displayWords();

    void colorWords(int, int, int, int);
    void findText(QString t);

private:
    Ui::MainWindow *ui;

    FileReading* file;
    Puzzle* puzzle;

    QWidget* left;
    QWidget* right;
    QLineEdit* line;
    QLabel* wordsFound;

    QVector<QVector<QLabel*>> button;
    TrieTree< std::pair< std::pair<int,int>, std::pair<int,int> > > tree;
    TrieTree<int> dictTree;
    TrieTree<int> wFound;
};

#endif // MAINWINDOW_H
