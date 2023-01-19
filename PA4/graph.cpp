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
        if (GraphNodeList.NList[i]->vertexName == nodeName) //이미 리스트에 있는 원소라면 해당 원소가 저장된 인덱스를 반환
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

        else //방문한 적 없는 노드가 있을 경우 true 반환 (탐색 지속하도록 함)
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
            /* vertexName이 min보다 작고, 방문한 적 없는 노드라면 min을 변경 */
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

        /* 방문해야 하는 노드만을 골라 배열에 저장 */
        for (int i = 0; i < GraphNodeList.NodeNumber; i++)
        {
            if (GraphNodeList.NList[i]->isMarked == false)
            {
                haveToVisit[index] = GraphNodeList.NList[i]->vertexName;
                index++;
            }
        }

        /* haveToVisit에 저장한 노드들만을 비교하여 가장 작은 vertexName을 골라냄 */
        int min = 0;

        for (int i = 0; i < index; i++)
        {
            if (haveToVisit[min] > haveToVisit[i])
                min = i;
        }

        /* 해당 vertexName을 가진 노드를 다시 인접 리스트 헤더에서 찾아내어 인덱스값 반환 */
        string target = haveToVisit[min];
        int t = findNode(target);

        return t;
    }
}

string Graph::findMin(string nodeName, string* visited, int ind)
{
    /* 입력받은 nodeName을 가진 노드 찾기 */
    int target = 0;
    
    for (int i = 0; i < GraphNodeList.NodeNumber; i++)
    {
        if (nodeName == GraphNodeList.NList[i]->vertexName)
        {
            target = i;
            break;
        }
    }

    /* 해당 노드의 인접 리스트에서 가장 작은 vertexName을 가졌으며 방문한 적 없는 노드 찾기 */
    Node* temp = GraphNodeList.NList[target]->adj;
    string haveToVisit[NodeMaxCount];

    int cnt = 0;

    /* 방문한 적 없는 인접 리스트의 노드만 따로 저장 */
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

    if (cnt == 0) //인접 리스트 중 방문한 적 없는 노드가 없다면 빈 string을 반환
        return t;

    else //인접 리스트 중 방문한 적 없는 노드가 있을 경우
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
        if (nodeName == GraphNodeList.NList[i]->vertexName) //전달받은 vertexName을 갖는 노드를 찾으면 인덱스를 반환
        {
            t = i;
            break;
        }
    }

    return t;
}

void Graph::dfs(string* answer, int t, string* visited, int* visitInd)
{
    /* 방문한 노드에 방문 여부 표시 후 answer에 vertexName 추가 */
    GraphNodeList.NList[t]->isMarked = true;
    *answer += GraphNodeList.NList[t]->vertexName;
    *answer += " ";

    /* visited 배열에 방문한 노드의 vertexName 추가 */
    int index = *visitInd;

    visited[index] = GraphNodeList.NList[t]->vertexName;
    (* visitInd)++;

    /* 인접 리스트 내의 노드를 순회 */
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
        if (nodeName == visited[i]) //방문했던 노드들을 저장한 배열 내에 전달받은 vertexName이 있다면(i.e. 방문한 적 있다면) true 반환
            return true;
    }

    return false;
}

int Graph::isCycleExist(int from, int now, string* visited, int* ind, bool* isCycle)
{
    if (*isCycle == true)
        return 0;

    /* 방문한 노드에 방문 여부 표시 후 visited 배열에 방문한 노드의 vertexName 추가 */
    GraphNodeList.NList[now]->isMarked = true;

    int index = *ind;

    visited[index] = GraphNodeList.NList[now]->vertexName;
    (*ind)++;

    Node* temp = GraphNodeList.NList[now]->adj;
    while (temp != NULL)
    {
        if (temp->vertexName == GraphNodeList.NList[from]->vertexName) //중복 검사를 피하기 위함
        {
            temp = temp->adj;
            continue;
        }

        else
        {
            if (isVisited(temp->vertexName, visited, *ind)) //방문한 적 있는 노드에 다다르면 cycle이 존재하는 것이므로 true 반환
            {
                *isCycle = true;
                return 0;
            }
            
            else
            {
                int next = findNode(temp->vertexName);
                isCycleExist(now, next, visited, ind, isCycle); //재귀 호출하여 탐색 지속
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
    Graph temp; //object 선언

    /* this에 저장되어 있는 것과 방향이 반대인 edge들을 모두 추가 */
    for (int i = 0; i < GraphNodeList.NodeNumber; i++)
    {
        Node* a = GraphNodeList.NList[i]->adj;
        while (a != NULL)
        {
            temp.addDirectedEdge(a->vertexName, GraphNodeList.NList[i]->vertexName);
            a = a->adj;
        }
    }

    return temp; //모든 edge의 방향이 reverse된 채 저장된 graph object 반환
}

void Graph::storeAdj(int ind, string* visited, string* willVisit, int* wind, int* visitInd)
{
    GraphNodeList.NList[ind]->isMarked = true; //방문 여부 업데이트

    /* visited에 해당 노드의 vertexName 저장 */
    visited[(*visitInd)] = GraphNodeList.NList[ind]->vertexName;
    (*visitInd)++;

    Node* temp = GraphNodeList.NList[ind]->adj; //인접 리스트 내의 노드를 가리킬 임시 변수
    Node* prev = GraphNodeList.NList[ind]; //temp 직전의 노드를 가리키는 변수
    while (temp != NULL)
    {
        /* 해당 노드를 방문한 적 없을 경우 storeAdj 재귀 */
        if (!isVisited(temp->vertexName, visited, *visitInd))
        {
            int t = findNode(temp->vertexName);
            storeAdj(t, visited, willVisit, wind, visitInd);
        }

        prev = temp;
        temp = temp->adj;
    }

    /* 재귀가 끝나는 지점에서 willVisit에 노드이름 저장 */
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
        if (vArr[i].length() == vArr[max].length() && i != max) //max가 아니면서 같은 길이를 갖는 string이 있을 경우 iInd 업데이트
        {
            arr[(*iInd)] = i;
            (*iInd)++;
        }

        else continue;
    }

    if ((*iInd) > 0) //위의 탐색에서 iInd가 변경된 경우 (i.e. max와 같은 길이의 string이 더 있을 경우)
        return true;

    else
        return false;
}

void Graph::sortString(string* temp, int index)
{
    /* string 삽입 정렬 구현 */
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
    /* 방문한 노드에 방문 여부 표시 후 answer에 vertexName 추가 */
    GraphNodeList.NList[t]->isMarked = true;
    *answer += GraphNodeList.NList[t]->vertexName;
    *answer += " ";

    /* visited 배열에 방문한 노드의 vertexName 추가 */
    int index = *visitInd;

    visited[index] = GraphNodeList.NList[t]->vertexName;
    (*visitInd)++;

    /* 인접 리스트 내의 노드를 순회 */
    while ((findMin(GraphNodeList.NList[t]->vertexName, visited, *visitInd)) != "")
    {      
        string target = findMin(GraphNodeList.NList[t]->vertexName, visited, *visitInd);
        int t1 = findNode(target);

        /* 다음 노드의 adj가 없을 경우 */
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
    /* 행렬 초기화 */
    for (int i = 0; i < nodeNumber; i++)
    {
        for (int j = 0; j < nodeNumber; j++)
            graph[i][j] = 0;
    }
    
    /* 연결된 노드끼리는 행렬에 가중치를 적어 표시해줌 */
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
        /* 거리가 가장 짧으면서 방문한 적 없는 노드 찾기 */
        if (distance[i] < minDist && !GraphNodeList.NList[i]->isMarked)
        {
            int cnt = -100;

            /* 방문해야 하는 노드 리스트에 있는지 확인 */
            for (int j = 0; j < ind; j++)
            {
                if (haveToVisit[j] == i)
                    cnt = 100;
            }

            /* 위의 조건을 만족하며 방문해야 하는 노드라면 최단 거리 및 노드 업데이트 */
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
    int target = 0; //목표 인덱스

    /* haveToVisit 배열에서 목표 인덱스를 찾아 저장 */
    for (int i = 0; i < ind; i++)
    {
        if (haveToVisit[i] == next)
        {
            target = i;
            break;
        }
    }

    /* 목표 인덱스에 해당하는 원소 삭제 */
    for (int i = target; i < ind; i++)
        haveToVisit[i] = haveToVisit[i + 1];
}

bool Graph::hasOne(string nodeName, string prev)
{
    long long int whether = prev.find(nodeName); //prev에 nodeName이 존재하는지 탐색

    if (whether != string::npos) //prev에 nodeName이 있다면 true 반환
        return true;

    else return false;
}

void Graph::dfsForDijkstra(int** graph, int* distance, int start, string** prev)
{
    int nodeNumber = GraphNodeList.NodeNumber;
    
    /* 방문해야 하는 노드의 인덱스를 저장할 배열 선언 및 초기화 */
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
    /* 시작과 끝이 같은 경우(종료 조건) */
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
    /* 행렬 초기화 (초깃값이 INF) */
    for (int i = 0; i < nodeNumber; i++)
    {
        for (int j = 0; j < nodeNumber; j++)
        {
            graph[i][j] = INF;

            if (i == j) //행렬의 대각선만 0으로 초기화
                graph[i][j] = 0;
        }
    }

    /* 연결된 간선끼리는 가중치를 표기해 업데이트 */
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
            if (k == i) //중복 탐색 방지
                continue;
            
            for (int j = 0; j < nodeNumber; j++)
            {
                if (i == j || k == j) //중복 탐색 방지
                    continue;
                
                if (graph[i][k] == INF || graph[k][j] == INF) //서로 이어지지 않은 정점끼리 탐색 방지
                    continue;
                
                else if (graph[i][j] > graph[i][k] + graph[k][j]) //최단 거리 업데이트
                {
                    graph[i][j] = graph[i][k] + graph[k][j];
                    path[i][j] = k; //최단 거리가 되도록 해주는 정점 기록
                }
            }
        }
    }
}

void Graph::addPath(int** path, string* answer, int start, int final)
{
    int temp = path[start][final];

    if (temp == -1) //종료 조건
        return;

    if (start != final)
    {
        string nodeName = GraphNodeList.NList[temp]->vertexName;
        if (!hasOne(nodeName, *answer))
        {
            (*answer) += GraphNodeList.NList[temp]->vertexName;
            (*answer) += " ";
        }

        addPath(path, answer, temp, final); //start를 업데이트한 후 재귀 호출하여 path를 더함
    }
}

bool Graph::alreadyHave(Node* haveToVisit, int* prev, int nodeInd, string nodeName, int target)
{
    for (int i = 0; i < nodeInd; i++)
    {
        int listNode = findNode(haveToVisit[i].vertexName);

        /* 무방향 그래프임을 이용해 동일한 간선인지 확인 */
        if (listNode == target && !GraphNodeList.NList[listNode]->isMarked) //넣으려는 노드와 배열 내 노드의 번호가 같을 경우 (동일 간선일 가능성 존재)
        {
            int a = prev[i];
            string cmp = GraphNodeList.NList[a]->vertexName;

            if (cmp == nodeName) //동일 간선일 경우
                return true;
        }
    }

    return false;
}

void Graph::findEraseOne(Node* haveToVisit, int* nodeInd, int* prev, int weight, string nodeName)
{
    /* 전달받은 vertexName을 갖는 노드를 찾기 */
    int find = 0;

    for (int i = 0; i < (*nodeInd); i++)
    {
        if (haveToVisit[i].vertexName == nodeName && haveToVisit[i].NodeWeight == weight)
        {
            find = i;
            break;
        }
    }

    /* 해당 노드 삭제 */
    /* 해당 노드의 위치가 맨 끝일 경우 */
    if (find == (*nodeInd) - 1)
    {
        haveToVisit[find].vertexName = "";
        haveToVisit[find].NodeWeight = NULL;
        (*nodeInd)--;
        return;
    }

    /* 나머지 경우 */
    /* 해당 노드 뒤의 노드들을 한 칸씩 당겨서 저장 */
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

    /* 해당 노드 이름을 가진 노드가 여러 개일 경우 모두 삭제 */
    while (whether)
    {
        /* 해당 노드 이름을 가진 노드의 위치를 찾음 (맨 앞부터 찾게 됨) */
        int find = 0;

        for (int i = 0; i < (*nodeInd); i++)
        {
            if (haveToVisit[i].vertexName == nodeName)
            {
                find = i;
                break;
            }
        }

        /* 해당 노드 이름을 갖는 노드가 맨 끝일 경우 (더 이상 반복 지속 필요 x) */
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

    /* 인접 리스트의 개수 세기 */
    while (temp != NULL)
    {
        cnt++;
        temp = temp->adj;
    }

    temp = GraphNodeList.NList[target]->adj;
    int canGo = 0, cannot = 0;
    
    /* 인접 리스트의 노드들을 방문한 적 있는지 확인 */
    while (temp != NULL)
    {
        int index = findNode(temp->vertexName);

        if (!GraphNodeList.NList[index]->isMarked)
            canGo++;

        else
            cannot++;

        temp = temp->adj;
    }

    if (cannot == cnt) //방문한 적 있는 노드들과만 인접해 있다면 갈 곳이 없다는 뜻의 true 반환
        return true;

    else //그렇지 않을 시 false 반환
        return false;
}

bool Graph::isThereOne(Edge* EList, int eInd, string newFrom, string newTo)
{   
    for (int i = 0; i < eInd; i++)
    {
        if (EList[i].from == newTo && EList[i].to == newFrom) //EList에 이미 있는 간선이라면 true 반환
            return true;
    }

    return false;
}

void Graph::initEList(Edge* EList, int* eInd, int nodeNumber)
{
    int ind = (*eInd);
    
    /* 간선을 오름차순으로 정렬 */
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
            
            if ((*eInd) == 0) //처음 간선을 추가하는 경우
            {
                EList[ind].from = fromN;
                EList[ind].to = temp->vertexName;
                EList[ind].weight = temp->NodeWeight;
            }

            else //리스트에 간선이 있는 경우
            {
                Edge buffer;
                buffer.from = fromN;
                buffer.to = temp->vertexName;
                buffer.weight = temp->NodeWeight;

                int ins = -100;

                /* 새로운 간선을 삽입할 부분 찾기 */
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

                /* 새로운 간선 삽입 전 기존 간선 밀기 */
                for (int i = (*eInd); i > ins; i--)
                {
                    EList[i] = EList[i - 1];
                }

                EList[ins] = buffer; //새로운 간선 삽입
            }

            (*eInd)++; //EList 내의 원소 개수 업데이트

            temp = temp->adj;
        }
    }
}

int Graph::whoIs(int* parent, string nodeName)
{
    int n = findNode(nodeName);

    if (parent[n] == n) //정점의 parent가 자기 자신일 경우
        return n;

    string Nodename = GraphNodeList.NList[parent[n]]->vertexName;

    return parent[n] = whoIs(parent, Nodename); //parent가 자기 자신이 아닐 경우 parent를 재귀 호출로 업데이트하여 반환
}

bool Graph::haveSameParent(int* parent, string from, string to)
{
    int f = whoIs(parent, from);
    int t = whoIs(parent, to);
    
    if (f == t) //두 노드의 parent가 같을 경우 true 반환
        return true;

    return false;
}

void Graph::unionParent(int* parent, string from, string to)
{
    int f = whoIs(parent, from);
    int t = whoIs(parent, to);

    /* 작은 노드 인덱스를 기준으로 두 노드의 parent 통합 업데이트 */
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

    /* 인접 리스트 추가용 첫 번째 노드 생성 */
    Node* newNodeA = new Node;
    newNodeA->vertexName = nodeA;
    newNodeA->adj = NULL;

    /* 인접 리스트 추가용 두 번째 노드 생성 */
    Node* newNodeB = new Node;
    newNodeB->vertexName = nodeB;
    newNodeB->adj = NULL;

    if (ind == 0) //인접 리스트에 아직 아무 노드도 없을 때
    {
        GraphNodeList.NList[ind] = new Node;
        GraphNodeList.NList[ind]->vertexName = nodeA; //인접 리스트의 헤더로 첫 번째 노드 삽입
        GraphNodeList.NList[ind]->isMarked = false; //새 노드를 추가하며 isMarked 초기화
        ind++;

        GraphNodeList.NList[ind] = new Node;
        GraphNodeList.NList[ind]->vertexName = nodeB; //인접 리스트의 헤더로 두 번째 노드 삽입
        GraphNodeList.NList[ind]->isMarked = false; //새 노드를 추가하며 isMarked 초기화
        GraphNodeList.NList[ind]->adj = NULL; //두 번째 노드의 인접 리스트에는 아무것도 추가하지 않음

        ind = 0;

        GraphNodeList.NList[ind]->adj = newNodeB; //첫 번째 입력받은 노드의 인접 리스트에 두 번째 노드 추가

        GraphNodeList.NodeNumber += 2; //인접 리스트에 노드 2개가 추가되었음을 표시

        return true;
    }

    else //인접 리스트에 노드가 존재할 때
    {
        int isA = isExist(nodeA);
        int isB = isExist(nodeB);

        if (isA >= 0 && isB < 0) //첫 번째 노드만 리스트에 존재할 경우
        {
            /* 이미 존재하는 첫 번째 노드의 인접 리스트에 두 번째 노드 추가 */
            Node* last = GraphNodeList.NList[isA]; //리스트에 존재하는 첫 번째 노드의 헤더를 가리키는 임시 변수

            while (last->adj != NULL) //첫 번째 노드의 인접 리스트의 끝을 가리키도록 함
            {
                last = last->adj;
            }

            last->adj = newNodeB; //첫 번째 노드의 인접 리스트 끝에 두 번째 노드 추가

            ind = GraphNodeList.NodeNumber; //인접 리스트에 헤더 노드 추가할 부분을 가리키는 임시 변수

            /* 인접 리스트에 두 번째 노드 추가 (두 번째 노드의 인접 리스트에는 아무것도 추가하지 않음) */
            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeB;
            GraphNodeList.NList[ind]->isMarked = false; //새 노드를 추가하며 isMarked 초기화
            GraphNodeList.NList[ind]->adj = NULL; //인접 리스트에 아무것도 넣지 않음

            GraphNodeList.NodeNumber++; //인접 리스트에 노드 1개가 추가되었음을 표시
        }

        else if (isA < 0 && isB >= 0) //두 번째 노드만 인접 리스트에 존재할 경우 (두 번째 노드의 인접 리스트는 건드리지 않음)
        {
            ind = GraphNodeList.NodeNumber; //인접 리스트에 헤더 노드 추가할 부분을 가리키는 임시 변수

            /* 인접 리스트에 첫 번째 노드 추가 후 두 번째 노드를 인접 노드로 추가 */
            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeA;
            GraphNodeList.NList[ind]->isMarked = false; //새 노드를 추가하며 isMarked 초기화

            GraphNodeList.NList[ind]->adj = newNodeB; //첫 번째 노드의 인접 리스트에 두 번째 노드 추가

            GraphNodeList.NodeNumber++; //인접 리스트에 노드 1개가 추가되었음을 표시
        }

        else if (isA >= 0 && isB >= 0) //두 노드 모두 존재할 경우
        {
            /* 첫 번째 노드의 인접 리스트의 끝을 가리키는 임시 노드 선언 */
            Node* lastA = GraphNodeList.NList[isA];

            while (lastA->adj != NULL)
            {
                lastA = lastA->adj;
            }

            lastA->adj = newNodeB; //첫 번째 노드의 인접 리스트에 두 번째 노드 추가
        }

        else if (isA < 0 && isB < 0) //두 노드 모두 존재하지 않을 경우
        {
            ind = GraphNodeList.NodeNumber; //인접 리스트에 헤더 노드 추가할 부분을 가리키는 임시 변수
            
            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeA; //인접 리스트의 헤더로 첫 번째 노드 삽입
            GraphNodeList.NList[ind]->isMarked = false; //새 노드를 추가하며 isMarked 초기화
            ind++;

            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeB; //인접 리스트의 헤더로 두 번째 노드 삽입
            GraphNodeList.NList[ind]->isMarked = false; //새 노드를 추가하며 isMarked 초기화
            GraphNodeList.NList[ind]->adj = NULL; //인접 리스트에 아무것도 넣지 않음

            ind = GraphNodeList.NodeNumber;

            GraphNodeList.NList[ind]->adj = newNodeB; //인접 리스트에 노드 추가

            GraphNodeList.NodeNumber += 2; //인접 리스트에 노드 2개가 추가되었음을 표시
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

    /* 인접 리스트 추가용 첫 번째 노드 생성 */
    Node* newNodeA = new Node;
    newNodeA->vertexName = nodeA;
    newNodeA->adj = NULL;

    /* 인접 리스트 추가용 두 번째 노드 생성 */
    Node* newNodeB = new Node;
    newNodeB->vertexName = nodeB;
    newNodeB->NodeWeight = weight;
    newNodeB->adj = NULL;

    if (ind == 0) //인접 리스트에 아직 아무 노드도 없을 때
    {
        if (nodeA > nodeB)
        {
            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeB; //인접 리스트의 헤더로 두 번째 노드 삽입
            GraphNodeList.NList[ind]->isMarked = false; //새 노드를 추가하며 isMarked 초기화
            GraphNodeList.NList[ind]->adj = NULL; //두 번째 노드의 인접 리스트에는 아무것도 추가하지 않음

            ind++;

            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeA; //인접 리스트의 헤더로 첫 번째 노드 삽입
            GraphNodeList.NList[ind]->isMarked = false; //새 노드를 추가하며 isMarked 초기화

            ind = 1;
        }

        else
        {
            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeA; //인접 리스트의 헤더로 첫 번째 노드 삽입
            GraphNodeList.NList[ind]->isMarked = false; //새 노드를 추가하며 isMarked 초기화
            ind++;

            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeB; //인접 리스트의 헤더로 두 번째 노드 삽입
            GraphNodeList.NList[ind]->isMarked = false; //새 노드를 추가하며 isMarked 초기화
            GraphNodeList.NList[ind]->adj = NULL; //두 번째 노드의 인접 리스트에는 아무것도 추가하지 않음
            
            ind = 0;
        }

        GraphNodeList.NList[ind]->adj = newNodeB; //첫 번째 입력받은 노드의 인접 리스트에 두 번째 노드 추가

        GraphNodeList.NodeNumber += 2; //인접 리스트에 노드 2개가 추가되었음을 표시

        return true;
    }

    else //인접 리스트에 노드가 존재할 때
    {
        int isA = isExist(nodeA);
        int isB = isExist(nodeB);

        if (isA >= 0 && isB < 0) //첫 번째 노드만 리스트에 존재할 경우
        {
            /* 이미 존재하는 첫 번째 노드의 인접 리스트에 두 번째 노드 추가 */
            Node* last = GraphNodeList.NList[isA]; //리스트에 존재하는 첫 번째 노드의 첫 번째 인접 노드를 가리키는 임시 변수

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
            last->adj = newNodeB; //첫 번째 노드의 인접 리스트 끝에 두 번째 노드 추가

            ind = GraphNodeList.NodeNumber; //인접 리스트에 헤더 노드 추가할 부분을 가리키는 임시 변수

            /* 인접 리스트에 두 번째 노드 추가 (두 번째 노드의 인접 리스트에는 아무것도 추가하지 않음) */
            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeB;
            GraphNodeList.NList[ind]->isMarked = false; //새 노드를 추가하며 isMarked 초기화
            GraphNodeList.NList[ind]->adj = NULL; //인접 리스트에 아무것도 넣지 않음

            GraphNodeList.NodeNumber++; //인접 리스트에 노드 1개가 추가되었음을 표시
        }

        else if (isA < 0 && isB >= 0) //두 번째 노드만 인접 리스트에 존재할 경우 (두 번째 노드의 인접 리스트는 건드리지 않음)
        {
            ind = GraphNodeList.NodeNumber; //인접 리스트에 헤더 노드 추가할 부분을 가리키는 임시 변수

            /* 인접 리스트에 첫 번째 노드 추가 후 두 번째 노드를 인접 노드로 추가 */
            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeA;
            GraphNodeList.NList[ind]->isMarked = false; //새 노드를 추가하며 isMarked 초기화

            GraphNodeList.NList[ind]->adj = newNodeB; //첫 번째 노드의 인접 리스트에 두 번째 노드 추가

            GraphNodeList.NodeNumber++; //인접 리스트에 노드 1개가 추가되었음을 표시
        }

        else if (isA >= 0 && isB >= 0) //두 노드 모두 존재할 경우
        {
            /* 이미 존재하는 첫 번째 노드의 인접 리스트에 두 번째 노드 추가 */
            Node* last = GraphNodeList.NList[isA]; //리스트에 존재하는 첫 번째 노드의 첫 번째 인접 노드를 가리키는 임시 변수

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
            last->adj = newNodeB; //첫 번째 노드의 인접 리스트 끝에 두 번째 노드 추가
        }

        else if (isA < 0 && isB < 0) //두 노드 모두 존재하지 않을 경우
        {
            ind = GraphNodeList.NodeNumber; //인접 리스트에 헤더 노드 추가할 부분을 가리키는 임시 변수

            if (nodeA < nodeB)
            {
                GraphNodeList.NList[ind] = new Node;
                GraphNodeList.NList[ind]->vertexName = nodeA; //인접 리스트의 헤더로 첫 번째 노드 삽입
                GraphNodeList.NList[ind]->isMarked = false; //새 노드를 추가하며 isMarked 초기화
                ind++;

                GraphNodeList.NList[ind] = new Node;
                GraphNodeList.NList[ind]->vertexName = nodeB; //인접 리스트의 헤더로 두 번째 노드 삽입
                GraphNodeList.NList[ind]->isMarked = false; //새 노드를 추가하며 isMarked 초기화
                GraphNodeList.NList[ind]->adj = NULL; //인접 리스트에 아무것도 넣지 않음

                ind = GraphNodeList.NodeNumber;
            }

            else
            {
                GraphNodeList.NList[ind] = new Node;
                GraphNodeList.NList[ind]->vertexName = nodeB; //인접 리스트의 헤더로 두 번째 노드 삽입
                GraphNodeList.NList[ind]->isMarked = false; //새 노드를 추가하며 isMarked 초기화
                GraphNodeList.NList[ind]->adj = NULL; //인접 리스트에 아무것도 넣지 않음
                ind++;

                GraphNodeList.NList[ind] = new Node;
                GraphNodeList.NList[ind]->vertexName = nodeA; //인접 리스트의 헤더로 첫 번째 노드 삽입
                GraphNodeList.NList[ind]->isMarked = false; //새 노드를 추가하며 isMarked 초기화

                ind = GraphNodeList.NodeNumber + 1;
            }
            
            GraphNodeList.NList[ind]->adj = newNodeB; //인접 리스트에 노드 추가

            GraphNodeList.NodeNumber += 2; //인접 리스트에 노드 2개가 추가되었음을 표시
        }

        /* 추가 한 리스트 원소 사이의 순서 정렬 */
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

    /* 인접 리스트 추가용 첫 번째 노드 생성 */
    Node* newNodeA = new Node;
    newNodeA->vertexName = nodeA;
    newNodeA->adj = NULL;

    /* 인접 리스트 추가용 두 번째 노드 생성 */
    Node* newNodeB = new Node;
    newNodeB->vertexName = nodeB;
    newNodeB->adj = NULL;

    if (ind == 0) //인접 리스트에 아직 아무 노드도 없을 때
    {
        GraphNodeList.NList[ind] = new Node;
        GraphNodeList.NList[ind]->vertexName = nodeA; //인접 리스트의 헤더로 첫 번째 노드 삽입
        GraphNodeList.NList[ind]->isMarked = false; //새 노드를 추가하며 isMarked 초기화
        ind++;

        GraphNodeList.NList[ind] = new Node;
        GraphNodeList.NList[ind]->vertexName = nodeB; //인접 리스트의 헤더로 두 번째 노드 삽입
        GraphNodeList.NList[ind]->isMarked = false; //새 노드를 추가하며 isMarked 초기화

        ind = 0;

        GraphNodeList.NList[ind]->adj = newNodeB; //인접 리스트에 노드 추가
        ind++;

        GraphNodeList.NList[ind]->adj = newNodeA; //인접 리스트에 노드 추가

        GraphNodeList.NodeNumber += 2; //인접 리스트에 노드 2개가 추가되었음을 표시

        return true;
    }

    else //인접 리스트에 노드가 존재할 때
    {
        int isA = isExist(nodeA);
        int isB = isExist(nodeB);

        if (isA >= 0 && isB < 0) //첫 번째 노드만 리스트에 존재할 경우
        {
            /* 이미 존재하는 첫 번째 노드의 인접 리스트에 두 번째 노드 추가 */
            Node* last = GraphNodeList.NList[isA]; //리스트에 존재하는 첫 번째 노드의 헤더를 가리키는 임시 변수

            while (last->adj != NULL) //첫 번째 노드의 인접 리스트의 끝을 가리키도록 함
            {
                last = last->adj;
            }

            last->adj = newNodeB; //첫 번째 노드의 인접 리스트 끝에 두 번째 노드 추가

            ind = GraphNodeList.NodeNumber; //인접 리스트에 헤더 노드 추가할 부분을 가리키는 임시 변수

            /* 인접 리스트에 두 번째 노드 추가 후 첫 번째 노드를 인접 노드로 추가 */
            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeB;
            GraphNodeList.NList[ind]->isMarked = false; //새 노드를 추가하며 isMarked 초기화

            GraphNodeList.NList[ind]->adj = newNodeA; //두 번째 노드의 인접 리스트에 첫 번째 노드 추가

            GraphNodeList.NodeNumber++; //인접 리스트에 노드 1개가 추가되었음을 표시
        }

        else if (isA < 0 && isB >= 0) //두 번째 노드만 인접 리스트에 존재할 경우
        {
            /* 이미 존재하는 두 번째 노드의 인접 리스트에 첫 번째 노드 추가 */
            Node* last = GraphNodeList.NList[isB];

            while (last->adj != NULL) //두 번째 노드의 인접 리스트의 끝을 가리키도록 함
            {
                last = last->adj;
            }

            last->adj = newNodeA; //두 번째 노드의 인접 리스트 끝에 첫 번째 노드 추가

            ind = GraphNodeList.NodeNumber; //인접 리스트에 헤더 노드 추가할 부분을 가리키는 임시 변수
            
            /* 인접 리스트에 첫 번째 노드 추가 후 두 번째 노드를 인접 노드로 추가 */
            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeA;
            GraphNodeList.NList[ind]->isMarked = false; //새 노드를 추가하며 isMarked 초기화

            GraphNodeList.NList[ind]->adj = newNodeB; //첫 번째 노드의 인접 리스트에 두 번째 노드 추가

            GraphNodeList.NodeNumber++; //인접 리스트에 노드 1개가 추가되었음을 표시
        }

        else if (isA >= 0 && isB >= 0) //두 노드 모두 존재할 경우
        {
            /* 첫 번째 노드의 인접 리스트의 끝을 가리키는 임시 노드 선언 */
            Node* lastA = GraphNodeList.NList[isA];

            while (lastA->adj != NULL)
            {
                lastA = lastA->adj;
            }

            /* 두 번째 노드의 인접 리스트의 끝을 가리키는 임시 노드 선언 */
            Node* lastB = GraphNodeList.NList[isB];

            while (lastB->adj != NULL)
            {
                lastB = lastB->adj;
            }

            lastA->adj = newNodeB; //첫 번째 노드의 인접 리스트에 두 번째 노드 추가
            lastB->adj = newNodeA; //두 번째 노드의 인접 리스트에 첫 번째 노드 추가
        }

        else if (isA < 0 && isB < 0) //두 노드 모두 존재하지 않을 경우
        {
            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeA; //인접 리스트의 헤더로 첫 번째 노드 삽입
            GraphNodeList.NList[ind]->isMarked = false; //새 노드를 추가하며 isMarked 초기화
            ind++;

            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeB; //인접 리스트의 헤더로 두 번째 노드 삽입
            GraphNodeList.NList[ind]->isMarked = false; //새 노드를 추가하며 isMarked 초기화

            ind = GraphNodeList.NodeNumber;

            GraphNodeList.NList[ind]->adj = newNodeB; //인접 리스트에 노드 추가
            ind++;

            GraphNodeList.NList[ind]->adj = newNodeA; //인접 리스트에 노드 추가

            GraphNodeList.NodeNumber += 2; //인접 리스트에 노드 2개가 추가되었음을 표시
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

    /* 인접 리스트 추가용 첫 번째 노드 생성 */
    Node* newNodeA = new Node;
    newNodeA->vertexName = nodeA;
    newNodeA->NodeWeight = weight;
    newNodeA->adj = NULL;

    /* 인접 리스트 추가용 두 번째 노드 생성 */
    Node* newNodeB = new Node;
    newNodeB->vertexName = nodeB;
    newNodeB->NodeWeight = weight;
    newNodeB->adj = NULL;

    if (ind == 0) //인접 리스트에 아직 아무 노드도 없을 때
    {
        if (nodeA > nodeB)
        {
            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeB; //인접 리스트의 헤더로 두 번째 노드 삽입
            GraphNodeList.NList[ind]->isMarked = false; //새 노드를 추가하며 isMarked 초기화
            GraphNodeList.NList[ind]->adj = newNodeA; //인접 리스트에 노드 추가

            ind++;

            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeA; //인접 리스트의 헤더로 첫 번째 노드 삽입
            GraphNodeList.NList[ind]->isMarked = false; //새 노드를 추가하며 isMarked 초기화
            GraphNodeList.NList[ind]->adj = newNodeB; //인접 리스트에 노드 추가
        }

        else
        {
            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeA; //인접 리스트의 헤더로 첫 번째 노드 삽입
            GraphNodeList.NList[ind]->isMarked = false; //새 노드를 추가하며 isMarked 초기화
            GraphNodeList.NList[ind]->adj = newNodeB; //인접 리스트에 노드 추가
            ind++;

            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeB; //인접 리스트의 헤더로 두 번째 노드 삽입
            GraphNodeList.NList[ind]->isMarked = false; //새 노드를 추가하며 isMarked 초기화
            GraphNodeList.NList[ind]->adj = newNodeA; //인접 리스트에 노드 추가
        }

        GraphNodeList.NodeNumber += 2; //인접 리스트에 노드 2개가 추가되었음을 표시

        return true;
    }

    else //인접 리스트에 노드가 존재할 때
    {
        int isA = isExist(nodeA);
        int isB = isExist(nodeB);

        if (isA >= 0 && isB < 0) //첫 번째 노드만 리스트에 존재할 경우
        {
            /* 이미 존재하는 첫 번째 노드의 인접 리스트에 두 번째 노드 추가 */
            Node* last = GraphNodeList.NList[isA]; //리스트에 존재하는 첫 번째 노드의 첫 번째 인접 노드를 가리키는 임시 변수

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
            last->adj = newNodeB; //첫 번째 노드의 인접 리스트 끝에 두 번째 노드 추가

            ind = GraphNodeList.NodeNumber; //인접 리스트에 헤더 노드 추가할 부분을 가리키는 임시 변수

            /* 인접 리스트에 두 번째 노드 추가 (두 번째 노드의 인접 리스트에는 아무것도 추가하지 않음) */
            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeB;
            GraphNodeList.NList[ind]->isMarked = false; //새 노드를 추가하며 isMarked 초기화
            GraphNodeList.NList[ind]->adj = newNodeA; //인접 리스트에 노드 추가

            GraphNodeList.NodeNumber++; //인접 리스트에 노드 1개가 추가되었음을 표시
        }

        else if (isA < 0 && isB >= 0) //두 번째 노드만 인접 리스트에 존재할 경우
        {
            /* 이미 존재하는 두 번째 노드의 인접 리스트에 첫 번째 노드 추가 */
            Node* last = GraphNodeList.NList[isB]; //리스트에 존재하는 두 번째 노드의 첫 번째 인접 노드를 가리키는 임시 변수

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
            last->adj = newNodeA; //두 번째 노드의 인접 리스트에 첫 번째 노드 추가
            
            ind = GraphNodeList.NodeNumber; //인접 리스트에 헤더 노드 추가할 부분을 가리키는 임시 변수

            /* 인접 리스트에 첫 번째 노드 추가 후 두 번째 노드를 인접 노드로 추가 */
            GraphNodeList.NList[ind] = new Node;
            GraphNodeList.NList[ind]->vertexName = nodeA;
            GraphNodeList.NList[ind]->isMarked = false; //새 노드를 추가하며 isMarked 초기화
            GraphNodeList.NList[ind]->adj = newNodeB; //첫 번째 노드의 인접 리스트에 두 번째 노드 추가

            GraphNodeList.NodeNumber++; //인접 리스트에 노드 1개가 추가되었음을 표시
        }

        else if (isA >= 0 && isB >= 0) //두 노드 모두 존재할 경우
        {
            /* 이미 존재하는 첫 번째 노드의 인접 리스트에 두 번째 노드 추가 */
            Node* lastA = GraphNodeList.NList[isA]; //리스트에 존재하는 첫 번째 노드의 첫 번째 인접 노드를 가리키는 임시 변수

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
            lastA->adj = newNodeB; //첫 번째 노드의 인접 리스트 끝에 두 번째 노드 추가

            /* 이미 존재하는 두 번째 노드의 인접 리스트에 첫 번째 노드 추가 */
            Node* lastB = GraphNodeList.NList[isB]; //리스트에 존재하는 두 번째 노드의 첫 번째 인접 노드를 가리키는 임시 변수

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
            lastB->adj = newNodeA; //첫 번째 노드의 인접 리스트 끝에 두 번째 노드 추가
        }

        else if (isA < 0 && isB < 0) //두 노드 모두 존재하지 않을 경우
        {
            ind = GraphNodeList.NodeNumber; //인접 리스트에 헤더 노드 추가할 부분을 가리키는 임시 변수

            if (nodeA < nodeB)
            {
                GraphNodeList.NList[ind] = new Node;
                GraphNodeList.NList[ind]->vertexName = nodeA; //인접 리스트의 헤더로 첫 번째 노드 삽입
                GraphNodeList.NList[ind]->isMarked = false; //새 노드를 추가하며 isMarked 초기화
                GraphNodeList.NList[ind]->adj = newNodeB; //인접 리스트에 노드 추가
                ind++;

                GraphNodeList.NList[ind] = new Node;
                GraphNodeList.NList[ind]->vertexName = nodeB; //인접 리스트의 헤더로 두 번째 노드 삽입
                GraphNodeList.NList[ind]->isMarked = false; //새 노드를 추가하며 isMarked 초기화
                GraphNodeList.NList[ind]->adj = newNodeA; //인접 리스트에 노드 추가

                ind = GraphNodeList.NodeNumber;
            }

            else
            {
                GraphNodeList.NList[ind] = new Node;
                GraphNodeList.NList[ind]->vertexName = nodeB; //인접 리스트의 헤더로 두 번째 노드 삽입
                GraphNodeList.NList[ind]->isMarked = false; //새 노드를 추가하며 isMarked 초기화
                GraphNodeList.NList[ind]->adj = NULL; //인접 리스트에 아무것도 넣지 않음
                ind++;

                GraphNodeList.NList[ind] = new Node;
                GraphNodeList.NList[ind]->vertexName = nodeA; //인접 리스트의 헤더로 첫 번째 노드 삽입
                GraphNodeList.NList[ind]->isMarked = false; //새 노드를 추가하며 isMarked 초기화

                ind = GraphNodeList.NodeNumber + 1;
            }

            GraphNodeList.NList[ind]->adj = newNodeB; //인접 리스트에 노드 추가

            GraphNodeList.NodeNumber += 2; //인접 리스트에 노드 2개가 추가되었음을 표시
        }

        /* 추가 한 리스트 원소 사이의 순서 정렬 */
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
    string answer = ""; //리턴을 위한 변수

    string visited[NodeMaxCount]; //방문한 적 있는 노드의 vertexName을 저장하는 배열
    int visitInd = 0; //visited의 인덱스를 세기 위한 변수

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
    string visited[NodeMaxCount]; //방문한 적 있는 노드의 vertexName을 저장하는 배열
    int visitInd = 0; //visited의 인덱스를 세기 위한 변수
    int treeCnt = 0; //tree의 성질을 만족하는 component의 개수를 세어줄 변수

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
    string answer = ""; //dfs의 결과를 저장할 변수

    string willVisit[NodeMaxCount]; //방문해야 하는 노드의 vertexName을 저장하는 배열
    string vArr[NodeMaxCount]; //SCC를 덩어리 별로 저장할 변수

    string visited[NodeMaxCount]; //방문한 적 있는 노드의 vertexName을 저장하는 배열
    int visitInd = 0; //visited의 인덱스를 세기 위한 변수
    int vind = 0; //vArr의 인덱스를 세기 위한 변수
    int wind = 0;

    /* 인접 리스트를 역순으로 willVisit에 채워 넣음 */
    for (int i = 0; i < GraphNodeList.NodeNumber; i++)
    {
        if (GraphNodeList.NList[i]->isMarked == false)
            storeAdj(i, visited, willVisit, &wind, &visitInd);
    }

    Graph reverse = getReverse();
    
    /* dfs 진행을 위해 isMarked 초기화 */
    for (int i = 0; i < GraphNodeList.NodeNumber; i++)
        GraphNodeList.NList[i]->isMarked = false;

    /* dfs 진행을 위해 visited 및 visitInd 초기화 */
    for (int i = 0; i < visitInd; i++)
    {
        visited[i] = "";
    }

    visitInd = 0;

    if(vArr[wind] == "")
        wind--;

    /* dfs를 진행하며 SCC를 덩어리 별로 저장 */
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

    int max = 0; //가장 길이가 긴 string을 알아내기 위해 변수 선언
    for (int i = 0; i < vind; i++)
    {
        if (vArr[max].length() < vArr[i].length())
            max = i;

        else continue;
    }

    int sameLength[NodeMaxCount]; //max와 같은 길이의 SCC가 있으면 저장해줄 배열
    int iInd = 0; //sameLength의 인덱스를 세기 위한 변수 선언

    int ifSameLength = hasSameLength(sameLength, vArr, vind, max, &iInd); //같은 길이의 SCC가 있는지 확인해주는 함수에 대입

    if (ifSameLength == true) //max와 같은 길이의 SCC가 있을 경우
    {
        int smallest = 0;
        int index = 0;

        /* max와 같은 길이의 SCC의 인덱스를 저장해둔 배열을 돌며 사전순으로 가장 작은 vertexName을 갖는 SCC를 찾기 */
        for (int i = 0; i < iInd; i++)
        {
            index = sameLength[i];
            if (vArr[max][0] > vArr[index][0])
                max = index;

            else continue;
        }
    }
    
    answer = vArr[max]; //answer에 사전순으로 가장 작은 SCC를 대입함

    string temp[NodeMaxCount]; //answer 정렬을 위한 임시 배열
    int index = 0; //temp의 인덱스 저장
    int prevSpace = -1; //이전 공백 인덱스 저장
    int currentSpace = -1; //현재 공백 인덱스 저장
    for (int i = 0; i < answer.length(); i++)
    {
        /* 공백을 기준으로 string을 분할하여 저장 */
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

            temp[index] = answer.substr(prevSpace, currentSpace - prevSpace); //temp의 index번째 란에 answer의 이전 공백부터 다음 공백까지의 string 입력
            prevSpace = i + 1; //이전 공백 인덱스 업데이트
            index++; //temp 인덱스 업데이트
        }
    }

    /* 노드가 하나인 경우, 혹은 하나 이상인 경우의 마지막 노드는 temp에 들어가지 않기 때문에 해당 노드를 temp에 추가해줌 */
    int len = answer.length() - 1;
    temp[index] = answer[len];
    index++;

    sortString(temp, index); //temp에 저장한 각 vertexName을 사전순으로 정렬
    answer = ""; //answer 초기화

    /* 정렬한 temp를 공백과 더하여 answer에 다시 저장 */
    for (int i = 0; i < index; i++)
    {
        answer += temp[i];
        answer += " ";
    }

    answer.pop_back(); //맨 마지막 공백 삭제

    return answer;
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

string Graph::getDijkstraShortestPath(string source, string destination)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////    
    int start = findNode(source); //시작점의 인덱스
    int final = findNode(destination); //끝점의 인덱스
    
    int nodeNumber = GraphNodeList.NodeNumber; //노드 개수를 가리키는 변수 선언

    string answer = ""; //반환용 string 선언

    string** prev = new string * [nodeNumber]; //이전에 거쳐온 원소들을 저장하는 리스트
    for (int i = 0; i < nodeNumber; i++)
        prev[i] = new string[nodeNumber];

    /* 거리 저장용 배열 선언 후 초깃값으로 초기화 */
    int* distance = new int[nodeNumber];

    for (int i = 0; i < nodeNumber; i++)
        distance[i] = INF;

    /* graph의 weight를 2차원 배열 형태로 저장 */
    int** graph = new int* [nodeNumber];
    for (int i = 0; i < nodeNumber; i++)
        graph[i] = new int[nodeNumber];

    graphToMatrix(graph, nodeNumber);
    dfsForDijkstra(graph, distance, start, prev);

    if (distance[final] == INF) //final에 도달하지 못한 경우
    {
        answer = "error";
    }

    else //도달한 경우
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
    int start = findNode(source); //시작점의 인덱스
    int final = findNode(destination); //끝점의 인덱스

    int nodeNumber = GraphNodeList.NodeNumber; //노드 개수를 가리키는 변수 선언
    string answer = ""; //반환용 string 선언

    /* 경로 저장용 배열 선언 */
    int** path = new int* [nodeNumber];
    for (int i = 0; i < nodeNumber; i++)
        path[i] = new int[nodeNumber];

    /* 경로 저장용 배열 초기화 */
    for (int i = 0; i < nodeNumber; i++)
    {
        for (int j = 0; j < nodeNumber; j++)
            path[i][j] = -1;
    }

    /* graph의 weight를 2차원 배열 형태로 저장 */
    int** graph = new int* [nodeNumber];
    for (int i = 0; i < nodeNumber; i++)
        graph[i] = new int[nodeNumber];

    graphToMatrix5(graph, nodeNumber);

    floyd(graph, nodeNumber, path, start, final); //graph 업데이트 (최소 거리 탐색)

    answer += GraphNodeList.NList[start]->vertexName; //시작노드 이름 string에 더하기
    answer += " ";

    addPath(path, &answer, start, final); //재귀 호출로 최소 거리 경로 string에 더하기

    answer += GraphNodeList.NList[final]->vertexName; //끝노드 이름 string에 더하기
    answer += " ";

    answer += to_string(graph[start][final]); //최소 거리 string에 더하기

    return answer;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

int Graph::primMST(ofstream &fout, string startNode)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    string visited[NodeMaxCount]; //방문한 적 있는 노드의 vertexName을 저장하는 배열
    int prev[NodeMaxCount]; //방문할 노드의 이전 노드를 저장하는 배열
    int visitInd = 0;

    Node haveToVisit[NodeMaxCount]; //방문할 노드의 이름과 가중치를 저장하는 배열
    int nodeInd = 0;

    int cnt = 0; //MST의 간선 개수를 세어줄 변수
    int nodeNumber = GraphNodeList.NodeNumber; //그래프 노드 개수

    int dist = 0; //MST에 더해지는 간선의 가중치를 누적하여 합해주는 변수

    string answer = ""; //fout용 변수

    int start = findNode(startNode); //시작 노드의 번호
    int target = 0;
    int parent = 0;

    while (cnt != nodeNumber - 1)
    {
        if (cnt == 0) //처음 시작의 경우 시작 노드로 출발
            target = start;

        /* 방문 여부 표시 */
        GraphNodeList.NList[target]->isMarked = true;
        visited[visitInd] = GraphNodeList.NList[target]->vertexName;
        visitInd++;

        /* 해당 노드에서 더 이상 나아갈 수 없다면 이전 노드로 돌아가서 동작 반복 */
        if (noWay(target))
        {
            target = parent;
            continue;
        }

        /* answer에 해당 노드 더함 */
        answer += GraphNodeList.NList[target]->vertexName;
        answer += " ";

        /* 인접 노드를 중복 없이 모두 저장 */
        Node* temp = GraphNodeList.NList[target]->adj;
        /* 인접 노드가 없다면 이전 노드로 돌아가서 동작 반복 */
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

        /* 인접 노드 중 방문한 적 없으며 가장 거리가 짧은 노드 선택 */
        bool whether = false;
        int minDis = INF, minNode = 0, weight = 0;
        string nodeName = "";

        while (!whether)
        {
            /* 가장 짧은 가중치의 간선 선택 */
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

            /* 해당 간선과 이어진 노드를 방문한 적 있다면 해당 간선 삭제 후 반복 */
            if (GraphNodeList.NList[target]->isMarked)
                findEraseOne(haveToVisit, &nodeInd, prev, weight, nodeName);

            else
                whether = true;
        }

        /* 선택된 간선 삭제 후 answer에 간선과 이어진 노드 및 가중치 출력 */
        findEraseAll(haveToVisit, &nodeInd, prev, nodeName);
        answer += GraphNodeList.NList[target]->vertexName;
        answer += " ";
        answer += to_string(minDis);

        fout << answer << endl;

        answer = "";
        dist += minDis; //MST path의 가중치 누적합 업데이트

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
    int nodeNumber = GraphNodeList.NodeNumber; //총 노드 개수
    int edgeNum = 0; //간선 개수 저장용 변수

    /* 간선 개수 세기 */
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

    Edge* EList = new Edge[edgeNum]; //간선 리스트
    int eInd = 0; //간선 리스트 인덱스 카운트용

    initEList(EList, &eInd, nodeNumber); //간선 리스트 정렬하여 저장

    int dist = 0; //최종 거리 저장용 변수
    string answer = ""; //출력용 string

    int* parent = new int[nodeNumber]; //노드별로 인접 노드 중 가장 작은 노드의 인덱스를 저장하는 배열
    for (int i = 0; i < nodeNumber; i++) //parent 초기화
        parent[i] = i;

    for (int i = 0; i < edgeNum; i++)
    {
        if (!haveSameParent(parent, EList[i].from, EList[i].to)) //parent가 같지 않을 경우(해당 노드들을 방문한 적 없을 경우)에만 실행
        {
            dist += EList[i].weight; //최종 거리 업데이트
            answer = answer + EList[i].from + " " + EList[i].to + " " + to_string(EList[i].weight); //string에 MST에 추가할 간선 저장
            fout << answer << endl; //이번 반복에서 MST에 추가하게 된 간선 출력

            answer = ""; //string 초기화

            unionParent(parent, EList[i].from, EList[i].to); //두 노드들을 방문했음을 표시
        }
    }

    return dist;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}