#include "algorithms.h"

using namespace std;

vector<node_id_t> bfs(Graph* graph, node_id_t startVertex) 
{
    vector<node_id_t> traverse;

    traverse_queue_t queue;
    map<node_id_t, bool> visited;
    queue.push(make_pair(startVertex, 0));

    while(!queue.empty()) 
    {
        edge_t v = queue.front();
        queue.pop();

        if (visited[v.first] || !visited.count(v.first)) continue;
        visited[v.first] = true;

        traverse.push_back(v.first);

        graph->enqueueNeighboursOf(v.first, queue);
    }

    return traverse;
}

bool checkAcyclic(Graph* graph) 
{
    traverse_queue_t queue;
    map<node_id_t, bool> visited;
    queue.push(make_pair(graph->getFirstVertex(), 0));

    while(!queue.empty()) 
    {
        edge_t v = queue.front();
        queue.pop();

        if (visited[v.first] || !visited.count(v.first))
            return false;
        visited[v.first] = true;

        graph->enqueueNeighboursOf(v.first, queue);
    }

    return true;
}


weight_t** FloydWarshallAlgorithm(Graph* graph) 
{
    auto weights = new weight_t* [graph->getVerticesNum()];

    for (node_id_t i = 0; i < graph->getVerticesNum(); i++) 
    {
        weights[i] = new weight_t[graph->getVerticesNum()];
        for (node_id_t j = 0; j < graph->getVerticesNum(); j++)
        {
            weights[i][j] = graph->weightAt(i, j);
        }       
    }

    for (node_id_t k = 0; k < graph->getVerticesNum(); k++)
        for (node_id_t i = 0; i < graph->getVerticesNum(); i++)
            for (node_id_t j = 0; j < graph->getVerticesNum(); j++) 
            {
                if ((weights[i][j] > (weights[i][k] + weights[k][j])) && (weights[k][j] != INFINITY && weights[i][k] != INFINITY))
                {
                    weights[i][j] = weights[i][k] + weights[k][j];
                }
            }

    return weights;
};

vector<node_id_t> bfsTopologicalSort(Graph* graph) 
{
    vector<node_id_t> sorted;
    queue<node_id_t> queue;
    vector<node_id_t> indegree(graph->getVerticesNum(), 0);

    for (node_id_t i = 0; i < graph->getVerticesNum(); i++)
        for (auto it : graph->adjacentTo(i))
            indegree[it.first]++;

    for (node_id_t i = 0; i < graph->getVerticesNum(); i++)
        if (indegree[i] == 0)
            queue.push(i);

    while (!queue.empty()) 
    {
        node_id_t node = queue.front();
        queue.pop();
        sorted.push_back(node);

        for (auto it : graph->adjacentTo(node)) 
        {
            indegree[it.first]--;
            if (indegree[it.first] == 0)
                queue.push(it.first);
        }
    }

    return sorted;
}

Graph* bfsSpanningTree(Graph* graph, node_id_t startVertex, graph_type_t newGraphType) 
{
    weight_t sumWeight = 0;

    Graph* tree = GraphFactory::newGraph(newGraphType, graph->getVerticesNum());

    // queue holds <outcome node, income node> pairs
    queue<edge_with_source_t> queue;
    map<node_id_t, bool> visited;
    queue.push(make_tuple(0, startVertex, 0));

    while(!queue.empty()) 
    {
        edge_with_source_t edge = queue.front();
        queue.pop();

        if (visited[std::get<1>(edge)] || !visited.count(std::get<1>(edge))) continue;

        visited[std::get<1>(edge)] = true;

        if (std::get<1>(edge) != startVertex) 
        {
            tree->addEdge(get<0>(edge), get<1>(edge), get<2>(edge));
            sumWeight += std::get<2>(edge);
        }

        for (auto adj : graph->adjacentTo(get<1>(edge))) 
        {
            queue.push(std::make_tuple(
                // node, adjacent, edge weight
                get<1>(edge), adj.first,
                // replace inf with 0
                adj.second == INFINITY ? 0 : adj.second));
        }
    }

    cout << " Sum weight: " << sumWeight << endl;

    return tree;
}

int minKey(vector<int> key, vector<bool> set) 
{
    int min = INT_MAX, minIndex;

    for (int v = 0; v < key.size(); ++v) 
    {
        if (set[v] == false && key[v] < min) 
        {
            min = key[v]; 
            minIndex = v;
        }
    }

    return minIndex;
}

Graph* PrimAlgorithm(Graph* graph, graph_type_t newGraphType) {

    node_id_t graphSize = graph->getVerticesNum();

    weight_t sumWeight = 0;

    Graph* tree = GraphFactory::newGraph(newGraphType, graphSize);

    vector<int>key(graphSize, 0);
    vector<int>parent(graphSize, 0);
    vector<bool>mstSet(graphSize, 0);

    for (node_id_t i = 0; i < graphSize; ++i) 
    {
        key[i] = INT_MAX; 
        mstSet[i] = false;
    }

    key[0] = 0;
    key[0] = -1;

    for (node_id_t count = 0; count < graphSize - 1; ++count) 
    {
        int u = minKey(key, mstSet);
        mstSet[u] = true;

        for (node_id_t v = 0; v < graphSize; ++v) 
        {
            weight_t uv = graph->weightAt(u, v, true);

            if (uv && mstSet[v] == false && uv < key[v]) 
            {
                parent[v] = u;
                key[v] = uv;
            }
        }
    }

    for (node_id_t i = 1; i < graphSize; ++i) 
    {
        weight_t edgeWeight = graph->weightAt(i, parent[i], true);
        sumWeight += edgeWeight;
        tree->addBidirectEdge(parent[i], i, edgeWeight);
    }

    cout << " Sum weight: " << sumWeight << endl;

    return tree;
}
