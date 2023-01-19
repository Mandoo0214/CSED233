#pragma once
#include "bst.h"

using namespace std;

class AVLTree: public BinarySearchTree
{
public:
    AVLTree() { };
    ~AVLTree() { };

    int insertion(int key);
    int deletion(int key);

private:
    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////

    Node* _insertion(Node* node, int key);
    Node* _deletion(Node* node, Node* parent, int key);
    
    Node* balanceAVL(Node* node, int key);
    Node* deleteBalance(Node* node, int key);
    int findBF(Node* node);

    Node* rotateToRight(Node* node);
    Node* rotateToLeft(Node* node);

    Node* findMin(Node* node);
    bool isExist(Node* node, int key);
    void heightUpdate(Node* node);

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};