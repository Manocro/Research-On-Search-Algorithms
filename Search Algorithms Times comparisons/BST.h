#ifndef BST_H
#define BST_H

#include <iostream>
#include <chrono>
#include <fstream>

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
public:
    BinarySearchTree() : root(nullptr) {}

    // Insert a new node into the BST
    void insert(int value) {
        root = insertRec(root, value);
    }

    // Search for a node in the BST
    bool search(int value) {
        return searchRec(root, value);
    }

    // Delete a node from the BST
    void remove(int value) {
        root = removeRec(root, value);
    }
private:
    TreeNode* root;

    //insert a value
    TreeNode* insertRec(TreeNode* node, int value) {
        if (node == nullptr) {
            return new TreeNode(value);
        }
        if (value < node->data) {
            node->left = insertRec(node->left, value);
        }
        else if (value > node->data) {
            node->right = insertRec(node->right, value);
        }
        return node;
    }

    // search for a value
    bool searchRec(TreeNode* node, int value) {
        if (node == nullptr) {
            return false;
        }
        if (node->data == value) {
            return true;
        }
        else if (value < node->data) {
            return searchRec(node->left, value);
        }
        else {
            return searchRec(node->right, value);
        }
    }

    // delete a node
    TreeNode* removeRec(TreeNode* node, int value) {
        if (node == nullptr) {
            return node;
        }

        // Find the node to be deleted
        if (value < node->data) {
            node->left = removeRec(node->left, value);
        }
        else if (value > node->data) {
            node->right = removeRec(node->right, value);
        }
        else {
            // Node with one or no child
            if (node->left == nullptr) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }

            // Node with two children
            TreeNode* temp = minValueNode(node->right);
            node->data = temp->data;
            node->right = removeRec(node->right, temp->data);
        }
        return node;
    }

    //smallest value in a subtree
    TreeNode* minValueNode(TreeNode* node) {
        TreeNode* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }
public:
    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);

        if (!file.is_open())
        {
            std::cerr << "Error occurred while trying to open " << filename << std::endl;
            exit(EXIT_FAILURE);
        }
        int value;
        int numberOfInserts = 0;

        auto start = std::chrono::high_resolution_clock::now();
        while (file >> value) {
            insert(value);
            numberOfInserts++;
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "Execution time of insert is: " << duration << " ms" << std::endl;


        std::cout << "Number of successful inserts: "<< numberOfInserts << std::endl;
        file.close();
    }

    void deleteFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            std::cerr << "Error occurred while trying to open " << filename << std::endl;
            exit(EXIT_FAILURE);
        }

        int value;


        auto start = std::chrono::high_resolution_clock::now();
        while (file >> value) {
            remove(value);
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "Execution time of delete is: " << duration << " ms" << std::endl;

        file.close();
    }

    void searchFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            std::cerr << "Error occurred while trying to open " << filename << std::endl;
            exit(EXIT_FAILURE);
        }

        int value;
        int numberFound = 0;
        int numberNotFound = 0;

        auto start = std::chrono::high_resolution_clock::now();
        while (file >> value) {
            if (search(value)) {
                //std::cout << value << " found in the AVL tree.\n";
                numberFound++;
            }
            else {
                //std::cout << value << " not found in the AVL tree.\n";
                numberNotFound++;
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "Execution time of search is: " << duration << " ms" << std::endl;

        std::cout << "Numbers Found: " << numberFound << std::endl;
        std::cout << "Numbers not Found: " << numberNotFound << std::endl;

        file.close();
    }







};



#endif 