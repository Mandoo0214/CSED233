#include "tree.h"
#include "bst.h"
#include <iostream>
#include <string>

using namespace std;

int BinarySearchTree::insertion(int key)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    if (isExist(_root, key) == 1) //이미 BST에 존재하는 노드이면 -1을 반환하고 종료
        return -1;

    else //존재하지 않는 노드이면 insertion 동작 수행
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

    if (isExist(_root, key) == 0 || _root == NULL) //존재하지 않는 노드이거나 BST가 비어있다면 -1을 반환하고 종료
        return -1;

    else //존재하는 노드이면 deletion 동작 수행
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
    if (node == NULL) //현재 노드가 비어있는 경우 해당 자리를 동적 할당 및 key 삽입
    {
        Node* newNode = new Node(key);
        return newNode;
    }
        
    else if (key < node->key) //현재 노드의 key보다 key가 작은 경우 왼쪽 트리로 순회하며 insertion 동작을 수행
        node->left = _insertion(node->left, key);

    else if (key > node->key) //현재 노드의 key보다 key가 큰 경우 오른쪽 트리로 순회하며 insertion 동작을 수행
        node->right = _insertion(node->right, key);

    return node;
}

Node* BinarySearchTree::_deletion(Node* node, Node* parent, int key)
{
    if (key < node->key) //왼쪽 트리로 순회하며 deletion 동작을 수행해야 하는 경우 (key가 현재 노드의 key보다 작은 경우)
        node->left = _deletion(node->left, node, key);

    else if (key > node->key) //왼쪽 트리로 순회하며 deletion 동작을 수행해야 하는 경우 (key가 현재 노드의 key보다 큰 경우)
        node->right = _deletion(node->right, node, key);

    else //key가 현재 노드의 key와 같은 경우(node가 NULL이거나 트리에 존재하지 않는 경우는 deletion 함수에서 걸러짐)
    {
        if (node->left == NULL && node->right == NULL) //서브 트리가 0개일 때 (리프 노드인 경우)
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

        else if (node->left == NULL || node->right == NULL) //서브 트리가 1개일 때
        {
            /* 삭제하려는 노드의 서브 트리를 복사 */
            Node* temp = NULL;

            if (node->left != NULL)
                temp = node->left;

            else
                temp = node->right;

            /* 부모 노드가 있는 경우 삭제하려는 노드의 서브 트리와 부모 노드 연결 */
            if (parent)
            {
                if (parent->left == node)
                    parent->left = temp;

                else
                    parent->right = temp;
            }

            node = temp;
        }

        else if (node->left != NULL && node->right != NULL) //서브 트리가 2개일 때
        {
            /* 오른쪽 서브트리에서 최소인 노드를 찾아 삭제하기 */
            Node* minOfRight = findMin(node->right);
            node = _deletion(_root, NULL, minOfRight->key);

            /* 오른쪽 서브트리의 최소 노드 값을 삭제하려는 값이 들어있는 노드에 복사해 넣기 */
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

    while (node) //트리 내에 해당 key값을 가진 노드가 존재하는지 탐색
    {
        if (key == node->key) //해당 key값의 노드가 있을 경우 1을 반환
            return true;

        else if (key < node->key)
            node = node->left;

        else
            node = node->right;
    }

    return false; //해당 노드가 없을 경우 0을 반환
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
