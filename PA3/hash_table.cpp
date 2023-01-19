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
    
    for (int i = 0; i < this->table_size; i++) //state �ʱ�ȭ
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

    int tempHf = hf->hashing(key) % table_size; //task 5�� hash function�� �����ؼ� mod table_size�� ���� ��
    
    if (this->states[tempHf] == EMPTY) //�浹 ���� �ٷ� �� ĭ�� ������ ���� �� ���� ��
    {
        this->table[tempHf] = key;
        this->states[tempHf] = OCCUPIED;
        cCnt = 0; //�浹 Ƚ�� �ʱ�ȭ
    }

    else //�浹�� �Ͼ�� ���
    {
        cCnt++; //�浹 Ƚ�� ������Ʈ
        
        int tempSr = this->sr->getSeqNumber(cCnt); //pseudo-random probing ������ ��
        tempHf = (hf->hashing(key) + tempSr) % table_size; //hash function + pseudo-random probing ���ؼ� mod table_size�� ���� ��

        if (this->states[tempHf] == EMPTY) //���� ���� ĭ�� ������ ���� �� ���� ��
        {
            this->table[tempHf] = key;
            this->states[tempHf] = OCCUPIED;
            cCnt = 0; //�浹 Ƚ�� �ʱ�ȭ
            return;
        }

        else //���� ���� ĭ���� ������ ���� �� ���� ��
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
