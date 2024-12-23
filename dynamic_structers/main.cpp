#include <iostream>
#include <stdexcept>


template <typename T>
class Node {
public:
    T data;
    Node* next;
    Node* prev;

    Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
};


template <typename T>
class Queue {
private:
    Node<T>* head;
    Node<T>* tail;
    size_t size;

public:
    Queue() : head(nullptr), tail(nullptr), size(0) {}

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

  
    void enqueue(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (isEmpty()) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        ++size;
    }

 
    T dequeue() {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty!");
        }
        Node<T>* temp = head;
        T value = temp->data;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        }
        else {
            tail = nullptr;
        }
        delete temp;
        --size;
        return value;
    }

   
    bool isEmpty() const {
        return size == 0;
    }

    size_t getSize() const {
        return size;
    }


    T front() const {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty!");
        }
        return head->data;
    }

  
    T back() const {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty!");
        }
        return tail->data;
    }
};

int main() {
    Queue<int> q;

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    std::cout << "Front: " << q.front() << std::endl;
    std::cout << "Back: " << q.back() << std::endl;

    std::cout << "Dequeued: " << q.dequeue() << std::endl;

    std::cout << "Front after dequeue: " << q.front() << std::endl;
    std::cout << "Queue size: " << q.getSize() << std::endl;

    return 0;
}
