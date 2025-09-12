#include "avl_tree.h"
#include "mystl/algorithm.h"
#include <iostream>
#include <cstdlib>

bool ext::avl::is_avl_tree(const ext::avl_node* root)
{
    if (root == nullptr)
    {
        return true;
    }

    if (abs(ext::avl::calc_balance_factor(root)) > 1)
    {
        std::cout << "The tree is not balance\n" << root->val << "\n";
        return false;
    }

    if (root->left != nullptr && root->val <= root->left->val)
    {
        return false;
    }

    if (root->right != nullptr && root->val >= root->right->val)
    {
        return false;
    }

    return ext::avl::is_avl_tree(root->left) && ext::avl::is_avl_tree(root->right);
}

int ext::avl::get_height(const ext::avl_node* node)
{
    return node == nullptr ? -1 : node->height;
}

void ext::avl::update_height(ext::avl_node* node)
{
    if (node != nullptr)
    {
        node->height = mystl::max(ext::avl::get_height(node->left), ext::avl::get_height(node->right)) + 1;
    }
}

int ext::avl::calc_balance_factor(const ext::avl_node* root)
{
    if (root == nullptr)
    {
        return 0;
    }

    return ext::avl::get_height(root->left) - ext::avl::get_height(root->right);
}

int ext::avl::update_tree_height(ext::avl_node* root)
{
    if (root == nullptr)
    {
        return -1;
    }

    root->height = mystl::max(ext::avl::update_tree_height(root->left), ext::avl::update_tree_height(root->right)) + 1;

    return root->height;
}

ext::avl_node* ext::avl::rotate_left(ext::avl_node* node)
{
    if (node == nullptr || node->right == nullptr)
    {
        return node;
    }

    ext::avl_node* right = node->right;

    node->right = right->left;
    right->left = node;

    ext::avl::update_height(node);
    ext::avl::update_height(right);

    return right;
}

ext::avl_node* ext::avl::rotate_right(ext::avl_node* node)
{
    if (node == nullptr || node->left == nullptr)
    {
        return node;
    }

    ext::avl_node* left = node->left;

    node->left  = left->right;
    left->right = node;

    ext::avl::update_height(node);
    ext::avl::update_height(left);

    return left;
}

ext::avl_node* ext::avl::balance(ext::avl_node* node)
{
    const int bf = ext::avl::calc_balance_factor(node);

    if (bf > 1 && ext::avl::calc_balance_factor(node->left) >= 0) // LL
    {
        return ext::avl::rotate_right(node);
    }

    if (bf < -1 && ext::avl::calc_balance_factor(node->right) <= 0) // RR
    {
        return ext::avl::rotate_left(node);
    }

    if (bf > 1 && ext::avl::calc_balance_factor(node->left) < 0) // LR
    {
        node->left = ext::avl::rotate_left(node->left);
        return ext::avl::rotate_right(node);
    }

    if (bf < -1 && ext::avl::calc_balance_factor(node->right) > 0) // RL
    {
        node->right = ext::avl::rotate_right(node->right);
        return ext::avl::rotate_left(node);
    }

    return node;
}

ext::avl_node* ext::avl::find(ext::avl_node* root,
                              const int      val)
{
    if (root == nullptr || root->val == val)
    {
        return root;
    }

    if (root->val > val)
    {
        return ext::avl::find(root->left, val);
    }

    return ext::avl::find(root->right, val);
}

ext::avl_node* ext::avl::insert(ext::avl_node* root,
                                const int      val)
{
    if (root == nullptr)
    {
        return new ext::avl_node { val };
    }

    if (val == root->val)
    {
        return root;
    }

    val > root->val
        ? root->right = ext::avl::insert(root->right, val)
        : root->left  = ext::avl::insert(root->left, val);

    ext::avl::update_height(root);
    root = ext::avl::balance(root);

    return root;
}

ext::avl_node* ext::avl::delete_(ext::avl_node* root,
                                 const int      val)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    if (val < root->val)
    {
        root->left = ext::avl::delete_(root->left, val);
    }
    else if (val > root->val)
    {
        root->right = ext::avl::delete_(root->right, val);
    }
    else
    {
        if (root->left == nullptr && root->right == nullptr)
        {
            delete root;
            return nullptr;
        }

        if (root->left == nullptr)
        {
            ext::avl_node* right = root->right;
            delete root;
            root = right;
        }
        else if (root->right == nullptr)
        {
            ext::avl_node* left = root->left;
            delete root;
            root = left;
        }
        else
        {
            ext::avl_node* tmp = root->right;
            while (tmp->left != nullptr)
            {
                tmp = tmp->left;
            }

            int tmpVal = tmp->val;
            root->right = ext::avl::delete_(root->right, tmp->val);
            root->val = tmpVal;
        }
    }

    ext::avl::update_height(root);
    root = ext::avl::balance(root);

    return root;
}

void ext::avl::clear(ext::avl_node* root)
{
    if (root != nullptr)
    {
        ext::avl::clear(root->left);
        ext::avl::clear(root->right);

        delete root;
    }
}
