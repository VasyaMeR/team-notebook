/**
 * Author: Merenych Vasyl
 * Date: 2024-03-13
 * License: CC0
 * Source: folklore
 * Description: Sum over submasks 
 * Time: O(n * 2 * n)
 * Status: -
 */

for (int i = 0; i < n; i++) {
	for (int mask = 0; mask < (1<<n); mask++) {
		if (mask&(1<<i)) {
			dp[mask] += dp[mask^(1<<i)];
		}
	}
}