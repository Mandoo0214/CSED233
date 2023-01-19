#pragma once
#include <string>

using namespace std;

struct Node {
  Node(char input_value) : value(input_value), left(NULL), right(NULL) {}
  char value;
  Node *left;
  Node *right;
};

class BinaryTree {
public:
  BinaryTree() { _root = NULL; };
  ~BinaryTree() {
    delete[] _root;
    _root = NULL;
  };
  void buildFromString(const char *data);

  string preOrder();
  string postOrder();
  string inOrder();
  int getDepth(int node_value);
  bool isProper();

private:
  Node *_root;
  Node *_buildFromString(const char *data, int start, int end);

  /////////////////////////////////////////////////////////
  //////  TODO: Add Private members if required ///////////
  
  void addStringpreOrder(string *answer, Node *Node);
  void addStringpostOrder(string *answer, Node *Node);
  void addStringinOrder(string *answer, Node *Node);

  int calDepth(const int target, Node *Node);
  bool whetherProper(Node *Node);

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
};