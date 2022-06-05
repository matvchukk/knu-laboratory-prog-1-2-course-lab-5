// 1. ациклічність графу
// 2. bfs
// 3. алгоритм флойда
// 4. топологічне сортування на основі bfs
// 5. кістякове деерво на bfs
// 6. minimum span tree: reverse-delete

#pragma once

#include <iostream>
#include <queue>
#include <math.h>
#include <vector>
#include <tuple>
#include <limits.h>

#include "graph.h"

std::vector<node_id_t> bfs(Graph* graph, node_id_t startVertex);

bool checkAcyclic(Graph* graph);

weight_t** FloydWarshallAlgorithm(Graph* graph);

std::vector<node_id_t> bfsTopologicalSort(Graph* graph);

Graph* bfsSpanningTree(Graph*, node_id_t startVertex, graph_type_t);

Graph* PrimAlgorithm(Graph*, graph_type_t);
