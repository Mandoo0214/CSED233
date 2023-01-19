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
    if (node == NULL) //현재 노드가 비어있는 경우 해당 자리를 동적 할당 및 key 삽입
    {
        Node* newNode = new Node(key);
        return newNode;
    }

    else if (key < node->key) //현재 노드의 key보다 key가 작은 경우 왼쪽 트리로 순회하며 insertion 동작을 수행
        node->left = _insertion(node->left, key);

    else if (key > node->key) //현재 노드의 key보다 key가 큰 경우 오른쪽 트리로 순회하며 insertion 동작을 수행
        node->right = _insertion(node->right, key);
    
    heightUpdate(node);
    node = balanceAVL(node, key); //AVL property를 지킬 수 있도록 조정

    return node;
}

Node* AVLTree::_deletion(Node* node, Node* parent, int key)
{
    if (node == NULL)
        return node;

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
            Node* minOfRight = findMin(node->right); //오른쪽 서브트리에서 최소인 노드를 찾기
            node->key = minOfRight->key; //오른쪽 서브트리의 최소 노드 값을 삭제하려는 값이 들어있는 노드에 복사해 넣기

            node->right = _deletion(node->right, node, minOfRight->key); //오른쪽 서브트리의 최소 노드 삭제하기
        }
    }

    if (node == NULL) //node가 NULL일 경우 반환
        return NULL;

    else
    {
        heightUpdate(node); //height 업데이트
        node = deleteBalance(node, key); //AVL property를 지킬 수 있도록 조정

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
    
    if (node->left == NULL && node->right == NULL) //리프 노드인 경우
        i = 0;

    else if (node->left == NULL && node->right != NULL) //오른쪽 서브트리만 존재하는 경우
        i = -1 - node->right->height;

    else if (node->left != NULL && node->right == NULL) //왼쪽 서브트리만 존재하는 경우
        i = node->left->height + 1;

    else if (node->left != NULL && node->right != NULL) //서브트리 두 개가 모두 존재하는 경우
        i = node->left->height - node->right->height;

    return i;
}

Node* AVLTree::rotateToRight(Node* curNode)
{
    /* 회전 동작 수행을 위한 임시 변수 선언 */
    Node* temp = curNode->left;
    Node* tempChildren = temp->right;

    /* 회전 동작 */
    temp->right = curNode;
    curNode->left = tempChildren;

    /* height 업데이트 */
    heightUpdate(curNode);
    heightUpdate(temp);

    return temp; //해당 subtree의 새로운 root node 반환
}

Node* AVLTree::rotateToLeft(Node* node)
{
    /* 회전 동작 수행을 위한 임시 변수 선언 */
    Node* temp = node->right;
    Node* tempChildren = temp->left;

    /* 회전 동작 */
    temp->left = node;
    node->right = tempChildren;

    /* height 업데이트 */
    heightUpdate(node);
    heightUpdate(temp);

    return temp; //해당 subtree의 새로운 root node 반환
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

void AVLTree::heightUpdate(Node* node)
{
    if (node == NULL) //노드가 비어있을 경우 리턴
        return;
    
    /* 노드 height 업데이트 */
    if (node->left == NULL && node->right == NULL) //리프 노드인 경우
        node->height = 0;

    else if (node->left == NULL && node->right != NULL) //오른쪽 서브트리만 존재하는 경우
        node->height = 1 + node->right->height;

    else if (node->left != NULL && node->right == NULL) //왼쪽 서브트리만 존재하는 경우
        node->height = 1 + node->left->height;

    else if (node->left != NULL && node->right != NULL) //서브트리 두 개가 모두 존재하는 경우
        node->height = 1 + max(node->left->height, node->right->height);
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////


int AVLTree::insertion(int key)
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

int AVLTree::deletion(int key)
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
