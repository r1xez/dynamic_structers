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
class Array {
private:
    Node<T>* head;
    Node<T>* tail;
    size_t size;
    size_t capacity;
    size_t grow;

    void clear() {
        while (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        size = 0;
    }

    void expandCapacity(size_t newCapacity) {
        while (capacity < newCapacity) {
            capacity += grow;
        }
    }

public:
    Array(size_t initialCapacity = 1, size_t growStep = 1)
        : head(nullptr), tail(nullptr), size(0), capacity(initialCapacity), grow(growStep) {}

    ~Array() {
        clear();
    }

    size_t GetSize() const {
        return size;
    }

    size_t GetUpperBound() const {
        return size == 0 ? 0 : size - 1;
    }

    bool IsEmpty() const {
        return size == 0;
    }

    void FreeExtra() {
        if (size < capacity) {
            capacity = size;
        }
    }

    void RemoveAll() {
        clear();
    }

    T GetAt(size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        Node<T>* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    void SetAt(size_t index, const T& value) {
        if (index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        Node<T>* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        current->data = value;
    }

    T& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        Node<T>* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    void Add(const T& value) {
        if (size == capacity) {
            expandCapacity(size + 1);
        }
        Node<T>* newNode = new Node<T>(value);
        if (!head) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        ++size;
    }

    void InsertAt(size_t index, const T& value) {
        if (index > size) {
            throw std::out_of_range("Index out of bounds");
        }
        if (index == size) {
            Add(value);
            return;
        }
        Node<T>* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        Node<T>* newNode = new Node<T>(value);
        newNode->next = current;
        newNode->prev = current->prev;
        if (current->prev) {
            current->prev->next = newNode;
        }
        else {
            head = newNode;
        }
        current->prev = newNode;
        ++size;
    }

    void RemoveAt(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        Node<T>* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        if (current->prev) {
            current->prev->next = current->next;
        }
        else {
            head = current->next;
        }
        if (current->next) {
            current->next->prev = current->prev;
        }
        else {
            tail = current->prev;
        }
        delete current;
        --size;
    }

    void Print() const {
        Node<T>* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    Array<int> arr(5, 2);

    int choice;
    do {
        std::cout << "\nMenu:\n"
            << "1. Add Element\n"
            << "2. Get Element by Index\n"
            << "3. Set Element by Index\n"
            << "4. Insert Element at Index\n"
            << "5. Remove Element at Index\n"
            << "6. Print Array\n"
            << "7. Clear Array\n"
            << "8. Exit\n"
            << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            int value;
            std::cout << "Enter value to add: ";
            std::cin >> value;
            arr.Add(value);
            break;
        }
        case 2: {
            int index;
            std::cout << "Enter index to get: ";
            std::cin >> index;
            try {
                std::cout << "Element at index " << index << ": " << arr.GetAt(index) << std::endl;
            }
            catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
            }
            break;
        }
        case 3: {
            int index, value;
            std::cout << "Enter index to set: ";
            std::cin >> index;
            std::cout << "Enter value to set: ";
            std::cin >> value;
            try {
                arr.SetAt(index, value);
            }
            catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
            }
            break;
        }
        case 4: {
            int index, value;
            std::cout << "Enter index to insert: ";
            std::cin >> index;
            std::cout << "Enter value to insert: ";
            std::cin >> value;
            try {
                arr.InsertAt(index, value);
            }
            catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
            }
            break;
        }
        case 5: {
            int index;
            std::cout << "Enter index to remove: ";
            std::cin >> index;
            try {
                arr.RemoveAt(index);
            }
            catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
            }
            break;
        }
        case 6: {
            std::cout << "Array contents: ";
            arr.Print();
            break;
        }
        case 7: {
            arr.RemoveAll();
            std::cout << "Array cleared." << std::endl;
            break;
        }
        case 8:
            std::cout << "Exiting..." << std::endl;
            break;
        default:
            std::cout << "Invalid choice!" << std::endl;
        }
    } while (choice != 8);

    return 0;
}
