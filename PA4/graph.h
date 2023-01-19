#pragma once
#include <fstream>
#include <iostream>
#include <string>
#define NodeMaxCount 101
#define INF 2147483647 
using namespace std;

/////////////////////////////////////////////////////////
///  TODO: Add Your Struct or Functions if required /////
struct Node //graph의 vertex
{
    string vertexName = "";
    int NodeWeight = 0;
    bool isMarked = false;
    Node* adj = NULL;
};

struct NodeList //인접 리스트
{
    int NodeNumber = 0;
    Node* NList[NodeMaxCount];
};

struct Edge
{
    int weight;
    string from;
    string to;
};
///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

class Graph{
public:
    Graph() { };
    ~Graph() { };

    int addDirectedEdge(string nodeA, string nodeB);
    int addDirectedEdge(string nodeA, string nodeB, int weight);
    int addUndirectedEdge(string nodeA, string nodeB);
    int addUndirectedEdge(string nodeA, string nodeB, int weight);

    string DFS();
    int getTreeCount();
    string getStronglyConnectedComponent();
    string getDijkstraShortestPath(string source, string destination);
    string getFloydShortestPath(string source, string destination);
    int primMST(ofstream &, string startNode);
    int kruskalMST(ofstream &);


private:
    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////
    NodeList GraphNodeList;

    int isExist(string nodeName); //인접 리스트에 해당 vertexName의 노드가 존재하는지 검사하는 함수

    bool isRemain(); //인접 리스트에 방문하지 않은 노드가 있는지 검사하는 함수
    int findMin(string* visited, int ind); //인접 리스트 헤더에서 가장 작은 vertexName을 가지고 방문한 적 없는 노드를 찾는 함수
    string findMin(string nodeName, string* visited, int ind); //인접 리스트 중 특정 인덱스에서 가장 작은 vertexName을 가지고 방문한 적 없는 노드를 찾는 함수
    int findNode(string nodeName); //vertexName을 입력받았을 경우 인접 리스트의 헤더 중에서 해당 노드를 찾아주는 함수
    bool isVisited(string nodeName, string* visited, int ind); //해당 노드를 방문한 적 있는지 알려주는 함수

    int isCycleExist(int from, int now, string* visited, int* ind, bool* isCycle); //connected component 안에 cycle이 존재하는지 확인해주는 함수

    Graph getReverse(); //방향이 뒤집힌 그래프를 만들어주는 함수
    void storeAdj(int ind, string* visited, string* willVisit, int* wind, int* visitInd); //인접 리스트를 탐색하여 방문할 노드를 저장해주는 함수
    int hasSameLength(int* arr, string* vArr, int vind, int max, int* iInd); //SCC를 구할 때 max와 같은 길이의 SCC가 여러 개 있는지 확인해주는 함수
    void sortString(string* temp, int index); //string을 정렬해주는 함수
    int dfsForSCC(string* answer, int t, string* visited, int* visitInd); //SCC를 구할 때 사용할 특수한 dfs

    void graphToMatrix(int** graph, int nodeNumber); //인접 행렬을 만드는 함수
    void dfsForDijkstra(int** graph, int* distance, int start, string** prev); //다익스트라 dfs
    int findShortest(int* distance, int* haveToVisit, int ind); //가장 가까운 노드를 찾는 함수
    void addPathToString(int start, int final, string* answer, string** prev); //path 내의 노드를 string에 순차적으로 넣어주는 함수 
    void findErase(int* haveToVisit, int ind, int next); //방문한 노드를 방문해야 할 노드를 저장해둔 배열에서 지우는 함수
    bool hasOne(string nodeName, string prev); //이미 특정 노드를 경로에 포함하였는지 확인하는 함수

    void graphToMatrix5(int** graph, int nodeNumber); //task 5를 위한 인접 행렬 생성 함수
    void floyd(int** graph, int nodeNumber, int** path, int start, int final); //플로이드 알고리즘 진행 함수
    void addPath(int** path, string* answer, int start, int final); //string에 방문했던 노드를 순차적으로 넣어주는 함수

    bool alreadyHave(Node* haveToVisit, int* prev, int nodeInd, string nodeName, int target); //방문해야 할 노드를 저장해둔 배열에 특정 노드가 존재하는지 확인하는 함수
    void findEraseOne(Node* haveToVisit, int* nodeInd, int* prev, int weight, string nodeName); //방문해야 할 노드를 저장해둔 배열에서 특정 노드를 지우는 함수
    void findEraseAll(Node* haveToVisit, int* nodeInd, int* prev, string nodeName); //방문해야 할 노드를 저장해둔 배열에서 특정 노드 이름을 가진 원소 모두를 지우는 함수
    bool noWay(int target); //앞으로 나아갈 수 있는지 확인해주는 함수

    bool isThereOne(Edge* EList, int eInd, string newFrom, string newTo); //EList에 이미 존재하는 간선인지 확인하는 함수
    void initEList(Edge* EList, int* eInd, int nodeNumber); //EList를 정렬하여 채워주는 함수
    int whoIs(int* parent, string nodeName); //parent를 재귀 탐색하는 함수
    bool haveSameParent(int* parent, string from, string to); //해당 간선의 두 노드들을 모두 방문한 적이 있는지(parent 배열에서 같은 숫자로 표기되어 있는지) 확인해주는 함수
    void unionParent(int* parent, string from, string to); //방문한 간선에 연결된 노드들의 parent를 통합하여 업데이트해주는 함수

public:
    void dfs(string* answer, int t, string* visited, int* visitInd); //재귀 함수로 구현하기 위해 필요한 함수
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};
