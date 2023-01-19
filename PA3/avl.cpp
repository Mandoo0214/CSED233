#include "tree.h"
#include "bst.h"
#include "avl.h"
#include <iostream>
#include <string>

using namespace std;


/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */

Node* AVLTree::_insertion(Node* node, int key)
{
    if (node == NULL) //���� ��尡 ����ִ� ��� �ش� �ڸ��� ���� �Ҵ� �� key ����
    {
        Node* newNode = new Node(key);
        return newNode;
    }

    else if (key < node->key) //���� ����� key���� key�� ���� ��� ���� Ʈ���� ��ȸ�ϸ� insertion ������ ����
        node->left = _insertion(node->left, key);

    else if (key > node->key) //���� ����� key���� key�� ū ��� ������ Ʈ���� ��ȸ�ϸ� insertion ������ ����
        node->right = _insertion(node->right, key);
    
    heightUpdate(node);
    node = balanceAVL(node, key); //AVL property�� ��ų �� �ֵ��� ����

    return node;
}

Node* AVLTree::_deletion(Node* node, Node* parent, int key)
{
    if (node == NULL)
        return node;

    if (key < node->key) //���� Ʈ���� ��ȸ�ϸ� deletion ������ �����ؾ� �ϴ� ��� (key�� ���� ����� key���� ���� ���)
        node->left = _deletion(node->left, node, key);

    else if (key > node->key) //���� Ʈ���� ��ȸ�ϸ� deletion ������ �����ؾ� �ϴ� ��� (key�� ���� ����� key���� ū ���)
        node->right = _deletion(node->right, node, key);

    else //key�� ���� ����� key�� ���� ���(node�� NULL�̰ų� Ʈ���� �������� �ʴ� ���� deletion �Լ����� �ɷ���)
    {
        if (node->left == NULL && node->right == NULL) //���� Ʈ���� 0���� �� (���� ����� ���)
        {
            if (parent)
            {
                if (parent->left == node)
                    parent->left = NULL;

                else if (parent->right == node)
                    parent->right = NULL;
            }

            node = NULL;
        }

        else if (node->left == NULL || node->right == NULL) //���� Ʈ���� 1���� ��
        {
            /* �����Ϸ��� ����� ���� Ʈ���� ���� */
            Node* temp = NULL;

            if (node->left != NULL)
                temp = node->left;

            else
                temp = node->right;

            /* �θ� ��尡 �ִ� ��� �����Ϸ��� ����� ���� Ʈ���� �θ� ��� ���� */
            if (parent)
            {
                if (parent->left == node)
                    parent->left = temp;

                else
                    parent->right = temp;
            }

            node = temp;
        }

        else if (node->left != NULL && node->right != NULL) //���� Ʈ���� 2���� ��
        {
            Node* minOfRight = findMin(node->right); //������ ����Ʈ������ �ּ��� ��带 ã��
            node->key = minOfRight->key; //������ ����Ʈ���� �ּ� ��� ���� �����Ϸ��� ���� ����ִ� ��忡 ������ �ֱ�

            node->right = _deletion(node->right, node, minOfRight->key); //������ ����Ʈ���� �ּ� ��� �����ϱ�
        }
    }

    if (node == NULL) //node�� NULL�� ��� ��ȯ
        return NULL;

    else
    {
        heightUpdate(node); //height ������Ʈ
        node = deleteBalance(node, key); //AVL property�� ��ų �� �ֵ��� ����

        return node;
    }
}

Node* AVLTree::balanceAVL(Node* node, int key)
{
    int bf = findBF(node);

    if (bf > 1 && key < node->left->key) //LL case
        return rotateToRight(node);

    if (bf < -1 && key > node->right->key) //RR case
        return rotateToLeft(node);

    if (bf > 1 && key > node->left->key) //LR case
    {
        node->left = rotateToLeft(node->left); //RR operation
        return rotateToRight(node); //LL operation
    }

    if (bf < -1 && key < node->right->key) //RL case
    {
        node->right = rotateToRight(node->right); //LL operation
        return rotateToLeft(node); //RR operation
    }

    return node;
}

Node* AVLTree::deleteBalance(Node* node, int key)
{
    if (findBF(node) > 1 && findBF(node->left) >= 0) //LL case
        return rotateToRight(node);

    if (findBF(node) < -1 && findBF(node->right) <= 0) //RR case
        return rotateToLeft(node);

    if (findBF(node) > 1 && findBF(node->left) < 0) //LR case
    {
        node->left = rotateToLeft(node->left); //RR operation
        return rotateToRight(node); //LL operation
    }

    if (findBF(node) < -1 && findBF(node->right) > 0) //RL case
    {
        node->right = rotateToRight(node->right); //LL operation
        return rotateToLeft(node); //RR operation
    }

    return node;
}

int AVLTree::findBF(Node* node)
{  
    int i;
    
    if (node->left == NULL && node->right == NULL) //���� ����� ���
        i = 0;

    else if (node->left == NULL && node->right != NULL) //������ ����Ʈ���� �����ϴ� ���
        i = -1 - node->right->height;

    else if (node->left != NULL && node->right == NULL) //���� ����Ʈ���� �����ϴ� ���
        i = node->left->height + 1;

    else if (node->left != NULL && node->right != NULL) //����Ʈ�� �� ���� ��� �����ϴ� ���
        i = node->left->height - node->right->height;

    return i;
}

Node* AVLTree::rotateToRight(Node* curNode)
{
    /* ȸ�� ���� ������ ���� �ӽ� ���� ���� */
    Node* temp = curNode->left;
    Node* tempChildren = temp->right;

    /* ȸ�� ���� */
    temp->right = curNode;
    curNode->left = tempChildren;

    /* height ������Ʈ */
    heightUpdate(curNode);
    heightUpdate(temp);

    return temp; //�ش� subtree�� ���ο� root node ��ȯ
}

Node* AVLTree::rotateToLeft(Node* node)
{
    /* ȸ�� ���� ������ ���� �ӽ� ���� ���� */
    Node* temp = node->right;
    Node* tempChildren = temp->left;

    /* ȸ�� ���� */
    temp->left = node;
    node->right = tempChildren;

    /* height ������Ʈ */
    heightUpdate(node);
    heightUpdate(temp);

    return temp; //�ش� subtree�� ���ο� root node ��ȯ
}

Node* AVLTree::findMin(Node* node)
{
    if (node == NULL)
        return NULL;

    if (node->left == NULL)
        return node;

    else
        return findMin(node->left);
}

bool AVLTree::isExist(Node* node, int key)
{
    if (node == NULL)
        return false;

    while (node) //Ʈ�� ���� �ش� key���� ���� ��尡 �����ϴ��� Ž��
    {
        if (key == node->key) //�ش� key���� ��尡 ���� ��� 1�� ��ȯ
            return true;

        else if (key < node->key)
            node = node->left;

        else
            node = node->right;
    }

    return false; //�ش� ��尡 ���� ��� 0�� ��ȯ
}

void AVLTree::heightUpdate(Node* node)
{
    if (node == NULL) //��尡 ������� ��� ����
        return;
    
    /* ��� height ������Ʈ */
    if (node->left == NULL && node->right == NULL) //���� ����� ���
        node->height = 0;

    else if (node->left == NULL && node->right != NULL) //������ ����Ʈ���� �����ϴ� ���
        node->height = 1 + node->right->height;

    else if (node->left != NULL && node->right == NULL) //���� ����Ʈ���� �����ϴ� ���
        node->height = 1 + node->left->height;

    else if (node->left != NULL && node->right != NULL) //����Ʈ�� �� ���� ��� �����ϴ� ���
        node->height = 1 + max(node->left->height, node->right->height);
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////


int AVLTree::insertion(int key)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    if (isExist(_root, key) == 1) //�̹� BST�� �����ϴ� ����̸� -1�� ��ȯ�ϰ� ����
        return -1;

    else //�������� �ʴ� ����̸� insertion ���� ����
    {
        _root = _insertion(_root, key);
        return 0;
    }

    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int AVLTree::deletion(int key)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    if (isExist(_root, key) == 0 || _root == NULL) //�������� �ʴ� ����̰ų� BST�� ����ִٸ� -1�� ��ȯ�ϰ� ����
        return -1;

    else //�����ϴ� ����̸� deletion ���� ����
    {
        _root = _deletion(_root, NULL, key);
        return 0;
    }

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}
