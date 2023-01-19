#include "hash_function.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int HashFunction::hashing(int key)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    
    int* arr = new int[2 * key_size]; //2n 크기의 배열 선언
    for (int i = 0; i < 2 * key_size; i++) //배열 초기화
    {
        arr[i] = 0;
    }

    int square = key * key, ind = 0; //key의 제곱(10진수 형태)와 배열 인덱스를 저장하기 위한 변수 선언
    while (square) //2진수로 변환하는 과정
    {
        arr[ind] = square % 2;

        square /= 2;
        ind++;
    }

    ind = key_size - index_size / 2;
    int dec = 0, pow = 0; //mid-square를 10진수로 저장하기 위한 변수와 제곱한 수를 저장하기 위한 변수 선언
    for (int j = 0; j < index_size; j++) //2진수를 10진수로 변환
    {
        pow = power(2, j);
        dec += arr[ind] * pow;
        ind++;
    }
        
    return dec;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */

int HashFunction::power(int base, int ex)
{
    int rslt = 1;
    
    for (int i = 0; i < ex; i++)
    {
        rslt *= base;
    }

    return rslt;
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
