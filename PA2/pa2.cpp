/*
    Programming Assignment #2
    20210479 이주현
*/
#include "heap.h"
#include "tree.h"
#include "utils.h"
#include <fstream>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

/*
    [Task 1] Quiz
    
    1-1.  Let T is a general tree and T’ is a binary tree converted from T. 
          Which of the following traversal visits the nodes in the same order \
            as the inorder traversal of T’?

          (1) Preorder traversal of T
          (2) Inorder traversal of T
          (3) Postorder traversal of T
          (4) None of the aboves


    1-2.  What is the time complexity of rearranging min-heap into max-heap?
          
          (1) O(1)
          (2) O(log n)
          (3) O(n)
          (4) O(2^n)

*/
void task_1(ofstream &fout, const char *quiz_num) {
  fout << "[Task 1]" << endl;
  int answer_1_1 = 3;  // TODO: Change to your answer
  int answer_1_2 = 3;  // TODO: Change to your answer

  if (!strcmp(quiz_num, "1")) {
    fout << answer_1_1 << endl;
  } else if (!strcmp(quiz_num, "2")) {
    fout << answer_1_2 << endl;
  } else {
    cerr << "Wrong quiz number:" << quiz_num << endl;
  }
}

/*
    [Task 2] Tree Traversal

    Description:
        Print the expected sequence of values of tree traversal
        TODO: Implement BinaryTree::preOrder, BinaryTree::postOrder and \
          BinaryTree::inOrder functions

    Input:
        - tree_string: string with bracket representation
        - traverse_mode: string that represent traverse mode \
            One of "preorder", "postorder", "inorder"

    Output:
        - sequence of values of tree traversal, separated with spacebar
*/
void task_2(ofstream &fout, const char *tree_string,
            const char *traverse_mode) {
  fout << "[Task 2]" << endl;
  try {
    BinaryTree tree;
    tree.buildFromString(tree_string);

    if (!strcmp(traverse_mode, "preorder")) {
      fout << tree.preOrder() << endl;
    } else if (!strcmp(traverse_mode, "postorder")) {
      fout << tree.postOrder() << endl;
    } else if (!strcmp(traverse_mode, "inorder")) {
      fout << tree.inOrder() << endl;
    } else {
      cerr << "invalid traverse mode" << endl;
    }
  } catch (const char *e) {
    cerr << e << endl;
  }
}

/*
    [Task 3] Tree Depth

    Description:
        Print the depth of the specific node in a given tree
        TODO: Implement BinaryTree::getDepth function

    Input:
        - tree_string: string with bracket representation (all node values in the tree are unique)
        - node_value : integer value which indicates specific node

    Output:
        - depth of the specific node in a given tree
        - return -1 if the specific node does not exist in given tree
*/
void task_3(ofstream &fout, const char *tree_string, int node_value) {
  fout << "[Task 3]" << endl;
  try {
    BinaryTree tree;
    tree.buildFromString(tree_string);
    fout << tree.getDepth(node_value) << endl;
  } catch (const char *e) {
    cerr << e << endl;
  }
}

/*
    [Task 4] Properness of Binary Tree

    Description:
        Check whether if the given tree is proper binary tree
        TODO: Implement BinaryTree::isProper function
        
    Input:
        - tree_string: string with bracket representation

    Output:
        - true if the given tree is proper binary tree
        - false otherwise
*/
void task_4(ofstream &fout, const char *tree_string) {
  fout << "[Task 4]" << endl;
  try {
    BinaryTree tree;
    tree.buildFromString(tree_string);
    fout << tree.isProper() << endl;
  } catch (const char *e) {
    cerr << e << endl;
  }
}

/*
    [Task 5] Max Heap Insertion

    Description:
        Insert a new element to a binary max heap.
        Heap should maintain the max heap property after the insertion.
        TODO: Implement MaxHeap::insertKey function

    Input:
        (‘insert’,integer): insert integer into the current max heap

    Output:
        Values in the heap in a node number order, in a string separated with
        the white space (automatically printed with built-in function)
        There will be no “error case” such as overflow, underflow or empty heap
*/
void task_5(ofstream &fout, InstructionSequence& instr_seq) {
  fout << "[Task 5]" << endl;
  try {
    MaxHeap heap;
    for (int i = 0; i < instr_seq.getLength(); i++) {
      string command = instr_seq.getInstruction(i).getCommand();
      if (command.compare("insert") == 0) {
        heap.insertKey(instr_seq.getInstruction(i).getValue());
      } else {
        cerr << "Invalid command" << endl;
        exit(-1);
      }
    }
    fout << heap.printHeap() << endl;
  } catch (const char *e) {
    cerr << e << endl;
  }
}

/*
    [Task 6] Max Heap Deletion

    Description:
        Delete the maximum value from the binary max heap.
        Heap should maintain the max heap property after the deletion.
        TODO: Implement MaxHeap::deleteMax function
        TODO: Implement MaxHeap::maxHeapProp function

    Input:
        (‘insert’,integer): insert integer into the current max heap
        (‘delMax’,NULL): delete maximum value from current binary max heap
          and rearrange heap to maintain the max heap property.

    Output:
        Values in the heap in a node number order, in a string separated with
        the white space (automatically printed with built-in function)
        There will be no “error case” such as overflow, underflow or empty heap
*/
void task_6(ofstream &fout, InstructionSequence& instr_seq) {
  fout << "[Task 6]" << endl;
  try {
    MaxHeap heap;
    for (int i = 0; i < instr_seq.getLength(); i++) {
      string command = instr_seq.getInstruction(i).getCommand();
      if (command.compare("insert") == 0) {
        heap.insertKey(instr_seq.getInstruction(i).getValue());

      } else if (command.compare("delMax") == 0) {
        heap.deleteMax();

      } else {
        cerr << "Invalid command" << endl;
        exit(-1);
      }
    }
    fout << heap.printHeap() << endl;
  } catch (const char *e) {
    cerr << e << endl;
  }
}


int main(int argc, char **argv) {
  string filename = "submit.txt";
  int task_num = 0;
  const char *instr_seq;
  int node_value;
  string result;
  InstructionSequence instr_seq_heap;

  // Open file
  ofstream fout;
  fout.open(filename, fstream::app);
  if (!fout.is_open()) {
    cerr << "Unable to open file: " << filename << endl;
    return -1;
  }

  // Choosing task number. Default is running ALL tasks (0)
  if (argc >= 2)
    task_num = atoi(argv[1]);
  if (argc >= 3) {
    instr_seq = argv[2];
    if (task_num == 3)
       node_value = atoi(argv[3]);
    if (task_num >= 5)
      instr_seq_heap.parseInstructions(argv[2]);
  }

  // Running the task(s)
  switch (task_num) {
  case 1:
    task_1(fout, instr_seq);
    break;
  case 2:
    task_2(fout, instr_seq, argv[3]);
    break;
  case 3:
    task_3(fout, instr_seq, node_value);
    break;
  case 4:
    task_4(fout, instr_seq);
    break;
  case 5:
    task_5(fout, instr_seq_heap);
    break;
  case 6:
    task_6(fout, instr_seq_heap);
    break;
  case 0:
    task_1(fout, "1");
    task_1(fout, "2");
    task_2(fout, TASK_2_DEFAULT_ARGUMENT, TASK_2_DEFAULT_ARGUMENT_2);
    task_3(fout, TASK_3_DEFAULT_ARGUMENT, TASK_3_DEFAULT_ARGUMENT_2);
    task_4(fout, TASK_4_DEFAULT_ARGUMENT);

    instr_seq_heap.parseInstructions(TASK_5_DEFAULT_ARGUMENT);
    task_5(fout, instr_seq_heap);

    instr_seq_heap.parseInstructions(TASK_6_DEFAULT_ARGUMENT);
    task_6(fout, instr_seq_heap);

    break;
  default:
    cout << "Wrong task number" << endl;
  }

  fout.close();
  return 0;
}