#include "binary_search_tree.h"
#include "extensions/tree.h"

bool ext::bst::is_bst(const ext::tree_node* root)
{
    if (root == nullptr)
    {
        return true;
    }

    if (root->left != nullptr && root->left->val >= root->val)
    {
        return false;
    }

    if (root->right != nullptr && root->right->val <= root->val)
    {
        return false;
    }

    return ext::bst::is_bst(root->left) && ext::bst::is_bst(root->right);
}

ext::tree_node* ext::bst::find(ext::tree_node* root,
                               const int       val)
{
    if (root == nullptr || root->val == val)
    {
        return root;
    }

    if (root->val > val)
    {
        return ext::bst::find(root->left, val);
    }

    return ext::bst::find(root->right, val);
}

ext::tree_node* ext::bst::insert(ext::tree_node* root,
                                 const int       val)
{
    if (root == nullptr)
    {
        root = new ext::tree_node { val };

        return root;
    }

    if (val < root->val)
    {
        root->left = ext::bst::insert(root->left, val);
    }
    else if (val > root->val)
    {
        root->right = ext::bst::insert(root->right, val);
    }

    return root;
}

ext::tree_node* ext::bst::delete_(ext::tree_node* root,
                                  const int       val)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    if (root->val == val)
    {
        if (root->left == nullptr && root->right == nullptr)
        {
            delete root;
            return nullptr;
        }

        if (root->right == nullptr)
        {
            ext::tree_node* left = root->left;
            delete root;
            return left;
        }

        if (root->left == nullptr)
        {
            ext::tree_node* right = root->right;
            delete root;
            return right;
        }

        ext::tree_node* tmp = root->right;
        while (tmp->left != nullptr)
        {
            tmp = tmp->left;
        }

        int tmpVal  = tmp->val;
        root->right = ext::bst::delete_(root->right, tmp->val);
        root->val   = tmpVal;

        return root;
    }

    val > root->val
        ? root->right = ext::bst::delete_(root->right, val)
        : root->left  = ext::bst::delete_(root->left, val);

    return root;
}

int ext::bst::min(const ext::tree_node* root)
{
    if (root == nullptr)
    {
        throw std::invalid_argument("bst::min: input root is nullptr");
    }

    while (root->left != nullptr)
    {
        root = root->left;
    }

    return root->val;
}

int ext::bst::max(const ext::tree_node* root)
{
    if (root == nullptr)
    {
        throw std::invalid_argument("bst::max: input root is nullptr");
    }

    while (root->right != nullptr)
    {
        root = root->right;
    }

    return root->val;
}

int ext::bst::height(const ext::tree_node* root)
{
    if (root == nullptr)
    {
        return -1;
    }

    return 1 + mystl::max(ext::bst::height(root->left), ext::bst::height(root->right));
}

ext::tree_node* ext::bst::successor(ext::tree_node* root,
                                    const int       val)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    if (root->val <= val)
    {
        return ext::bst::successor(root->right, val);
    }

    ext::tree_node* right = ext::bst::successor(root->left, val);

    return right == nullptr ? root : right;
}

mystl::size_t ext::bst::count(const ext::tree_node* root)
{
    if (root == nullptr)
    {
        return 0;
    }

    return 1 + ext::bst::count(root->left) + ext::bst::count(root->right);
}

mystl::vector<int> ext::bst::sort(const ext::tree_node* root)
{
    mystl::vector<int> orders;
    ext::tree::inorder(root, orders);
    return orders;
}