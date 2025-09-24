#include "mystl/vector.h"
#include "extensions/graph.h"

#include "gtest/gtest.h"

namespace ext_test
{
namespace graph
{
    const mystl::vector<mystl::vector<int>> ADJ_MATRIX = {
        { 0, 4, 4, 0, 0, 0 },
        { 4, 0, 2, 5, 0, 0 },
        { 4, 2, 0, 5, 11, 0 },
        { 0, 5, 5, 0, 2, 1 },
        { 0, 0, 11, 2, 0, 1 },
        { 0, 0, 0, 1, 1, 0 }
    };
}
} // namespace ext_test

GTEST_TEST(ext_graph, dijkstra)
{
    const int src = 0;

    const mystl::vector<mystl::vector<int>> adjMatrix = ext::graph::adjacency_list_to_matrix(5, { { 0, 1, 4 }, { 0, 2, 8 }, { 1, 4, 6 }, { 2, 3, 2 }, { 3, 4, 10 } }, true);

    const mystl::vector<int> dist = ext::graph::dijkstra(src, adjMatrix);
    const mystl::vector<int> res  = { 0, 4, 8, 10, 10 };
    EXPECT_EQ(dist.size(), res.size());
    EXPECT_TRUE(mystl::equal(dist.begin(), dist.end(), res.begin()));
}


GTEST_TEST(ext_graph, mst_kruskal)
{
    const mystl::vector<mystl::vector<int>> res = ext::graph::mst_kruskal(ext_test::graph::ADJ_MATRIX);
    EXPECT_EQ(res.size(), ext_test::graph::ADJ_MATRIX.size() - 1);
    int cost = 0;
    for (const mystl::vector<int>& edge : res)
    {
        cost += edge[2];
    }

    EXPECT_EQ(cost, 13);
}

GTEST_TEST(ext_graph, mst_prim)
{
    EXPECT_EQ(ext::graph::mst_prim(ext_test::graph::ADJ_MATRIX), 13);
}