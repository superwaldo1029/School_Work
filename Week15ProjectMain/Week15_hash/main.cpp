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

class HashTable {
private:
    Node** table;
    int size;

    int hash(const std::string& name) {
        int sum = 0;
        for (char c : name) {
            sum += static_cast<int>(c);
        }
        return sum % size;
    }

public:
    HashTable(int s) : size(s) {
        table = new Node*[size]();
    }

    void insertName(const std::string& name) {
        int index = hash(name);
        Node* newNode = new Node(name);

        if (!table[index]) {
            table[index] = newNode;
            insertCounter++;
            return;
        }

        Node* current = table[index];
        Node* prev = nullptr;

        while (current && current->name < name) {
            insertCounter++;
            prev = current;
            current = current->next;
        }

        if (!prev) {
            newNode->next = table[index];
            table[index] = newNode;
        } else {
            newNode->next = current;
            prev->next = newNode;
        }
    }

    bool searchName(const std::string& name) {
        int index = hash(name);

        if (!table[index]) return false;

        Node* current = table[index];
        while (current) {
            searchCounter++;
            if (current->name == name) return true;
            if (current->name > name) return false;
            current = current->next;
        }
        return false;
    }
};

int main() {
    int tableSize;
    std::cout << "Enter hash table size (5, 10, 15, or 20): ";
    std::cin >> tableSize;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    HashTable table(tableSize);
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
                table.insertName(name);
                std::cout << "Insert operations: " << insertCounter << "\n";
                break;

            case 'b':
                std::cout << "Enter name to search: ";
                std::getline(std::cin, name);
                if (table.searchName(name)) {
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