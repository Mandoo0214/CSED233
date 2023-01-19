#include "shift_register.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int ShiftRegister::getSeqNumber(int idx)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    
    init_set();

    int rslt = 0; //���� ����� ������ ����

    for (int i = 1; i <= idx; i++)
    {
        if (i == 1)
        {
            rslt = initial_seed;
            continue;
        }

        else if (i == 2)
            rslt = 2 * initial_seed;

        else
            rslt *= 2;

        if (rslt >= M)
        {
            rslt -= M;
            dec_to_binary(rslt);
            rslt = arrayXor();
        }
    }

    return rslt;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */

void ShiftRegister::init_set()
{
    /* m�� 2�� �� �������� ����ϱ� */
    int tempM = M;

    while (tempM)
    {
        tempM /= 2;
        max++;
    }

    /* k 2������ �����ϱ� */
    k_arr = new int[max - 1]; //�迭 �����Ҵ� (max - 1 ũ���)

    for (int i = 0; i < max - 1; i++) //�迭 �ʱ�ȭ
        k_arr[i] = 0;

    int tempK = k;

    for (int j = 0; tempK; j++) //2������ ��ȯ(�迭�� �Ųٷ� �����)
    {
        k_arr[j] = tempK % 2;
        tempK /= 2;
    }
}

void ShiftRegister::dec_to_binary(int target)
{
    cur_arr = new int[max - 1]; //�迭 �����Ҵ� (max - 1 ũ���)

    for (int i = 0; i < max - 1; i++) //�迭 �ʱ�ȭ
        cur_arr[i] = 0;

    for (int j = 0; target; j++) //2������ ��ȯ(�迭�� �Ųٷ� �����)
    {
        cur_arr[j] = target % 2;
        target /= 2;
    }
}

int ShiftRegister::arrayXor()
{
    int* temp = new int[max - 1]; //xor ������ ���� �ӽ� �迭 �����Ҵ�

    for (int i = 0; i < max - 1; i++) //�迭�� xor ���� ��� ����
        temp[i] = k_arr[i] ^ cur_arr[i];

    int dec = 0, pow = 0; //10������ ������ ����, ������ �� ������ ���� ����

    for (int j = 0; j < max - 1; j++) //xor ���� ��� 10������ ��ȯ
    {
        pow = power(2, j);
        dec += temp[j] * pow;
    }

    return dec;
}

int ShiftRegister::power(int base, int ex)
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
