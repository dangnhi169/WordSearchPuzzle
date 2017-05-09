#ifndef TRIETREE_H
#define TRIETREE_H

#include <vector>
#include <QString>

#define ALPHABETS 26
//#define OFFSET 97   //for lower case
#define OFFSET 65   //for upper case

template <class T>
class TrieTree{

    struct node{
        template <class U> friend class TrieTree;

        QChar c;
        //point to childeren nodes (array)
        node* children[ALPHABETS];
        //associated value
        T value;
        bool isLeaf;

        node(){
            for(int i = 0; i < ALPHABETS; i++){
                children[i] = nullptr;
            }
            //value = -1;
            isLeaf = false;
        }
    };
private:
    node* root;

    void insert(node*& cur, QString str, T val, int index);
    node* search(node*& cur, QString str, int index, int size);
    void makeEmpty(node*& t);

public:
    TrieTree();
    TrieTree(const TrieTree<T>&);
    ~TrieTree();

    TrieTree<T>& operator=(const TrieTree<T>& rhs);
    node* clone(node* t) const;
    void insert(QString str, T val);
    T search(QString str);
    bool contains(QString str);
    void makeEmpty();
};

template <class T>
TrieTree<T>::TrieTree(){
    root = new node();
}

template <class T>
TrieTree<T>::TrieTree(const TrieTree<T>& rhs){
    root = nullptr;
    *this = rhs;
}

template <class T>
TrieTree<T>& TrieTree<T>::operator=(const TrieTree<T>& rhs){
    //prevent self assign
    if(this != &rhs){

        //clear tree
        makeEmpty();

        //copy tree over
        root = clone(rhs.root);
    }

    return *this;
}

//clone subtree from t node
template <class T>
typename TrieTree<T>::node* TrieTree<T>::clone(node* t) const{
    if( t == nullptr ){
        return nullptr;
    } else {
        node* k = new node();
        for(int i = 0; i < ALPHABETS; i++){
            k->children[i] = clone(t->children[i]);
        }
        k->c = t->c;
        k->value = t->value;
        k->isLeaf = t->isLeaf;
        return k;
    }
}

template <class T>
void TrieTree<T>::insert(QString str, T val){
    //position of first letter
    int pos = str.at(0).toLatin1() - OFFSET;

    //insert str recursively to the tree
    insert(root->children[pos], str, val, 0);
}

template <class T>
void TrieTree<T>::insert(node*& cur, QString str, T val, int index){

    //if current node is null, create new node
    if(cur == nullptr){
        cur = new node();
    }

    //if this is end of QString, store value to node and return current node
    if(index == str.size() - 1){

        //set up QCharacters, value for leaf node
        cur->c = str.at(index);
        cur->value = val;
        cur->isLeaf = true;
    } else {

        //set up Character for current node
        cur->c = str.at(index);

        //get position of next node and call insert again for next node
        int pos = str.at(index + 1).toLatin1() - OFFSET;
        insert(cur->children[pos], str, val, index + 1);
    }
}

template <class T>
T TrieTree<T>::search(QString str){
    int pos = str.at(0).toLatin1() - OFFSET;
    node* cur = search(root->children[pos], str, 0, str.size());
    if(cur == nullptr){
        throw std::exception("Invalid type");
    } else {
        return cur->value;
    }
}

template <class T>
typename TrieTree<T>::node* TrieTree<T>::search(node*& cur, QString str, int index, int size){
    if(cur == nullptr || cur->c != str.at(index)){
        return nullptr;
    } else if(index == size - 1){
        return cur;
    } else {
        int pos = str.at(index + 1).toLatin1() - OFFSET;
        return search(cur->children[pos], str, index + 1, size);
    }
}

template <class T>
bool TrieTree<T>::contains(QString str){
    int pos = str.at(0).toLatin1() - OFFSET;
    node* cur = search(root->children[pos], str, 0, str.size());
    if(cur == nullptr || (cur->isLeaf == false)){
        return false;
    } else {
        return true;
    }
}

template <class T>
void TrieTree<T>::makeEmpty(){
    makeEmpty(root);
}

template <class T>
void TrieTree<T>::makeEmpty(node*& t){
    if(t != nullptr){
        for(int i = 0; i < ALPHABETS; i++){
            makeEmpty(t->children[i]);
        }
        delete t;
    }

    t = nullptr;
}

template <class T>
TrieTree<T>::~TrieTree(){
    makeEmpty();
}


#endif // TRIETREE_H
