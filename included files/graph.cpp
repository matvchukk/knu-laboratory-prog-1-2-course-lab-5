#include "graph.h"

using namespace std;

Graph::Graph(node_id_t verticesNum) 
{
	this->verticesNum = verticesNum;
}

node_id_t Graph::getVerticesNum() 
{
	return this->verticesNum;
}

void Graph::addBidirectEdge(node_id_t i, node_id_t j, weight_t weight) 
{
	addEdge(i, j, weight);
	addEdge(j, i, weight);
}

void Graph::removeBidirectEdge(node_id_t i, node_id_t j) 
{
	removeEdge(i, j);
	removeEdge(j, i);
}

void Graph::userInputs() 
{
	int counter = 0;

	node_id_t fromNode, toNode;
	weight_t  weight;
	bool continueInput = 1;
	while (continueInput) 
	{
		cout << "(" << counter << " edges so far) " << " Give new edge in format <outcome node> <income node> <weight>: ";
		cin >> fromNode >> toNode >> weight;

		if (fromNode > this->verticesNum || toNode > this->verticesNum) 
		{
			cout << " You have given vertices that don't exist in the graph " << endl;
			continue;
		}

		counter++;

		if (directionality == Bidirectional)
			addBidirectEdge(fromNode, toNode, weight);
		else
			addEdge(fromNode, toNode, weight);

		cout << " Continue input? (0 or 1) " << endl;
		cin >> continueInput;
	}
}

void Graph::setDirectionality(GraphDirectionality option) 
{
	this->directionality = option;
}

GraphDirectionality Graph::getDirectionality() 
{
	return this->directionality;
}

AdjacencyMatrixGraph::AdjacencyMatrixGraph(node_id_t verticesNum) 
{
	this->verticesNum = verticesNum;
	adjacency = new adjacency_t* [verticesNum];
	weights = new weight_t* [verticesNum];

	for (node_id_t i = 0; i < verticesNum; i++) 
	{
		adjacency[i] = new adjacency_t[verticesNum];
		weights[i] = new weight_t[verticesNum];

		for (node_id_t j = 0; j < verticesNum; j++)
			adjacency[i][j] = false;
	}
}

weight_t AdjacencyMatrixGraph::weightAt(node_id_t i, node_id_t j, bool nonInf) 
{
	weight_t w = weights[i][j];
	if (w == INFINITY)
	{
		if (!nonInf) return INFINITY;
		else return 0;
	}	
	else return weights[i][j];
};

void AdjacencyMatrixGraph::addEdge(node_id_t i, node_id_t j, weight_t weight) 
{ 
	this->adjacency[i][j] = true;
	this->weights  [i][j] = weight;
}

void AdjacencyMatrixGraph::removeEdge(node_id_t i, node_id_t j) 
{
	this->adjacency[i][j] = false;
}

void AdjacencyMatrixGraph::enqueueNeighboursOf(node_id_t i, traverse_queue_t& queue) 
{
	for (node_id_t j = 0; j < verticesNum; j++) 
	{
		if (!adjacency[i][j]) continue;
		queue.push(make_pair(j, weights[i][j]));
	}
}

vertex_linkage_t AdjacencyMatrixGraph::adjacentTo(node_id_t i) 
{	
	vertex_linkage_t linkage;

	for (node_id_t j = 0; j < verticesNum; j++) 
	{
		if (!this->adjacency[i][j]) continue;
		linkage[j] = this->weights[i][j];
	}

	return linkage;
}

void AdjacencyMatrixGraph::print() 
{
	for (node_id_t i = 0; i < verticesNum; i++) 
	{
		cout << i << " : ";
		for (node_id_t j = 0; j < verticesNum; j++)
		{
			cout << adjacency[i][j] << " (" << weights[i][j] << ") ";
		}
		cout << "\n";
	}
}

void AdjacencyMatrixGraph::randomGenerate() 
{	
	static default_random_engine e;
	static uniform_real_distribution<> weight_dis(WEIGHT_LOWER_RANGE, WEIGHT_UPPER_RANGE);
	static uniform_int_distribution<> adj_dis(0, 1);

	for (node_id_t i = 0; i < verticesNum; i++)
		for (node_id_t j = 0; j < verticesNum; j++) 
		{
			adjacency[i][j] = adj_dis(e);
			weight_t w = adjacency[i][j] ? weight_dis(e) : INFINITY;
			weights[i][j] = w;
			if (directionality == Bidirectional)
				weights[j][i] = adjacency[i][j] ? w : INFINITY;
		}
}

AdjacencyMatrixGraph::~AdjacencyMatrixGraph() 
{
	for (node_id_t i = 0; i < verticesNum; i++) 
	{
		delete[] adjacency[i];
		delete[] weights  [i];
	}
	delete[] adjacency;
	delete[] weights;
}

AdjacencyListGraph* AdjacencyMatrixGraph::toAdjList() 
{
	auto graph = new AdjacencyListGraph(verticesNum);

	for (node_id_t i = 0; i < verticesNum; i++)
		for (node_id_t j = 0; j < verticesNum; j++) 
		{
			if (!adjacency[i][j]) continue;
			graph->addEdge(i, j, weights[i][j]);
		}

	return graph;
}

node_id_t AdjacencyListGraph::getFirstVertex() 
{
	return adjList.begin()->first;
}

weight_t AdjacencyListGraph::weightAt(node_id_t i, node_id_t j, bool nonInf) 
{
	vertex_linkage_t links = adjList[i];

	if (!links.count(j))
		if (!nonInf) return 0;
		else return INFINITY;
	else return links[j];
};

void AdjacencyListGraph::addEdge(node_id_t i, node_id_t j, weight_t weight) 
{
	this->adjList[i][j] = weight;
}

void AdjacencyListGraph::removeEdge(node_id_t i, node_id_t j) 
{
	this->adjList[i].erase(j);
}

void AdjacencyListGraph::enqueueNeighboursOf(node_id_t i, traverse_queue_t& queue) 
{
	for (const auto& link : adjList[i])
		queue.push(link);
}

vertex_linkage_t AdjacencyListGraph::adjacentTo(node_id_t i) 
{	
	return this->adjList[i];
}

void AdjacencyListGraph::print() 
{
	for (const auto& node : adjList) 
	{
		cout << node.first << ": ";
		for (const auto& link : node.second) 
		{
			cout << link.first << " (" << link.second << ") ";
		}
		cout << endl;
	}
}

void AdjacencyListGraph::randomGenerate() 
{
	random_device rd;
	default_random_engine e(rd());
	uniform_real_distribution<> weight_dis(WEIGHT_LOWER_RANGE, WEIGHT_UPPER_RANGE);
	uniform_int_distribution<> node_dis(0, verticesNum);
	uniform_int_distribution<> edges_num_dis(0, verticesNum * verticesNum);

	for (int i = 0; i < edges_num_dis(e); ++i) 
	{
		node_id_t a = node_dis(e);
		node_id_t b = node_dis(e);
		node_id_t w = weight_dis(e);
		this->adjList[a][b] = w;
		if (directionality == Bidirectional)
			this->adjList[b][a] = w;
	}
}

AdjacencyMatrixGraph* AdjacencyListGraph::toAdjMatrix() 
{
	auto graph = new AdjacencyMatrixGraph(verticesNum);
	for (const auto& node : adjList)
		for (const auto& link : node.second)
			graph->addEdge(node.first, link.first, link.second);

	return graph;
}

Graph* GraphFactory::newGraph(const graph_type_t graphType, node_id_t nodesNum) 
{
	if (graphType == CREATE_ADJACENT_MATRIX) return new AdjacencyMatrixGraph(nodesNum);
	else return new AdjacencyListGraph(nodesNum);
}

void GraphFactory::generateGraphDate(Graph *graph, const graph_generation_type_t generationType) 
{
	if (generationType == CREATE_ADJACENT_MATRIX) graph->randomGenerate();
	else graph->userInputs();
}

Graph* GraphFactory::alternateGraphType(const graph_type_t graphType, Graph* graph) 
{
	Graph* newGraph;

	if (graphType == CREATE_ADJACENT_MATRIX) newGraph = graph->toAdjList();
	else newGraph = graph->toAdjMatrix();

	newGraph->setDirectionality(graph->getDirectionality());

	return newGraph;
}

void GraphFactory::printWeightMatrix(weight_t** weights, const node_id_t size) 
{
	for (int i = 0; i < size; ++i) 
	{
		cout << i << ": ";
		for (int j = 0; j < size; ++j) 
		{
			cout << weights[i][j] << "\t";
		}
		cout << endl;
	}
}
