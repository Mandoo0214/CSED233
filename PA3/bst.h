#pragma once
#include "tree.h"

using namespace std;

class BinarySearchTree: public BinaryTree {
public:
    BinarySearchTree() { };
    ~BinarySearchTree() { };

    int insertion(int key);
    int deletion(int key);

private:
    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////

    Node* _insertion(Node* node, int key);
    Node* _deletion(Node* node, Node* parent, int key);

    Node* findMin(Node* node);
    bool isExist(Node* node, int key);

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};