/**
 * Author: Vasyl Merenych
 * Date: 2024-03-13
 * License: CC0
 * Source: folklore
 * Description: A red-black tree with the ability to get an element by index (find\_by\_order) and index of a specific element (order\_of\_key)
 * Time: get - O(\log N), segment tree is 2 times faster
 * Status: -
 */

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
 