/**
 * Author: Vasyl Merenych
 * Date: 2023-11-30
 * License: CC0
 * Source: folklore
 * Description: Binary bor for integer numbers. Get finds maximum xor of two numbers.
 * Time: add - O(\log A), get - O(\log A)
 * Status: -
 */
#include<array>

struct xor_bor_node {
	std::array<xor_bor_node*, 2> mp = {nullptr, nullptr};

	void add(int mask, int k = 30) {
		if (k == -1)
			return;
		int bit = (mask>>k)&1;

		if (!this->mp[bit])
			this->mp[bit] = new xor_bor_node();
		this->mp[bit]->add(mask, k - 1);
	}

	int get(int mask, int k = 30) {
		if (k == -1)
			return 0;
		int bit = (mask>>k)&1;
		int cur= bit;
		if (mp[!bit])
			cur = !bit;
		return ((cur^bit) << k) | mp[cur]->get(mask, k - 1);
	}
};
