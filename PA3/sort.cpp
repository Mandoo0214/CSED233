#include "sort.h"
#include <iostream>
#include <fstream>
#include <string>


sortAlg::sortAlg()
{
    arr_size = 0;
    arr = new int[100]; // Each test case will be less than 100 values
}

using namespace std;

void sortAlg::printArray(ofstream &fout)
{
    string answer;
    for (int i = 0; i < arr_size - 1; i++)
        answer += to_string(arr[i]) + " ";
    answer += to_string(arr[arr_size - 1]);
    fout << answer << endl;
}


void sortAlg::selectionSort(ofstream &fout)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    for (int i = 0; i < arr_size - 1; i++)
    {
        int minIndex = i; //처음에 최솟값을 i번째 값이라 가정

        for (int j = i + 1; j < arr_size; j++) //i 뒤쪽의 배열을 돌며 최솟값 탐색
        {
            if (arr[minIndex] > arr[j])
                minIndex = j;
        }

        if (arr[minIndex] != arr[i]) //최솟값이 i번째 값(자기자신)이 아닌 경우 swap 실시
        {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }

        printArray(fout); // DO NOT ERASE THIS LINE
    }

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}


void sortAlg::merge(int left, int right)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    int mid = (left + right) / 2, ind = 0; //중간값을 나타낼 변수 및 임시 배열의 인덱스를 세어줄 변수 선언
    if (arr_size % 2 == 0 && right == arr_size && left + right == arr_size) //전체 원소가 짝수 개인 리스트 전체를 합치는 경우 2개로 나눠진 리스트의 첫 번째 원소를 가리킬 수 있도록 함
        mid++;

    if (arr_size % 2 == 1 && right == arr_size && left + right == arr_size) //전체 원소가 홀수 개인 리스트 전체를 합치는 경우 맨 마지막 원소 하나를 알맞은 자리에 끼워넣는 것과 같음
        mid = arr_size - 1;

    int i = left, j = mid; //if문 조건 비교를 위한 임시 변수들

    int* temp = new int[20]; //배열 merge를 위한 임시 배열

    while (i < mid && j < right) //두 sublist를 정렬하여 합침
    {
        if (arr[i] <= arr[j])
        {
            temp[ind] = arr[i];
            i++;
        }

        else
        {
            temp[ind] = arr[j];
            j++;
        }
        
        ind++;
    }

    while (i < mid) //만약 어느 한 쪽의 list에 원소가 남았을 경우 차례대로 임시 배열에 저장함
    {
        temp[ind] = arr[i];
        ind++;
        i++;
    }

    while (j < right) //만약 어느 한 쪽의 list에 원소가 남았을 경우 차례대로 임시 배열에 저장함
    {
        temp[ind] = arr[j];
        ind++;
        j++;
    }

    for (int k = 0; k < right - left; k++) //임시 배열의 원소를 다시 arr에 복사해 넣음
    {
        arr[left + k] = temp[k];
    }

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}


void sortAlg::mergeSort(ofstream &fout, int left, int right)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    
    if (left < right)
    {
        for (int i = 1; i < arr_size; i *= 2)
        {
            for (int j = 0; j < arr_size - i; j += i * 2)
            {
                int end = min(j + i * 2, arr_size);

                merge(j, end);
                printArray(fout);// DO NOT ERASE THIS LINE
            }
        }
    }

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////

}
