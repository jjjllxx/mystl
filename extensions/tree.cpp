#include "tree.h"
#include "mystl/queue.h"

ext::tree_node::tree_node(const int val) :
    val(val),
    left(nullptr),
    right(nullptr)
{
}

void ext::tree::preorder(const tree_node* node,
                         mystl::vector<int>&    orders)
{
    if (node != nullptr)
    {
        orders.push_back(node->val);
        preorder(node->left, orders);
        preorder(node->right, orders);
    }
}

void ext::tree::inorder(const tree_node* node,
                        mystl::vector<int>&    orders)
{
    if (node != nullptr)
    {
        inorder(node->left, orders);
        orders.push_back(node->val);
        inorder(node->right, orders);
    }
}

void ext::tree::postorder(const tree_node* node,
                          mystl::vector<int>&    orders)
{
    if (node != nullptr)
    {
        postorder(node->left, orders);
        postorder(node->right, orders);
        orders.push_back(node->val);
    }
}

ext::tree_node* ext::tree::insert_left(tree_node* node,
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
        node->left = new tree_node(val);
    }

    return node->left;
}

ext::tree_node* ext::tree::insert_right(tree_node* node,
                                       const int val)
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
        node->right = new tree_node(val);
    }

    return node->right;
}

mystl::vector<mystl::vector<int>> ext::tree::layerorder(const tree_node* node)
{
    mystl::vector<mystl::vector<int>>    res;
    mystl::queue<const tree_node*> q;
    q.push(node);

    while (q.empty() == false)
    {
        mystl::size_t      sz = q.size();
        mystl::vector<int> cur_layer;
        cur_layer.reserve(sz);

        while (sz--)
        {
            const tree_node* cur = q.front();
            q.pop();
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

void ext::tree::clear_tree(tree_node* root)
{
    if (root != nullptr)
    {
        clear_tree(root->left);
        clear_tree(root->right);

        delete root;   
    }
}