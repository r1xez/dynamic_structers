#include <iostream>


template <typename T>
class Node {
public:
    T data;
    Node* next;
    Node* prev;

    Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
};

template <typename T>
class DoublyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;

    void append(Node<T>*& listHead, Node<T>*& listTail, const T& value) const {
        Node<T>* newNode = new Node<T>(value);
        if (!listHead) {
            listHead = listTail = newNode;
        }
        else {
            listTail->next = newNode;
            newNode->prev = listTail;
            listTail = newNode;
        }
    }

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoublyLinkedList() {
        while (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

   
    void pushBack(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (!head) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

   
    Node<T>* clone() const {
        Node<T>* newHead = nullptr;
        Node<T>* newTail = nullptr;
        Node<T>* current = head;
        while (current) {
            append(newHead, newTail, current->data);
            current = current->next;
        }
        return newHead;
    }

   
    Node<T>* operator+(const DoublyLinkedList& other) const {
        Node<T>* newHead = nullptr;
        Node<T>* newTail = nullptr;

       
        Node<T>* current = head;
        while (current) {
            append(newHead, newTail, current->data);
            current = current->next;
        }

       
        current = other.head;
        while (current) {
            append(newHead, newTail, current->data);
            current = current->next;
        }

        return newHead;
    }

    Node<T>* operator*(const DoublyLinkedList& other) const {
        Node<T>* newHead = nullptr;
        Node<T>* newTail = nullptr;

        Node<T>* current1 = head;

       
        while (current1) {
            Node<T>* current2 = other.head;

           
            while (current2) {
                if (current1->data == current2->data) {
                    
                    append(newHead, newTail, current1->data);
                    break; 
                }
                current2 = current2->next;
            }

            current1 = current1->next;
        }

        return newHead;
    }

   
    void printList(Node<T>* listHead = nullptr) const {
        Node<T>* current = listHead ? listHead : head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    DoublyLinkedList<int> list1;
    list1.pushBack(1);
    list1.pushBack(2);
    list1.pushBack(3);

    DoublyLinkedList<int> list2;
    list2.pushBack(3);
    list2.pushBack(4);
    list2.pushBack(5);

    std::cout << "List 1: ";
    list1.printList();

    std::cout << "List 2: ";
    list2.printList();

    
    Node<int>* clonedList = list1.clone();
    std::cout << "Cloned List 1: ";
    list1.printList(clonedList);

    
    Node<int>* mergedList = list1 + list2;
    std::cout << "Merged List: ";
    list1.printList(mergedList);

    
    Node<int>* commonList = list1 * list2;
    std::cout << "Common Elements List: ";
    list1.printList(commonList);

    return 0;
}
