#include "tree.h"
#include "bst.h"
#include <iostream>
#include <string>

using namespace std;

int BinarySearchTree::insertion(int key)
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

int BinarySearchTree::deletion(int key)
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

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */

Node* BinarySearchTree::_insertion(Node* node, int key)
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

    return node;
}

Node* BinarySearchTree::_deletion(Node* node, Node* parent, int key)
{
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
            /* ������ ����Ʈ������ �ּ��� ��带 ã�� �����ϱ� */
            Node* minOfRight = findMin(node->right);
            node = _deletion(_root, NULL, minOfRight->key);

            /* ������ ����Ʈ���� �ּ� ��� ���� �����Ϸ��� ���� ����ִ� ��忡 ������ �ֱ� */
            node->key = minOfRight->key;
        }
    }

    return node;
}

Node* BinarySearchTree::findMin(Node* node)
{
    if (node == NULL)
        return NULL;

    if (node->left == NULL)
        return node;

    else
        return findMin(node->left);
}

bool BinarySearchTree::isExist(Node* node, int key)
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

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
