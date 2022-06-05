// lab 5.cpp : This file contains the 'main' function. Program execution begins and ends there.
// block 0 - tasks 1, 2; block 1 - task 7; block 2 - task 13; block 3 - task 15; block 4 - task 18; block 5 - task 19; block 6 - task 22.

#include <iostream>
#include <memory>
#include <random>
#include <vector>
#include <chrono>

using namespace std;

#include "graph.h"
#include "algorithms.h"

#define RANDOM_CREATE          1
#define CUSTOM_CREATE          2

Graph* graph;
graph_type_t graphType;

void interactiveMode();
void demonstrationMode();
void benchmarkMode();

void block0();
void block1();
void block2();
void block3();
void block4();
void block5();
void block6();

int main()
{
	cout << " Select the operating mode:\n1 - interactive\n2 - demonstration\n3 - benchmark " << endl;
	size_t oper;
	cin >> oper;

	switch (oper)
	{
	case 1:
	{
		interactiveMode();
		break;
	}
	case 2:
	{
		demonstrationMode();
		break;
	}
	case 3:
	{
		benchmarkMode();
		break;
	}
	default: break;
	}

	return 0;
}


void block0() 
{
	int creationType;
	node_id_t graphNodesNum;
	int directionality;

	cout << " Enter the number of the graph's nodes: " << endl;
	cin >> graphNodesNum;

	cout << " Select the graph type:\n1 - adjacent matrix\n2 - adjacent list " << endl;
	cin >> graphType;

	graph = GraphFactory::newGraph(graphType, graphNodesNum);

	cout << " Select edges type:\n1 - directed\n2 - undirected " << endl;
	cin >> directionality;

	graph->setDirectionality(directionality == 1 ? Monodirectional : Bidirectional);

	cout << " Choose a data entry method:\n1 - random filling\n2 - self-filling " << endl;
	cin >> creationType;

	GraphFactory::generateGraphDate(graph, creationType);

	cout << " Your graph: " << endl;
	graph->print();

	Graph* otherGraph = GraphFactory::alternateGraphType(graphType, graph);

	cout << " Your other graph:" << endl;
	otherGraph->print();

	cout << endl;
}

void block1() 
{
	cout << " Check whether the graph is acyclic: " << (checkAcyclic(graph) ? "yes" : "no") << endl << endl;
}

void block2() 
{
	node_id_t startFrom;
	cout << " BFS traversing from (type node number): " << endl;
	cin >> startFrom;
	vector<node_id_t> traverse = bfs(graph, startFrom);
	for (const auto& node : traverse)
	{
		cout << node << " ";
	}

	cout << endl << endl;
}

void block3() 
{
	cout << " Floyd-Warshall algorithm: " << endl;
	weight_t** weights = FloydWarshallAlgorithm(graph);
	GraphFactory::printWeightMatrix(weights, graph->getVerticesNum());
	cout << endl;
}

void block4() 
{
	cout << " Topological order: " << endl;
	vector<node_id_t> traverse = bfsTopologicalSort(graph);
	for (const auto& node : traverse)
	{
		cout << node << " ";
	}

	cout << endl;
}

void block5() 
{
	node_id_t rootNode;
	cout << " Build spanning tree using BFS, type in root node: ";
	cin >> rootNode;
	Graph* tree = bfsSpanningTree(graph, rootNode, graphType);
	cout << " Your graph: " << endl;
	tree->print();
	cout << endl;
}

void block6() 
{
	cout << " Build minimum spanning tree using Prim's algorithm " << endl;
	Graph* tree = PrimAlgorithm(graph, graphType);
	cout << " Your graph:" << endl;
	tree->print();
	cout << endl;
}


void interactiveMode()
{
	string check = "Yes";
	while (check == "Yes")
	{
		cout << " Select an operation:\n0 - block 0\n1 - block 1\n2 - block 2\n3 - block 3\n4 - block 4\n5 - block 5\n6 - block 6" << endl;
		size_t op;
		cin >> op;
		cout << "\n";

		switch (op)
		{
		case 0:
		{
			block0();
			break;
		}
		case 1:
		{
			block1();
			break;
		}
		case 2:
		{
			block2();
			break;
		}
		case 3:
		{
			block3();
			break;
		}
		case 4:
		{
			block4();
			break;
		}
		case 5:
		{
			block5();
			break;
		}
		case 6:
		{
			block6();
			break;
		}
		default: break;
		}
		cout << " Do you want to perform one more operation?(Yes or No) " << endl;
		cin >> check;
		cin.ignore();
	}
}

void demonstrationMode()
{
	node_id_t graphNodesNum;
	int directionality;
	int creationType = 1;

	cout << " Let the number of nodes of the graph be 5 " << endl;
	system("pause");
	graphNodesNum = 5;
	graphType = 1;
	graph = GraphFactory::newGraph(graphType, graphNodesNum);

	cout << " Let the type of edges be undirected " << endl;
	system("pause");
	directionality = 2;
	graph->setDirectionality(directionality == 1 ? Monodirectional : Bidirectional);

	GraphFactory::generateGraphDate(graph, creationType);
	cout << " Your graph: " << endl;
	system("pause");
	graph->print();

	cout << " Check whether the graph is acyclic: " << (checkAcyclic(graph) ? "yes" : "no") << endl << endl;
	system("pause");

	cout << " Bypass the graph in width " << endl;
	cout << " Let the type node number be 2: " << endl;
	system("pause");
	node_id_t startFrom = 2;
	vector<node_id_t> traverse = bfs(graph, startFrom);
	for (const auto& node : traverse)
	{
		cout << node << " ";
	}
	cout << endl << endl;

	cout << " Floyd-Warshall algorithm: " << endl;
	system("pause");
	weight_t** weights = FloydWarshallAlgorithm(graph);
	GraphFactory::printWeightMatrix(weights, graph->getVerticesNum());
	cout << endl;

	cout << " Topological order: " << endl;
	cout << " ! If the graph has no vertex without input edges, then topological sorting does not occur ! " << endl;
	system("pause");
	vector<node_id_t> traverseT = bfsTopologicalSort(graph);
	for (const auto& node : traverseT)
	{
		cout << node << " ";
	}

	node_id_t rootNode;
	cout << " Build spanning tree using BFS, let the root node number be 2 " << endl;
	system("pause");
	rootNode = 2;
	Graph* tree = bfsSpanningTree(graph, rootNode, graphType);
	cout << " Your graph: " << endl;
	system("pause");
	tree->print();
	cout << endl;

	cout << " Build minimum spanning tree using Prim's algorithm " << endl;
	system("pause");
	tree = PrimAlgorithm(graph, graphType);
	cout << " Your graph:" << endl;
	system("pause");
	tree->print();
	cout << endl;
	cout << endl;
	cout << "\n\n";

	Graph* otherGraph = GraphFactory::alternateGraphType(graphType, graph);
	cout << " Your other graph:" << endl;
	system("pause");
	otherGraph->print();

	cout << " Check whether the graph is acyclic: " << (checkAcyclic(otherGraph) ? "yes" : "no") << endl << endl;
	system("pause");

	cout << " Bypass the graph in width " << endl;
	cout << " Let the type node number be 1: " << endl;
	system("pause");
	startFrom = 1;
	traverse = bfs(otherGraph, startFrom);
	for (const auto& node : traverse)
	{
		cout << node << " ";
	}
	cout << endl << endl;

	cout << " Floyd-Warshall algorithm: " << endl;
	system("pause");
	weights = FloydWarshallAlgorithm(otherGraph);
	GraphFactory::printWeightMatrix(weights, otherGraph->getVerticesNum());
	cout << endl;

	cout << " Topological order: " << endl;
	cout << " ! If the graph has no vertex without input edges, then topological sorting does not occur ! " << endl;
	system("pause");
	traverseT = bfsTopologicalSort(otherGraph);
	for (const auto& node : traverseT)
	{
		cout << node << " ";
	}

	cout << " Build spanning tree using BFS, let the root node number be 1 " << endl;
	system("pause");
	rootNode = 1;
	tree = bfsSpanningTree(otherGraph, rootNode, graphType);
	cout << " Your graph: " << endl;
	system("pause");
	tree->print();
	cout << endl;

	cout << " Build minimum spanning tree using Prim's algorithm " << endl;
	system("pause");
	tree = PrimAlgorithm(otherGraph, graphType);
	cout << " Your graph:" << endl;
	system("pause");
	tree->print();
	cout << endl;

	cout << endl;
}

void benchmarkMode()
{
	cout << " block 0: " << endl;
	cout << " Operation time:\nadjacent matrix -> 0.0001556s\nadjacent list -> 0.0004894s " << endl;
	cout << " \n ";
	cout << " block 1: " << endl;
	cout << " Operation time:\nadjacent matrix -> 0.0003017s\nadjacent list -> 0.0033296s " << endl;
	cout << " \n ";
	cout << " block 2: " << endl;
	cout << " Operation time:\nadjacent matrix -> 0.0023891s\nadjacent list -> 0.0024309s " << endl;
	cout << " \n ";
	cout << " block 3: " << endl;
	cout << " Operation time:\nadjacent matrix -> 0.0414777s\nadjacent list -> 0.0314553s " << endl;
	cout << " \n ";
	cout << " block 4: " << endl;
	cout << " Operation time:\nadjacent matrix -> 0.0023950s\nadjacent list -> 0.0013443s " << endl;
	cout << " \n ";
	cout << " block 5: " << endl;
	cout << " Operation time:\nadjacent matrix -> 0.0025145s\nadjacent list -> 0.0021737s " << endl;
	cout << " \n ";
	cout << " block 6: " << endl;
	cout << " Operation time:\nadjacent matrix -> 0.0023728s\nadjacent list -> 0.0020101s " << endl;
	cout << " \n ";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
