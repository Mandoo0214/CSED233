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
        int minIndex = i; //ó���� �ּڰ��� i��° ���̶� ����

        for (int j = i + 1; j < arr_size; j++) //i ������ �迭�� ���� �ּڰ� Ž��
        {
            if (arr[minIndex] > arr[j])
                minIndex = j;
        }

        if (arr[minIndex] != arr[i]) //�ּڰ��� i��° ��(�ڱ��ڽ�)�� �ƴ� ��� swap �ǽ�
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

    int mid = (left + right) / 2, ind = 0; //�߰����� ��Ÿ�� ���� �� �ӽ� �迭�� �ε����� ������ ���� ����
    if (arr_size % 2 == 0 && right == arr_size && left + right == arr_size) //��ü ���Ұ� ¦�� ���� ����Ʈ ��ü�� ��ġ�� ��� 2���� ������ ����Ʈ�� ù ��° ���Ҹ� ����ų �� �ֵ��� ��
        mid++;

    if (arr_size % 2 == 1 && right == arr_size && left + right == arr_size) //��ü ���Ұ� Ȧ�� ���� ����Ʈ ��ü�� ��ġ�� ��� �� ������ ���� �ϳ��� �˸��� �ڸ��� �����ִ� �Ͱ� ����
        mid = arr_size - 1;

    int i = left, j = mid; //if�� ���� �񱳸� ���� �ӽ� ������

    int* temp = new int[20]; //�迭 merge�� ���� �ӽ� �迭

    while (i < mid && j < right) //�� sublist�� �����Ͽ� ��ħ
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

    while (i < mid) //���� ��� �� ���� list�� ���Ұ� ������ ��� ���ʴ�� �ӽ� �迭�� ������
    {
        temp[ind] = arr[i];
        ind++;
        i++;
    }

    while (j < right) //���� ��� �� ���� list�� ���Ұ� ������ ��� ���ʴ�� �ӽ� �迭�� ������
    {
        temp[ind] = arr[j];
        ind++;
        j++;
    }

    for (int k = 0; k < right - left; k++) //�ӽ� �迭�� ���Ҹ� �ٽ� arr�� ������ ����
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
