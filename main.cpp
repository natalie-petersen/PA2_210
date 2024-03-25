#include <iostream>

using namespace std;


class Data {
private:
    int value;
public:
    Data(int x) {
        this->value = x;
    }

    int getValue() {
        return value;
    }

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
    explicit Node(T *data) {
        this->data = data;
        this->leftChild = nullptr;
        this->rightChild = nullptr;
        this->parent = nullptr;
    }

    void print() { //this works, not sure how so don't touch it for now
        cout << "This node has data ";
        if (getData() == nullptr)
            cout << "none ";
        else
            cout << data->getValue() << " and ";
        if (getLeftChild() == nullptr)
            cout << " no left child ";
        else
            cout << "left child " << getLeftChild()->getData()->getValue();
        cout << " and ";
        if (getRightChild() == nullptr)
            cout << " no right child";
        else
            cout << "right child " << getRightChild()->getData()->getValue();
        cout << " with parent ";
        if (getParent() == nullptr)
            cout << " none";
        else
            cout << getParent()->getData()->getValue();
        cout << endl;
    }

    T *getData() {
        return data;
    }

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
        height = 0;
        numberOfElements = 1;
        root = new Node<T>(r);
    }

    ~BinarySearchTree() {
        while (numberOfElements > 0)
            deleteElement(root);

    }

    //write setters and getters
    //elem should be a Data element, in this case (whatever the Node Class is using as its datatype)
    void insertElement(T *d) {
        Node<T> *elem = new Node<T>(d);
        if (numberOfElements == 0)
            root = elem;
        else{
            elem->setParent(findParent(elem));
            insertNonRoot(elem);
        }
        numberOfElements++;
        elem->print();
    }

    bool insertNonRoot(Node<T> *elem) {

        Node<T> *p = elem->getParent(); //shortcut to avoid long -> trails
        if (elem->getData()->getValue() <= p->getData()->getValue()) { //if element's value is less than parent's value, insert left
            elem->setParent(p);
            p->setLeftChild(elem); //setting elem to be the child of its parent
            return true; //inserted left child
        } else if (elem->getData()->getValue() > p->getData()->getValue()) { //if element's value is greater, insert right
            p->setRightChild(elem); //setting elem to be the child of its parent
            return true; //inserted right child
        }
            return false; //insertion failed

    }

    Node<T> *findParent(Node<T> *elem) {
        Node<T> *curr = root;
        int val = elem->getData()->getValue();
        int ctr = 0;
        //if less than root, recursively insert at left child
        //if greater than root, recursively insert at right child
        //if these children are empty, insert there
        while (ctr < numberOfElements) { //prevents an infinite loop for now
            if (val <= curr->getData()->getValue()) { //if less than parent, go to the left
                if (curr->getLeftChild() == nullptr)
                    return curr;
                else
                    curr = curr->getLeftChild();
            } else if (val > curr->getData()->getValue()) { //if greater than parent, go to the right
                if (curr->getRightChild() == nullptr)
                    return curr;
                else
                    curr = curr->getRightChild();
            }
            ctr++;
        }
        return root;
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

    Node<T> *getRoot() { return root; }
};

int main() {
    int a[] = {10,45,23,67,89,34,12,99};
    Data* newData = new Data(a[0]);
    BinarySearchTree<Data>* newBST = new BinarySearchTree<Data>(newData);
    for(int i=1;i< (sizeof(a)/sizeof(int));i++)
    {
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