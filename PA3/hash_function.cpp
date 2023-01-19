#include "hash_function.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int HashFunction::hashing(int key)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    
    int* arr = new int[2 * key_size]; //2n ũ���� �迭 ����
    for (int i = 0; i < 2 * key_size; i++) //�迭 �ʱ�ȭ
    {
        arr[i] = 0;
    }

    int square = key * key, ind = 0; //key�� ����(10���� ����)�� �迭 �ε����� �����ϱ� ���� ���� ����
    while (square) //2������ ��ȯ�ϴ� ����
    {
        arr[ind] = square % 2;

        square /= 2;
        ind++;
    }

    ind = key_size - index_size / 2;
    int dec = 0, pow = 0; //mid-square�� 10������ �����ϱ� ���� ������ ������ ���� �����ϱ� ���� ���� ����
    for (int j = 0; j < index_size; j++) //2������ 10������ ��ȯ
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
