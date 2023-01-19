#include "heap.h"
#include <iostream>
#include <string>

using namespace std;


MaxHeap::MaxHeap() {
    heap_size = 0;
    heap_arr = new int[100]; // Default array of size 100
}

string MaxHeap::printHeap(){
    string answer;
    for (int i = 1; i <= heap_size; i++)
        answer += to_string(heap_arr[i]) + " ";
    return answer;
}

void MaxHeap::insertKey(int k)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    if (heap_size == 0) //heap에 노드를 처음 삽입할 때
    {
      heap_arr[1] = k; //배열의 [1] 자리에 노드 삽입
      heap_size++; //heap size 카운트
    }

    else if (heap_size > 0) //heap에 삽입된 노드가 존재할 때
    {
      heap_size++; //index 표현의 용이함을 위해 size 미리 카운트
      
      int ind = heap_size; //노드 비교용 변수
      int buffer = 0; //노드 교환 시 사용할 임시 변수
      
      heap_arr[heap_size] = k; //heap 맨 끝자리에 새로운 값 입력
      
      while (ind/2 >= 1 && k > heap_arr[ind/2])
      {
        buffer = heap_arr[ind/2];
        heap_arr[ind/2] = heap_arr[ind];
        heap_arr[ind] = buffer;

        ind /= 2;
      }
    }
  
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}


void MaxHeap::deleteMax()
{
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  heap_arr[1] = heap_arr[heap_size]; //root node 자리에 가장 끝 node를 삽입
  heap_size--; //heap size 업데이트

  int newroot = heap_arr[1]; //root node 자리에 삽입된 node의 값을 저장할 변수

  maxHeapProp(newroot);
  
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}


void MaxHeap::maxHeapProp(int i)
{
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  int buffer = 0; //node swap 시 사용할 임시 변수
  int ind = 2; //다음에 비교할 node index를 가리킬 지시용 변수
  int ip = 1; //받은 node값이 어디에 위치하는지 표시할 변수

  while (ind <= heap_size) //전체 heap을 모두 비교
  {
    if (i < heap_arr[ind] && heap_arr[ind] < heap_arr[ind + 1] && ind < heap_size && ind / 2 == (ind + 1) / 2) //같은 부모를 둔 자식 노드 두 개가 모두 i보다 크다면 둘 중 더 큰 것과 swap되어야 함
    {
      ind++;
      continue;
    }

    else if (i < heap_arr[ind]) //위의 경우에 속하지 않으면서 해당 노드의 값이 i보다 큰 경우
    {
      buffer = heap_arr[ind];
      heap_arr[ind] = heap_arr[ip];
      heap_arr[ip] = buffer;

      ip = ind; //받았던 i 값이 저장된 node 위치를 업데이트

      ind++;
    }

    else //해당 노드의 값이 i보다 작은 경우
    {
      ind++;
      continue;
    }
  }
  
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}