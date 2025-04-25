#include <iostream>
#include <string>
using namespace std;
const int MAX_SIZE = 100;
unsigned long long insertCounter = 0;
unsigned long long searchCounter = 0;
struct NameDatabase {
    string names[MAX_SIZE];
    int size = 0;
    void insert(string name) {
        if(size < MAX_SIZE) {
            names[size++] = name;
            insertCounter++;
        }
    }
    bool search(string name) {
        for(int i = 0; i < size; i++) {
            searchCounter++;
            if(names[i] == name) return true;
        }
        return false;
    }
};
int main() {
    NameDatabase db;
    char choice;
    string name;
    while(true) {
        cout << "\na) Enter new name\nb) Search name\nc) Exit\nChoice: ";
        cin >> choice;
        cin.ignore();
        if(choice == 'a') {
            cout << "Enter name: ";
            getline(cin, name);
            db.insert(name);
            cout << "Inserted. Counter: " << insertCounter << " Size: " << db.size;
        } else if(choice == 'b') {
            cout << "Enter name to search: ";
            getline(cin, name);
            bool found = db.search(name);
            cout << (found ? "Found" : "Name not in database");
            cout << " Counter: " << searchCounter << " Size: " << db.size;
        } else if(choice == 'c') break;
    }
    return 0;
}