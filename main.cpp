#include <iostream>

using namespace std;


class Data {
private:
    int value;
public:
    Data(){
        value = -1;
    }
    Data(int x) {
        value = x;
    }

    int getValue() { return value; }

    void setValue(int val) { value = val; }

    void print() { cout << value; }
};

template<typename T>
class Node {
private:
    T *data;
    Node<T> *leftChild;
    Node<T> *rightChild;
    Node<T> *parent;
public:
    Node(T *data) {
        this->data = data;
    }

    void print() {
        data->print();
    }

    T *getData() { return data; }

    Node<T> *getLeftChild() { return leftChild; }

    Node<T> *getRightChild() { return rightChild; }

    Node<T> *getParent() { return parent; }

    void setLeftChild(Node<T> *c) { leftChild = c; }

    void setRightChild(Node<T> *c) { rightChild = c; }

    void setParent(Node<T> *c) { parent = c; }
};

template<typename T>
class BinarySearchTree {
private:
    Node<T> *root;
    int numberOfElements;
    int height;
public:
    BinarySearchTree(T *r) {
        root = new Node<T>(r);
        root->setLeftChild(nullptr);
        root->setRightChild(nullptr);
        root->setParent(nullptr);
        height = 0;
        numberOfElements = 1;
    }

    ~BinarySearchTree() {
        //while(root!=nullptr)

    }

    //write setters and getters
    //elem should be a Data element, in this case (whatever the Node Class is using as its datatype)
    bool insertElement(T *elem) {
        //if less than root, recursively insert at left child
        //if greater than root, recursively insert at right child
        //if these children are empty, insert there
        Node<T> *r = findParent(elem);
        numberOfElements++;
        return 1;
    }

    Node<T> *findParent(T *obj) {
        Node<T> *p;
        Node<T> *chld;
        chld = new Node<T>(obj);
        if (chld->getData()->getValue() <= root->getData()->getValue()) {
            if (root->getLeftChild()==nullptr)
                root->setLeftChild(chld);
            else
            p = root->getLeftChild();
        }
        else {
            if (root->getRightChild()==nullptr)
                root->setRightChild(chld);
            else
            p = root->getRightChild();
        }
        root->getLeftChild()->print();
        root->getRightChild()->print();
        cout << "entering loop" << endl;
        return p;
        while (true) {
            cout<<chld->getData()->getValue() << endl;
            cout << p << endl;
            if (chld->getData()->getValue() <= p->getData()->getValue()) {
                try {
                    cout << "Less";
                    p = p->getLeftChild();
                }
                catch (exception &e) {
                    break;
                }
            } else if (chld->getData()->getValue() > p->getData()->getValue()) {
                try {
                    cout << "More";
                    p = p->getRightChild();
                }
                catch (exception &e) {
                    break;
                }
            }
            cout << "??";
            cout << p->getData();
        }
        return p;
    }

    void print() {
        for (int i = 0; i < numberOfElements; i++) {
            cout << findKthElement(i) << endl;
        }
    }

    Node<T> *findSmallest() {
        cout << "find smallest" << endl;
        return nullptr;
    }

    Node<T> *findBiggest() {
        cout << "find biggest" << endl;
        return nullptr;
    }

    bool deleteElement(T *data) {
        cout << "delete element" << endl;
        return 0;
    }

    Node<T> *findKthElement(int k) {
        cout << "find kth element" << endl;
        return nullptr;
    }

    int getnumberOfElements() { return this->numberOfElements; }

    void sortAscending() {

        cout << "sort ascending" << endl;
    }

    void sortDescending() {
        cout << "sort ascending" << endl;
    }
};

int main() {
    int a[] = {10, 45, 23, 67, 89, 34, 12, 99};
    Data *newData = new Data(a[0]);
    BinarySearchTree<Data> *newBST = new BinarySearchTree<Data>(newData);
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
    newBST->deleteElement(newData); // delete a number that doesn't exist. What will you print?
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

