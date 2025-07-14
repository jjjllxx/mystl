#pragma once

#include "Tree.h"
#include "DS/Vector.h"

namespace dsa
{
namespace BST
{
    bool is_bst(const dsa::TreeNode* root);

    dsa::TreeNode* find(dsa::TreeNode* root,
                        const int      val);
    dsa::TreeNode* insert(dsa::TreeNode* root,
                          const int      val);
    dsa::TreeNode* delete_val(dsa::TreeNode* root,
                              const int      val);

    void insert_bst(dsa::TreeNode* root,
                    dsa::TreeNode* node);

    int min(const dsa::TreeNode* root);
    int max(const dsa::TreeNode* root);
    dsa::TreeNode* successor(dsa::TreeNode* root,
                             const int      val);

    std::size_t count(const dsa::TreeNode* root);
    std::size_t height(const dsa::TreeNode* root);

    dsa::Vector<int> sort(const dsa::TreeNode* root);
} // namespace BST
} // namespace dsa
