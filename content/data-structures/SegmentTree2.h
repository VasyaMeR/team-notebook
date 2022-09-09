/**
 * Author: Dmytro Mayor
 * Date: 2022-09-09
 * License: CC0
 * Source: folklore
 * Description: Customizable tree + persistent tree.
 * Time: update - O(\log N), get - O(\log N)
 * Status: -
 */
#pragma once

#define OPTIMIZE_DREVO_MEMORY_R
#define OPTIMIZE_DREVO_MEMORY_G

template<class T, T default_value, T (*merge_value)(const T&, const T&), void (*update_value)(T&, const T&)>
class Node {
protected:
    using NodeT = Node<T, default_value, merge_value, update_value>;
    using ll = long long;

    Node* left = nullptr;
    Node* right = nullptr;

    T value;

    Node* my_copy() {
        Node* result = new NodeT();
        result->left = this->left;
        result->right = this->right;
        result->value = this->value;
        return result;
    }

    Node* get_left_node() {
        if(left == nullptr)
            left = new NodeT();
        return left;
    }

    Node* get_right_node() {
        if(right == nullptr)
            right = new NodeT();
        return right;
    }

    const T& get_left_val() const {
        if(left == nullptr)
            return default_value;
        return left->value;
    }

    const T& get_right_val() {
        if(right == nullptr)
            return default_value;
        return right->value;
    }

    void recalc() {
#ifdef OPTIMIZE_DREVO_MEMORY_R
        if(!left && !right) {
            this->value = default_value;
            return;
        }
        if(!left) {
            this->value = merge_value(default_value, get_right_node()->value);
            return;
        }
        if(!right) {
            this->value = merge_value(get_left_node()->value, default_value);
            return;
        }
#endif
        this->value = merge_value(get_left_node()->value, get_right_node()->value);
    }

    void upd_acreate_shadow(ll l, ll r, ll pos, T new_value) {
        if (l == r) {
            update_value(this->value, move(new_value));
            return;
        }
        ll m = (l + r) / 2;
        if(pos <= m) {
            if(this->left) {
                this->left = this->left->upd_acreate(l, m, pos, move(new_value));
            } else {
                this->left = new NodeT();
                this->left->upd(l, m, pos, move(new_value));
            }
        } else {
            if(this->right) {
                this->right = this->right->upd_acreate(m + 1, r, pos, move(new_value));
            } else {
                this->right = new NodeT();
                this->right->upd(m + 1, r, pos, move(new_value));
            }
        }
        recalc();
    }
public:
    explicit Node(): value(default_value) {}

    void upd(ll l, ll r, ll pos, T new_value) {
        if(l == r) {
            update_value(this->value, move(new_value));
            return;
        }
        ll m = (l + r) / 2;
        (pos <= m ? get_left_node()->upd(l, m, pos, move(new_value)) : get_right_node()->upd(m + 1, r, pos, move(new_value)));
        recalc();
    }

    Node* upd_acreate(ll l, ll r, ll pos, T new_value) {
        Node* result = my_copy();
        result->upd_acreate_shadow(l, r, pos, new_value);
        return result;
    }

    T get(ll l, ll r, ll L, ll R) {
        if(r < L || R < l)
            return default_value;
        if(L <= l && r <= R)
            return this->value;
        ll m = (l + r) / 2;
#ifdef OPTIMIZE_DREVO_MEMORY_G
        if(!left && !right) return this->value;
        if(!left) return right->get(m + 1, r, L, R);
        if(!right) return left->get(l, m, L, R);
#endif
        return merge_value(left->get(l, m, L, R), right->get(m + 1, r, L, R));
    }
};

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

template<class T, T default_value, T (*merge_value)(const T&, const T&), void (*update_value)(T&, const T&)>
class PersistentTree {
private:
    ll l, r;
    vec<Node<T, default_value, merge_value, update_value>*> roots;
public:
    PersistentTree(ll l, ll r): l(l), r(r) {
        roots.push_back(new Node<T, default_value, merge_value, update_value>());
    }

    size_t upd_acreate(ll pos, T value) {
        roots.push_back(roots[roots.size() - 1]->upd_acreate(l, r, pos, move(value)));
        return roots.size() - 1;
    }

    T get(ll tree_id, ll L, ll R) {
        return roots[tree_id]->get(l, r, L, R);
    }
};

template<class T>
T sum(const T& l, const T& r) {
    return l + r;
}

template<class T>
T my_max(const T& l, const T& r) {
    return max(l, r);
}

template<class T>
void set_value(T& var, const T& value) {
    var = value;
}

template<class T>
void add_value(T& var, const T& value) {
    var = var + value;
}

template<class T, T default_value>
using SumTree = Tree<T, default_value, sum<T>, add_value<T>>;

template<class T, T default_value>
using PersistentSumTree = PersistentTree<T, default_value, sum<T>, set_value<T>>;
