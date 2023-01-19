#pragma once
#include <iostream>
#include <string>
using namespace std;

class MaxHeap {

public:
    MaxHeap();

    int heap_size;
    int *heap_arr;

    void maxHeapProp(int);
    void insertKey(int);
    void deleteMax();
    string printHeap();

private:
    /////////////////////////////////////////////////////////
    //////  TODO: Add Private members if required ///////////

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};

