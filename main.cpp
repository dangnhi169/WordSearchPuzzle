#include "mainwindow.h"
#include <QApplication>

int main(int argc, char* argv[]){
    QApplication a(argc, argv);

//    TrieTree< std::pair< std::pair<int,int>, std::pair<int,int> > > tree = puzzle.getTree();
//    std::cout << tree.search("file").first.first << " " << tree.search("file").first.second <<std::endl;
//    std::cout << tree.search("file").second.first << " " << tree.search("file").second.second <<std::endl;

    MainWindow w;
    w.show();

    a.exec();

    return 0;
}
