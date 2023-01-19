#include <iostream>
#include <fstream>
#include <string>
#include "hash_function.h"
#include "shift_register.h"
#include "hash_table.h"

using namespace std;


HashTable::HashTable(int table_size, HashFunction *hf, ShiftRegister *sr) : table_size(table_size)
{
    this->hf = hf;
    this->sr = sr;
    this->table = new int[this->table_size];
    this->states = new TableState[this->table_size];

    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    
    /*  Write your codes if you need  */
    
    for (int i = 0; i < this->table_size; i++) //state 초기화
        states[i] = EMPTY;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

HashTable::~HashTable()
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    
    /*  Write your codes if you need  */
    
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////

    delete[] this->table;
    delete[] this->states;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
void HashTable::print_table(ostream &out)
{
    for (int i=0; i < this->table_size; i++)
    {
        out << i << ": ";
        if (this->states[i] == EMPTY)
            out << "empty" << endl;
        else if (this->states[i] == DELETED)
            out << "deleted" << endl;
        else if (this->states[i] == OCCUPIED)
            out << this->table[i] << endl;
        else
            out << "unknown state" << endl;
    }
}

void HashTable::insert(int key)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    int tempHf = hf->hashing(key) % table_size; //task 5의 hash function을 적용해서 mod table_size를 취한 값
    
    if (this->states[tempHf] == EMPTY) //충돌 없이 바로 빈 칸에 정보를 넣을 수 있을 때
    {
        this->table[tempHf] = key;
        this->states[tempHf] = OCCUPIED;
        cCnt = 0; //충돌 횟수 초기화
    }

    else //충돌이 일어났을 경우
    {
        cCnt++; //충돌 횟수 업데이트
        
        int tempSr = this->sr->getSeqNumber(cCnt); //pseudo-random probing 적용한 값
        tempHf = (hf->hashing(key) + tempSr) % table_size; //hash function + pseudo-random probing 더해서 mod table_size를 취한 값

        if (this->states[tempHf] == EMPTY) //새로 구한 칸에 정보를 넣을 수 있을 때
        {
            this->table[tempHf] = key;
            this->states[tempHf] = OCCUPIED;
            cCnt = 0; //충돌 횟수 초기화
            return;
        }

        else //새로 구한 칸에도 정보를 넣을 수 없을 때
            insert(key);
    }

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

void HashTable::erase(int key)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    for (int i = 0; i < table_size; i++)
    {
        if (this->table[i] == key)
        {
            this->states[i] = DELETED;
            this->table[i] = -100;
            break;
        }
    }

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
