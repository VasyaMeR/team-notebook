/**
 * Author: Merenych Vasyl
 * Date: 2022-11-28
 * License: CC0
 * Source: folklore
 * Description: Xor basis, all elements in the main set can be constructed using xor operation and elements in the basis 
 * Time: insert per element - O(log(A_max)) 
 * Status: -
 */

array<int, 61> basis; // basis[i] -> element with smallest set bit equal to i 
int sz; // Current size of the basis

bool insert_vector(int mask) {
	for (int i = 0; i <= 60; i++) {
		if ((mask & (1ll << i)) == 0)
			continue;
		if (!basis[i]) {
			basis[i] = mask;
			sz++;
			return true;
		}
		mask ^= basis[i];
	}
	return false;
}