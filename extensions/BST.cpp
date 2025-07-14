#include "BST.h"
#include "Tree.h"

bool dsa::BST::is_bst(const dsa::TreeNode* root)
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

    return dsa::BST::is_bst(root->left) && dsa::BST::is_bst(root->right);
}

dsa::TreeNode* dsa::BST::find(dsa::TreeNode* root,
                              const int      val)
{
    if (root == nullptr || root->val == val)
    {
        return root;
    }

    if (root->val > val)
    {
        return dsa::BST::find(root->left, val);
    }

    return dsa::BST::find(root->right, val);
}

dsa::TreeNode* dsa::BST::insert(dsa::TreeNode* root,
                                const int      val)
{
    if (root == nullptr)
    {
        root = new dsa::TreeNode { val };

        return root;
    }

    if (root->val == val)
    {
        return nullptr;
    }

    if (root->val > val)
    {
        if (root->left == nullptr)
        {
            root->left = new dsa::TreeNode { val };

            return root->left;
        }

        return dsa::BST::insert(root->left, val);
    }

    if (root->right == nullptr)
    {
        root->right = new dsa::TreeNode { val };

        return root->right;
    }

    return dsa::BST::insert(root->right, val);
}

dsa::TreeNode* dsa::BST::delete_val(dsa::TreeNode* root,
                                    const int      val)
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
            dsa::TreeNode* left = root->left;
            delete root;
            return left;
        }

        if (root->left == nullptr)
        {
            dsa::TreeNode* right = root->right;
            delete root;
            return right;
        }

        dsa::TreeNode* maxNodeInLeft = root->left;

        if (maxNodeInLeft->right == nullptr)
        {
            root->val  = maxNodeInLeft->val;
            root->left = maxNodeInLeft->left;
        }
        else
        {
            dsa::TreeNode* pre = nullptr;
            while (maxNodeInLeft->right != nullptr)
            {
                pre           = maxNodeInLeft;
                maxNodeInLeft = maxNodeInLeft->right;
            }

            pre->right = maxNodeInLeft->left;
            root->val  = maxNodeInLeft->val;
        }

        delete maxNodeInLeft;

        return root;
    }

    if (root->val > val)
    {
        root->left = dsa::BST::delete_val(root->left, val);
    }
    else
    {
        root->right = dsa::BST::delete_val(root->right, val);
    }

    return root;
}

void dsa::BST::insert_bst(dsa::TreeNode* root,
                          dsa::TreeNode* node)
{
    if (root == nullptr)
    {
        throw std::invalid_argument("BST::insert_node: input root is nullptr");
    }

    if (node->val == root->val)
    {
        return;
    }

    if (node->val < root->val)
    {
        if (root->left == nullptr)
        {
            root->left = node;
            return;
        }

        return dsa::BST::insert_bst(root->left, node);
    }

    if (root->right == nullptr)
    {
        root->right = node;
    }

    dsa::BST::insert_bst(root->right, node);
}

int dsa::BST::min(const dsa::TreeNode* root)
{
    if (root == nullptr)
    {
        throw std::invalid_argument("BST::min: input root is nullptr");
    }

    while (root->left != nullptr)
    {
        root = root->left;
    }

    return root->val;
}

int dsa::BST::max(const dsa::TreeNode* root)
{
    if (root == nullptr)
    {
        throw std::invalid_argument("BST::max: input root is nullptr");
    }

    while (root->right != nullptr)
    {
        root = root->right;
    }

    return root->val;
}

dsa::TreeNode* dsa::BST::successor(dsa::TreeNode* root,
                                   const int      val)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    if (root->val <= val)
    {
        return dsa::BST::successor(root->right, val);
    }

    dsa::TreeNode* right = dsa::BST::successor(root->left, val);

    return right == nullptr ? root : right;
}

std::size_t dsa::BST::count(const dsa::TreeNode* root)
{
    if (root == nullptr)
    {
        return 0;
    }

    return 1 + dsa::BST::count(root->left) + dsa::BST::count(root->right);
}

std::size_t dsa::BST::height(const dsa::TreeNode* root)
{
    if (root == nullptr)
    {
        return 0;
    }

    return 1 + dsa::max(dsa::BST::height(root->left), dsa::BST::height(root->right));
}

dsa::Vector<int> dsa::BST::sort(const dsa::TreeNode* root)
{
    dsa::Vector<int> orders;
    dsa::Tree::inorder(root, orders);
    return orders;
}