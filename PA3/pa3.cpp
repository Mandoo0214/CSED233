/*
    Programming Assignment #3
    20210479 이주현
*/
#include <fstream>
#include <iostream>
#include <string>
#include <math.h>
#include "utils.h"
#include "tree.h"
#include "sort.h"
#include "bst.h"
#include "avl.h"
#include "hash_function.h"
#include "shift_register.h"
#include "hash_table.h"

using namespace std;


/*
    [Task 1] selection sort

    Description:
        Implement a function that sorts a given array using the selection sort algorithm in ascending order.
        You can modify sort.cpp and sort.h files for this problem.

        TODO: Implement sortAlg::selectionSort function

    Input:
        ('insertion',integer): insert integer into the array
        ('selectionSort',NULL): sort the array using selection sort algorithm

    Output:
        Every value in the array for each sorting step including the initial step,
        string separated with the white space (please use built-in function to print the array).
        You don’t need to consider exceptional cases such as overflow or an empty array.
        We will not test such cases.

*/

void task_1(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 1]" << endl;
    try {
        sortAlg sort;
        for (int i = 0; i < instr_seq.getLength(); i++) {
            string command = instr_seq.getInstruction(i).getCommand();
            if (command.compare("insertion") == 0) {
                sort.arr[sort.arr_size] = instr_seq.getInstruction(i).getValue();
                sort.arr_size++;
            } else if (command.compare("selectionSort") == 0) {
                sort.printArray(fout);
                sort.selectionSort(fout);
            } else {
                cerr << "Invalid command" << endl;
                exit(-1);
            }
        }
    } catch (const char *e) {
        cerr << e << endl;
    }
}

/*
    [Task 2] merge sort

    Description:
        Implement a function that sorts a given array using the merge sort
        algorithm in ascending order using non-recursive merge sort.
        You can modify sort.cpp and sort.h files for this problem.

        TODO: Implement sortAlg::mergeSort function
        TODO: Implement sortAlg::merge function

    Input:
        ('insertion',integer): insert integer into the array
        ('mergeSort',NULL): sort the array using merge sort algorithm

    Output:
        Every value in the array for each sorting step including the initial step,
        string separated with the white space (please use built-in function to print the array).
        You don’t need to consider exceptional cases such as overflow or an empty array.
        We will not test such cases.
*/

void task_2(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 2]" << endl;
    try {
        sortAlg sort;
        for (int i = 0; i < instr_seq.getLength(); i++) {
            string command = instr_seq.getInstruction(i).getCommand();
            if (command.compare("insertion") == 0) {
                sort.arr[sort.arr_size] = instr_seq.getInstruction(i).getValue();
                sort.arr_size++;
            } else if (command.compare("mergeSort") == 0) {
                sort.printArray(fout);
                sort.mergeSort(fout, 0, sort.arr_size - 1);
            } else {
                cerr << "Invalid command" << endl;
                exit(-1);
            }
        }
    } catch (const char *e) {
        cerr << e << endl;
    }
}

/*
    [Task 3] BST insertion / deletion

    Description:
        Implement a function that inserts and deletes an element into a BST.
        You can modify bst.cpp and bst.h files for this problem.

        TODO: Implementation BinarySearchTree::insertion function
        TODO: Implementation BinarySearchTree::deletion function

    Input of BinearySearchTree::insertion
        Key of the element to be inserted.

    Output of BinearySearchTree::insertion
        Return the -1 if the key already exists in the tree, 0 otherwise.
        (If the key already exists, do not insert the element)

    Input of BinearySearchTree::deletion
        Key of the element to be deleted.

    Output of BinearySearchTree::deletion
        Return the -1 if the key does not exist in the tree, 0 otherwise.
        (If the key does not exist, do not delete any element)

    task_3 prints
        the return for *each* insertion/deletion and
        the results of preorder and inorder traversal of the constructed tree.
*/

void task_3(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 3]" << endl;
    try {
        BinarySearchTree tree;
        int ret;
        for (int i = 0; i < instr_seq.getLength(); i++) {
            string command = instr_seq.getInstruction(i).getCommand();
            int key = instr_seq.getInstruction(i).getValue();
            if (command.compare("insertion") == 0) {
                ret = tree.insertion(key);
                fout << ret << endl;
            } else if (command.compare("deletion") == 0) {
                ret = tree.deletion(key);
                fout << ret << endl;
            } else {
                cerr << "Invalid command" << endl;
                exit(-1);
            }
        }
        fout << tree.preOrder() << endl;
        fout << tree.inOrder() << endl;
    } catch (const char *e) {
        cerr << e << endl;
    }
}

/*
    [Task 4] AVL tree insertion / deletion

    Description:
        Implement a function that inserts and deletes an element into a AVL tree.
        The insertion and deletion might cause the AVL tree to violate its properties (imbalance). 
        Your code should be able to resolve the various imbalance type (LL, LR, RL, RR) of the AVL tree. 
        You can modify avl.cpp and avl.h files for this problem. 

        TODO: Implementation AVLTree::insertion function
        TODO: Implementation AVLTree::deletion function

        Hint : suggest you to call 'insertion' and 'deletion' function in BinarySearchTree class 

    Input of AVLTree::insertion
        Key of the element to be inserted.

    Output of AVLTree::insertion
        Return -1 if the key already exists in the tree, 0 otherwise.
        (If the key already exists, do not insert the element)

    Input of AVLTree::deletion function
        Key of the element to  deleted

    Output of AVLTree::deletion
        Return -1 if the key does not exist in the tree, 0 otherwise.
        (If the key does not exist, do not delete any element)

    task_4 prints
        the return for *each* insertion/deletion and
        the results of preorder and inorder traversal of the constructed tree.
*/

void task_4(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 4]" << endl;
    try {
        AVLTree tree;
        int ret;
    for (int i = 0; i < instr_seq.getLength(); i++) {
        string command = instr_seq.getInstruction(i).getCommand();
            int key = instr_seq.getInstruction(i).getValue();
            if (command.compare("insertion") == 0) {
                ret = tree.insertion(key);
                fout << ret << endl;
            } else if (command.compare("deletion") == 0) {
                ret = tree.deletion(key);
                fout << ret << endl;
            } else {
                cerr << "Invalid command" << endl;
                exit(-1);
            }
        }
        fout << tree.preOrder() << endl;
        fout << tree.inOrder() << endl;
    } catch (const char *e) {
        cerr << e << endl;
    }
}

/*
    [Task 5] Mid-square hashing

    Description:
        Implement a mid-square hash function
        This hash function is used with n-bit integer keys \
          and hashing into a table of size 2^r, when r is even
        You can modify hash_function.cpp and hash_function.h files

        TODO: Implementation HashFunction::hashing function


    Input: Three commands (The order is always 'n', 'r', and 'key')
      - ('n', integer): The size of a key
      - ('r', integer): The size of an index
      - ('key', integer): A key to be hashed (in decimal)

    Output
      - The result (i.e. index) of hashing in decimal
*/

void task_5(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 5]" << endl;
    try {
        int n, r, key;
        int idx;
        HashFunction *hf;

        if (instr_seq.getLength() != 3 ||
            instr_seq.getInstruction(0).getCommand().compare("n") != 0 ||
            instr_seq.getInstruction(1).getCommand().compare("r") != 0 ||
            instr_seq.getInstruction(2).getCommand().compare("key") != 0) {
            cerr << "Invalid command" << endl;
            exit(-1);
        }

        n = instr_seq.getInstruction(0).getValue();
        r = instr_seq.getInstruction(1).getValue();
        key = instr_seq.getInstruction(2).getValue();
        hf = new HashFunction(n, r);

        idx = hf->hashing(key);

        fout << idx << endl;

        delete hf;
    } catch (const char *e) {
        cerr << e << endl;
    }
}

/*
    [Task 6] Shift-Register Sequence

    Description:
        Implement a function to generate a random permutation using a shift-register sequence.
        Given M (a power of 2), a constant k (1 ≤ k ≤ M - 1), and an initial sequence number d_1, then generates sequence d_2, d_3, d_4, ...
        We will use a below algorithm which is same as described in our Lecture note.
            1. Start with some number d1 such that 1 ≤ d_1 ≤ M – 1
            2. Repeat to generate successive numbers d_2, d_3, d_4, ...
                - Double the previous number (Left shift)
                - If the result ≥ M, then
                    - Subtract M and
                    - Take the "bitwise modulo-2 sum (bitwise XOR)" of
                        - the result &
                        - the selected constant k
        You can modify shift_register.cpp and shift_register.h files for this problem

        TODO: Implementation ShiftRegister::getSeqNumber function


    Input: Four commands (The order is always 'm', 'k', 'd' and 'i')
      - ('m', integer): the integer which is a power of 2
      - ('k', integer): the integer between 1 and M - 1
      - ('d', integer): the initial sequence number d_1 in decimal
      - ('i', integer): the target index of the sequence (starts from 1)

    Output
      - i-th number of the generated sequence in decimal (d_i)
*/

void task_6(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 6]" << endl;
    try {
        int m, k, d, i;
        int num;
        ShiftRegister *sr;

        if (instr_seq.getLength() != 4 ||
            instr_seq.getInstruction(0).getCommand().compare("m") != 0 ||
            instr_seq.getInstruction(1).getCommand().compare("k") != 0 ||
            instr_seq.getInstruction(2).getCommand().compare("d") != 0 ||
            instr_seq.getInstruction(3).getCommand().compare("i") != 0) {
            cerr << "Invalid command" << endl;
            exit(-1);
        }

        m = instr_seq.getInstruction(0).getValue();
        k = instr_seq.getInstruction(1).getValue();
        d = instr_seq.getInstruction(2).getValue();
        i = instr_seq.getInstruction(3).getValue();
        sr = new ShiftRegister(m, k, d);

        num = sr->getSeqNumber(i);

        fout << num << endl;

        delete sr;
    } catch (const char *e) {
        cerr << e << endl;
    }
}

/*
    [Task 7] Hash table

    Description:
        Implement a closed hash table with rehashing implementation.
        This hash table is used with n-bit integer keys \
          and hashing into a table of size 2^r, when r is even
        This hash table uses pseudo-random probing as a collision handling method.
        The index of the key k after i-th collision, h_i(k), is:
            h_i(k) = (h(k) + d_i) mod (2^r)
        when h is the hash function implemented in task_5,
        and d_i is the random permutation of integers 1, 2, ..., (2^r - 1) generated using the function implemented in task_6.
        You can modify hash_table.cpp and hash_table.h files for this problem.

        TODO: Implementation HashTable::insert & HashTable::erase functions


    Input: A sequence of commands
      - ('n', integer): The size of a key
                        (The first command is always 'n')
      - ('r', integer): The size of an index
                        (The second command is always 'r')
      - ('k', integer): the constant for shift-register sequence.
		                (The third command is always 'k')
      - ('d', integer): the initial sequence number of random permutation.
		                (The fourth command is always 'd')
      - ('insert', integer): Insert integer into the hash table
      - ('delete', integer): Delete integer from the hash table

    Output: For each slot of the hash table, print out
      - the value if the state of the slot is occupied
      - the state if the state of the slot is empty or deleted
*/

void task_7(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 7]" << endl;
    try {
        int n, r, k, d, key;
        HashFunction *hf;
        ShiftRegister *sr;
        HashTable *ht;

        if (instr_seq.getLength() < 4 ||
            instr_seq.getInstruction(0).getCommand().compare("n") != 0 ||
            instr_seq.getInstruction(1).getCommand().compare("r") != 0 ||
            instr_seq.getInstruction(2).getCommand().compare("k") != 0 ||
            instr_seq.getInstruction(3).getCommand().compare("d") != 0) {
            cerr << "Invalid starting commands" << endl;
            exit(-1);
        }

        n = instr_seq.getInstruction(0).getValue();
        r = instr_seq.getInstruction(1).getValue();
        k = instr_seq.getInstruction(2).getValue();
        d = instr_seq.getInstruction(3).getValue();
        hf = new HashFunction(n, r);
        sr = new ShiftRegister(pow(2, r), k, d);
        ht = new HashTable(pow(2, r), hf, sr);

        for (int i = 4; i < instr_seq.getLength(); i++) {
            string command = instr_seq.getInstruction(i).getCommand();
            int key = instr_seq.getInstruction(i).getValue();
            if (command.compare("insert") == 0) {
                ht->insert(key);
            } else if (command.compare("delete") == 0) {
                ht->erase(key);
            } else {
                cerr << "Invalid command" << endl;
                exit(-1);
            }
        }

        ht->print_table(fout);

        delete ht;
        delete sr;
        delete hf;
    } catch (const char *e) {
        cerr << e << endl;
    }
}

int main(int argc, char **argv) {
    string filename = "submit.txt";
    int task_num = 0;
    InstructionSequence instr_seq;

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
        try {
            instr_seq.parseInstructions(argv[2]);
        }
        catch (const char *e) {
            cerr << e << endl;
            return -1;
        }
    }

    // Running the task(s)
    switch (task_num) {
        case 1:
            task_1(fout, instr_seq);
            break;
        case 2:
            task_2(fout, instr_seq);
            break;
        case 3:
            task_3(fout, instr_seq);
            break;
        case 4:
            task_4(fout, instr_seq);
            break;
        case 5:
            task_5(fout, instr_seq);
            break;
        case 6:
            task_6(fout, instr_seq);
            break;
        case 7:
            task_7(fout, instr_seq);
            break;
        case 0:
            instr_seq.parseInstructions(TASK_1_DEFAULT_ARGUMENT);
            task_1(fout, instr_seq);

            instr_seq.parseInstructions(TASK_2_DEFAULT_ARGUMENT);
            task_2(fout, instr_seq);

            instr_seq.parseInstructions(TASK_3_DEFAULT_ARGUMENT);
            task_3(fout, instr_seq);

            instr_seq.parseInstructions(TASK_4_DEFAULT_ARGUMENT);
            task_4(fout, instr_seq);

            instr_seq.parseInstructions(TASK_5_DEFAULT_ARGUMENT);
            task_5(fout, instr_seq);

            instr_seq.parseInstructions(TASK_6_DEFAULT_ARGUMENT);
            task_6(fout, instr_seq);

            instr_seq.parseInstructions(TASK_7_DEFAULT_ARGUMENT);
            task_7(fout, instr_seq);
            break;
        default:
            cout << "Wrong task number" << endl;
    }

    fout.close();
    return 0;
}
