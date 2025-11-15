
#include <iostream>
#include <string>
#include "BST.h"


void displayMenu() {
    std::cout << "\nMenu:\n";
    std::cout << "1. Print AVL Tree\n";
    std::cout << "2. Delete values from file\n";
    std::cout << "3. Search values from file\n";
    std::cout << "4. Exit\n";
    std::cout << "Enter your choice: ";
}


int main() {
    BinarySearchTree bst;
    std::string inputFile, deleteFile, searchFile;
    int choice;

    std::cout << "Enter the input file with random values: ";
    std::cin >> inputFile;
    bst.loadFromFile(inputFile);

    while (true) {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                //std::cout << "AVL Tree In-Order Traversal:\n";
                //bst.print();
                break;

            case 2:
                std::cout << "Enter the file with values to delete: ";
                std::cin >> deleteFile;
                bst.deleteFromFile(deleteFile);
                // printing all the values in the avl tree to the console got too messy to work
                // std::cout << "Values deleted. Updated AVL Tree:\n";
                // avl.print();
                break;

            case 3:
                std::cout << "Enter the file with values to search: ";
                std::cin >> searchFile;
                bst.searchFromFile(searchFile);
                break;

            case 4:
                std::cout << "Exiting program.\n";
                return 0;

            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    return 0;
}