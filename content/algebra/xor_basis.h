/**
 * Author: Merenych Vasyl
 * Date: 2022-11-28
 * License: CC0
 * Source: folklore
 * Description: Xor basis, all elements in the main set can be constructed using xor operation and elements in the basis 
 * Time: insert per element - O(log(A_max)) 
 * Status: -
 */

#include <vector>

template<typename T = int, int max_bit = 31>
struct xor_basis
{
	std::vector<T> basis; // basis[i] -> element with smallest set bit equal to i 
	int sz; // Current size of the basis

	xor_basis() {
		basis.assign(max_bit);
	}

	bool insert(T val) {
		for (int i = 0; i < max_bit; i++) {
			if (((val >> i)&1) == 0)
				continue;
			if (!basis[i]) {
				basis[i] = val;
				sz++;
				return true;
			}
			val ^= basis[i];
		}
		return false;
	}

	bool contains(T val) {
		for (int i = 0; i < max_bit; i++) {
			if (((val >> i)&1) == 0)
				continue;
			if (!basis[i]) {
				return false;
			}
			val ^= basis[i];
		}
		return true;
	}

	T max_element() { // not-sure
		T val = 0;
		for (int i = max_bit - 1; i >= 0; i--) {
			if (basis[i] && !((val>>i)&1)) {
				val ^= basis[i];
			}
		}
		return val;
	}
};