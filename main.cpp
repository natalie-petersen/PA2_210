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
    Node(T *data) {
        this->data = data;
        this->leftChild = nullptr;
        this->rightChild = nullptr;
        this->parent = nullptr;
    }

    void print() { data->print(); }

    T *getData() { return data; }

    Node<T> *getLeftChild() { return leftChild; }

    Node<T> *getRightChild() { return rightChild; }

    Node<T> *getParent() { return parent; }

    void setLeftChild(Node<T> *c) { leftChild = c; }

    void setRightChild(Node<T> *c) { rightChild = c; }

    void setParent(Node<T> *c) { parent = c; }

    int compareToNode(Node<T> *other) {
        if (this->getData()->getValue() < other->getData()->getValue()) {//this is less than other
            return -1;
        } else if (this->getData()->getValue() == other->getData()->getValue()) { //this is equal to other
            return 0;
        } else //this is less than other
            return 1;
    }

    int compareToData(T *other) {
        if (this->getData()->getValue() < other->getValue()) {//this is less than other
            return -1;
        } else if (this->getData()->getValue() == other->getValue()) { //this is equal to other
            return 0;
        } else //this is greater than other
            return 1;
    }

    bool deleteNode() {
        setParent(nullptr);
        setLeftChild(nullptr);
        setRightChild(nullptr);
        return true;
    }

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

    void insertElement(T *d) {
        Node<T> *elem = new Node<T>(d);
        if (numberOfElements == 0) //accounting for if the entire tree is deleted for some reason
            root = elem;
        else {
            elem->setParent(findParent(elem)); //setting parent so we know where to insert beforehand
            insertNonRoot(elem, elem->getParent());
        }
        numberOfElements++; //updating number of elements
    }

    void print() {
        printRecursive(root); //has to go to another method because main shouldn't need the root to call print
        cout << endl;
    }

    void findSmallest() {
        sortedList.clear(); //clears list to make room for the new elements - could change the way sorting works to eliminate this step
        sortRecursive(root, true); //sorting list in ascending order
        sortedList.front()->print(); //prints top item (smallest since ascending)
        cout << endl;
    }

    void findBiggest() {
        sortedList.clear(); //clears list
        sortRecursive(root, false); //sorting list in descending order
        sortedList.front()->print(); //prints top item (largest since descending)
        cout << endl;
    }

    void deleteElement(T *data) {
        Node<T> *elem = findNode(data, root);
        if (elem == nullptr) {
            cout << "Number does NOT exist" << endl;
            return;
        }
        Node<T> *elemChild = nullptr;
        //deleting a leaf node (no children)
        if (elem->getRightChild() == nullptr && elem->getLeftChild() == nullptr) {
            if (elem->compareToNode(elem->getParent()) < 0) //if elem is less than its parent (lc)
                elem->getParent()->setLeftChild(nullptr);
            else
                elem->getParent()->setRightChild(nullptr);
            elem->deleteNode(); //deleting child node
            numberOfElements--;
        }
            //deleting an internal node with one child (but not both)
        else if (!(elem->getLeftChild() && elem->getRightChild())) {
            //left child only
            if (elem->getLeftChild() != nullptr) {
                elemChild = elem->getLeftChild();
                elemChild->setParent(elem->getParent()); //updating parent relation
                if (elem->getParent() != nullptr)
                    elem->getParent()->setLeftChild(elemChild); //updating predecessor's child relation
                else
                    root = elemChild;
            }
                //right child but no left child
            else {
                elemChild = elem->getRightChild();
                elemChild->setParent(elem->getParent()); //same process as before
                if (elem->getParent() != nullptr)
                    elem->getParent()->setRightChild(elemChild);
                else
                    root = elemChild;
            }
            //regardless of case, delete the node we need to delete and decrease # of elements in tree
            elem->deleteNode();
            numberOfElements--;
        }
            //two children scenario
        else if (elem->getLeftChild() != nullptr && elem->getRightChild() != nullptr) {
            Node<T> *suc = findSuccessor(elem);
            suc->setRightChild(elem->getRightChild());
            suc->getRightChild()->setParent(suc); //fixing the child of successor's info for parent
            suc->setLeftChild(
                    elem->getLeftChild()); //setting successor's left child to the left subtree of deleted node
            suc->getLeftChild()->setParent(suc); //making this relationship go both ways
            suc->getParent()->setRightChild(nullptr); //removing successor from parent's child list
            suc->setParent(elem->getParent());
            root = suc;
            //deleting node and fixing element #
            elem->deleteNode();
            numberOfElements--;
        }
    }

    void findKthElement(int k) {
        if (k > numberOfElements) { //trying to print an element at an index that doesn't exist/out of bounds
            cout << "Number does NOT exist" << endl;
            return;
        }
        sortedList.clear(); //clears list to make room for new elements
        sortRecursive(root, true); //sorting list in ascending order
        sortedList.at(k - 1)->print(); //prints kth element
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

    void sortDescending() {
        sortRecursive(root,
                      false); //still sorting recursively, but the false bool means that the list will be backwards
        printList();
    }


private:
    void printList() {
        sortedList.front()->getData()->print(); //prints first element without comma
        for (int i = 1; i < numberOfElements; i++) {
            cout << ", ";
            sortedList.at(i)->getData()->print();
        }
        cout << endl;
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

    Node<T> *findSuccessor(Node<T> *elem) {
        sortedList.clear();
        sortRecursive(elem->getLeftChild(),
                      false); //gets left subtree in descending order so that rightmost is in front
        return sortedList.front();
    }

    Node<T> *findNode(T *data, Node<T> *curr) {
        if (curr->compareToData(data) == 0) //if curr's value is what we're looking for, return
            return curr;
        else if (curr->compareToData(data) > 0) { //if curr is greater than what we're looking for, go left
            if (curr->getLeftChild() == nullptr)
                return nullptr;
            return findNode(data, curr->getLeftChild());
        } else if (curr->compareToData(data) < 0) { //if curr is less than what we're looking for, go right
            if (curr->getRightChild() == nullptr)
                return nullptr;
            return findNode(data, curr->getRightChild());
        }
        return nullptr;
    }

    void printRecursive(Node<T> *curr) {
        if (curr == nullptr)
            return; //base case, if there isn't anything there don't bother trying to print
        else {
            if(curr!=root)
                cout << ", ";
            curr->print(); //print root
            printRecursive(curr->getLeftChild()); //print left subtree
            printRecursive(curr->getRightChild()); //print right subtree
        }
    }

    Node<T> *findParent(Node<T> *elem) { //could make recursive?
        Node<T> *curr = root;
        while (true) {
            //if value of new element is less than or == to parent, go to left subtree
            if (elem->getData()->getValue() <= curr->getData()->getValue()) {
                if (curr->getLeftChild() == nullptr)
                    return curr;
                else
                    curr = curr->getLeftChild();
            }
                //if greater than parent, go to the right subtree
            else if (elem->getData()->getValue() > curr->getData()->getValue()) {
                if (curr->getRightChild() == nullptr)
                    return curr;
                else
                    curr = curr->getRightChild();
            }
        }
        return root;
    }

    bool insertNonRoot(Node<T> *elem, Node<T> *parent) {
        if (elem->compareToNode(parent) <=
            0) { //if element's value is less than or equal to parent's value, insert as left child
            parent->setLeftChild(elem); //setting elem to be the child of its parent
            return true; //inserted left child
        } else if (elem->compareToNode(parent) > 0) { //if element's value is greater, insert as right child
            parent->setRightChild(elem); //setting elem to be the child of its parent
            return true; //inserted right child
        }
        return false; //insertion failed

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
    //up to here works
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