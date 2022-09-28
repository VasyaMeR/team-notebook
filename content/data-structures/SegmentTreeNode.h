/**
 * Author: Dmytro Mayor
 * Date: 2022-09-09
 * License: CC0
 * Source: folklore
 * Description: Customizable segment tree node.
 * Time: update - O(\log N), get - O(\log N)
 * Status: -
 */

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

    void recalculate() {
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
        recalculate();
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
        recalculate();
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

        if(!left && !right) return this->value;
        if(!left) return right->get(m + 1, r, L, R);
        if(!right) return left->get(l, m, L, R);

        return merge_value(get_left_node()->get(l, m, L, R), get_right_node()->get(m + 1, r, L, R));
    }
};