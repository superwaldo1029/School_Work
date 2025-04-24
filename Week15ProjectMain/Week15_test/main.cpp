#include <iostream>
#include <string>
using namespace std;

// -------- Unsorted Array Implementation --------
const int MAX_SIZE = 100;
struct ArrayCounter {
    unsigned long long insert = 0;
    unsigned long long search = 0;
};

struct NameDatabase {
    string names[MAX_SIZE];
    int size = 0;
    ArrayCounter counter;

    void insert(string name) {
        if(size < MAX_SIZE) {
            names[size++] = name;
            counter.insert++;
        }
    }

    bool search(string name) {
        for(int i = 0; i < size; i++) {
            counter.search++;
            if(names[i] == name) return true;
        }
        return false;
    }
};

// -------- Sorted Linked List Implementation --------
struct LinkedCounter {
    unsigned long long insert = 0;
    unsigned long long search = 0;
};

struct Node {
    string name;
    Node* next;
    Node(string n): name(n), next(nullptr) {}
};

struct LinkedList {
    Node *head = nullptr, *mid = nullptr;
    int size = 0;
    LinkedCounter counter;

    void updateMid() {
        if(size <= 1) {
            mid = head;
            return;
        }
        Node* slow = head;
        Node* fast = head->next;
        while(fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        mid = slow;
    }

    void insert(string name) {
        Node* newNode = new Node(name);
        if(!head || head->name > name) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* curr = head;
            while(curr->next && curr->next->name < name) {
                counter.insert++;
                curr = curr->next;
            }
            newNode->next = curr->next;
            curr->next = newNode;
        }
        size++;
        updateMid();
    }

    bool search(string name) {
        if(!mid) return false;
        if(name <= mid->name) {
            Node* curr = head;
            while(curr != mid->next) {
                counter.search++;
                if(curr->name == name) return true;
                if(curr->name > name) return false;
                curr = curr->next;
            }
        } else {
            Node* curr = mid;
            while(curr) {
                counter.search++;
                if(curr->name == name) return true;
                if(curr->name > name) return false;
                curr = curr->next;
            }
        }
        return false;
    }

    ~LinkedList() {
        while(head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// -------- Hash Table Implementation --------
struct HashCounter {
    unsigned long long insert = 0;
    unsigned long long search = 0;
};

struct HashTable {
    Node** table;
    int tableSize;
    int size = 0;
    HashCounter counter;

    HashTable(int s): tableSize(s) {
        table = new Node*[tableSize]();
    }

    int hash(string name) {
        int sum = 0;
        for(char c : name) sum += c;
        return sum % tableSize;
    }

    void insert(string name) {
        int idx = hash(name);
        Node* newNode = new Node(name);
        if(!table[idx]) {
            table[idx] = newNode;
        } else {
            Node* curr = table[idx];
            Node* prev = nullptr;
            while(curr && curr->name < name) {
                counter.insert++;
                prev = curr;
                curr = curr->next;
            }
            if(!prev) {
                newNode->next = table[idx];
                table[idx] = newNode;
            } else {
                newNode->next = curr;
                prev->next = newNode;
            }
        }
        size++;
    }

    bool search(string name) {
        int idx = hash(name);
        Node* curr = table[idx];
        while(curr) {
            counter.search++;
            if(curr->name == name) return true;
            if(curr->name > name) return false;
            curr = curr->next;
        }
        return false;
    }

    ~HashTable() {
        for(int i = 0; i < tableSize; i++) {
            Node* curr = table[i];
            while(curr) {
                Node* temp = curr;
                curr = curr->next;
                delete temp;
            }
        }
        delete[] table;
    }
};

// Simple test data
const string TEST_NAMES[] = {
    "Michael", "Scott", "Dwight", "Schrute", "Jim", 
    "Halpert", "Pam", "Beesly", "Ryan", "Howard",
    "Angela", "Martin", "Andy", "Bernard", "Kelly", 
    "Kapoor", "Kevin", "Malone", "Toby", "Flenderson",
    "Meredith", "Palmer", "Stanley", "Hudson", "Darryl", 
    "Philbin", "Creed", "Bratton", "Jan", "Levinson",
    "Phyllis", "Vance", "Oscar", "Martinez", "Erin", 
    "Hannon", "Gabe", "Lewis", "David", "Wallace",
    "Robert", "California", "Holly", "Flax", "Roy", 
    "Anderson", "Karen", "Filippelli", "Charles", "Miner"
};

void printResults(const string& title, unsigned long long insertOps, unsigned long long searchOps) {
    cout << "\n" << string(50, '-');
    cout << "\n" << title;
    cout << "\nInsert Operations: " << insertOps;
    cout << "\nSearch Operations: " << searchOps;
}

int main() {
    const int TEST_SIZE = 50;

    // Test Array Implementation
    {
        NameDatabase arrayDb;

        // Insert Test
        for(int i = 0; i < TEST_SIZE; i++) {
            arrayDb.insert(TEST_NAMES[i]);
        }

        // Search Test
        for(int i = 0; i < 10; i++) {
            arrayDb.search(TEST_NAMES[i]);  // Existing names
        }
        arrayDb.search("NotInDatabase");   // Worst case

        printResults("Array Implementation",
                    arrayDb.counter.insert,
                    arrayDb.counter.search);
    }

    // Test Linked List Implementation
    {
        LinkedList listDb;

        // Insert Test
        for(int i = 0; i < TEST_SIZE; i++) {
            listDb.insert(TEST_NAMES[i]);
        }

        // Search Test
        for(int i = 0; i < 10; i++) {
            listDb.search(TEST_NAMES[i]);  // Existing names
        }
        listDb.search("NotInDatabase");   // Worst case

        printResults("Linked List Implementation",
                    listDb.counter.insert,
                    listDb.counter.search);
    }

    // Test Hash Table Implementation
    {
        HashTable hashDb(20);  // Size 20 for 50 names

        // Insert Test
        for(int i = 0; i < TEST_SIZE; i++) {
            hashDb.insert(TEST_NAMES[i]);
        }

        // Search Test
        for(int i = 0; i < 10; i++) {
            hashDb.search(TEST_NAMES[i]);  // Existing names
        }
        hashDb.search("NotInDatabase");   // Worst case

        printResults("Hash Table Implementation",
                    hashDb.counter.insert,
                    hashDb.counter.search);
    }

    cout << "\n" << string(50, '-') << "\n";
    return 0;
}