#include "Tree.h"
#include "Queue.h"
#include <cstddef>

dsa::TreeNode::TreeNode(const int val) :
    val(val),
    left(nullptr),
    right(nullptr)
{
}

void dsa::Tree::preorder(const dsa::TreeNode* node,
                         dsa::Vector<int>&    orders)
{
    if (node != nullptr)
    {
        orders.push_back(node->val);
        dsa::Tree::preorder(node->left, orders);
        dsa::Tree::preorder(node->right, orders);
    }
}

void dsa::Tree::inorder(const dsa::TreeNode* node,
                        dsa::Vector<int>&    orders)
{
    if (node != nullptr)
    {
        dsa::Tree::inorder(node->left, orders);
        orders.push_back(node->val);
        dsa::Tree::inorder(node->right, orders);
    }
}

void dsa::Tree::postorder(const dsa::TreeNode* node,
                          dsa::Vector<int>&    orders)
{
    if (node != nullptr)
    {
        dsa::Tree::postorder(node->left, orders);
        dsa::Tree::postorder(node->right, orders);
        orders.push_back(node->val);
    }
}

dsa::TreeNode* dsa::Tree::insert_left(dsa::TreeNode* node,
                                      const int      val)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    if (node->left != nullptr)
    {
        node->left->val = val;
    }
    else
    {
        node->left = new TreeNode(val);
    }

    return node->left;
}

dsa::TreeNode* dsa::Tree::insert_right(dsa::TreeNode* node,
                                       const int      val)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    if (node->right != nullptr)
    {
        node->right->val = val;
    }
    else
    {
        node->right = new TreeNode(val);
    }

    return node->right;
}

dsa::Vector<dsa::Vector<int>> dsa::Tree::layerorder(const dsa::TreeNode* node)
{
    dsa::Vector<dsa::Vector<int>>    res;
    dsa::Queue<const dsa::TreeNode*> q;
    q.push(node);

    while (q.empty() == false)
    {
        std::size_t      sz = q.size();
        dsa::Vector<int> cur_layer;
        cur_layer.reserve(sz);

        while (sz--)
        {
            const TreeNode* cur = q.pop();
            cur_layer.push_back(cur->val);

            if (cur->left != nullptr)
            {
                q.push(cur->left);
            }

            if (cur->right != nullptr)
            {
                q.push(cur->right);
            }
        }

        res.push_back(cur_layer);
    }

    return res;
}

void dsa::Tree::clear_tree(dsa::TreeNode* root)
{
    if (root != nullptr)
    {
        dsa::Tree::clear_tree(root->left);
        dsa::Tree::clear_tree(root->right);

        delete root;   
    }
}