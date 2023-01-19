#pragma once
#include <iostream>
#include <string>
using namespace std;

class ShiftRegister {

public:
    ShiftRegister(int m, int k, int d) : M(m), k(k), initial_seed(d) { };

    int getSeqNumber(int idx); // idx starts from 1

private:
    int M;
    int k;
    int initial_seed;

    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////

    int max = 0; //m�� 2�� �� �������� ������ ����

    int* k_arr; //k�� 2������ ������ �迭
    int* cur_arr; //�� �ܰ躰 ������ ���ڸ� 2������ ������ �迭

    void init_set(); //k�� 2���� �迭�� �����ϰ�, m�� 2�� �� �������� ����ϴ� �Լ�
    void dec_to_binary(int target); //�� �ܰ躰 ������ ���ڸ� 2���� �迭�� �����ϴ� �Լ�
    int arrayXor(); //xor ������ �����ϴ� �Լ�

    int power(int base, int ex); //base�� ex�������ִ� �Լ�

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};

