//MANUEL EDWARDO DE LA ROSA MODESTO.

#pragma once
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <cmath>
#include <string>
#include <chrono>

/*
@brief
In this implementation, I'm using fibonacci method for hashing and using simple chaining for handling the collisions. 
Idea of using the fibonacci method I found it online while searching on how to implement a hash table and which method was faster.
I used chatGPT in order to solve some of the problems while coding.
*/

class FibonacciHashTable {
private:
    std::vector<std::list<int>> table;
    size_t tableSize;
    const double A = (std::sqrt(5.0) - 1) / 2; // Golden ratio multiplier

    // Hash function using Fibonacci hashing
    size_t hash(int key) const {
        return static_cast<size_t>(tableSize * (key * A - std::floor(key * A)));
    }

    // Helper function to count the number of values in the file
    size_t countValuesInFile(const std::string& filename) {
        std::ifstream file(filename);
        size_t count = 0;
        int value;
        while (file >> value) {
            ++count;
        }
        return count;
    }

public:
    // Constructor: Initializes the hash table based on the number of values in the input file
    FibonacciHashTable(const std::string& dataFile) {
        tableSize = countValuesInFile(dataFile);
        table.resize(tableSize);
        loadDataFromFile(dataFile);
    }

    // Function to load data from the input file
    void loadDataFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            std::cerr << "Error occurred while trying to open " << filename << std::endl;
            exit(EXIT_FAILURE);
        }

        int value;
        auto start = std::chrono::high_resolution_clock::now();
        int numberOfInserts = 0;

        while (file >> value) {
            insert(value);
            numberOfInserts++;
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "Execution time of insert is: " << duration << " ms" << std::endl;


        std::cout << "Number of successful inserts: "<< numberOfInserts << std::endl;
    }

    // Insert a value into the hash table
    void insert(int key) {
        size_t index = hash(key);
        table[index].push_back(key);
    }

    // Search for a value in the hash table
    bool search(int key) const {
        size_t index = hash(key);
        for (const auto& value : table[index]) {
            if (value == key) {
                return true;
            }
        }
        return false;
    }

    // Delete a value from the hash table
    bool remove(int key) {
        size_t index = hash(key);
        auto& chain = table[index];
        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (*it == key) {
                chain.erase(it);
                return true;
            }
        }
        return false;
    }

    // Function to search for values from a file
    void searchFromFile(const std::string& searchFile) const {
        std::ifstream file(searchFile);
        if (!file.is_open())
        {
            std::cerr << "Error occurred while trying to open " << searchFile << std::endl;
            exit(EXIT_FAILURE);
        }

        int numberOfSuccessfulSearches = 0;
        int numberOfUnsuccessfulSearches = 0;
        auto start = std::chrono::high_resolution_clock::now();
        int value;
        while (file >> value) {
            if (search(value)) {
                numberOfSuccessfulSearches++;
            }
            else {
                //std::cout << value << " not found in the hash table.\n";
                numberOfUnsuccessfulSearches++;
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "Execution time of insert is: " << duration << " ms" << std::endl;


        std::cout << "Number of successful searches: "<< numberOfSuccessfulSearches << std::endl;
        std::cout << "Number of unsuccessful searches: "<< numberOfUnsuccessfulSearches << std::endl;
    }

    // Function to delete values from a file
    void deleteFromFile(const std::string& deleteFile) {
        std::ifstream file(deleteFile);
        if (!file.is_open())
        {
            std::cerr << "Error occurred while trying to open " << deleteFile << std::endl;
            exit(EXIT_FAILURE);
        }
        int value;
        int numberOfSuccessfulDeletes = 0;
        int numberOfUnsuccessfulDeletes = 0;

        auto start = std::chrono::high_resolution_clock::now();
        while (file >> value) {
            if (remove(value)) {
                //std::cout << value << " removed from the hash table.\n";
                numberOfSuccessfulDeletes++;
            }
            else {
                //std::cout << value << " not found in the hash table.\n";
                numberOfUnsuccessfulDeletes++;
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "Execution time of insert is: " << duration << " ms" << std::endl;
        std::cout << "Success successful deletes: " << numberOfSuccessfulDeletes << "\n";
        std::cout << "Unsuccessful deletes: " << numberOfUnsuccessfulDeletes << "\n";


    }

    // Display the hash table (for debugging purposes)
    void display() const {
        for (size_t i = 0; i < tableSize; ++i) {
            std::cout << "location " << i << ": ";
            for (const auto& value : table[i]) {
                std::cout << value << " -> ";
            }
            std::cout << "X\n";
        }
    }
};

#endif // HASHTABLE_H
