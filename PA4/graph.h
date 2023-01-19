#pragma once
#include <fstream>
#include <iostream>
#include <string>
#define NodeMaxCount 101
#define INF 2147483647 
using namespace std;

/////////////////////////////////////////////////////////
///  TODO: Add Your Struct or Functions if required /////
struct Node //graph�� vertex
{
    string vertexName = "";
    int NodeWeight = 0;
    bool isMarked = false;
    Node* adj = NULL;
};

struct NodeList //���� ����Ʈ
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

    int isExist(string nodeName); //���� ����Ʈ�� �ش� vertexName�� ��尡 �����ϴ��� �˻��ϴ� �Լ�

    bool isRemain(); //���� ����Ʈ�� �湮���� ���� ��尡 �ִ��� �˻��ϴ� �Լ�
    int findMin(string* visited, int ind); //���� ����Ʈ ������� ���� ���� vertexName�� ������ �湮�� �� ���� ��带 ã�� �Լ�
    string findMin(string nodeName, string* visited, int ind); //���� ����Ʈ �� Ư�� �ε������� ���� ���� vertexName�� ������ �湮�� �� ���� ��带 ã�� �Լ�
    int findNode(string nodeName); //vertexName�� �Է¹޾��� ��� ���� ����Ʈ�� ��� �߿��� �ش� ��带 ã���ִ� �Լ�
    bool isVisited(string nodeName, string* visited, int ind); //�ش� ��带 �湮�� �� �ִ��� �˷��ִ� �Լ�

    int isCycleExist(int from, int now, string* visited, int* ind, bool* isCycle); //connected component �ȿ� cycle�� �����ϴ��� Ȯ�����ִ� �Լ�

    Graph getReverse(); //������ ������ �׷����� ������ִ� �Լ�
    void storeAdj(int ind, string* visited, string* willVisit, int* wind, int* visitInd); //���� ����Ʈ�� Ž���Ͽ� �湮�� ��带 �������ִ� �Լ�
    int hasSameLength(int* arr, string* vArr, int vind, int max, int* iInd); //SCC�� ���� �� max�� ���� ������ SCC�� ���� �� �ִ��� Ȯ�����ִ� �Լ�
    void sortString(string* temp, int index); //string�� �������ִ� �Լ�
    int dfsForSCC(string* answer, int t, string* visited, int* visitInd); //SCC�� ���� �� ����� Ư���� dfs

    void graphToMatrix(int** graph, int nodeNumber); //���� ����� ����� �Լ�
    void dfsForDijkstra(int** graph, int* distance, int start, string** prev); //���ͽ�Ʈ�� dfs
    int findShortest(int* distance, int* haveToVisit, int ind); //���� ����� ��带 ã�� �Լ�
    void addPathToString(int start, int final, string* answer, string** prev); //path ���� ��带 string�� ���������� �־��ִ� �Լ� 
    void findErase(int* haveToVisit, int ind, int next); //�湮�� ��带 �湮�ؾ� �� ��带 �����ص� �迭���� ����� �Լ�
    bool hasOne(string nodeName, string prev); //�̹� Ư�� ��带 ��ο� �����Ͽ����� Ȯ���ϴ� �Լ�

    void graphToMatrix5(int** graph, int nodeNumber); //task 5�� ���� ���� ��� ���� �Լ�
    void floyd(int** graph, int nodeNumber, int** path, int start, int final); //�÷��̵� �˰��� ���� �Լ�
    void addPath(int** path, string* answer, int start, int final); //string�� �湮�ߴ� ��带 ���������� �־��ִ� �Լ�

    bool alreadyHave(Node* haveToVisit, int* prev, int nodeInd, string nodeName, int target); //�湮�ؾ� �� ��带 �����ص� �迭�� Ư�� ��尡 �����ϴ��� Ȯ���ϴ� �Լ�
    void findEraseOne(Node* haveToVisit, int* nodeInd, int* prev, int weight, string nodeName); //�湮�ؾ� �� ��带 �����ص� �迭���� Ư�� ��带 ����� �Լ�
    void findEraseAll(Node* haveToVisit, int* nodeInd, int* prev, string nodeName); //�湮�ؾ� �� ��带 �����ص� �迭���� Ư�� ��� �̸��� ���� ���� ��θ� ����� �Լ�
    bool noWay(int target); //������ ���ư� �� �ִ��� Ȯ�����ִ� �Լ�

    bool isThereOne(Edge* EList, int eInd, string newFrom, string newTo); //EList�� �̹� �����ϴ� �������� Ȯ���ϴ� �Լ�
    void initEList(Edge* EList, int* eInd, int nodeNumber); //EList�� �����Ͽ� ä���ִ� �Լ�
    int whoIs(int* parent, string nodeName); //parent�� ��� Ž���ϴ� �Լ�
    bool haveSameParent(int* parent, string from, string to); //�ش� ������ �� ������ ��� �湮�� ���� �ִ���(parent �迭���� ���� ���ڷ� ǥ��Ǿ� �ִ���) Ȯ�����ִ� �Լ�
    void unionParent(int* parent, string from, string to); //�湮�� ������ ����� ������ parent�� �����Ͽ� ������Ʈ���ִ� �Լ�

public:
    void dfs(string* answer, int t, string* visited, int* visitInd); //��� �Լ��� �����ϱ� ���� �ʿ��� �Լ�
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};
