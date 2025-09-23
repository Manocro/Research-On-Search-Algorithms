///MANUEL EDWARDO DE LA ROSA MODESTO.
#include "hashtable.h"
#include <iostream>
#include <string>

int main() {
    std::string dataFile, searchFile, deleteFile;
    int choice;

    // Getting the data file name
    std::cout << "Enter the name of the file with random values: ";
    std::cin >> dataFile;

    // Initialize the hash table
    FibonacciHashTable hashTable(dataFile);

    // Main menu loop
    while (true) {
        std::cout << "\nMenu:\n";
        std::cout << "1. Search values from a file\n";
        std::cout << "2. Delete values from a file\n";
        std::cout << "3. Display the hash table\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Enter the name of the search file: ";
            std::cin >> searchFile;
            hashTable.searchFromFile(searchFile);
            break;
        case 2:
            std::cout << "Enter the name of the delete file: ";
            std::cin >> deleteFile;
            hashTable.deleteFromFile(deleteFile);
            break;
        case 3:
            hashTable.display();
            break;
        case 4:
            std::cout << "Exiting the program.\n";
            return 0;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
