/*MANUEL EDWARDO DE LA ROSA MODESTO.
#include <iostream>
#include <string>
#include <list>
#include "linked_list_imp.h"

template <typename T>
void menu() {
    std::list<T> myList;
    std::string inputFile, searchFile, deleteFile;
    char option;

    std::cout << "Enter the name of the input file with random values: ";
    std::cin >> inputFile;
    if (!readFromFile(inputFile, myList)) {
        return;
    }

    do {
        std::cout << "\nMenu:\n";
        std::cout << "1. Search values\n";
        std::cout << "2. Delete values\n";
        std::cout << "3. Print list\n";
        std::cout << "4. Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> option;

        switch (option) {
        case '1':
            std::cout << "Enter the name of the file with values to search: ";
            std::cin >> searchFile;
            searchValues(searchFile, myList);
            break;
        case '2':
            std::cout << "Enter the name of the file with values to delete: ";
            std::cin >> deleteFile;
            deleteValues(deleteFile, myList);
            break;
        case '3':
            printList(myList);
            break;
        case '4':
            std::cout << "Exiting program." << std::endl;
            break;
        default:
            std::cerr << "Invalid option. Please try again." << std::endl;
        }
    } while (option != '4');
}

int main() {
    char choice;
    std::cout << "Choose data type (s for string, i for integer, d for double): ";
    std::cin >> choice;

    switch (choice) {
    case 's':
        menu<std::string>();
        break;
    case 'i':
        menu<int>();
        break;
    case 'd':
        menu<double>();
        break;
    default:
        std::cerr << "Invalid choice." << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
*/