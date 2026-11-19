                                                                  Mini-Git
Mini-Git is a menu-driven command-line version control system built in C++. We created this project for our Project-Based Learning (PBL) coursework to simulate how Git manages staging areas, commit histories, status checks, and remote pushes using core data structures and file handling.
Features
•	1. init: Initializes the repository and creates a .minigit_config.txt configuration file.
•	2. add: Adds a filename to the staging area queue.
•	3. commit: Moves all staged files into a new commit node with a unique Commit ID and commit message.
•	4. undo: Pops and displays the most recent action recorded in the undo history stack.
•	5. push: Simulates pushing the commit history to a local remote file (.minigit_remote.txt).
•	6. status: Displays files currently waiting in the staging area along with the latest Commit ID.
•	7. log: Traverses and prints the full commit history (Commit ID, message, and committed files).
•	8. exit: Cleanly exits the CLI and frees allocated commit memory.
Data Structures & OOP Design
The project is structured into three main classes (CommitNode, Repository, and Menu) using standard C++ libraries:
•	Doubly Linked List (CommitNode): Stores the commit history. Each node holds a commitID, message, a vector<string> of committed files, and prev/next pointers, with head and tail tracked by Repository.
•	Queue (std::queue<string>): Used for the stagingArea so files are processed and committed in FIFO (First-In, First-Out) order.
•	Stack (std::stack<string>): Used for undoStack to track user operations (init, add, commit) in LIFO (Last-In, First-Out) order.
•	File Handling (<fstream>): Writes repository initialization state to .minigit_config.txt and exports commit logs to .minigit_remote.txt on push.

