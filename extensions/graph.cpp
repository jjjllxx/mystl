#include "graph.h"
#include "extensions/union_find.h"
#include "mystl/functional.h"
#include "mystl/priority_queue.h"
#include "mystl/queue.h"
#include "mystl/stack.h"
#include "mystl/vector.h"
#include <climits>

mystl::vector<mystl::vector<int>> ext::graph::adjacency_list_to_matrix(const mystl::size_t                      nodeCnt,
                                                                       const mystl::vector<mystl::vector<int>>& adjList,
                                                                       const bool                               hasWeight,
                                                                       const bool                               hasDirection)
{
    mystl::vector<mystl::vector<int>> adjMatrix(nodeCnt, mystl::vector<int>(nodeCnt, 0));

    for (const mystl::vector<int>& edge : adjList)
    {
        const int val               = hasWeight == true ? edge[2] : 1;
        adjMatrix[edge[0]][edge[1]] = val;
        if (hasDirection == false)
        {
            adjMatrix[edge[1]][edge[0]] = val;
        }
    }

    return adjMatrix;
}

mystl::vector<mystl::vector<int>> ext::graph::adjacency_matrix_to_list(const mystl::vector<mystl::vector<int>>& adjMatrix,
                                                                       const bool                               hasWeight,
                                                                       const bool                               hasDirection)
{
    mystl::vector<mystl::vector<int>> adjList;

    if (hasDirection == true)
    {
        for (int i = 0; i < static_cast<int>(adjMatrix.size()); ++i)
        {
            for (int j = 0; j < static_cast<int>(adjMatrix[0].size()); ++j)
            {
                hasWeight == true
                    ? adjList.push_back({ i, j, adjMatrix[i][j] })
                    : adjList.push_back({ i, j });
            }
        }
    }
    else
    {
        for (int i = 0; i < static_cast<int>(adjMatrix.size()); ++i)
        {
            for (int j = 0; j < i; ++j)
            {
                hasWeight == true
                    ? adjList.push_back({ i, j, adjMatrix[i][j] })
                    : adjList.push_back({ i, j });
            }
        }
    }

    return adjList;
}

void ext::graph::dfs_adjacency_list_recursive(const int                                node,
                                              const mystl::vector<mystl::vector<int>>& adjList,
                                              mystl::vector<bool>&                     visited)
{
    visited[node] = true;

    for (const int nxt : adjList[node])
    {
        if (visited[nxt] == false)
        {
            dfs_adjacency_list_recursive(nxt, adjList, visited);
        }
    }
}

void ext::graph::dfs_adjacency_list_iterative(const int                                node,
                                              const mystl::vector<mystl::vector<int>>& adjList)
{
    mystl::vector<bool> visited(adjList.size(), false);
    mystl::stack<int>   stk;
    stk.push(node);
    visited[node] = true;

    while (stk.empty() == false)
    {
        const int cur = stk.top();
        stk.pop();
        for (const int nxt : adjList[cur])
        {
            if (visited[nxt] == false)
            {
                stk.push(nxt);
                visited[nxt] = true;
            }
        }
    }
}

void ext::graph::dfs_adjacency_matrix_recursive(const int                                node,
                                                const mystl::vector<mystl::vector<int>>& adjMatrix,
                                                mystl::vector<bool>&                     visited)
{
    visited[node] = true;

    for (mystl::size_t i = 0; i < adjMatrix[node].size(); ++i)
    {
        if (adjMatrix[node][i] != 0 && visited[i] == false)
        {
            dfs_adjacency_matrix_recursive(i, adjMatrix, visited);
        }
    }
}

void ext::graph::dfs_adjacency_matrix_iterative(const int                                node,
                                                const mystl::vector<mystl::vector<int>>& adjMatrix)
{
    mystl::vector<bool> visited(adjMatrix.size(), false);
    mystl::stack<int>   stk;

    stk.push(node);
    visited[node] = true;

    while (stk.empty() == false)
    {
        const int cur = stk.top();
        stk.pop();

        for (mystl::size_t i = 0; i < adjMatrix[cur].size(); ++i)
        {
            if (adjMatrix[cur][i] != 0 && visited[i] == false)
            {
                stk.push(i);
                visited[i] = true;
            }
        }
    }
}

void ext::graph::bfs_adjacency_list(const int                                node,
                                    const mystl::vector<mystl::vector<int>>& adjList)
{
    mystl::vector<bool> visited(adjList.size(), false);
    mystl::queue<int>   q;
    q.push(node);
    visited[node] = true;
    while (q.empty() == false)
    {
        const int cur = q.front();
        for (const int nxt : adjList[cur])
        {
            if (visited[nxt] == false)
            {
                q.push(nxt);
                visited[nxt] = true;
            }
        }
    }
}

void ext::graph::bfs_adjacency_matrix(const int                                node,
                                      const mystl::vector<mystl::vector<int>>& adjMatrix)
{
    mystl::vector<bool> visited(adjMatrix.size(), false);
    mystl::queue<int>   q;
    q.push(node);
    visited[node] = true;
    while (q.empty() == false)
    {
        const int cur = q.front();
        for (mystl::size_t i = 0; i < adjMatrix[cur].size(); ++i)
        {
            if (adjMatrix[cur][i] != 0 && visited[i] == false)
            {
                q.push(i);
                visited[i] = true;
            }
        }
    }
}

mystl::vector<int> ext::graph::dijkstra(const int                                node,
                                        const mystl::vector<mystl::vector<int>>& adjMatrix)
{
    mystl::vector<int> dist(adjMatrix.size(), INT_MAX);

    mystl::priority_queue<mystl::vector<int>, mystl::vector<mystl::vector<int>>, mystl::greater<mystl::vector<int>>> pq;
    pq.push({ 0, node });
    dist[node] = 0;

    while (pq.empty() == false)
    {
        const int cur = pq.top()[1];
        pq.pop();

        for (mystl::size_t nxt = 0; nxt < adjMatrix[cur].size(); ++nxt)
        {
            if (adjMatrix[cur][nxt] != 0)
            {
                if (adjMatrix[cur][nxt] + dist[cur] < dist[nxt])
                {
                    dist[nxt] = adjMatrix[cur][nxt] + dist[cur];
                    pq.push({ dist[nxt], static_cast<int>(nxt) });
                }
            }
        }
    }

    return dist;
}

mystl::vector<mystl::vector<int>> ext::graph::mst_kruskal(const mystl::vector<mystl::vector<int>>& adjMatrix)
{
    const int n = adjMatrix.size();

    ext::union_find uf { adjMatrix.size() };

    mystl::priority_queue<mystl::vector<int>, mystl::vector<mystl::vector<int>>, mystl::greater<mystl::vector<int>>> pq;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (adjMatrix[i][j] != 0)
            {
                pq.push({ adjMatrix[i][j], j, i });
            }
        }
    }

    mystl::vector<mystl::vector<int>> mst;
    mst.reserve(n - 1);
    while (pq.empty() == false)
    {
        const mystl::vector<int> edge = pq.top();
        pq.pop();
        if (uf.find(edge[1]) != uf.find(edge[2]))
        {
            uf.unite(edge[1], edge[2]);
            mst.push_back({ edge[1], edge[2], edge[0] });

            if (static_cast<int>(mst.size()) == n - 1)
            {
                break;
            }
        }
    }

    return mst;
}

int ext::graph::mst_prim(const mystl::vector<mystl::vector<int>>& adjMatrix)
{
    mystl::vector<bool> visited(adjMatrix.size(), false);

    mystl::priority_queue<mystl::vector<int>, mystl::vector<mystl::vector<int>>, mystl::greater<mystl::vector<int>>> pq;
    pq.push({ 0, 0 });
    int cost = 0;

    while (pq.empty() == false)
    {
        const mystl::vector<int> vex = pq.top();
        pq.pop();
        if (visited[vex[1]] == true)
        {
            continue;
        }
        visited[vex[1]] = true;
        cost += vex[0];

        for (mystl::size_t i = 0; i < adjMatrix[vex[1]].size(); ++i)
        {
            if (adjMatrix[vex[1]][i] != 0 && visited[i] == false)
            {
                pq.push({ adjMatrix[vex[1]][i], static_cast<int>(i) });
            }
        }
    }

    return cost;
}