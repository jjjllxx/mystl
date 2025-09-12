#pragma once

namespace ext
{
struct avl_node
{
    int       val;
    int       height;
    avl_node* left;
    avl_node* right;

    avl_node(const int val) :
        val(val),
        height(0),
        left(nullptr),
        right(nullptr)
    {
    }
};

namespace avl
{
    bool is_avl_tree(const ext::avl_node* root);
    int  get_height(const ext::avl_node* node);
    void update_height(ext::avl_node* node);
    int  update_tree_height(ext::avl_node* root);
    int  calc_balance_factor(const ext::avl_node* node);

    ext::avl_node* rotate_left(ext::avl_node* node);
    ext::avl_node* rotate_right(ext::avl_node* node);
    ext::avl_node* balance(ext::avl_node* node);

    ext::avl_node* find(ext::avl_node* root,
                        const int      val);
    ext::avl_node* insert(ext::avl_node* root,
                          const int      val);
    ext::avl_node* delete_(ext::avl_node* root,
                           const int      val);

    void clear(ext::avl_node* root);
} // namespace avl
} // namespace ext