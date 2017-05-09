#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->comboBox->addItem("8x8");
    ui->comboBox->addItem("15x15");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete file;
    delete puzzle;
}

void MainWindow::on_pushButton_clicked(){

    QString text = ui->comboBox->currentText();
    int size = text.split("x").at(0).toInt();

    file = new FileReading();
    file->readPuzzleFile(size);
    file->readDictionary();
    dictTree = file->getDictTree();

    puzzle = new Puzzle(file);
    puzzle->storeData();
    tree = puzzle->getTree();

    play();
}
void MainWindow::play(){

    //QStringList wordsList = file->getWordsList();
    QVector<QVector<QChar>> puzzle2D = file->getPuzzle();

    displayPuzzle(puzzle2D);
    displayWords();

    QHBoxLayout* boxLayout = new QHBoxLayout;

    boxLayout->addWidget(left);
    boxLayout->addWidget(right);

    QWidget* window = new QWidget;
    window->setLayout(boxLayout);
    setCentralWidget(window);

}

void MainWindow::displayPuzzle(QVector<QVector<QChar>> puzzle2D){

    left = new QWidget;
    QGridLayout* l = new QGridLayout;

    for (int r = 0; r <= puzzle2D.size(); r++) {
        QVector<QLabel*> vect;
        for (int c = 0; c <= puzzle2D.size(); c++) {

            //create new push button
            vect.push_back(new QLabel);

            //format the button
            if(c == 0){
                vect.last()->setText(QString::number(r));
                vect.last()->setEnabled(false);
            } else if(r == 0) {
                vect.last()->setText(QString::number(c));
                vect.last()->setEnabled(false);
            } else {
                vect.last()->setText(puzzle2D[r-1][c-1]);
            }
            vect.last()->setFixedSize(50,50);
            vect.last()->setAlignment(Qt::AlignCenter);
            vect.last()->setStyleSheet("border: 1px solid black");
            vect.last()->show();

            //add button to layout
            l->addWidget(vect.last(), r, c);
            l->setSpacing(0);
            l->setMargin(0);
            l->setContentsMargins(-1,-1,-1,-1);

        }
        button.push_back(vect);
    }

    left->setLayout(l);

}

void MainWindow::displayWords(){

    right = new QWidget;

    //box and Find button to support word input
    line = new QLineEdit;
    line->setPlaceholderText("Enter text here");
    QPushButton* b = new QPushButton("Find");

    QObject::connect(b, &QPushButton::clicked, [this] {
        QString word = this->line->text().toUpper();
        this->findText(word);
        }
    );

    //description line to explain the output
    QLabel* desc = new QLabel("Results:\nword: (starting position), (ending position)");
    desc->setWordWrap(true);
    desc->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);

    //box to print the words that found by user
    wordsFound = new QLabel;
    wordsFound->setText("");
    wordsFound->setAlignment(Qt::AlignTop);
    wordsFound->setStyleSheet("background-color: lightgray");

    //button to exit the game
    QPushButton* e = new QPushButton("Exit");
    QObject::connect(e, &QPushButton::clicked, [this] {
        QApplication::quit();
        }
    );

    //adding each part into a vertical layout
    QVBoxLayout* rightLayout = new QVBoxLayout;
    rightLayout->addWidget(line);
    rightLayout->addWidget(b);
    rightLayout->addWidget(desc);
    rightLayout->addWidget(wordsFound);
    rightLayout->addWidget(e);
    right->setLayout(rightLayout);
}

void MainWindow::findText(QString t){
    if(tree.contains(t)){

        //if not a valid English word from dictionary
        if(!dictTree.contains(t)){
            QMessageBox::warning(this, "Warning", "Not a valid English word");
            
        //if the word is already found
        } else if(wFound.contains(t)){
            QMessageBox::warning(this, "Warning", "Already found");
            
        } else {
            //positions
            int rowStart = tree.search(t).first.first + 1;
            int colStart = tree.search(t).first.second + 1;
            int rowEnd = tree.search(t).second.first + 1;
            int colEnd = tree.search(t).second.second + 1;

            //output to box showing words found
            QString start("(" + QString::number(rowStart) +
                          "," + QString::number(colStart) + ")");
            QString end("(" + QString::number(rowEnd) +
                          "," + QString::number(colEnd) + ")");

            wordsFound->setText(wordsFound->text() + t + ": " + start + ", " + end + "\n");
            wFound.insert(t, 0);

            //color words already found
            colorWords(rowStart, rowEnd, colStart, colEnd);
        }

    } else {
        QMessageBox::warning(this, "Error", "Cannot find \"" + t + "\"");
    }
}

void MainWindow::colorWords(int rowStart, int rowEnd, int colStart, int colEnd){

    button[rowStart][colStart]->setStyleSheet("background-color: yellow");

    //go left
    if(rowStart == rowEnd && colStart > colEnd){
        while (colStart > colEnd){
            colStart--;
            button[rowStart][colStart]->setStyleSheet("background-color: yellow");
        }
    //go right
    } else if(rowStart == rowEnd && colStart < colEnd){
        while (colStart < colEnd){
            colStart++;
            button[rowStart][colStart]->setStyleSheet("background-color: yellow");
        }
    //go up
    } else if(colStart == colEnd && rowStart > rowEnd){
        while (rowStart > rowEnd){
            rowStart--;
            button[rowStart][colStart]->setStyleSheet("background-color: yellow");
        }
    //go down
    } else if(colStart == colEnd && rowStart < rowEnd){
        while (rowStart < rowEnd){
            rowStart++;
            button[rowStart][colStart]->setStyleSheet("background-color: yellow");
        }
    //go up right
    } else if(rowStart > rowEnd && colStart < colEnd){
        while (rowStart > rowEnd && colStart < colEnd){
            rowStart--;
            colStart++;
            button[rowStart][colStart]->setStyleSheet("background-color: yellow");
        }
    //go up left
    } else if(rowStart > rowEnd && colStart > colEnd){
        while (rowStart > rowEnd && colStart > colEnd){
            rowStart--;
            colStart--;
            button[rowStart][colStart]->setStyleSheet("background-color: yellow");
        }
    //go down right
    } else if(rowStart < rowEnd && colStart < colEnd){
        while (rowStart < rowEnd && colStart < colEnd){
            rowStart++;
            colStart++;
            button[rowStart][colStart]->setStyleSheet("background-color: yellow");
        }
    //go down left
    } else {
        while (rowStart < rowEnd && colStart > colEnd){
            rowStart++;
            colStart--;
            button[rowStart][colStart]->setStyleSheet("background-color: yellow");
        }
    }


}

