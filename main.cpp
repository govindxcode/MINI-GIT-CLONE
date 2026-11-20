#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include <string>
#include <vector>
using namespace std;


class CommitNode {
private:
    int commitID;
    string message;
    vector<string> files;
    CommitNode* prev;
    CommitNode* next;

public:
   
    CommitNode(int id, string msg, vector<string> f) {
        commitID = id;
        message = msg;
        files = f;
        prev = NULL;
        next = NULL;
    }

    // Allow Repository to access private data
    friend class Repository;
};

//main class
class Repository {
private:
    queue<string> stagingArea;
    stack<string> undoStack;
    CommitNode* head;
    CommitNode* tail;
    int commitCounter;
    bool isInitialized;

public:
    // Constructor
    Repository() {
        head = NULL;
        tail = NULL;
        commitCounter = 1;
        isInitialized = false;
    }

    //initialize repo
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

    // Add file to staging queue
    void add(string filename) {
        if (!isInitialized) {
            cout << "Run init first.\n";
            return;
        }

        stagingArea.push(filename);
        undoStack.push("add " + filename);

        cout << "Added: " << filename << "\n";
    }

    // Commit staged files
    void commit(string message) {
        if (!isInitialized) {
            cout << "Run init first.\n";
            return;
        }

        if (stagingArea.empty()) {
            cout << "Nothing to commit.\n";
            return;
        }

        vector<string> filesToCommit;

        while (!stagingArea.empty()) {
            filesToCommit.push_back(stagingArea.front());
            stagingArea.pop();
        }

        CommitNode* newCommit =
            new CommitNode(commitCounter++, message, filesToCommit);

        if (head == NULL) {
            head = newCommit;
            tail = newCommit;
        } else {
            tail->next = newCommit;
            newCommit->prev = tail;
            tail = newCommit;
        }

        undoStack.push("commit");

        cout << "Commit " << newCommit->commitID
             << " saved: " << message << "\n";
    }

    // Simulated git push to a local remote file
    void push() {
        if (!isInitialized) {
            cout << "Run init first.\n";
            return;
        }

        if (head == NULL) {
            cout << "No commits to push.\n";
            return;
        }

        ofstream remote(".minigit_remote.txt", ios::app);

        if (!remote.is_open()) {
            cout << "Unable to open remote file.\n";
            return;
        }

        CommitNode* current = head;

        while (current != NULL) {
            remote << "Commit ID: " << current->commitID << "\n";
            remote << "Message: " << current->message << "\n";
            remote << "Files:\n";

            for (int i = 0; i < current->files.size(); i++) {
                remote << "  " << current->files[i] << "\n";
            }

            remote << "--------------------\n";
            current = current->next;
        }

        remote.close();

        cout << "Push successful!\n";
        cout << "Commits saved to .minigit_remote.txt\n";
    }

    // Undo last recorded action
    //Stack stores the last commit on the top and deletes the top when we want to undo any last commit.

    void undo() {
        if (undoStack.empty()) {
            cout << "No actions to undo.\n";
            return;
        }

        cout << "Last action: " << undoStack.top() << "\n";
        undoStack.pop();
        cout << "Action removed from undo history.\n";
    }

    // NEW FUNCTIONALITY : Show repository status
    void status() {
        if (!isInitialized) {
            cout << "Run init first.\n";
            return;
        }

        cout << "\n===== Repository Status =====\n";

        if (stagingArea.empty()) {
            cout << "Staging area is empty.\n";
        } else {
            cout << "Files ready to commit:\n";

            queue<string> temp = stagingArea;

            while (!temp.empty()) {
                cout << "- " << temp.front() << "\n";
                temp.pop();
            }
        }

        if (head == NULL) {
            cout << "No commits yet.\n";
        } else {
            cout << "Latest Commit ID: " << tail->commitID << "\n";
        }
    }

    // NEW FUNCTIONALITY : Show commit history
    void log() {
        if (!isInitialized) {
            cout << "Run init first.\n";
            return;
        }

        if (head == NULL) {
            cout << "No commits found.\n";
            return;
        }

        cout << "\n===== Commit History =====\n";

        CommitNode* current = head;

        while (current != NULL) {
            cout << "\nCommit ID: " << current->commitID;
            cout << "\nMessage: " << current->message;
            cout << "\nFiles:\n";

            for (int i = 0; i < current->files.size(); i++) {
                cout << "- " << current->files[i] << "\n";
            }

            cout << "--------------------\n";

            current = current->next;
        }
    }
    // NEW FUNCTIONALITY : Clear staged files from the staging area
    void clearStaging() {
        if (!isInitialized) {
            cout << "Run init first.\n";
            return;
        }

        if (stagingArea.empty()) {
            cout << "Staging area is already empty.\n";
            return;
        }

        while (!stagingArea.empty()) {
            stagingArea.pop();
        }

        undoStack.push("clear");
        cout << "Staging area cleared.\n";
    }
    void version() {
        cout << "\n===== Mini-Git Version =====\n";
        cout << "Mini-Git Version: 1.0.0\n";
        cout << "Project: Mini-Git CLI\n";
        cout << "Language: C++\n";
        cout << "Developer: Shantanu\n";
        cout << "Status: Running Successfully\n";
    }


    // Destructor
    //Every time a new commit is made a new node is created, created a destructor to free up the memory allocated in heap to avoid memory leaks
    ~Repository() {
        CommitNode* current = head;

        while (current != NULL) {
            CommitNode* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
};

//menu
class Menu {
public:
    void showMenu() {
        cout << "\n===== Mini-Git CLI =====\n";
        cout << "1. init\n";
        cout << "2. add\n";
        cout << "3. commit\n";
        cout << "4. undo\n";
        cout << "5. push\n";
        cout << "6. status\n";
        cout << "7. log\n";
        cout << "8. clear\n";
        cout<<"9. verison\n";
        cout<<"10. exit\n";
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
                cout << "Enter commit message: ";
                cin.ignore(10000, '\n');
                getline(cin, input);
                repo.commit(input);
                break;

            case 4:
                repo.undo();
                break;

            case 5:
                repo.push();
                break;

            case 6:
                repo.status();
                break;

            case 7:
                repo.log();
                break;

            case 8:
                repo.clearStaging();
                break;

             case 9:
                repo.version();
                break;

            case 10:
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
