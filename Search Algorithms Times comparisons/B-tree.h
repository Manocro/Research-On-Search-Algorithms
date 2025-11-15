//Jane Nim
//Team Project

#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

//https://www.geeksforgeeks.org/introduction-of-b-tree-2/

class BTreeNode {
public:
    std::vector<int> keys;
    std::vector<BTreeNode*> children;
    bool leaf;
    int t;

    BTreeNode(int _t, bool _leaf) : t(_t), leaf(_leaf) {
        keys.resize(2 * t - 1);
        children.resize(2 * t);
    }

    int findKey(int key) {
        int idx = 0;
        while (idx < keys.size() && keys[idx] < key)
            idx++;
        return idx;
    }

    void insertNonFull(int key);
    void splitChild(int i, BTreeNode* y);
    BTreeNode* search(int key);
    void remove(int key);
    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);
    int getPred(int idx);
    int getSucc(int idx);
    void fill(int idx);
    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);
    void merge(int idx);
};

class BTree {
public:
    BTreeNode* root;
    int t;

    explicit BTree(int _t) : root(nullptr), t(_t) {}

    void insert(int key);
    BTreeNode* search(int key) const {
        return (root == nullptr) ? nullptr : root->search(key);
    }
    void remove(int key) {
        if (!root) return;
        root->remove(key);
        if (root->keys.empty()) {
            BTreeNode* temp = root;
            root = (root->leaf) ? nullptr : root->children[0];
            delete temp;
        }
    }
    void loadFromFile(const std::string& filename);
    void deleteFromFile(const std::string& filename);
    void searchFromFile(const std::string& filename) const;

};

void BTree::insert(int key) {
    if (!root) {
        root = new BTreeNode(t, true);
        root->keys.push_back(key); // Use push_back instead of resize
    }
    else {
        if (root->keys.size() == 2 * t - 1) {
            BTreeNode* s = new BTreeNode(t, false);
            s->children.push_back(root); // Use push_back instead of indexing
            s->splitChild(0, root);
            int i = 0;
            if (s->keys.size() > 0 && s->keys[0] < key)
                i++;
            s->children[i]->insertNonFull(key);
            root = s;
        }
        else {
            root->insertNonFull(key);
        }
    }
}

void BTreeNode::insertNonFull(int key) {
    int i = keys.size() - 1;
    if (leaf) {
        while (i >= 0 && keys[i] > key) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys.push_back(key); // Use push_back instead of indexing
    }
    else {
        while (i >= 0 && keys[i] > key)
            i--;
        if (i + 1 < children.size() && children[i + 1]->keys.size() == 2 * t - 1) {
            splitChild(i + 1, children[i + 1]);
            if (i + 1 < keys.size() && keys[i + 1] < key)
                i++;
        }
        if (i + 1 < children.size()) // Check bounds before accessing children
            children[i + 1]->insertNonFull(key);
    }
}


void BTreeNode::splitChild(int i, BTreeNode* y) {
    BTreeNode* z = new BTreeNode(y->t, y->leaf);
    z->keys.resize(t - 1);
    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];
    if (!y->leaf) {
        z->children.resize(t);
        for (int j = 0; j < t; j++)
            z->children[j] = y->children[j + t];
    }
    y->keys.resize(t - 1);
    children.insert(children.begin() + i + 1, z);
    keys.insert(keys.begin() + i, y->keys[t - 1]);
}

BTreeNode* BTreeNode::search(int key) {
    int i = 0;
    while (i < keys.size() && key > keys[i])
        i++;
    if (i < keys.size() && keys[i] == key)
        return this;
    if (leaf)
        return nullptr;
    return children[i]->search(key);
}

void BTreeNode::remove(int key) {
    int idx = findKey(key);
    if (idx < keys.size() && keys[idx] == key) {
        if (leaf)
            removeFromLeaf(idx);
        else
            removeFromNonLeaf(idx);
    }
    else {
        if (leaf) return;
        bool flag = (idx == keys.size());
        if (children[idx]->keys.size() < t)
            fill(idx);
        if (flag && idx > keys.size())
            children[idx - 1]->remove(key);
        else
            children[idx]->remove(key);
    }
}

void BTreeNode::removeFromLeaf(int idx) {
    keys.erase(keys.begin() + idx);
}

void BTreeNode::removeFromNonLeaf(int idx) {
    int k = keys[idx];
    if (children[idx]->keys.size() >= t) {
        int pred = getPred(idx);
        keys[idx] = pred;
        children[idx]->remove(pred);
    }
    else if (children[idx + 1]->keys.size() >= t) {
        int succ = getSucc(idx);
        keys[idx] = succ;
        children[idx + 1]->remove(succ);
    }
    else {
        merge(idx);
        children[idx]->remove(k);
    }
}

int BTreeNode::getPred(int idx) {
    BTreeNode* cur = children[idx];
    while (!cur->leaf)
        cur = cur->children[cur->keys.size()];
    return cur->keys[cur->keys.size() - 1];
}

int BTreeNode::getSucc(int idx) {
    BTreeNode* cur = children[idx + 1];
    while (!cur->leaf)
        cur = cur->children[0];
    return cur->keys[0];
}

void BTreeNode::fill(int idx) {
    if (idx != 0 && children[idx - 1]->keys.size() >= t)
        borrowFromPrev(idx);
    else if (idx != keys.size() && children[idx + 1]->keys.size() >= t)
        borrowFromNext(idx);
    else {
        if (idx != keys.size())
            merge(idx);
        else
            merge(idx - 1);
    }
}

void BTreeNode::borrowFromPrev(int idx) {
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx - 1];
    child->keys.insert(child->keys.begin(), keys[idx - 1]);
    if (!child->leaf)
        child->children.insert(child->children.begin(), sibling->children.back());
    keys[idx - 1] = sibling->keys.back();
    sibling->keys.pop_back();
    if (!sibling->leaf)
        sibling->children.pop_back();
}

void BTreeNode::borrowFromNext(int idx) {
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx + 1];
    child->keys.push_back(keys[idx]);
    if (!child->leaf)
        child->children.push_back(sibling->children[0]);
    keys[idx] = sibling->keys[0];
    sibling->keys.erase(sibling->keys.begin());
    if (!sibling->leaf)
        sibling->children.erase(sibling->children.begin());
}

void BTreeNode::merge(int idx) {
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx + 1];
    child->keys.push_back(keys[idx]);
    for (int i = 0; i < sibling->keys.size(); i++)
        child->keys.push_back(sibling->keys[i]);
    if (!child->leaf) {
        for (int i = 0; i <= sibling->children.size(); i++)
            child->children.push_back(sibling->children[i]);
    }
    keys.erase(keys.begin() + idx);
    children.erase(children.begin() + idx + 1);
    delete sibling;
}

void BTree::loadFromFile(const std::string& filename) {
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

void BTree::deleteFromFile(const std::string& filename) {
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

void BTree::searchFromFile(const std::string& filename) const {
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
