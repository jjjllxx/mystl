#pragma once

#include "mystl/vector.h"
#include "tree.h"

namespace ext
{
namespace bst
{
    bool is_bst(const ext::tree_node* root);

    ext::tree_node* find(ext::tree_node* root,
                         const int       val);
    ext::tree_node* insert(ext::tree_node* root,
                           const int       val);
    ext::tree_node* delete_(ext::tree_node* root,
                                const int       val);

    int min(const ext::tree_node* root);
    int max(const ext::tree_node* root);
    int height(const ext::tree_node* root);

    ext::tree_node* successor(ext::tree_node* root,
                              const int       val);

    mystl::size_t count(const ext::tree_node* root);

    mystl::vector<int> sort(const ext::tree_node* root);
} // namespace bst
} // namespace ext
