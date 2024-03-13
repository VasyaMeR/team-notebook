/**
 * Author: Vasya Merenych
 * Date: 2024-03-13
 * License: CC0
 * Source: Codeforces
 * Description: A red-black tree with the ability to get an element by index (find_by_order) and index of a specific element (order_of_key).
 * Time: get - O(\log N), segment tree is 2 times faster
 * Status: Tested
 */

#include <ext/rope>
using namespace __gnu_cxx;

rope<int> v;
for(int i = 1; i <= n; ++i)
	v.push_back(i);
rope<int> cur = v.substr(l, r - l + 1); // start, length
v.erase(l, r - l + 1); // start, length
v.insert(v.mutable_begin(), cur);

for(rope <int>::iterator it = v.mutable_begin(); it != v.mutable_end(); ++it)
	cout << *it << " ";