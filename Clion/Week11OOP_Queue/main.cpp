#include <iostream>
#include <string>

class Inventory {
public:
    int serialNum;
    std::string manufactDate;
    int lotNum;

    void display() {
        std::cout << "Serial Number: " << serialNum << std::endl;
        std::cout << "Manufacture Date: " << manufactDate << std::endl;
        std::cout << "Lot Number: " << lotNum << std::endl;
        std::cout << "-----------------" << std::endl;
    }
};

const int MAX = 100;

class Queue {
public:
    Inventory parts[MAX];
    int front, rear;

    Queue() {
        front = -1;
        rear = -1;
    }

    void push(Inventory part) {
        if (rear < MAX - 1) {
            if (front == -1) {
                front = 0;
            }
            rear++;
            parts[rear] = part;
        } else {
            std::cout << "Queue is full!" << std::endl;
        }
    }

    Inventory pop() {
        Inventory temp;
        if (front >= 0 && front <= rear) {
            temp = parts[front];

            if (front == rear) {
                front = -1;
                rear = -1;
            } else {
                front++;
            }

            return temp;
        } else {
            std::cout << "Queue is empty!" << std::endl;
            return temp;
        }
    }

    bool isEmpty() {
        return (front == -1);
    }

    void displayAll() {
        if (isEmpty()) {
            std::cout << "No parts in inventory." << std::endl;
            return;
        }

        std::cout << "Remaining parts in queue:" << std::endl;
        for (int i = front; i <= rear; i++) {
            parts[i].display();
        }
    }
};

int main() {
    Queue inventory;
    char choice;

    do {
        std::cout << "Options:" << std::endl;
        std::cout << "A - Add part" << std::endl;
        std::cout << "T - Take part" << std::endl;
        std::cout << "Q - Quit" << std::endl;
        std::cout << "Enter choice: ";
        std::cin >> choice;

        if (choice == 'A') {
            Inventory newPart;

            std::cout << "Enter serial number: ";
            std::cin >> newPart.serialNum;

            std::cin.ignore();
            std::cout << "Enter manufacture date: ";
            std::getline(std::cin, newPart.manufactDate);

            std::cout << "Enter lot number: ";
            std::cin >> newPart.lotNum;

            inventory.push(newPart);
            std::cout << "Part added!" << std::endl;
        }
        else if (choice == 'T') {
            if (!inventory.isEmpty()) {
                Inventory part = inventory.pop();
                std::cout << "Part removed:" << std::endl;
                part.display();
            } else {
                std::cout << "No parts available!" << std::endl;
            }
        }
        else if (choice != 'Q') {
            std::cout << "Invalid choice!" << std::endl;
        }

    } while (choice != 'Q');

    std::cout << "\nFinal inventory:" << std::endl;
    inventory.displayAll();

    return 0;
}