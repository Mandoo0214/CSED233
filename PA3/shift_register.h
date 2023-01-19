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

    int max = 0; //m이 2의 몇 제곱인지 저장할 변수

    int* k_arr; //k를 2진수로 저장할 배열
    int* cur_arr; //각 단계별 생성된 숫자를 2진수로 저장할 배열

    void init_set(); //k를 2진수 배열로 저장하고, m이 2의 몇 제곱인지 계산하는 함수
    void dec_to_binary(int target); //각 단계별 생성된 숫자를 2진수 배열로 저장하는 함수
    int arrayXor(); //xor 동작을 수행하는 함수

    int power(int base, int ex); //base를 ex제곱해주는 함수

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};

