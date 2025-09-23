//JANE NIM
#pragma once
#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

class AVLTree {
private:
    struct Node {
        int value;
        Node* left;
        Node* right;
        int height;

        Node(int val) : value(val), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    // Helper functions
    int getHeight(Node* node) {
        return node ? node->height : 0;
    }

    int getBalance(Node* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
        return y;
    }

    Node* insert(Node* node, int value) {
        if (!node) return new Node(value);

        if (value < node->value) {
            node->left = insert(node->left, value);
        }
        else if (value > node->value) {
            node->right = insert(node->right, value);
        }
        else {
            return node; // Duplicates are not allowed
        }

        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
        int balance = getBalance(node);

        // Balancing the tree
        if (balance > 1 && value < node->left->value) return rotateRight(node);
        if (balance < -1 && value > node->right->value) return rotateLeft(node);
        if (balance > 1 && value > node->left->value) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && value < node->right->value) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left) current = current->left;
        return current;
    }

    Node* deleteNode(Node* root, int value) {
        if (!root) return root;

        if (value < root->value) {
            root->left = deleteNode(root->left, value);
        }
        else if (value > root->value) {
            root->right = deleteNode(root->right, value);
        }
        else {
            if (!root->left || !root->right) {
                Node* temp = root->left ? root->left : root->right;
                if (!temp) {
                    temp = root;
                    root = nullptr;
                }
                else {
                    *root = *temp;
                }
                delete temp;
            }
            else {
                Node* temp = minValueNode(root->right);
                root->value = temp->value;
                root->right = deleteNode(root->right, temp->value);
            }
        }

        if (!root) return root;

        root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;
        int balance = getBalance(root);

        // Balancing the tree
        if (balance > 1 && getBalance(root->left) >= 0) return rotateRight(root);
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
        if (balance < -1 && getBalance(root->right) <= 0) return rotateLeft(root);
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    bool search(Node* node, int value) {
        if (!node) return false;
        if (value == node->value) return true;
        if (value < node->value) return search(node->left, value);
        return search(node->right, value);
    }

    void printInOrder(Node* node) {
        if (!node) return;
        printInOrder(node->left);
        std::cout << node->value << " ";
        printInOrder(node->right);
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(int value) {
        root = insert(root, value);
    }

    void deleteValue(int value) {
        root = deleteNode(root, value);
    }

    bool search(int value) {
        return search(root, value);
    }

    void print() {
        printInOrder(root);
        std::cout << std::endl;
    }

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
            deleteValue(value);
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

#endif // AVLTREE_H
