#include <iostream>
#include <deque>

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
        data->print();

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
    deque<Node<T> *> sortedList; //list to store sorted elements

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
        if (numberOfElements == 0) //accounting for if the entire tree is deleted for some reason
            root = elem;
        else {
            elem->setParent(findParent(elem));
            insertNonRoot(elem, elem->getParent());
        }
        numberOfElements++;
    }

    bool insertNonRoot(Node<T> *elem, Node<T> *parent) {
        if (elem->getData()->getValue() <=
            parent->getData()->getValue()) { //if element's value is less than parent's value, insert left
            parent->setLeftChild(elem); //setting elem to be the child of its parent
            return true; //inserted left child
        } else if (elem->getData()->getValue() >
                   parent->getData()->getValue()) { //if element's value is greater, insert right
            parent->setRightChild(elem); //setting elem to be the child of its parent
            return true; //inserted right child
        }
        return false; //insertion failed

    }

    Node<T> *findParent(Node<T> *elem) { //could make recursive?
        Node<T> *curr = root;
        int ctr = 0;
        while (ctr < numberOfElements) { //prevents an infinite loop for now
            if (elem->getData()->getValue() <=
                curr->getData()->getValue()) { //if value of new element is less than or = to parent, go to the left
                if (curr->getLeftChild() == nullptr)
                    return curr;
                else
                    curr = curr->getLeftChild();
            } else if (elem->getData()->getValue() >
                       curr->getData()->getValue()) { //if greater than parent, go to the right
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
        printRecursive(root); //has to go to another method because main shouldn't need the root to call print
        cout << endl;
    }

    void printRecursive(Node<T> *curr) {
        if (curr == nullptr)
            return; //base case, if there isn't anything there don't bother trying to print
        else {
            curr->print(); //print root
            cout << " ";
            printRecursive(curr->getLeftChild()); //print left subtree
            printRecursive(curr->getRightChild()); //print right subtree
        }
    }

    void findSmallest() {
        cout << "smallest number is: ";
        sortedList.clear(); //clears list to make room for the new elements - could change the way sorting works to eliminate this step
        sortRecursive(root, true); //sorting list in ascending order
        sortedList.front()->print(); //prints top item (smallest since ascending)
        cout << endl;
    }

    void findBiggest() {
        cout << "biggest number is: ";
        sortedList.clear(); //clears list
        sortRecursive(root, false); //sorting list in descending order
        sortedList.front()->print(); //prints top item (largest since descending)
        cout << endl;
    }

    bool deleteElement(T *data) {
        cout << "delete element" << endl; //best method here
        return false;
    }

    void findKthElement(int k) {
        if (k >= numberOfElements) { //trying to print an element at an index that doesn't exist/out of bounds
            cout << "Number does NOT exist" << endl;
            return;
        }
        cout << k << "th element is: ";
        sortedList.clear(); //clears list to make room for new elements
        sortRecursive(root, true); //sorting list in ascending order
        sortedList.at(k)->print(); //prints kth element
        cout << endl;

    }

    int getnumberOfElements() { return this->numberOfElements; }

    void sortAscending() {
        //clears the list to store elements in
        sortedList.clear();
        //traverse tree in-order to sort elements and stores it in a sorted list (deque)
        sortRecursive(root, true);
        //prints elements
        printList();
    }

    void sortRecursive(Node<T> *curr, bool inc) {
        if (curr == nullptr) //base case
            return;
        else {
            sortRecursive(curr->getLeftChild(), inc); //traversing left subtree
            if (inc) //if increasing, lowest value should be at the first position (front) so higher values should be pushed back
                sortedList.push_back(curr);
            else { //vice versa
                sortedList.push_front(curr);
            }
            sortRecursive(curr->getRightChild(), inc); //traversing right subtree
        }
    }

    void sortDescending() {
        sortRecursive(root,false); //still sorting recursively, but the false bool means that the list will be backwards
        printList();
    }

    void printList() {
        sortedList.front()->getData()->print(); //prints first element without comma
        for (int i = 1; i < numberOfElements; i++) {
            cout << ", ";
            sortedList.at(i)->getData()->print();
        }
        cout << endl;
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