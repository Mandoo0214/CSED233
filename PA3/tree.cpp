#include "tree.h"
#include <iostream>
#include <string>

using namespace std;

string BinaryTree::inOrder() {
  string output;
  _inOrder(output, _root);
  if (!output.empty())
    output.pop_back();
  return output;
}

string BinaryTree::preOrder() {
  string output;
  _preOrder(output, _root);
  if (!output.empty())
    output.pop_back();
  return output;
}

void BinaryTree::_inOrder(string& output, Node *cur) {
  if(cur == NULL)
      return;

  _inOrder(output, cur->left);
  output.append(cur->print_key());
  output.append(" ");
  _inOrder(output, cur->right);
}

void BinaryTree::_preOrder(string& output, Node *cur) {
  if(cur == NULL)
      return;

  output.append(cur->print_key());
  output.append(" ");
  _preOrder(output, cur->left);
  _preOrder(output, cur->right);
}
