//MANUEL EDWARDO DE LA ROSA MODESTO.
#ifndef LINKED_LIST_IMP_H
#define LINKED_LIST_IMP_H

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <algorithm>
#include <sstream>
#include <chrono>

/**
 * @brief Reads values from a file into a list.
 * @param filename The name of the file to read from.
 * @param list The list to store values in.
 * @return true if the file was successfully read, false otherwise.
 */
template <typename T>
bool readFromFile(const std::string& filename, std::list<T>& list) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "File " << filename << " cannot be opened." << std::endl;
        return false;
    }

    T value;
    std::string line;
    int successfulInserts = 0;
    int failedInserts = 0;
    auto start = std::chrono::high_resolution_clock::now();
    while (getline(file, line)) {
        std::istringstream iss(line);
        if (iss >> value) {
            list.push_back(value);
            ++successfulInserts; // increment successful inserts
        }
        else {

            ++failedInserts; // increment failed inserts
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Execution time of push_back is: " << duration << " ms" << std::endl;
    std::cout << "Successful inserts: " << successfulInserts << " failed inserts: " << failedInserts << std::endl;


    file.close();
    return true;
}

/**
 * @brief Searches for values from a file in the list and prints the results.
 * @param filename The name of the file with values to search for.
 * @param list The list to search in.
 */
template <typename T>
void searchValues(const std::string& filename, const std::list<T>& list) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "File " << filename << " cannot be opened." << std::endl;
        return;
    }

    T value;
    std::string line;
    int successfulSearches = 0;
    int failedSearches = 0;
    auto start = std::chrono::high_resolution_clock::now();
    while (getline(file, line)) {
        std::istringstream iss(line);
        if (iss >> value) {
            if (std::find(list.begin(), list.end(), value) != list.end()) {
                ++successfulSearches;
            }
            else {
                ++failedSearches;
            }
        }
        else {

        }


    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Execution time of find is: " << duration << " ms" << std::endl;
    std::cout << "Successful searches: " << successfulSearches << " failed searches: " << failedSearches << std::endl;
    file.close();
}

/**
 * @brief Deletes values from the list based on a specified file.
 * @param filename The name of the file with values to delete.
 * @param list The list to delete values from.
 */
template <typename T>
void deleteValues(const std::string& filename, std::list<T>& list) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "File " << filename << " cannot be opened." << std::endl;
        return;
    }

    T value;
    std::string line;

    int successfulDeletes = 0;
    int failedDeletes = 0;
    auto start = std::chrono::high_resolution_clock::now();
    while (getline(file, line)) {
        std::istringstream iss(line);
        if (iss >> value) {
            auto it = std::find(list.begin(), list.end(), value);
            if (it != list.end()) {
                list.erase(it);
                successfulDeletes++;
                //std::cout << "Value " << value << " deleted from the list." << std::endl;
            }
            else {
                failedDeletes++;
                //std::cout << "Value " << value << " not found in the list for deletion." << std::endl;
            }
        }
        else {

            //std::cerr << "Invalid data format in file " << filename << ": " << line << std::endl;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Execution time of erase is: " << duration << " ms" << std::endl;
    std::cout << "Successful deletes: " << successfulDeletes << " failed deletes: " << failedDeletes << std::endl;
    file.close();
}

/**
 * @brief Prints all values in the list.
 * @param list The list to print.
 */
template <typename T>
void printList(const std::list<T>& list) {
    std::cout << "Current list values:" << std::endl;
    for (const auto& value : list) {
        std::cout << value << std::endl;
    }
}

#endif // LINKED_LIST_IMP_H
