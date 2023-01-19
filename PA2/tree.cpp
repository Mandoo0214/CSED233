#include "tree.h"
#include <iostream>
#include <cstring>
#include <string>

using namespace std;

/* This is given function. DO NOT MODIFY THIS FUNCTION */
int findIndex(const char *str, int start, int end) {
  if (start > end)
    return -1;

  string s;

  for (int i = start; i <= end; i++) {

    // if open parenthesis, push it
    if (str[i] == '(')
      s.push_back(str[i]);

    // if close parenthesis
    else if (str[i] == ')') {
      if (s.back() == '(') {
        s.pop_back();

        if (!s.length())
          return i;
      }
    }
  }
  // if not found return -1
  return -1;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
Node *BinaryTree::_buildFromString(const char *data, int start, int end) {
  if (start > end)
    return NULL;

  Node *root = new Node(data[start]);
  int index = -1;

  if (start + 1 <= end && data[start + 1] == '(')
    index = findIndex(data, start + 1, end);

  if (index != -1) {
    root->left = _buildFromString(data, start + 2, index - 1);
    root->right = _buildFromString(data, index + 2, end - 1);
  }
  return root;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
void BinaryTree::buildFromString(const char *data) {
  Node *root = _buildFromString(data, 0, strlen(data) - 1);
  _root = root;
}

string BinaryTree::preOrder()
{ 
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  
  string answer = ""; //답을 출력해줄 string

  addStringpreOrder(&answer, _root); //preOrder Traversal 처리용 함수
  
  return answer;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string BinaryTree::postOrder()
{
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  string answer = ""; //답을 출력해줄 string

  addStringpostOrder(&answer, _root); //postOrder Traversal 처리용 함수
  
  return answer;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string BinaryTree::inOrder()
{
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  string answer = ""; //답을 출력해줄 string

  addStringinOrder(&answer, _root); //inOrder Traversal 처리용 함수
  
  return answer;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

int BinaryTree::getDepth(int node_value)
{
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  
  string pre = "";
  pre = preOrder(); //tree의 노드들을 모두 적은 string 생성 (앞서 만든 preorder 함수 사용)
  string cmp = "";
  cmp += to_string(node_value); //타겟 노드를 적은 string 생성

  int len = pre.length(); //tree 노드를 적은 string의 길이 저장
  int cnt = 0; //for문이 끝까지 반복되었는지 확인해줄 변수

  for(int i = 0; i <= len; i++) //tree의 노드와 타겟 노드를 모두 비교해줌
  {
    if (pre[i] == cmp[0])
      break;
    
    cnt++;
  }

  if (cnt >= len) //만약 타겟 노드가 tree에 없다면 -1을 리턴함
    return -1;

  else //타겟 노드가 tree에 존재할 경우 실행
  {
    int depth = 0; //depth를 저장하기 위한 변수

    depth = calDepth(node_value, _root) - 1; //마지막에 1이 더 더해졌으므로 1을 빼줌
  
    return depth;
  }

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

bool BinaryTree::isProper()
{ /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  
  bool truth;

  truth = whetherProper(_root);
  
  return truth;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional private functions  */

void BinaryTree::addStringpreOrder(string *answer, Node *Node)
{
  if(Node != NULL) //tree를 전부 순회할 때까지 반복
  {
    int buffer = Node->value - 48; //char 변수를 int로 받으며 값을 제대로 변경하기 위해 48을 빼줌
    
    *answer += to_string(buffer);
    *answer += " "; //부모 노드를 string에 먼저 저장

    addStringpreOrder(answer, Node->left); //부모 노드 저장 후 왼쪽 노드부터 순회
    addStringpreOrder(answer, Node->right); //왼쪽 subtree 순회 후 오른쪽 노드 순회
  }
}

void BinaryTree::addStringpostOrder(string *answer, Node *Node)
{
  if(Node != NULL) //tree를 전부 순회할 때까지 반복
  {
    addStringpostOrder(answer, Node->left); //왼쪽 맨 아래 노드부터 순회
    addStringpostOrder(answer, Node->right); //왼쪽 subtree 순회 후 오른쪽 맨 아래 노드부터 순회

    int buffer = Node->value - 48; //char 변수를 int로 받으며 값을 제대로 변경하기 위해 48을 빼줌

    *answer += to_string(buffer);
    *answer += " "; //왼쪽, 오른쪽 subtree 순회 후 부모 노드 string에 저장
  }
}

void BinaryTree::addStringinOrder(string *answer, Node *Node)
{
  if(Node != NULL) //tree를 전부 순회할 때까지 반복
  {
    addStringinOrder(answer, Node->left); //왼쪽 맨 아래 노드부터 순회

    int buffer = Node->value - 48; //char 변수를 int로 받으며 값을 제대로 변경하기 위해 48을 빼줌

    *answer += to_string(buffer);
    *answer += " "; //왼쪽 subtree 순회 후 부모 노드 string에 저장

    addStringinOrder(answer, Node->right); //왼쪽, 부모 노드 순회 후 오른쪽 맨 아래 노드부터 순회
  }
}

int BinaryTree::calDepth(const int target, Node *Node)
{
  int cmp = Node->value - 48; //target과 비교를 위해 int형으로 바꾸어주는 변수
  int depth = 0; //depth를 저장할 변수, root에서 시작하므로 0에서 시작

  if (Node == NULL) //terminal node일 때 정지
    return -100;

  if (cmp == target || (depth = calDepth(target, Node->left)) > 0 || (depth = calDepth(target, Node->right)) > 0) //타겟 노드로부터 root까지의 depth를 재귀함수로 계산
    return depth + 1;

  else
    return depth;    
}

bool BinaryTree::whetherProper(Node *Node)
{
  bool truth = true;  
  
  if(Node->left == NULL && Node->right == NULL) //자식 노드가 없을 경우 참
    truth = true;

  else if(Node->left != NULL && Node->right != NULL) //자식 노드가 2개일 경우
    truth = whetherProper(Node->left) && whetherProper(Node->right); //자식 노드에 대해서도 검사 실시

  else //자식 노드가 홀수 개일 경우
    truth = false;

  return truth;
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////