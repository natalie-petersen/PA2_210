#include <iostream>
using namespace std;


class Data{
private:
    int value;
public:
    Data(int x){
        value = x;
    }
    int getValue(){return value;}
    void setValue(int val){value = val;}
    void print(){cout << value;}
};

template <typename T> class Node{
private:
    T* data;
    Node<T>* leftChild;
    Node<T>* rightChild;
    Node<T>* parent;
public:
    Node(T* data){
        this->data = data;
    }
    void print(){
        data->print();
    }
};
template <typename T> class BinarySearchTree{
private:
    Node<T>* root;
    int numberOfElements;
    int height;
public:
    BinarySearchTree(T* r){
        root = new Node<T>(r);
        height = 0;
        numberOfElements = 1;
    }
    bool insertElement(T* data){return 0;}
    void print(){}
    Node<T>* findSmallest(){return nullptr;}
    Node<T>* findBiggest(){return nullptr;}
    bool deleteElement(T* data){return 0;}
    Node<T>* findKthElement(int k){return nullptr;}
    int getnumberOfElements(){return this->numberOfElements;}
    void sortAscending(){}
    void sortDescending(){}
};

int main() {
    int a[] = {10, 45, 23, 67, 89, 34, 12, 99};
    Data *newData = new Data(a[0]);
    BinarySearchTree <Data> *newBST = new BinarySearchTree<Data>(newData);
    for (int i = 1; i < (sizeof(a) / sizeof(int)); i++) {
        newData = new Data(a[i]);
        newBST->insertElement(newData);
    }
    newBST->print();
    newBST->findSmallest();
    newBST->findBiggest();
    newData = new Data(10);
    newBST->deleteElement(newData); // delete root
    newBST->print();
    newData = new Data(45);
    newBST->deleteElement(newData); //delete with two children
    newBST->print();
    newData = new Data(12);
    newBST->deleteElement(newData); //delete with one child
    newBST->print();
    newData = new Data(10);
    newBST->deleteElement(newData); // delete a number that doesnt exist. What will you print?
    newBST->print();
    newBST->findKthElement(1); //first element
    newBST->findKthElement(newBST->getnumberOfElements()); //last element
    newBST->findKthElement(3); // some element in between
    newBST->findKthElement(7); // Edge case where item does not exist. What will you print?
    newBST->findSmallest();
    newBST->findBiggest();
    newBST->sortAscending();
    newBST->sortDescending();

    return 0;
}

