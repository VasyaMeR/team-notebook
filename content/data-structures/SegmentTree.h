/**
 * Author: Dmytro Mayor
 * Date: 2022-09-09
 * License: CC0
 * Source: folklore
 * Description: Customizable segment tree
 * Time: update - O(\log N), get - O(\log N)
 * Status: -
 */

#include <SegmentTreeNode.h>

template<class T, T default_value, T (*merge_value)(const T&, const T&), void (*update_value)(T&, const T&)>
class Tree {
private:
    ll l, r;
    Node<T, default_value, merge_value, update_value>* root = nullptr;
public:
    Tree(ll l, ll r): l(l), r(r), root(new Node<T, default_value, merge_value, update_value>()) {}

    void upd(ll pos, T value) {
        root->upd(l, r, pos, move(value));
    }

    T get(ll L, ll R) {
        return root->get(l, r, L, R);
    }
};

template<class T, T default_value>
using SumTree = Tree<T, default_value, sum<T>, add_value<T>>;
