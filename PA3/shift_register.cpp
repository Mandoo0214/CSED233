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

    int rslt = 0; //최종 결과를 저장할 변수

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
    /* m이 2의 몇 제곱인지 계산하기 */
    int tempM = M;

    while (tempM)
    {
        tempM /= 2;
        max++;
    }

    /* k 2진수로 저장하기 */
    k_arr = new int[max - 1]; //배열 동적할당 (max - 1 크기로)

    for (int i = 0; i < max - 1; i++) //배열 초기화
        k_arr[i] = 0;

    int tempK = k;

    for (int j = 0; tempK; j++) //2진수로 변환(배열에 거꾸로 저장됨)
    {
        k_arr[j] = tempK % 2;
        tempK /= 2;
    }
}

void ShiftRegister::dec_to_binary(int target)
{
    cur_arr = new int[max - 1]; //배열 동적할당 (max - 1 크기로)

    for (int i = 0; i < max - 1; i++) //배열 초기화
        cur_arr[i] = 0;

    for (int j = 0; target; j++) //2진수로 변환(배열에 거꾸로 저장됨)
    {
        cur_arr[j] = target % 2;
        target /= 2;
    }
}

int ShiftRegister::arrayXor()
{
    int* temp = new int[max - 1]; //xor 연산을 위한 임시 배열 동적할당

    for (int i = 0; i < max - 1; i++) //배열에 xor 연산 결과 저장
        temp[i] = k_arr[i] ^ cur_arr[i];

    int dec = 0, pow = 0; //10진수로 저장할 변수, 제곱한 수 저장할 변수 선언

    for (int j = 0; j < max - 1; j++) //xor 연산 결과 10진수로 변환
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
