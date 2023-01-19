/*
    Programming Assignment #4
    20210479 이주현
*/
#include <fstream>
#include <iostream>
#include <math.h>
#include <string>
#include "graph.h"
#include "utils.h"

using namespace std;


/*
    [Task 1] Graph Traversals

    Description:
        Implement a function that finds DFS traverse from the given undirected graph. 
        The graph may consist of several connected graphs. 
        The search starts with the node coming first in the lexicographical order of labels. 
        Also, the next node should be selected in lexicographical order among connected nodes. 
        If there exist n connected graphs, then print n traverses separated with a newline in lexicographical order.

        TODO: Implement Graph::addUndirectedEdge and Graph::DFS functions

    Input & output
    Input: Pairs of nodes with alphabet labels that indicate edges.
        - ('A','B'): an edge between node A and node B.
    Output:
        - Result of traverse separated with a white space
        - Multiple traverses are separated with a new line, in lexicographical order.

*/

void task_1(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 1]" << endl;

    try {
        Graph graph;
        for (int i = 0; i < instr_seq.getLength(); i++) {
            string firstNode = instr_seq.getInstruction(i).getCommand();
            string secondNode = instr_seq.getInstruction(i).getValueStr();
            graph.addUndirectedEdge(firstNode, secondNode);
        }
        fout << graph.DFS() << endl;
    } catch (const char *e) {
        cerr << e << endl;
    }
}


/*
    [Task 2] Tree in the Graph

    Description:
        Implement a function that find number of components satisfying tree property (Trees) in the given undirected graph.
        When a component is connected and acyclic (or having n-1 edges with n nodes), we regarded the component as tree.
    
        TODO: Implement Graph::addUndirectedEdge and Graph::getTreeCount functions

    Input & Output:
        Input: Pairs of nodes with alphabet labels that indicate edges.
            - If the input edge already exists in the graph, ignore the input.      
        Output: The number of trees in the graph generated from input.
            - Return 0 if no component in the graph satisfies the tree property.
*/

void task_2(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 2]" << endl;
  
    try {
      Graph graph;
      for (int i = 0; i < instr_seq.getLength(); i++) {
          string firstNode = instr_seq.getInstruction(i).getCommand();
          string secondNode = instr_seq.getInstruction(i).getValueStr();
          graph.addUndirectedEdge(firstNode, secondNode);
      }
      fout << graph.getTreeCount() << endl; //graph.getTreeCount()
    } catch (const char *e) {
        cerr << e << endl;
    }
}


/*
    [Task 3] Strongly Connected Component in a directed graph

    Description:
        Implement a function that retrieves the Strongly Connected Components (SCC) in the given directed graph. 
        This function finds the largest Strongly Connected Components that can be found in the given directed graph and prints out the node labels of it. 
        There might be multiple SCC with the same size. 
        If that is the case, retrieve the SCC that comes first in lexicographical order.
        For instance, if two connected components, (A,B,C) and (D,E,F) are found, select (A,B,C) because A comes first than B in lexicographical order.
        Unlike task 1, the edges of the graph have direction in this time.
        For instance, (‘A’,’B’) is different from (‘B’,’A’).
        
        TODO: Implement Graph::addDirectedEdge function and Graph::getStronglyConnectedComponenet function.
    
    Input & Output:
        Input: Pairs of nodes with alphabet labels that indicate edges.
            - ('A','B'): an edge from node A to node B.
            - If the input edge already exists in the graph, ignore the input.
        Output: A sequence of the node labels of the largest strongly connected componenet.
            - Output should be sorted in lexicographical order and separated with space.
*/

void task_3(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 3]" << endl;
  
    try {
      Graph graph;
      for (int i = 0; i < instr_seq.getLength(); i++) {
          string firstNode = instr_seq.getInstruction(i).getCommand();
          string secondNode = instr_seq.getInstruction(i).getValueStr();
          graph.addDirectedEdge(firstNode, secondNode);
      }
      fout << graph.getStronglyConnectedComponent() << endl;
    } catch (const char *e) {
        cerr << e << endl;
    }
}


/*
    [Task 4] Single Source Shortest Path of Graph

    Description:
        Implement a function that finds the shortest path from the source node to the destination node in the given graph using Dijkstra's algorithm.
        We assume that the given graph is a directed, weighted, and weakly-connected graph.
        All weights of edges are positive (i.e. larger than 0).
        This function should return the sequence of node labels along the path and also the length (sum of the weights of the edges) of the path.
        If the path from the source node to the destination node doesn't exist, return 'error'.
        You can modify the graph.cpp and graph.h files for this problem.

        TODO: Implement Graph::addDirectedEdge and Graph::getDijkstraShortestPath functions

    Input & output
    Input: A sequence of commands
        - ('A-B',integer): an edge from node A to node B with weight value {integer}.
        - ('A','B'): a pair of node labels that indicates the source and the destination node. The first element indicates the source node and the second one indicates the destination node.
    Output:
        - A sequence of the node labels along the path followed by length of the path.
        - error if the path does not exist 
 */

void task_4(ofstream &fout, InstructionSequence &instr_seq)
{
    fout << "[Task 4]" << endl;
  
    try {
        Graph graph;
        for (int i = 0; i < instr_seq.getLength() - 1; i++) {
            string command = instr_seq.getInstruction(i).getCommand();
            int value = instr_seq.getInstruction(i).getValue();
            string firstNode = command.substr(0, command.find('-'));
            string secondNode =
                command.substr(command.find('-') + 1, command.length());
            graph.addDirectedEdge(firstNode, secondNode, value);

        }
        string source =
            instr_seq.getInstruction(instr_seq.getLength() - 1).getCommand();
        string destination =
            instr_seq.getInstruction(instr_seq.getLength() - 1).getValueStr();

        fout << graph.getDijkstraShortestPath(source, destination) << endl;
    } catch (const char *e) {
        cerr << e << endl;
    }
}


/*
    [Task 5] All Pairs Shortest Paths of Graph
    
    Description:
        Implement a function that finds the shortest paths of all pairs of nodes in the given graph using Floyd's algorithm.
        Unlike problem 4, there will be an edge(s) with negative weight value(s).
        This function should return the sequence of node labels along the path and also the distance of the path from the source to the destination
        The nodes are sorted in lexicographical order in the distance matrix.
        If the source and the destination is identical, distance is 0.
        If there is no path from the source to the destination, distance is INF.
        You can modify the graph.cpp and graph.h files for this problem.
        
        TODO: Implement Graph::addDirectedEdge and Graph::getFloydShortestPath function

    Input & Output
    Input: A sequence of commands 
        - ('A-B',integer): an edge from node A to node B with weight value {integer}.
        - ('A','B'): a pair of node labels that indicates the source and the destination node. The first element indicates the source node and the second one indicates the destination node.
    Output:
        - A sequence of the node labels along the path followed by length of the path.
        - error if the path does not exist 
 */

void task_5(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 5]" << endl;
  
    try {
        Graph graph;
        for (int i = 0; i < instr_seq.getLength() - 1; i++) {
            string command = instr_seq.getInstruction(i).getCommand();
            int value = instr_seq.getInstruction(i).getValue();
            string firstNode = command.substr(0, command.find('-'));
            string secondNode =
                command.substr(command.find('-') + 1, command.length());
            graph.addDirectedEdge(firstNode, secondNode, value);
        }
        string source =
            instr_seq.getInstruction(instr_seq.getLength() - 1).getCommand();
        string destination =
            instr_seq.getInstruction(instr_seq.getLength() - 1).getValueStr();
        fout << graph.getFloydShortestPath(source, destination) << endl;
    } catch (const char *e) {
        cerr << e << endl;
    }
}


/*
    [Task 6] Prim's Algorithm

    Description:
        Implement a function that finds the Minimum-cost Spanning Tree (MST) of the given
        weighted undirected graph using the Prim's algorithm.
        Given a start node, this function start with the single-vertex tree of the given node.
        Then, the function prints the added edge and the weight of the edge each time the tree grows.
        When printing an edge, you first have to print the label of the node that already
        exists in the tree, then print the label of the node that newly inserted into the tree.
        If there are multiple edges with the same weight, this function checks the label of the added node
        (i.e. the node which is not included in the tree) and selects the node with the first label in lexicographical order.
        Finally, the function returns the cost of the MST (i.e. the sum of edge weights).
        You can assume that the given graph is a connected graph.
        You can modify graph.cpp and graph.h files for this problem.

        TODO: Implement Graph::addUndirectedEdge and Graph::primMST functions

    Input & output
    Input: A sequence of commands
        - ('A-B',integer): an edge between node A and node B with weight value {integer}.
        - ('MST','A'): find MST using the Prim's algorithm which start with node A.
    Output:
        - For each time the tree grows, print the labels of the nodes indicating the added edges
            and the weight of the edge as a string separated with a white space.
        - Print the cost of MST.
*/

void task_6(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 6]" << endl;
  
    try {
        Graph graph;
        for (int i = 0; i < instr_seq.getLength(); i++) {
            string command = instr_seq.getInstruction(i).getCommand();
            if (command.compare("MST") == 0) {
                string startNode = instr_seq.getInstruction(i).getValueStr();
                fout << graph.primMST(fout, startNode) << endl;
            } else {
                string firstNode = command.substr(0, command.find('-'));
                string secondNode =
                    command.substr(command.find('-') + 1, command.length());
                int value = instr_seq.getInstruction(i).getValue();
                graph.addUndirectedEdge(firstNode, secondNode, value);
            }
        }
    } catch (const char *e) {
        cerr << e << endl;
    }
}


/*
    [Task 7] Kruskal's Algorithm

    Description:
        Implement a function that finds the Minimum-cost Spanning Tree (MST) of the given weighted undirected graph using the Kruskal's algorithm.
        The function prints the added edge and the weight of the edge each time the tree grows.
        When printing an edge, you have to print the label in lexicographical order.
        If there are multiple edges with the same weight, this function also selects the edge in lexicographical order.
        That means it compares the first node of edges, and if the first node is the same, it compares the second node of edges.
        The function return the cost of the MST (i.e. the sum of edge weights). You can assume that the given graph is a connected graph.
        You can modify graph.cpp and graph.h files for this problem.

        TODO: Implement Graph::addUndirectedEdge and Graph::kruskalMST functions

    Input & output
    Input: A sequence of commands
        - ('A-B',integer): an edge between node A and node B with weight value {integer}.
        - ('MST',NULL): find MST using the Kruskal's algorithm.
    Output:
        - For each time the tree grows, print the labels of the nodes indicating the added edges
            in lexicographical order and the weight of the edge as a string separated with a white space.
        - Print the cost of MST.
*/

void task_7(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 7]" << endl;
  
    try {
        Graph graph;
        for (int i = 0; i < instr_seq.getLength(); i++) {
            string command = instr_seq.getInstruction(i).getCommand();
            if (command.compare("MST") == 0) {
                fout << graph.kruskalMST(fout) << endl;
            } else {
                string firstNode = command.substr(0, command.find('-'));
                string secondNode =
                    command.substr(command.find('-') + 1, command.length());
                int value = instr_seq.getInstruction(i).getValue();
                graph.addUndirectedEdge(firstNode, secondNode, value);
            }
        }
    } catch (const char *e) {
        cerr << e << endl;
    }
}


int main(int argc, char **argv) {
    string filename = "submit.txt";
    int task_num = 0;
    InstructionSequence instr_seq;

    // Open file
    ofstream fout;
    fout.open(filename, fstream::app);
    if (!fout.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        return -1;
    }

    // Choosing task number. Default is running ALL tasks (0)
    if (argc >= 2)
        task_num = atoi(argv[1]);
    if (argc >= 3) {
        try {
            instr_seq.parseInstructions(argv[2]);
        } catch (const char *e) {
            cerr << e << endl;
            return -1;
        }
    }

    // Running the task(s)
    switch (task_num) {
        case 1:
            task_1(fout, instr_seq);
            break;
        case 2:
            task_2(fout, instr_seq);
            break;
        case 3:
            task_3(fout, instr_seq);
            break;
        case 4:
            task_4(fout, instr_seq);
            break;
        case 5:
           task_5(fout, instr_seq);
           break;
        case 6:
           task_6(fout, instr_seq);
           break;
        case 7:
           task_7(fout, instr_seq);
           break;
        case 0:
            instr_seq.parseInstructions(TASK_1_DEFAULT_ARGUMENT);
            task_1(fout, instr_seq);

            instr_seq.parseInstructions(TASK_2_DEFAULT_ARGUMENT);
            task_2(fout, instr_seq);

            instr_seq.parseInstructions(TASK_3_DEFAULT_ARGUMENT);
            task_3(fout, instr_seq);

            instr_seq.parseInstructions(TASK_4_DEFAULT_ARGUMENT);
            task_4(fout, instr_seq);

            instr_seq.parseInstructions(TASK_5_DEFAULT_ARGUMENT);
            task_5(fout, instr_seq);

            instr_seq.parseInstructions(TASK_6_DEFAULT_ARGUMENT);
            task_6(fout, instr_seq);

            instr_seq.parseInstructions(TASK_7_DEFAULT_ARGUMENT);
            task_7(fout, instr_seq);

            break;
        default:
            cout << "Wrong task number" << endl;
    }

    fout.close();
    return 0;
}
