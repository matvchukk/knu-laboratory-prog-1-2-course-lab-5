#pragma once

#include <iostream>
#include <math.h>
#include <memory>
#include <random>
#include <map>
#include <queue>

// could've possibly done it by enums
#define RANDOM_CREATE          1
#define CUSTOM_CREATE          2
#define CREATE_ADJACENT_MATRIX 1
#define CREATE_ADJACENT_LIST   2

#define WEIGHT_UPPER_RANGE 10
#define WEIGHT_LOWER_RANGE 0

typedef unsigned int   node_id_t;
typedef bool           adjacency_t;
typedef float          weight_t;

typedef int graph_type_t;
typedef int graph_generation_type_t;

enum GraphDirectionality { Monodirectional, Bidirectional };

class AdjacencyMatrixGraph;
class AdjacencyListGraph;

typedef std::map<node_id_t, weight_t>              vertex_linkage_t;
typedef std::map<node_id_t, vertex_linkage_t>      adj_list_t;
typedef std::pair<node_id_t, weight_t>             edge_t;
typedef std::tuple<node_id_t, node_id_t, weight_t> edge_with_source_t;
typedef std::queue<edge_t>                         traverse_queue_t;

class Graph {
protected:
	GraphDirectionality directionality;
	node_id_t           verticesNum;

public:

	Graph(node_id_t verticesNum = 0);
	virtual ~Graph() {};

	node_id_t getVerticesNum();
	node_id_t getFirstVertex() {return 0;};

	// if nonInf = false and i&j is not adjacent, returns INF. if nonInf = true,
	// returns 0
	virtual weight_t weightAt(node_id_t i, node_id_t j, bool nonInf = false)
		{return INFINITY;};

	virtual void addEdge           (node_id_t i, node_id_t j, weight_t weight) {};
	virtual void removeEdge        (node_id_t i, node_id_t j) {};
	void addBidirectEdge   (node_id_t i, node_id_t j, weight_t weight);
	void removeBidirectEdge(node_id_t i, node_id_t j);

	virtual void enqueueNeighboursOf(node_id_t i, traverse_queue_t& queue) {};
	virtual vertex_linkage_t adjacentTo(node_id_t i) = 0;

	virtual void print() {};

	virtual void randomGenerate() {};

	virtual AdjacencyListGraph* toAdjList() {return nullptr;};
	virtual AdjacencyMatrixGraph* toAdjMatrix() {return nullptr;};

	void setDirectionality(GraphDirectionality);
	GraphDirectionality getDirectionality();

	void userInputs();
};

class AdjacencyMatrixGraph : public Graph {
private:
	adjacency_t** adjacency;
	weight_t**    weights;

public:
	// matrix will be initialized to zero
	AdjacencyMatrixGraph(node_id_t verticesNum);

	weight_t weightAt(node_id_t i, node_id_t j, bool nonInf = false) override;

	void addEdge(node_id_t i, node_id_t j, weight_t weight) override;

	void removeEdge(node_id_t i, node_id_t j) override;

	void enqueueNeighboursOf(node_id_t i, traverse_queue_t& queue) override;

	vertex_linkage_t adjacentTo(node_id_t i) override;

	void print() override;

	void randomGenerate() override;

	AdjacencyListGraph* toAdjList() override;

	~AdjacencyMatrixGraph();
};

class AdjacencyListGraph : public Graph {
private:
	adj_list_t adjList;

public:
	AdjacencyListGraph(node_id_t verticesNum): Graph(verticesNum) {};
	
	node_id_t getFirstVertex();

	weight_t weightAt(node_id_t i, node_id_t j, bool nonInf = false) override;

	void addEdge(node_id_t i, node_id_t j, weight_t weight) override;

	void removeEdge(node_id_t i, node_id_t j) override;

	vertex_linkage_t adjacentTo(node_id_t i) override;

	void enqueueNeighboursOf(node_id_t i, traverse_queue_t& queue) override;

	void print() override;

	void randomGenerate() override;

	AdjacencyMatrixGraph* toAdjMatrix() override;
};

class GraphFactory {
public:
	static Graph* newGraph(const graph_type_t graphType, node_id_t nodesNum);

	static void generateGraphDate(Graph* graph, const graph_generation_type_t);

	static Graph* alternateGraphType(const graph_type_t graphType, Graph* graph);

	static void printWeightMatrix(weight_t**, const node_id_t);
};