#include <iostream>
#include <string>
#include <limits>

struct Node {
    std::string name;
    Node* next;
    Node(const std::string& n) : name(n), next(nullptr) {}
};

unsigned long long insertCounter = 0;
unsigned long long searchCounter = 0;

class NameList {
private:
    Node* head;
    Node* mid;
    int size;

public:
    NameList() : head(nullptr), mid(nullptr), size(0) {}

    void insertName(const std::string& name) {
        Node* newNode = new Node(name);

        if (!head || head->name > name) {
            newNode->next = head;
            head = newNode;
            insertCounter++;
        } else {
            Node* current = head;
            while (current->next && current->next->name < name) {
                current = current->next;
                insertCounter++;
            }
            newNode->next = current->next;
            current->next = newNode;
        }

        size++;
        updateMid();
    }

    bool searchName(const std::string& name) {
        if (!mid) return false;

        if (name <= mid->name) {
            Node* current = head;
            while (current && current->name <= mid->name) {
                searchCounter++;
                if (current->name == name) return true;
                if (current->name > name) return false;
                current = current->next;
            }
        } else {
            Node* current = mid;
            while (current) {
                searchCounter++;
                if (current->name == name) return true;
                if (current->name > name) return false;
                current = current->next;
            }
        }
        return false;
    }

private:
    void updateMid() {
        if (size <= 1) {
            mid = head;
            return;
        }

        Node* slow = head;
        Node* fast = head;
        Node* prev = nullptr;

        while (fast && fast->next) {
            fast = fast->next->next;
            prev = slow;
            slow = slow->next;
        }

        mid = slow;
    }
};

int main() {
    NameList list;
    char choice;
    std::string name;

    while (true) {
        std::cout << "\nMenu:\n";
        std::cout << "a) Enter a new name\n";
        std::cout << "b) Search for a name\n";
        std::cout << "c) Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 'a':
                std::cout << "Enter name: ";
                std::getline(std::cin, name);
                list.insertName(name);
                std::cout << "Insert operations: " << insertCounter << "\n";
                break;

            case 'b':
                std::cout << "Enter name to search: ";
                std::getline(std::cin, name);
                if (list.searchName(name)) {
                    std::cout << "Name found\n";
                } else {
                    std::cout << "Name not in database\n";
                }
                std::cout << "Search operations: " << searchCounter << "\n";
                break;

            case 'c':
                return 0;

            default:
                std::cout << "Invalid choice\n";
        }
    }
    return 0;
}