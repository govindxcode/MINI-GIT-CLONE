#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include <string>
using namespace std;

class Repository {
private:
    queue<string> stagingArea;
    stack<string> undoStack;
    bool isInitialized;

public:
    Repository() {
        isInitialized = false;
    }

    void init() {
        if (isInitialized) {
            cout << "Repository already initialized.\n";
            return;
        }

        ofstream file(".minigit_config.txt");

        if (file.is_open()) {
            file << "Mini-Git Initialized\n";
            file.close();

            isInitialized = true;
            undoStack.push("init");

            cout << "Repository initialized.\n";
        } else {
            cout << "Error initializing repository.\n";
        }
    }

    void add(string filename) {
        if (!isInitialized) {
            cout << "Run init first.\n";
            return;
        }

        stagingArea.push(filename);
        undoStack.push("add " + filename);

        cout << "Added: " << filename << "\n";
    }
};

class Menu {
public:
    void showMenu() {
        cout << "\n===== Mini-Git CLI =====\n";
        cout << "1. init\n";
        cout << "2. add\n";
        cout << "3. exit\n";
        cout << "Enter choice: ";
    }
};

int main() {
    Repository repo;
    Menu menu;

    int choice;
    string input;

    while (true) {
        menu.showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                repo.init();
                break;

            case 2:
                cout << "Enter filename: ";
                cin >> input;
                repo.add(input);
                break;

            case 3:
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid choice.\n";
                cin.clear();
                cin.ignore(10000, '\n');
        }
    }

    return 0;
}