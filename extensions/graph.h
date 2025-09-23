#pragma once

#include "mystl/vector.h"

namespace ext
{
namespace graph
{
    mystl::vector<mystl::vector<int>> adjacency_list_to_matrix(const mystl::size_t                      nodeCnt,
                                                               const mystl::vector<mystl::vector<int>>& adjList,
                                                               const bool                               hasWeight    = false,
                                                               const bool                               hasDirection = false);

    mystl::vector<mystl::vector<int>> adjacency_matrix_to_list(const mystl::vector<mystl::vector<int>>& adjMatrix,
                                                               const bool                               hasWeight    = false,
                                                               const bool                               hasDirection = false);

    void dfs_adjacency_list_recursive(const int                                node,
                                      const mystl::vector<mystl::vector<int>>& adjList,
                                      mystl::vector<bool>&                     visited);

    void dfs_adjacency_list_iterative(const int                                node,
                                      const mystl::vector<mystl::vector<int>>& adjList);

    void dfs_adjacency_matrix_recursive(const int                                node,
                                        const mystl::vector<mystl::vector<int>>& adjMatrix,
                                        mystl::vector<bool>&                     visited);

    void dfs_adjacency_matrix_iterative(const int                                node,
                                        const mystl::vector<mystl::vector<int>>& adjMatrix);

    void bfs_adjacency_list(const int                                node,
                            const mystl::vector<mystl::vector<int>>& adjList);
    void bfs_adjacency_matrix(const int                                node,
                              const mystl::vector<mystl::vector<int>>& adjMatrix);

    mystl::vector<int> dijkstra(const int                                node,
                                const mystl::vector<mystl::vector<int>>& adjMatrix);

    // Minimun Spanning tree
    mystl::vector<mystl::vector<int>> mst_kruskal(const mystl::vector<mystl::vector<int>>& adjMatrix);
    int                               mst_prim(const mystl::vector<mystl::vector<int>>& adjMatrix);

} // namespace graph
} // namespace ext
