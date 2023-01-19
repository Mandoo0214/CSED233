#include "graph.h"
#include <fstream>
#include <iostream>
#include <string>
#define INF 2147483647 
using namespace std;


/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////
/*  Write your codes if you have additional functions  */
int Graph::isExist(string nodeName)
{
    for (int i = 0; i < GraphNodeList.NodeNumber; i++)
    {
        if (GraphNodeList.NList[i]->vertexName == nodeName) //�̹� ����Ʈ�� �ִ� ���Ҷ�� �ش� ���Ұ� ����� �ε����� ��ȯ
            return i;
    }

    return -100;
}

bool Graph::isRemain()
{
    for (int i = 0; i < GraphNodeList.NodeNumber; i++)
    {
        if (GraphNodeList.NList[i]->isMarked)
            continue;

        else //�湮�� �� ���� ��尡 ���� ��� true ��ȯ (Ž�� �����ϵ��� ��)
            return true;
    }

    return false;
}

int Graph::findMin(string* visited, int ind)
{
    if (ind == 0)
    {
        int min = 0;

        for (int i = 0; i < GraphNodeList.NodeNumber; i++)
        {
            /* vertexName�� min���� �۰�, �湮�� �� ���� ����� min�� ���� */
            if (GraphNodeList.NList[min]->vertexName > GraphNodeList.NList[i]->vertexName && GraphNodeList.NList[i]->isMarked == false)
                min = i;

            else
                continue;
        }

        return min;
    }
    
    else
    {
        string haveToVisit[NodeMaxCount];
        int index = 0;

        /* �湮�ؾ� �ϴ� ��常�� ��� �迭�� ���� */
        for (int i = 0; i < GraphNodeList.NodeNumber; i++)
        {
            if (GraphNodeList.NList[i]->isMarked == false)
            {
                haveToVisit[index] = GraphNodeList.NList[i]->vertexName;
                index++;
            }
        }

        /* haveToVisit�� ������ ���鸸�� ���Ͽ� ���� ���� vertexName�� ��� */
        int min = 0;

        for (int i = 0; i < index; i++)
        {
            if (haveToVisit[min] > haveToVisit[i])
                min = i;
        }

        /* �ش� vertexName�� ���� ��带 �ٽ� ���� ����Ʈ ������� ã�Ƴ��� �ε����� ��ȯ */
        string target = haveToVisit[min];
        int t = findNode(target);

        return t;
    }
}

string Graph::findMin(string nodeName, string* visited, int ind)
{
    /* �Է¹��� nodeName�� ���� ��� ã�� */
    int target = 0;
    
    for (int i = 0; i < GraphNodeList.NodeNumber; i++)
    {
        if (nodeName == GraphNodeList.NList[i]->vertexName)
        {
            target = i;
            break;
        }
    }

    /* �ش� ����� ���� ����Ʈ���� ���� ���� vertexName�� �������� �湮�� �� ���� ��� ã�� */
    Node* temp = GraphNodeList.NList[target]->adj;
    string haveToVisit[NodeMaxCount];

    int cnt = 0;

    /* �湮�� �� ���� ���� ����Ʈ�� ��常 ���� ���� */
    while (temp != NULL)
    {
        if (!isVisited(temp->vertexName, visited, ind))
        {
            haveToVisit[cnt] = temp->vertexName;
            cnt++;
        }

        temp = temp->adj;            
    }

    string t = "";

    if (cnt == 0) //���� ����Ʈ �� �湮�� �� ���� ��尡 ���ٸ� �� string�� ��ȯ
        return t;

    else //���� ����Ʈ �� �湮�� �� ���� ��尡 ���� ���
    {
        t = haveToVisit[0];

        for (int i = 1; i < cnt; i++)
        {
            if (t > haveToVisit[i])
                t = haveToVisit[i];
        }

        return t;
    }
}

int Graph::findNode(string nodeName)
{
    int t = 0;

    for (int i = 0; i < GraphNodeList.NodeNumber; i++)
    {
        if (nodeName == GraphNodeList.NList[i]->vertexName) //���޹��� vertexName�� ���� ��带 ã���� �ε����� ��ȯ
        {
            t = i;
            break;
        }
    }

    return t;
}

void Graph::dfs(string* answer, int t, string* visited, int* visitInd)
{
    /* �湮�� ��忡 �湮 ���� ǥ�� �� answer�� vertexName �߰� */
    GraphNodeList.NList[t]->isMarked = true;
    *answer += GraphNodeList.NList[t]->vertexName;
    *answer += " ";

    /* visited �迭�� �湮�� ����� vertexName �߰� */
    int index = *visitInd;

    visited[index] = GraphNodeList.NList[t]->vertexName;
    (* visitInd)++;

    /* ���� ����Ʈ ���� ��带 ��ȸ */
    while ((findMin(GraphNodeList.NList[t]->vertexName, visited, *visitInd)) != "")
    {
        string target = findMin(GraphNodeList.NList[t]->vertexName, visited, *visitInd);
        int t1 = findNode(target);
        dfs(answer, t1, visited, visitInd);
    }
}

bool Graph::isVisited(string nodeName, string* visited, int ind)
{
    for (int i = 0; i < ind; i++)
    {
        if (nodeName == visited[i]) //�湮�ߴ� ������ ������ �迭 ���� ���޹��� vertexName�� �ִٸ�(i.e. �湮�� �� �ִٸ�) true ��ȯ
            return true;
    }

    return false;
}

int Graph::isCycleExist(int from, int now, string* visited, int* ind, bool* isCycle)
{
    if (*isCycle == true)
        return 0;

    /* �湮�� ��忡 �湮 ���� ǥ�� �� visited �迭�� �湮�� ����� vertexName �߰� */
    GraphNodeList.NList[now]->isMarked = true;

    int index = *ind;

    visited[index] = GraphNodeList.NList[now]->vertexName;
    (*ind)++;

    Node* temp = GraphNodeList.NList[now]->adj;
    while (temp != NULL)
    {
        if (temp->vertexName == GraphNodeList.NList[from]->vertexName) //�ߺ� �˻縦 ���ϱ� ����
        {
            temp = temp->adj;
            continue;
        }

        else
        {
            if (isVisited(temp->vertexName, visited, *ind)) //�湮�� �� �ִ� ��忡 �ٴٸ��� cycle�� �����ϴ� ���̹Ƿ� true ��ȯ
            {
                *isCycle = true;
                return 0;
            }
            
            else
            {
                int next = findNode(temp->vertexName);
                isCycleExist(now, next, visited, ind, isCycle); //��� ȣ���Ͽ� Ž�� ����
            }

            temp = temp->adj;
        }
    }

    if (*isCycle == true)
        return 0;

    else
        return 1;
}

Graph Graph::getReverse()
{
    Graph temp; //object ����

    /* this�� ����Ǿ� �ִ� �Ͱ� ������ �ݴ��� edge���� ��� �߰� */
    for (int i = 0; i < GraphNodeList.NodeNumber; i++)
    {
        Node* a = GraphNodeList.NList[i]->adj;
        while (a != NULL)
        {
            temp.addDirectedEdge(a->vertexName, GraphNodeList.NList[i]->vertexName);
            a = a->adj;
        }
    }

    return temp; //��� edge�� ������ reverse�� ä ����� graph object ��ȯ
}

void Graph::storeAdj(int ind, string* visited, string* willVisit, int* wind, int* visitInd)
{
    GraphNodeList.NList[ind]->isMarked = true; //�湮 ���� ������Ʈ

    /* visited�� �ش� ����� vertexName ���� */
    visited[(*visitInd)] = GraphNodeList.NList[ind]->vertexName;
    (*visitInd)++;

    Node* temp = GraphNodeList.NList[ind]->adj; //���� ����Ʈ ���� ��带 ����ų �ӽ� ����
    Node* prev = GraphNodeList.NList[ind]; //temp ������ ��带 ����Ű�� ����
    while (temp != NULL)
    {
        /* �ش� ��带 �湮�� �� ���� ��� storeAdj ��� */
        if (!isVisited(temp->vertexName, visited, *visitInd))
        {
            int t = findNode(temp->vertexName);
            storeAdj(t, visited, willVisit, wind, visitInd);
        }

        prev = temp;
        temp = temp->adj;
    }

    /* ��Ͱ� ������ �������� willVisit�� ����̸� ���� */
    if (!isVisited(prev->vertexName, willVisit, *wind))
    {
        willVisit[(*wind)] = prev->vertexName;
        (*wind)++;
    }

    else return;
}

int Graph::hasSameLength(int* arr, string* vArr, int vind, int max, int* iInd)
{
    for (int i = 0; i < vind; i++)
    {
        if (vArr[i].length() == vArr[max].length() && i != max) //max�� �ƴϸ鼭 ���� ���̸� ���� string�� ���� ��� iInd ������Ʈ
        {
            arr[(*iInd)] = i;
            (*iInd)++;
        }

        else continue;
    }

    if ((*iInd) > 0) //���� Ž������ iInd�� ����� ��� (i.e. max�� ���� ������ string�� �� ���� ���)
        return true;

    else
        return false;
}

void Graph::sortString(string* temp, int index)
{
    /* string ���� ���� ���� */
    string target = "";
    for (int i = 1; i < index; i++)
    {
        target = temp[i];
        
        int j = i - 1;

        while (j >= 0 && temp[j] > target)
        {
            temp[j + 1] = temp[j];
            j--;
        }

        temp[j + 1] = target;
    }
}

int Graph::dfsForSCC(string* answer, int t, string* visited, int* visitInd)
{
    /* �湮�� ��忡 �湮 ���� ǥ�� �� answer�� vertexName �߰� */
    GraphNodeList.NList[t]->isMarked = true;
    *answer += GraphNodeList.NList[t]->vertexName;
    *answer += " ";

    /* visited �迭�� �湮�� ����� vertexName �߰� */
    int index = *visitInd;

    visited[index] = GraphNodeList.NList[t]->vertexName;
    (*visitInd)++;

    /* ���� ����Ʈ ���� ��带 ��ȸ */
    while ((findMin(GraphNodeList.NList[t]->vertexName, visited, *visitInd)) != "")
    {      
        string target = findMin(GraphNodeList.NList[t]->vertexName, visited, *visitInd);
        int t1 = findNode(target);

        /* ���� ����� adj�� ���� ��� */
        if (GraphNodeList.NList[t1]->adj == NULL)
        {
            visited[(*visitInd)] = GraphNodeList.NList[t1]->vertexName;
            (*visitInd)++;

            target = findMin(GraphNodeList.NList[t]->vertexName, visited, *visitInd);

            (*visitInd)--;
            visited[(*visitInd)] = "";

            if (target != "")
            {
                t1 = findNode(target);
                dfsForSCC(answer, t1, visited, visitInd);
            }

            else return false;
        }

        else
        {
            dfsForSCC(answer, t1, visited, visitInd);
            return true;
        }   
    }

    return true;
}

void Graph::graphToMatrix(int** graph, int nodeNumber)
{
    /* ��� �ʱ�ȭ */
    for (int i = 0; i < nodeNumber; i++)
    {
        for (int j = 0; j < nodeNumber; j++)
            graph[i][j] = 0;
    }
    
    /* ����� ��峢���� ��Ŀ� ����ġ�� ���� ǥ������ */
    for (int i = 0; i < nodeNumber; i++)
    {
        Node* buffer = GraphNodeList.NList[i]->adj;

        while (buffer != NULL)
        {
            int t = findNode(buffer->vertexName);
            graph[i][t] = buffer->NodeWeight;

            buffer = buffer->adj;
        }
    }
}

int Graph::findShortest(int* distance, int* haveToVisit, int ind)
{
    int minDist = INF, minNode = 0, nodeNumber = GraphNodeList.NodeNumber;
    for (int i = 0; i < nodeNumber; i++)
    {
        /* �Ÿ��� ���� ª���鼭 �湮�� �� ���� ��� ã�� */
        if (distance[i] < minDist && !GraphNodeList.NList[i]->isMarked)
        {
            int cnt = -100;

            /* �湮�ؾ� �ϴ� ��� ����Ʈ�� �ִ��� Ȯ�� */
            for (int j = 0; j < ind; j++)
            {
                if (haveToVisit[j] == i)
                    cnt = 100;
            }

            /* ���� ������ �����ϸ� �湮�ؾ� �ϴ� ����� �ִ� �Ÿ� �� ��� ������Ʈ */
            if (cnt > 0)
            {
                minDist = distance[i];
                minNode = i;
            }
        }

        else continue;
    }

    return minNode;
}

void Graph::findErase(int* haveToVisit, int ind, int next)
{
    int target = 0; //��ǥ �ε���

    /* haveToVisit �迭���� ��ǥ �ε����� ã�� ���� */
    for (int i = 0; i < ind; i++)
    {
        if (haveToVisit[i] == next)
        {
            target = i;
            break;
        }
    }

    /* ��ǥ �ε����� �ش��ϴ� ���� ���� */
    for (int i = target; i < ind; i++)
        haveToVisit[i] = haveToVisit[i + 1];
}

bool Graph::hasOne(string nodeName, string prev)
{
    long long int whether = prev.find(nodeName); //prev�� nodeName�� �����ϴ��� Ž��

    if (whether != string::npos) //prev�� nodeName�� �ִٸ� true ��ȯ
        return true;

    else return false;
}

void Graph::dfsForDijkstra(int** graph, int* distance, int start, string** prev)
{
    int nodeNumber = GraphNodeList.NodeNumber;
    
    /* �湮�ؾ� �ϴ� ����� �ε����� ������ �迭 ���� �� �ʱ�ȭ */
    int* haveToVisit = new int[nodeNumber];

    for (int i = 0; i < nodeNumber; i++)
        haveToVisit[i] = -10;
    int ind = 0;

    GraphNodeList.NList[start]->isMarked = true;
    distance[start] = 0;

    haveToVisit[ind] = start;
    ind++;

    while (ind)
    {
        int next = 0;
        
        if (ind == 1)
            next = haveToVisit[ind - 1];

        else
            next = findShortest(distance, haveToVisit, ind);

        if (next != start)
            GraphNodeList.NList[next]->isMarked = true;

        findErase(haveToVisit, ind, next);
        ind--;

        Node* temp = GraphNodeList.NList[next]->adj;
        while (temp != NULL)
        {
            int adj = findNode(temp->vertexName);
            
            if (!GraphNodeList.NList[adj]->isMarked)
            {
                if ((distance[next] + temp->NodeWeight) < distance[adj])
                {                 
                    distance[adj] = distance[next] + temp->NodeWeight;

                    string nodeName = GraphNodeList.NList[adj]->vertexName;
                    if (!hasOne(nodeName, prev[start][next]))
                    {
                        prev[start][next] = GraphNodeList.NList[adj]->vertexName;
                    }
                    
                    int cnt = -100;
                    for (int k = 0; k < ind; k++)
                    {
                        if (haveToVisit[k] == adj)
                            cnt = 100;
                    }

                    if (cnt > 0)
                        continue;

                    else
                    {
                        haveToVisit[ind] = adj;
                        ind++;
                    }
                }
            }

            temp = temp->adj;
        }
    }
}

void Graph::addPathToString(int start, int final, string* answer, string** prev)
{
    /* ���۰� ���� ���� ���(���� ����) */
    if (start == final)
    {
        (*answer) += prev[start][final];
        (*answer) += " ";
        return;
    }
    
    string nodeName = prev[start][final];
    int target = findNode(nodeName);

    addPathToString(start, target, answer, prev);

    (*answer) += prev[start][final];
    (*answer) += " ";

}

void Graph::graphToMatrix5(int** graph, int nodeNumber)
{
    /* ��� �ʱ�ȭ (�ʱ갪�� INF) */
    for (int i = 0; i < nodeNumber; i++)
    {
        for (int j = 0; j < nodeNumber; j++)
        {
            graph[i][j] = INF;

            if (i == j) //����� �밢���� 0���� �ʱ�ȭ
                graph[i][j] = 0;
        }
    }

    /* ����� ���������� ����ġ�� ǥ���� ������Ʈ */
    for (int i = 0; i < nodeNumber; i++)
    {
        Node* buffer = GraphNodeList.NList[i]->adj;

        while (buffer != NULL)
        {
            int t = findNode(buffer->vertexName);
            graph[i][t] = buffer->NodeWeight;

            buffer = buffer->adj;
        }
    }
}

void Graph::floyd(int** graph, int nodeNumber, int** path, int start, int final)
{
    for (int k = 0; k < nodeNumber; k++)
    {
        for (int i = 0; i < nodeNumber; i++)
        {
            if (k == i) //�ߺ� Ž�� ����
                continue;
            
            for (int j = 0; j < nodeNumber; j++)
            {
                if (i == j || k == j) //�ߺ� Ž�� ����
                    continue;
                
                if (graph[i][k] == INF || graph[k][j] == INF) //���� �̾����� ���� �������� Ž�� ����
                    continue;
                
                else if (graph[i][j] > graph[i][k] + graph[k][j]) //�ִ� �Ÿ� ������Ʈ
                {
                    graph[i][j] = graph[i][k] + graph[k][j];
                    path[i][j] = k; //�ִ� �Ÿ��� �ǵ��� ���ִ� ���� ���
                }
            }
        }
    }
}

void Graph::addPath(int** path, string* answer, int start, int final)
{
    int temp = path[start][final];

    if (temp == -1) //���� ����
        return;

    if (start != final)
    {
        string nodeName = GraphNodeList.NList[temp]->vertexName;
        if (!hasOne(nodeName, *answer))
        {
            (*answer) += GraphNodeList.NList[temp]->vertexName;
            (*answer) += " ";
        }

        addPath(path, answer, temp, final); //start�� ������Ʈ�� �� ��� ȣ���Ͽ� path�� ����
    }
}

bool Graph::alreadyHave(Node* haveToVisit, int* prev, int nodeInd, string nodeName, int target)
{
    for (int i = 0; i < nodeInd; i++)
    {
        int listNode = findNode(haveToVisit[i].vertexName);

        /* ������ �׷������� �̿��� ������ �������� Ȯ�� */
        if (listNode == target && !GraphNodeList.NList[listNode]->isMarked) //�������� ���� �迭 �� ����� ��ȣ�� ���� ��� (���� ������ ���ɼ� ����)
        {
            int a = prev[i];
            string cmp = GraphNodeList.NList[a]->vertexName;

            if (cmp == nodeName) //���� ������ ���
                return true;
        }
    }

    return false;
}

void Graph::findEraseOne(Node* haveToVisit, int* nodeInd, int* prev, int weight, string nodeName)
{
    /* ���޹��� vertexName�� ���� ��带 ã�� */
    int find = 0;

    for (int i = 0; i < (*nodeInd); i++)
    {
        if (haveToVisit[i].vertexName == nodeName && haveToVisit[i].NodeWeight == weight)
        {
            find = i;
            break;
        }
    }

    /* �ش� ��� ���� */
    /* �ش� ����� ��ġ�� �� ���� ��� */
    if (find == (*nodeInd) - 1)
    {
        haveToVisit[find].vertexName = "";
        haveToVisit[find].NodeWeight = NULL;
        (*nodeInd)--;
        return;
    }

    /* ������ ��� */
    /* �ش� ��� ���� ������ �� ĭ�� ��ܼ� ���� */
    for (int i = find; i < (*nodeInd) - 1; i++)
    {
        if (i == (*nodeInd) - 1)
            continue;

        haveToVisit[i] = haveToVisit[i + 1];
        prev[i] = prev[i + 1];
    }

    find = (*nodeInd) - 1;
    haveToVisit[find].vertexName = "";
    haveToVisit[find].NodeWeight = NULL;
    (*nodeInd)--;
    return;
}

void Graph::findEraseAll(Node* haveToVisit, int* nodeInd, int* prev, string nodeName)
{
    bool whether = true;

    /* �ش� ��� �̸��� ���� ��尡 ���� ���� ��� ��� ���� */
    while (whether)
    {
        /* �ش� ��� �̸��� ���� ����� ��ġ�� ã�� (�� �պ��� ã�� ��) */
        int find = 0;

        for (int i = 0; i < (*nodeInd); i++)
        {
            if (haveToVisit[i].vertexName == nodeName)
            {
                find = i;
                break;
            }
        }

        /* �ش� ��� �̸��� ���� ��尡 �� ���� ��� (�� �̻� �ݺ� ���� �ʿ� x) */
        if (find == (*nodeInd) - 1)
        {
            haveToVisit[find].vertexName = "";
            haveToVisit[find].NodeWeight = NULL;

            whether = false;
        }

        else
        {
            for (int i = find; i < (*nodeInd) - 2; i++)
            {
                haveToVisit[i] = haveToVisit[i + 1];
                prev[i] = prev[i + 1];
            }
        }
        
        (*nodeInd)--;
    }

    return;
}

bool Graph::noWay(int target)
{
    Node* temp = GraphNodeList.NList[target]->adj;
    int cnt = 0;

    /* ���� ����Ʈ�� ���� ���� */
    while (temp != NULL)
    {
        cnt++;
        temp = temp->adj;
    }

    temp = GraphNodeList.NList[target]->adj;
    int canGo = 0, cannot = 0;
    
    /* ���� ����Ʈ�� ������ �湮�� �� �ִ��� Ȯ�� */
    while (temp != NULL)
    {
        int index = findNode(temp->vertexName);

        if (!GraphNodeList.NList[index]->isMarked)
            canGo++;

        else
            cannot++;

        temp = temp->adj;
    }

    if (cannot == cnt) //�湮�� �� �ִ� ������� ������ �ִٸ� �� ���� ���ٴ� ���� true ��ȯ
        return true;

    else //�׷��� ���� �� false ��ȯ
        return false;
}

bool Graph::isThereOne(Edge* EList, int eInd, string newFrom, string newTo)
{   
    for (int i = 0; i < eInd; i++)
    {
        if (EList[i].from == newTo && EList[i].to == newFrom) //EList�� �̹� �ִ� �����̶�� true ��ȯ
            return true;
    }

    return false;
}

void Graph::initEList(Edge* EList, int* eInd, int nodeNumber)
{
    int ind = (*eInd);
    
    /* ������ ������������ ���� */
    for (int i = 0; i < nodeNumber; i++)
    {
        string fromN = GraphNodeList.NList[i]->vertexName;
        Node* temp = GraphNodeList.NList[i]->adj;

        while (temp != NULL)
        {
            if (isThereOne(EList, (*eInd), fromN, temp->vertexName))
            {
                temp = temp->adj;
                continue;
            }
            
            if ((*eInd) == 0) //ó�� ������ �߰��ϴ� ���
            {
                EList[ind].from = fromN;
                EList[ind].to = temp->vertexName;
                EList[ind].weight = temp->NodeWeight;
            }

            else //����Ʈ�� ������ �ִ� ���
            {
                Edge buffer;
                buffer.from = fromN;
                buffer.to = temp->vertexName;
                buffer.weight = temp->NodeWeight;

                int ins = -100;

                /* ���ο� ������ ������ �κ� ã�� */
                for (int i = 0; i < (*eInd); i++)
                {
                    if (EList[i].weight < buffer.weight)
                        continue;

                    else
                    {
                        if (EList[i].weight == buffer.weight && EList[i].from < fromN)
                            ins = i + 1;
                        
                        else
                            ins = i;

                        break;
                    }
                }

                if (ins < 0)
                    ins = (*eInd);

                /* ���ο� ���� ���� �� ���� ���� �б� */
                for (int i = (*eInd); i > ins; i--)
                {
                    EList[i] = EList[i - 1];
                }

                EList[ins] = buffer; //���ο� ���� ����
            }

            (*eInd)++; //EList ���� ���� ���� ������Ʈ

            temp = temp->adj;
        }
    }
}

int Graph::whoIs(int* parent, string nodeName)
{
    int n = findNode(nodeName);

    if (parent[n] == n) //������ parent�� �ڱ� �ڽ��� ���
        return n;

    string Nodename = GraphNodeList.NList[parent[n]]->vertexName;

    return parent[n] = whoIs(parent, Nodename); //parent�� �ڱ� �ڽ��� �ƴ� ��� parent�� ��� ȣ��� ������Ʈ�Ͽ� ��ȯ
}

bool Graph::haveSameParent(int* parent, string from, string to)
{
    int f = whoIs(parent, from);
    int t = whoIs(parent, to);
    
    if (f == t) //�� ����� parent�� ���� ��� true ��ȯ
        return true;

    return false;
}

void Graph::unionParent(int* parent, string from, string to)
{
    int f = whoIs(parent, from);
    int t = whoIs(parent, to);

    /* ���� ��� �ε����� �������� �� ����� parent ���� ������Ʈ */
    if (f < t)
        parent[t] = f;

    else
        parent[f] = t;
}
///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////


int Graph::addDirectedEdge(string nodeA, string nodeB)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int ind = GraphNodeList.NodeNumber;

    /* ���� ����Ʈ �߰��� ù ��° ��� ���� */
    Node* newNodeA = new Node;
    newNodeA->vertexName = nodeA;
    newNodeA->adj = NULL;

    /* ���� ����Ʈ �߰��� �� ��° ��� ���� */
    Node* newNodeB = new Node;
    newNodeB->vertexName = nodeB;
    newNodeB->adj = NULL;

    if (ind == 0) //���� ����Ʈ�� ���� �ƹ� ��嵵 ���� ��
    {
        GraphNodeList.NList[ind] = new Node;
        GraphNodeList.NList[ind]->vertexName = nodeA; //���� ����Ʈ�� ����� ù ��° ��� ����
        GraphNodeList.NList[ind]->isMarked = false; //�� ��带 �߰��ϸ� isMarked �ʱ�ȭ
        ind++;

        GraphNodeList.NList[ind] = new Node;
        GraphNodeList.NList[ind]->vertexName = nodeB; //���� ����Ʈ�� ����� �� ��° ��� ����
        GraphNodeList.NList[ind]->isMarked = false; //�� ��带 �߰��ϸ� isMarked �ʱ�ȭ
        GraphNodeList.NList[ind]->adj = NULL; //�� ��° ����� ���� ����Ʈ���� �ƹ��͵� �߰����� ����

        ind = 0;

        GraphNodeList.NList[ind]->adj = newNodeB; //ù ��° �Է¹��� ����� ���� ����Ʈ�� �� ��° ��� �߰�

        GraphNodeList.NodeNumber += 2; //���� ����Ʈ�� ��� 2���� �߰��Ǿ����� ǥ��

        return true;
    }

    else //���� ����Ʈ�� ��尡 ������ ��
    {
        int isA = isExist(nodeA);
        int isB = isExist(nodeB);

        if (isA >= 0 && isB < 0) //ù ��° ��常 ����Ʈ�� ������ ���
        {
            /* �̹� �����ϴ� ù ��° ����� ���� ����Ʈ�� �� ��° ��� �߰� */
            Node* last = GraphNodeList.NList[isA]; //����Ʈ�� �����ϴ� ù ��° ����� ����� ����Ű�� �ӽ� ����

            while (last->adj != NULL) //ù ��° ����� ���� ����Ʈ�� ���� ����Ű���� ��
            {
                last = last->adj;
            }

            last->adj = newNodeB; //ù ��° ����� ���� ����Ʈ ���� �� ��° ��� �߰�

            ind = GraphNodeList.NodeNumber; //���� ����Ʈ�� ��� ��� �߰��� �κ��� ����Ű�� �ӽ� ����

            /* ���� ����Ʈ�� �� ��° ��� �߰� (�� ��° ����� ���� ����Ʈ���� �ƹ��͵� �߰����� ����) */
            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeB;
            GraphNodeList.NList[ind]->isMarked = false; //�� ��带 �߰��ϸ� isMarked �ʱ�ȭ
            GraphNodeList.NList[ind]->adj = NULL; //���� ����Ʈ�� �ƹ��͵� ���� ����

            GraphNodeList.NodeNumber++; //���� ����Ʈ�� ��� 1���� �߰��Ǿ����� ǥ��
        }

        else if (isA < 0 && isB >= 0) //�� ��° ��常 ���� ����Ʈ�� ������ ��� (�� ��° ����� ���� ����Ʈ�� �ǵ帮�� ����)
        {
            ind = GraphNodeList.NodeNumber; //���� ����Ʈ�� ��� ��� �߰��� �κ��� ����Ű�� �ӽ� ����

            /* ���� ����Ʈ�� ù ��° ��� �߰� �� �� ��° ��带 ���� ���� �߰� */
            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeA;
            GraphNodeList.NList[ind]->isMarked = false; //�� ��带 �߰��ϸ� isMarked �ʱ�ȭ

            GraphNodeList.NList[ind]->adj = newNodeB; //ù ��° ����� ���� ����Ʈ�� �� ��° ��� �߰�

            GraphNodeList.NodeNumber++; //���� ����Ʈ�� ��� 1���� �߰��Ǿ����� ǥ��
        }

        else if (isA >= 0 && isB >= 0) //�� ��� ��� ������ ���
        {
            /* ù ��° ����� ���� ����Ʈ�� ���� ����Ű�� �ӽ� ��� ���� */
            Node* lastA = GraphNodeList.NList[isA];

            while (lastA->adj != NULL)
            {
                lastA = lastA->adj;
            }

            lastA->adj = newNodeB; //ù ��° ����� ���� ����Ʈ�� �� ��° ��� �߰�
        }

        else if (isA < 0 && isB < 0) //�� ��� ��� �������� ���� ���
        {
            ind = GraphNodeList.NodeNumber; //���� ����Ʈ�� ��� ��� �߰��� �κ��� ����Ű�� �ӽ� ����
            
            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeA; //���� ����Ʈ�� ����� ù ��° ��� ����
            GraphNodeList.NList[ind]->isMarked = false; //�� ��带 �߰��ϸ� isMarked �ʱ�ȭ
            ind++;

            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeB; //���� ����Ʈ�� ����� �� ��° ��� ����
            GraphNodeList.NList[ind]->isMarked = false; //�� ��带 �߰��ϸ� isMarked �ʱ�ȭ
            GraphNodeList.NList[ind]->adj = NULL; //���� ����Ʈ�� �ƹ��͵� ���� ����

            ind = GraphNodeList.NodeNumber;

            GraphNodeList.NList[ind]->adj = newNodeB; //���� ����Ʈ�� ��� �߰�

            GraphNodeList.NodeNumber += 2; //���� ����Ʈ�� ��� 2���� �߰��Ǿ����� ǥ��
        }

        return true;
    }

    return false;
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int Graph::addDirectedEdge(string nodeA, string nodeB, int weight)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int ind = GraphNodeList.NodeNumber;

    /* ���� ����Ʈ �߰��� ù ��° ��� ���� */
    Node* newNodeA = new Node;
    newNodeA->vertexName = nodeA;
    newNodeA->adj = NULL;

    /* ���� ����Ʈ �߰��� �� ��° ��� ���� */
    Node* newNodeB = new Node;
    newNodeB->vertexName = nodeB;
    newNodeB->NodeWeight = weight;
    newNodeB->adj = NULL;

    if (ind == 0) //���� ����Ʈ�� ���� �ƹ� ��嵵 ���� ��
    {
        if (nodeA > nodeB)
        {
            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeB; //���� ����Ʈ�� ����� �� ��° ��� ����
            GraphNodeList.NList[ind]->isMarked = false; //�� ��带 �߰��ϸ� isMarked �ʱ�ȭ
            GraphNodeList.NList[ind]->adj = NULL; //�� ��° ����� ���� ����Ʈ���� �ƹ��͵� �߰����� ����

            ind++;

            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeA; //���� ����Ʈ�� ����� ù ��° ��� ����
            GraphNodeList.NList[ind]->isMarked = false; //�� ��带 �߰��ϸ� isMarked �ʱ�ȭ

            ind = 1;
        }

        else
        {
            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeA; //���� ����Ʈ�� ����� ù ��° ��� ����
            GraphNodeList.NList[ind]->isMarked = false; //�� ��带 �߰��ϸ� isMarked �ʱ�ȭ
            ind++;

            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeB; //���� ����Ʈ�� ����� �� ��° ��� ����
            GraphNodeList.NList[ind]->isMarked = false; //�� ��带 �߰��ϸ� isMarked �ʱ�ȭ
            GraphNodeList.NList[ind]->adj = NULL; //�� ��° ����� ���� ����Ʈ���� �ƹ��͵� �߰����� ����
            
            ind = 0;
        }

        GraphNodeList.NList[ind]->adj = newNodeB; //ù ��° �Է¹��� ����� ���� ����Ʈ�� �� ��° ��� �߰�

        GraphNodeList.NodeNumber += 2; //���� ����Ʈ�� ��� 2���� �߰��Ǿ����� ǥ��

        return true;
    }

    else //���� ����Ʈ�� ��尡 ������ ��
    {
        int isA = isExist(nodeA);
        int isB = isExist(nodeB);

        if (isA >= 0 && isB < 0) //ù ��° ��常 ����Ʈ�� ������ ���
        {
            /* �̹� �����ϴ� ù ��° ����� ���� ����Ʈ�� �� ��° ��� �߰� */
            Node* last = GraphNodeList.NList[isA]; //����Ʈ�� �����ϴ� ù ��° ����� ù ��° ���� ��带 ����Ű�� �ӽ� ����

            while (last->adj != NULL)
            {
                if (last->adj->vertexName < nodeB)
                {
                    last = last->adj;
                    continue;
                }

                else
                {
                    break;
                }
            }
            
            newNodeB->adj = last->adj;
            last->adj = newNodeB; //ù ��° ����� ���� ����Ʈ ���� �� ��° ��� �߰�

            ind = GraphNodeList.NodeNumber; //���� ����Ʈ�� ��� ��� �߰��� �κ��� ����Ű�� �ӽ� ����

            /* ���� ����Ʈ�� �� ��° ��� �߰� (�� ��° ����� ���� ����Ʈ���� �ƹ��͵� �߰����� ����) */
            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeB;
            GraphNodeList.NList[ind]->isMarked = false; //�� ��带 �߰��ϸ� isMarked �ʱ�ȭ
            GraphNodeList.NList[ind]->adj = NULL; //���� ����Ʈ�� �ƹ��͵� ���� ����

            GraphNodeList.NodeNumber++; //���� ����Ʈ�� ��� 1���� �߰��Ǿ����� ǥ��
        }

        else if (isA < 0 && isB >= 0) //�� ��° ��常 ���� ����Ʈ�� ������ ��� (�� ��° ����� ���� ����Ʈ�� �ǵ帮�� ����)
        {
            ind = GraphNodeList.NodeNumber; //���� ����Ʈ�� ��� ��� �߰��� �κ��� ����Ű�� �ӽ� ����

            /* ���� ����Ʈ�� ù ��° ��� �߰� �� �� ��° ��带 ���� ���� �߰� */
            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeA;
            GraphNodeList.NList[ind]->isMarked = false; //�� ��带 �߰��ϸ� isMarked �ʱ�ȭ

            GraphNodeList.NList[ind]->adj = newNodeB; //ù ��° ����� ���� ����Ʈ�� �� ��° ��� �߰�

            GraphNodeList.NodeNumber++; //���� ����Ʈ�� ��� 1���� �߰��Ǿ����� ǥ��
        }

        else if (isA >= 0 && isB >= 0) //�� ��� ��� ������ ���
        {
            /* �̹� �����ϴ� ù ��° ����� ���� ����Ʈ�� �� ��° ��� �߰� */
            Node* last = GraphNodeList.NList[isA]; //����Ʈ�� �����ϴ� ù ��° ����� ù ��° ���� ��带 ����Ű�� �ӽ� ����

            while (last->adj != NULL)
            {
                if (last->adj->vertexName < nodeB)
                {
                    last = last->adj;
                    continue;
                }

                else
                {
                    break;
                }
            }

            newNodeB->adj = last->adj;
            last->adj = newNodeB; //ù ��° ����� ���� ����Ʈ ���� �� ��° ��� �߰�
        }

        else if (isA < 0 && isB < 0) //�� ��� ��� �������� ���� ���
        {
            ind = GraphNodeList.NodeNumber; //���� ����Ʈ�� ��� ��� �߰��� �κ��� ����Ű�� �ӽ� ����

            if (nodeA < nodeB)
            {
                GraphNodeList.NList[ind] = new Node;
                GraphNodeList.NList[ind]->vertexName = nodeA; //���� ����Ʈ�� ����� ù ��° ��� ����
                GraphNodeList.NList[ind]->isMarked = false; //�� ��带 �߰��ϸ� isMarked �ʱ�ȭ
                ind++;

                GraphNodeList.NList[ind] = new Node;
                GraphNodeList.NList[ind]->vertexName = nodeB; //���� ����Ʈ�� ����� �� ��° ��� ����
                GraphNodeList.NList[ind]->isMarked = false; //�� ��带 �߰��ϸ� isMarked �ʱ�ȭ
                GraphNodeList.NList[ind]->adj = NULL; //���� ����Ʈ�� �ƹ��͵� ���� ����

                ind = GraphNodeList.NodeNumber;
            }

            else
            {
                GraphNodeList.NList[ind] = new Node;
                GraphNodeList.NList[ind]->vertexName = nodeB; //���� ����Ʈ�� ����� �� ��° ��� ����
                GraphNodeList.NList[ind]->isMarked = false; //�� ��带 �߰��ϸ� isMarked �ʱ�ȭ
                GraphNodeList.NList[ind]->adj = NULL; //���� ����Ʈ�� �ƹ��͵� ���� ����
                ind++;

                GraphNodeList.NList[ind] = new Node;
                GraphNodeList.NList[ind]->vertexName = nodeA; //���� ����Ʈ�� ����� ù ��° ��� ����
                GraphNodeList.NList[ind]->isMarked = false; //�� ��带 �߰��ϸ� isMarked �ʱ�ȭ

                ind = GraphNodeList.NodeNumber + 1;
            }
            
            GraphNodeList.NList[ind]->adj = newNodeB; //���� ����Ʈ�� ��� �߰�

            GraphNodeList.NodeNumber += 2; //���� ����Ʈ�� ��� 2���� �߰��Ǿ����� ǥ��
        }

        /* �߰� �� ����Ʈ ���� ������ ���� ���� */
        int targetInd = GraphNodeList.NodeNumber - 1;

        for (int i = 0; i < GraphNodeList.NodeNumber; i++)
        {
            if (GraphNodeList.NList[i]->vertexName < GraphNodeList.NList[targetInd]->vertexName)
                continue;

            else
            {
                Node* tempNode = GraphNodeList.NList[i];

                GraphNodeList.NList[i] = GraphNodeList.NList[targetInd];
                GraphNodeList.NList[targetInd] = tempNode;
            }
        }
        return true;
    }

    return false;
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int Graph::addUndirectedEdge(string nodeA, string nodeB)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int ind = GraphNodeList.NodeNumber;

    /* ���� ����Ʈ �߰��� ù ��° ��� ���� */
    Node* newNodeA = new Node;
    newNodeA->vertexName = nodeA;
    newNodeA->adj = NULL;

    /* ���� ����Ʈ �߰��� �� ��° ��� ���� */
    Node* newNodeB = new Node;
    newNodeB->vertexName = nodeB;
    newNodeB->adj = NULL;

    if (ind == 0) //���� ����Ʈ�� ���� �ƹ� ��嵵 ���� ��
    {
        GraphNodeList.NList[ind] = new Node;
        GraphNodeList.NList[ind]->vertexName = nodeA; //���� ����Ʈ�� ����� ù ��° ��� ����
        GraphNodeList.NList[ind]->isMarked = false; //�� ��带 �߰��ϸ� isMarked �ʱ�ȭ
        ind++;

        GraphNodeList.NList[ind] = new Node;
        GraphNodeList.NList[ind]->vertexName = nodeB; //���� ����Ʈ�� ����� �� ��° ��� ����
        GraphNodeList.NList[ind]->isMarked = false; //�� ��带 �߰��ϸ� isMarked �ʱ�ȭ

        ind = 0;

        GraphNodeList.NList[ind]->adj = newNodeB; //���� ����Ʈ�� ��� �߰�
        ind++;

        GraphNodeList.NList[ind]->adj = newNodeA; //���� ����Ʈ�� ��� �߰�

        GraphNodeList.NodeNumber += 2; //���� ����Ʈ�� ��� 2���� �߰��Ǿ����� ǥ��

        return true;
    }

    else //���� ����Ʈ�� ��尡 ������ ��
    {
        int isA = isExist(nodeA);
        int isB = isExist(nodeB);

        if (isA >= 0 && isB < 0) //ù ��° ��常 ����Ʈ�� ������ ���
        {
            /* �̹� �����ϴ� ù ��° ����� ���� ����Ʈ�� �� ��° ��� �߰� */
            Node* last = GraphNodeList.NList[isA]; //����Ʈ�� �����ϴ� ù ��° ����� ����� ����Ű�� �ӽ� ����

            while (last->adj != NULL) //ù ��° ����� ���� ����Ʈ�� ���� ����Ű���� ��
            {
                last = last->adj;
            }

            last->adj = newNodeB; //ù ��° ����� ���� ����Ʈ ���� �� ��° ��� �߰�

            ind = GraphNodeList.NodeNumber; //���� ����Ʈ�� ��� ��� �߰��� �κ��� ����Ű�� �ӽ� ����

            /* ���� ����Ʈ�� �� ��° ��� �߰� �� ù ��° ��带 ���� ���� �߰� */
            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeB;
            GraphNodeList.NList[ind]->isMarked = false; //�� ��带 �߰��ϸ� isMarked �ʱ�ȭ

            GraphNodeList.NList[ind]->adj = newNodeA; //�� ��° ����� ���� ����Ʈ�� ù ��° ��� �߰�

            GraphNodeList.NodeNumber++; //���� ����Ʈ�� ��� 1���� �߰��Ǿ����� ǥ��
        }

        else if (isA < 0 && isB >= 0) //�� ��° ��常 ���� ����Ʈ�� ������ ���
        {
            /* �̹� �����ϴ� �� ��° ����� ���� ����Ʈ�� ù ��° ��� �߰� */
            Node* last = GraphNodeList.NList[isB];

            while (last->adj != NULL) //�� ��° ����� ���� ����Ʈ�� ���� ����Ű���� ��
            {
                last = last->adj;
            }

            last->adj = newNodeA; //�� ��° ����� ���� ����Ʈ ���� ù ��° ��� �߰�

            ind = GraphNodeList.NodeNumber; //���� ����Ʈ�� ��� ��� �߰��� �κ��� ����Ű�� �ӽ� ����
            
            /* ���� ����Ʈ�� ù ��° ��� �߰� �� �� ��° ��带 ���� ���� �߰� */
            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeA;
            GraphNodeList.NList[ind]->isMarked = false; //�� ��带 �߰��ϸ� isMarked �ʱ�ȭ

            GraphNodeList.NList[ind]->adj = newNodeB; //ù ��° ����� ���� ����Ʈ�� �� ��° ��� �߰�

            GraphNodeList.NodeNumber++; //���� ����Ʈ�� ��� 1���� �߰��Ǿ����� ǥ��
        }

        else if (isA >= 0 && isB >= 0) //�� ��� ��� ������ ���
        {
            /* ù ��° ����� ���� ����Ʈ�� ���� ����Ű�� �ӽ� ��� ���� */
            Node* lastA = GraphNodeList.NList[isA];

            while (lastA->adj != NULL)
            {
                lastA = lastA->adj;
            }

            /* �� ��° ����� ���� ����Ʈ�� ���� ����Ű�� �ӽ� ��� ���� */
            Node* lastB = GraphNodeList.NList[isB];

            while (lastB->adj != NULL)
            {
                lastB = lastB->adj;
            }

            lastA->adj = newNodeB; //ù ��° ����� ���� ����Ʈ�� �� ��° ��� �߰�
            lastB->adj = newNodeA; //�� ��° ����� ���� ����Ʈ�� ù ��° ��� �߰�
        }

        else if (isA < 0 && isB < 0) //�� ��� ��� �������� ���� ���
        {
            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeA; //���� ����Ʈ�� ����� ù ��° ��� ����
            GraphNodeList.NList[ind]->isMarked = false; //�� ��带 �߰��ϸ� isMarked �ʱ�ȭ
            ind++;

            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeB; //���� ����Ʈ�� ����� �� ��° ��� ����
            GraphNodeList.NList[ind]->isMarked = false; //�� ��带 �߰��ϸ� isMarked �ʱ�ȭ

            ind = GraphNodeList.NodeNumber;

            GraphNodeList.NList[ind]->adj = newNodeB; //���� ����Ʈ�� ��� �߰�
            ind++;

            GraphNodeList.NList[ind]->adj = newNodeA; //���� ����Ʈ�� ��� �߰�

            GraphNodeList.NodeNumber += 2; //���� ����Ʈ�� ��� 2���� �߰��Ǿ����� ǥ��
        }

        return true;
    }

    return false;
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int Graph::addUndirectedEdge(string nodeA, string nodeB, int weight)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int ind = GraphNodeList.NodeNumber;

    /* ���� ����Ʈ �߰��� ù ��° ��� ���� */
    Node* newNodeA = new Node;
    newNodeA->vertexName = nodeA;
    newNodeA->NodeWeight = weight;
    newNodeA->adj = NULL;

    /* ���� ����Ʈ �߰��� �� ��° ��� ���� */
    Node* newNodeB = new Node;
    newNodeB->vertexName = nodeB;
    newNodeB->NodeWeight = weight;
    newNodeB->adj = NULL;

    if (ind == 0) //���� ����Ʈ�� ���� �ƹ� ��嵵 ���� ��
    {
        if (nodeA > nodeB)
        {
            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeB; //���� ����Ʈ�� ����� �� ��° ��� ����
            GraphNodeList.NList[ind]->isMarked = false; //�� ��带 �߰��ϸ� isMarked �ʱ�ȭ
            GraphNodeList.NList[ind]->adj = newNodeA; //���� ����Ʈ�� ��� �߰�

            ind++;

            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeA; //���� ����Ʈ�� ����� ù ��° ��� ����
            GraphNodeList.NList[ind]->isMarked = false; //�� ��带 �߰��ϸ� isMarked �ʱ�ȭ
            GraphNodeList.NList[ind]->adj = newNodeB; //���� ����Ʈ�� ��� �߰�
        }

        else
        {
            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeA; //���� ����Ʈ�� ����� ù ��° ��� ����
            GraphNodeList.NList[ind]->isMarked = false; //�� ��带 �߰��ϸ� isMarked �ʱ�ȭ
            GraphNodeList.NList[ind]->adj = newNodeB; //���� ����Ʈ�� ��� �߰�
            ind++;

            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeB; //���� ����Ʈ�� ����� �� ��° ��� ����
            GraphNodeList.NList[ind]->isMarked = false; //�� ��带 �߰��ϸ� isMarked �ʱ�ȭ
            GraphNodeList.NList[ind]->adj = newNodeA; //���� ����Ʈ�� ��� �߰�
        }

        GraphNodeList.NodeNumber += 2; //���� ����Ʈ�� ��� 2���� �߰��Ǿ����� ǥ��

        return true;
    }

    else //���� ����Ʈ�� ��尡 ������ ��
    {
        int isA = isExist(nodeA);
        int isB = isExist(nodeB);

        if (isA >= 0 && isB < 0) //ù ��° ��常 ����Ʈ�� ������ ���
        {
            /* �̹� �����ϴ� ù ��° ����� ���� ����Ʈ�� �� ��° ��� �߰� */
            Node* last = GraphNodeList.NList[isA]; //����Ʈ�� �����ϴ� ù ��° ����� ù ��° ���� ��带 ����Ű�� �ӽ� ����

            while (last->adj != NULL)
            {
                if (last->adj->vertexName < nodeB)
                {
                    last = last->adj;
                    continue;
                }

                else
                {
                    break;
                }
            }

            newNodeB->adj = last->adj;
            last->adj = newNodeB; //ù ��° ����� ���� ����Ʈ ���� �� ��° ��� �߰�

            ind = GraphNodeList.NodeNumber; //���� ����Ʈ�� ��� ��� �߰��� �κ��� ����Ű�� �ӽ� ����

            /* ���� ����Ʈ�� �� ��° ��� �߰� (�� ��° ����� ���� ����Ʈ���� �ƹ��͵� �߰����� ����) */
            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeB;
            GraphNodeList.NList[ind]->isMarked = false; //�� ��带 �߰��ϸ� isMarked �ʱ�ȭ
            GraphNodeList.NList[ind]->adj = newNodeA; //���� ����Ʈ�� ��� �߰�

            GraphNodeList.NodeNumber++; //���� ����Ʈ�� ��� 1���� �߰��Ǿ����� ǥ��
        }

        else if (isA < 0 && isB >= 0) //�� ��° ��常 ���� ����Ʈ�� ������ ���
        {
            /* �̹� �����ϴ� �� ��° ����� ���� ����Ʈ�� ù ��° ��� �߰� */
            Node* last = GraphNodeList.NList[isB]; //����Ʈ�� �����ϴ� �� ��° ����� ù ��° ���� ��带 ����Ű�� �ӽ� ����

            while (last->adj != NULL)
            {
                if (last->adj->vertexName < nodeA)
                {
                    last = last->adj;
                    continue;
                }

                else
                {
                    break;
                }
            }

            newNodeA->adj = last->adj;
            last->adj = newNodeA; //�� ��° ����� ���� ����Ʈ�� ù ��° ��� �߰�
            
            ind = GraphNodeList.NodeNumber; //���� ����Ʈ�� ��� ��� �߰��� �κ��� ����Ű�� �ӽ� ����

            /* ���� ����Ʈ�� ù ��° ��� �߰� �� �� ��° ��带 ���� ���� �߰� */
            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeA;
            GraphNodeList.NList[ind]->isMarked = false; //�� ��带 �߰��ϸ� isMarked �ʱ�ȭ
            GraphNodeList.NList[ind]->adj = newNodeB; //ù ��° ����� ���� ����Ʈ�� �� ��° ��� �߰�

            GraphNodeList.NodeNumber++; //���� ����Ʈ�� ��� 1���� �߰��Ǿ����� ǥ��
        }

        else if (isA >= 0 && isB >= 0) //�� ��� ��� ������ ���
        {
            /* �̹� �����ϴ� ù ��° ����� ���� ����Ʈ�� �� ��° ��� �߰� */
            Node* lastA = GraphNodeList.NList[isA]; //����Ʈ�� �����ϴ� ù ��° ����� ù ��° ���� ��带 ����Ű�� �ӽ� ����

            while (lastA->adj != NULL)
            {
                if (lastA->adj->vertexName < nodeB)
                {
                    lastA = lastA->adj;
                    continue;
                }

                else
                {
                    break;
                }
            }

            newNodeB->adj = lastA->adj;
            lastA->adj = newNodeB; //ù ��° ����� ���� ����Ʈ ���� �� ��° ��� �߰�

            /* �̹� �����ϴ� �� ��° ����� ���� ����Ʈ�� ù ��° ��� �߰� */
            Node* lastB = GraphNodeList.NList[isB]; //����Ʈ�� �����ϴ� �� ��° ����� ù ��° ���� ��带 ����Ű�� �ӽ� ����

            while (lastB->adj != NULL)
            {
                if (lastB->adj->vertexName < nodeB)
                {
                    lastB = lastB->adj;
                    continue;
                }

                else
                {
                    break;
                }
            }

            newNodeA->adj = lastB->adj;
            lastB->adj = newNodeA; //ù ��° ����� ���� ����Ʈ ���� �� ��° ��� �߰�
        }

        else if (isA < 0 && isB < 0) //�� ��� ��� �������� ���� ���
        {
            ind = GraphNodeList.NodeNumber; //���� ����Ʈ�� ��� ��� �߰��� �κ��� ����Ű�� �ӽ� ����

            if (nodeA < nodeB)
            {
                GraphNodeList.NList[ind] = new Node;
                GraphNodeList.NList[ind]->vertexName = nodeA; //���� ����Ʈ�� ����� ù ��° ��� ����
                GraphNodeList.NList[ind]->isMarked = false; //�� ��带 �߰��ϸ� isMarked �ʱ�ȭ
                GraphNodeList.NList[ind]->adj = newNodeB; //���� ����Ʈ�� ��� �߰�
                ind++;

                GraphNodeList.NList[ind] = new Node;
                GraphNodeList.NList[ind]->vertexName = nodeB; //���� ����Ʈ�� ����� �� ��° ��� ����
                GraphNodeList.NList[ind]->isMarked = false; //�� ��带 �߰��ϸ� isMarked �ʱ�ȭ
                GraphNodeList.NList[ind]->adj = newNodeA; //���� ����Ʈ�� ��� �߰�

                ind = GraphNodeList.NodeNumber;
            }

            else
            {
                GraphNodeList.NList[ind] = new Node;
                GraphNodeList.NList[ind]->vertexName = nodeB; //���� ����Ʈ�� ����� �� ��° ��� ����
                GraphNodeList.NList[ind]->isMarked = false; //�� ��带 �߰��ϸ� isMarked �ʱ�ȭ
                GraphNodeList.NList[ind]->adj = NULL; //���� ����Ʈ�� �ƹ��͵� ���� ����
                ind++;

                GraphNodeList.NList[ind] = new Node;
                GraphNodeList.NList[ind]->vertexName = nodeA; //���� ����Ʈ�� ����� ù ��° ��� ����
                GraphNodeList.NList[ind]->isMarked = false; //�� ��带 �߰��ϸ� isMarked �ʱ�ȭ

                ind = GraphNodeList.NodeNumber + 1;
            }

            GraphNodeList.NList[ind]->adj = newNodeB; //���� ����Ʈ�� ��� �߰�

            GraphNodeList.NodeNumber += 2; //���� ����Ʈ�� ��� 2���� �߰��Ǿ����� ǥ��
        }

        /* �߰� �� ����Ʈ ���� ������ ���� ���� */
        int targetInd = GraphNodeList.NodeNumber - 1;

        for (int i = 0; i < GraphNodeList.NodeNumber; i++)
        {
            if (GraphNodeList.NList[i]->vertexName < GraphNodeList.NList[targetInd]->vertexName)
                continue;

            if (targetInd == i)
                continue;

            else
            {
                Node* tempNode = GraphNodeList.NList[i];

                GraphNodeList.NList[i] = GraphNodeList.NList[targetInd];
                GraphNodeList.NList[targetInd] = tempNode;
            }
        }
        return true;
    }

    return false;
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

string Graph::DFS()
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    string answer = ""; //������ ���� ����

    string visited[NodeMaxCount]; //�湮�� �� �ִ� ����� vertexName�� �����ϴ� �迭
    int visitInd = 0; //visited�� �ε����� ���� ���� ����

    int t = findMin(visited, visitInd);
    dfs(&answer, t, visited, &visitInd);

    answer.pop_back();

    while (isRemain())
    {
        answer += '\n';

        t = findMin(visited, visitInd);
        dfs(&answer, t, visited, &visitInd);
    }

    return answer;    
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int Graph::getTreeCount() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    string visited[NodeMaxCount]; //�湮�� �� �ִ� ����� vertexName�� �����ϴ� �迭
    int visitInd = 0; //visited�� �ε����� ���� ���� ����
    int treeCnt = 0; //tree�� ������ �����ϴ� component�� ������ ������ ����

    bool isCycle = false;

    int first = findMin(visited, visitInd);
    treeCnt += isCycleExist(first, first, visited, &visitInd, &isCycle);

    while (isRemain())
    {
        first = findMin(visited, visitInd);

        isCycle = false;
        treeCnt += isCycleExist(first, first, visited, &visitInd, &isCycle);
    }

    return treeCnt;
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

string Graph::getStronglyConnectedComponent()
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    string answer = ""; //dfs�� ����� ������ ����

    string willVisit[NodeMaxCount]; //�湮�ؾ� �ϴ� ����� vertexName�� �����ϴ� �迭
    string vArr[NodeMaxCount]; //SCC�� ��� ���� ������ ����

    string visited[NodeMaxCount]; //�湮�� �� �ִ� ����� vertexName�� �����ϴ� �迭
    int visitInd = 0; //visited�� �ε����� ���� ���� ����
    int vind = 0; //vArr�� �ε����� ���� ���� ����
    int wind = 0;

    /* ���� ����Ʈ�� �������� willVisit�� ä�� ���� */
    for (int i = 0; i < GraphNodeList.NodeNumber; i++)
    {
        if (GraphNodeList.NList[i]->isMarked == false)
            storeAdj(i, visited, willVisit, &wind, &visitInd);
    }

    Graph reverse = getReverse();
    
    /* dfs ������ ���� isMarked �ʱ�ȭ */
    for (int i = 0; i < GraphNodeList.NodeNumber; i++)
        GraphNodeList.NList[i]->isMarked = false;

    /* dfs ������ ���� visited �� visitInd �ʱ�ȭ */
    for (int i = 0; i < visitInd; i++)
    {
        visited[i] = "";
    }

    visitInd = 0;

    if(vArr[wind] == "")
        wind--;

    /* dfs�� �����ϸ� SCC�� ��� ���� ���� */
    while (reverse.isRemain() && wind >= 0)
    {
        int t = reverse.findNode(willVisit[wind]);
        
        if (reverse.GraphNodeList.NList[t]->isMarked == false)
            reverse.dfsForSCC(&answer, t, visited, &visitInd);

        wind--;

        if (answer != "")
        {
            answer.pop_back();
            vArr[vind] = answer;
            vind++;
        }

        answer = "";
    }

    while (reverse.isRemain())
    {
        int t = reverse.findMin(visited, visitInd);
        
        reverse.dfsForSCC(&answer, t, visited, &visitInd);

        if (answer != "")
        {
            answer.pop_back();
            vArr[vind] = answer;
            vind++;
        }

        answer = "";
    }

    int max = 0; //���� ���̰� �� string�� �˾Ƴ��� ���� ���� ����
    for (int i = 0; i < vind; i++)
    {
        if (vArr[max].length() < vArr[i].length())
            max = i;

        else continue;
    }

    int sameLength[NodeMaxCount]; //max�� ���� ������ SCC�� ������ �������� �迭
    int iInd = 0; //sameLength�� �ε����� ���� ���� ���� ����

    int ifSameLength = hasSameLength(sameLength, vArr, vind, max, &iInd); //���� ������ SCC�� �ִ��� Ȯ�����ִ� �Լ��� ����

    if (ifSameLength == true) //max�� ���� ������ SCC�� ���� ���
    {
        int smallest = 0;
        int index = 0;

        /* max�� ���� ������ SCC�� �ε����� �����ص� �迭�� ���� ���������� ���� ���� vertexName�� ���� SCC�� ã�� */
        for (int i = 0; i < iInd; i++)
        {
            index = sameLength[i];
            if (vArr[max][0] > vArr[index][0])
                max = index;

            else continue;
        }
    }
    
    answer = vArr[max]; //answer�� ���������� ���� ���� SCC�� ������

    string temp[NodeMaxCount]; //answer ������ ���� �ӽ� �迭
    int index = 0; //temp�� �ε��� ����
    int prevSpace = -1; //���� ���� �ε��� ����
    int currentSpace = -1; //���� ���� �ε��� ����
    for (int i = 0; i < answer.length(); i++)
    {
        /* ������ �������� string�� �����Ͽ� ���� */
        if (answer[i] == ' ')
        {
            if (prevSpace < 0)
            {
                prevSpace = 0;
                currentSpace = i;
            }

            else
            {
                currentSpace = i;
            }

            temp[index] = answer.substr(prevSpace, currentSpace - prevSpace); //temp�� index��° ���� answer�� ���� ������� ���� ��������� string �Է�
            prevSpace = i + 1; //���� ���� �ε��� ������Ʈ
            index++; //temp �ε��� ������Ʈ
        }
    }

    /* ��尡 �ϳ��� ���, Ȥ�� �ϳ� �̻��� ����� ������ ���� temp�� ���� �ʱ� ������ �ش� ��带 temp�� �߰����� */
    int len = answer.length() - 1;
    temp[index] = answer[len];
    index++;

    sortString(temp, index); //temp�� ������ �� vertexName�� ���������� ����
    answer = ""; //answer �ʱ�ȭ

    /* ������ temp�� ����� ���Ͽ� answer�� �ٽ� ���� */
    for (int i = 0; i < index; i++)
    {
        answer += temp[i];
        answer += " ";
    }

    answer.pop_back(); //�� ������ ���� ����

    return answer;
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

string Graph::getDijkstraShortestPath(string source, string destination)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////    
    int start = findNode(source); //�������� �ε���
    int final = findNode(destination); //������ �ε���
    
    int nodeNumber = GraphNodeList.NodeNumber; //��� ������ ����Ű�� ���� ����

    string answer = ""; //��ȯ�� string ����

    string** prev = new string * [nodeNumber]; //������ ���Ŀ� ���ҵ��� �����ϴ� ����Ʈ
    for (int i = 0; i < nodeNumber; i++)
        prev[i] = new string[nodeNumber];

    /* �Ÿ� ����� �迭 ���� �� �ʱ갪���� �ʱ�ȭ */
    int* distance = new int[nodeNumber];

    for (int i = 0; i < nodeNumber; i++)
        distance[i] = INF;

    /* graph�� weight�� 2���� �迭 ���·� ���� */
    int** graph = new int* [nodeNumber];
    for (int i = 0; i < nodeNumber; i++)
        graph[i] = new int[nodeNumber];

    graphToMatrix(graph, nodeNumber);
    dfsForDijkstra(graph, distance, start, prev);

    if (distance[final] == INF) //final�� �������� ���� ���
    {
        answer = "error";
    }

    else //������ ���
    {
        answer += GraphNodeList.NList[start]->vertexName;
        answer += " ";

        addPathToString(start, final, &answer, prev);
        answer += distance[final];
    }
        
    return answer;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

string Graph::getFloydShortestPath(string source, string destination)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int start = findNode(source); //�������� �ε���
    int final = findNode(destination); //������ �ε���

    int nodeNumber = GraphNodeList.NodeNumber; //��� ������ ����Ű�� ���� ����
    string answer = ""; //��ȯ�� string ����

    /* ��� ����� �迭 ���� */
    int** path = new int* [nodeNumber];
    for (int i = 0; i < nodeNumber; i++)
        path[i] = new int[nodeNumber];

    /* ��� ����� �迭 �ʱ�ȭ */
    for (int i = 0; i < nodeNumber; i++)
    {
        for (int j = 0; j < nodeNumber; j++)
            path[i][j] = -1;
    }

    /* graph�� weight�� 2���� �迭 ���·� ���� */
    int** graph = new int* [nodeNumber];
    for (int i = 0; i < nodeNumber; i++)
        graph[i] = new int[nodeNumber];

    graphToMatrix5(graph, nodeNumber);

    floyd(graph, nodeNumber, path, start, final); //graph ������Ʈ (�ּ� �Ÿ� Ž��)

    answer += GraphNodeList.NList[start]->vertexName; //���۳�� �̸� string�� ���ϱ�
    answer += " ";

    addPath(path, &answer, start, final); //��� ȣ��� �ּ� �Ÿ� ��� string�� ���ϱ�

    answer += GraphNodeList.NList[final]->vertexName; //����� �̸� string�� ���ϱ�
    answer += " ";

    answer += to_string(graph[start][final]); //�ּ� �Ÿ� string�� ���ϱ�

    return answer;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

int Graph::primMST(ofstream &fout, string startNode)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    string visited[NodeMaxCount]; //�湮�� �� �ִ� ����� vertexName�� �����ϴ� �迭
    int prev[NodeMaxCount]; //�湮�� ����� ���� ��带 �����ϴ� �迭
    int visitInd = 0;

    Node haveToVisit[NodeMaxCount]; //�湮�� ����� �̸��� ����ġ�� �����ϴ� �迭
    int nodeInd = 0;

    int cnt = 0; //MST�� ���� ������ ������ ����
    int nodeNumber = GraphNodeList.NodeNumber; //�׷��� ��� ����

    int dist = 0; //MST�� �������� ������ ����ġ�� �����Ͽ� �����ִ� ����

    string answer = ""; //fout�� ����

    int start = findNode(startNode); //���� ����� ��ȣ
    int target = 0;
    int parent = 0;

    while (cnt != nodeNumber - 1)
    {
        if (cnt == 0) //ó�� ������ ��� ���� ���� ���
            target = start;

        /* �湮 ���� ǥ�� */
        GraphNodeList.NList[target]->isMarked = true;
        visited[visitInd] = GraphNodeList.NList[target]->vertexName;
        visitInd++;

        /* �ش� ��忡�� �� �̻� ���ư� �� ���ٸ� ���� ���� ���ư��� ���� �ݺ� */
        if (noWay(target))
        {
            target = parent;
            continue;
        }

        /* answer�� �ش� ��� ���� */
        answer += GraphNodeList.NList[target]->vertexName;
        answer += " ";

        /* ���� ��带 �ߺ� ���� ��� ���� */
        Node* temp = GraphNodeList.NList[target]->adj;
        /* ���� ��尡 ���ٸ� ���� ���� ���ư��� ���� �ݺ� */
        if (temp == NULL) 
        {
            target = parent;
            continue;
        }

        while (temp != NULL)
        {          
            if (!alreadyHave(haveToVisit, prev, nodeInd, temp->vertexName, target))
            {
                int index = findNode(temp->vertexName);
                if (!GraphNodeList.NList[index]->isMarked)
                {
                    haveToVisit[nodeInd].vertexName = temp->vertexName;
                    haveToVisit[nodeInd].NodeWeight = temp->NodeWeight;
                    prev[nodeInd] = target;
                    nodeInd++;
                }
            }
  
            temp = temp->adj;
        }

        /* ���� ��� �� �湮�� �� ������ ���� �Ÿ��� ª�� ��� ���� */
        bool whether = false;
        int minDis = INF, minNode = 0, weight = 0;
        string nodeName = "";

        while (!whether)
        {
            /* ���� ª�� ����ġ�� ���� ���� */
            for (int i = 0; i < nodeInd; i++)
            {
                if (haveToVisit[i].NodeWeight < minDis)
                {
                    minDis = haveToVisit[i].NodeWeight;
                    nodeName = haveToVisit[i].vertexName;
                    weight = haveToVisit[i].NodeWeight;
                    minNode = findNode(nodeName);
                    parent = prev[i];
                }
            }

            target = minNode;

            /* �ش� ������ �̾��� ��带 �湮�� �� �ִٸ� �ش� ���� ���� �� �ݺ� */
            if (GraphNodeList.NList[target]->isMarked)
                findEraseOne(haveToVisit, &nodeInd, prev, weight, nodeName);

            else
                whether = true;
        }

        /* ���õ� ���� ���� �� answer�� ������ �̾��� ��� �� ����ġ ��� */
        findEraseAll(haveToVisit, &nodeInd, prev, nodeName);
        answer += GraphNodeList.NList[target]->vertexName;
        answer += " ";
        answer += to_string(minDis);

        fout << answer << endl;

        answer = "";
        dist += minDis; //MST path�� ����ġ ������ ������Ʈ

        cnt++;
    }
    
    return dist;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

int Graph::kruskalMST(ofstream &fout)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int nodeNumber = GraphNodeList.NodeNumber; //�� ��� ����
    int edgeNum = 0; //���� ���� ����� ����

    /* ���� ���� ���� */
    for (int i = 0; i < nodeNumber; i++)
    {
        Node* temp = GraphNodeList.NList[i]->adj;

        while (temp != NULL)
        {
            edgeNum++;
            temp = temp->adj;
        }
    }

    edgeNum /= 2;

    Edge* EList = new Edge[edgeNum]; //���� ����Ʈ
    int eInd = 0; //���� ����Ʈ �ε��� ī��Ʈ��

    initEList(EList, &eInd, nodeNumber); //���� ����Ʈ �����Ͽ� ����

    int dist = 0; //���� �Ÿ� ����� ����
    string answer = ""; //��¿� string

    int* parent = new int[nodeNumber]; //��庰�� ���� ��� �� ���� ���� ����� �ε����� �����ϴ� �迭
    for (int i = 0; i < nodeNumber; i++) //parent �ʱ�ȭ
        parent[i] = i;

    for (int i = 0; i < edgeNum; i++)
    {
        if (!haveSameParent(parent, EList[i].from, EList[i].to)) //parent�� ���� ���� ���(�ش� ������ �湮�� �� ���� ���)���� ����
        {
            dist += EList[i].weight; //���� �Ÿ� ������Ʈ
            answer = answer + EList[i].from + " " + EList[i].to + " " + to_string(EList[i].weight); //string�� MST�� �߰��� ���� ����
            fout << answer << endl; //�̹� �ݺ����� MST�� �߰��ϰ� �� ���� ���

            answer = ""; //string �ʱ�ȭ

            unionParent(parent, EList[i].from, EList[i].to); //�� ������ �湮������ ǥ��
        }
    }

    return dist;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}