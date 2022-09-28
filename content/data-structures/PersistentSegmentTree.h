/**
 * Author: Dmytro Mayor
 * Date: 2022-09-09
 * License: CC0
 * Source: folklore
 * Description: Persistent segment tree
 * Time: update - O(\log N), get - O(\log N)
 * Status: -
 */

#include <SegmentTreeNode.h>

template<class T, T default_value, T (*merge_value)(const T&, const T&), void (*update_value)(T&, const T&)>
class PersistentTree {
private:
    ll l, r;
    vec<Node<T, default_value, merge_value, update_value>*> roots;
public:
    PersistentTree(ll l, ll r): l(l), r(r) {
        roots.push_back(new Node<T, default_value, merge_value, update_value>());
    }

    size_t update(ll pos, T value) {
        roots.push_back(roots[roots.size() - 1]->upd_acreate(l, r, pos, move(value)));
        return roots.size() - 1;
    }

    T get(ll tree_id, ll L, ll R) {
        return roots[tree_id]->get(l, r, L, R);
    }
};

template<class T, T default_value>
using PersistentSumTree = PersistentTree<T, default_value, max<T>, set_value<T>>;
