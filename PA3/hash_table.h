#pragma once
#include <iostream>
#include <string>
#include "hash_function.h"
#include "shift_register.h"

using namespace std;


enum TableState {
    EMPTY,
    OCCUPIED,
    DELETED,
};


class HashTable {
public:
    HashTable(int table_size, HashFunction *hf, ShiftRegister *sr);
    ~HashTable();

    void print_table(ostream &out);

    void insert(int key);
    void erase(int key);

private:
    const int table_size;
    HashFunction *hf;
    ShiftRegister *sr;
    int *table;
    TableState *states;

    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////

    int cCnt = 0; //충돌횟수 카운트용 변수

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};

