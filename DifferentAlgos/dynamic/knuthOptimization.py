from typing import List

class Solution:
    def minCost(self, n: int, cuts: List[int]) -> int:
        cuts.append(0)
        cuts.append(n)
        cuts.sort()
        m = len(cuts)
        dp = [[0] * m for _ in range(m)]
        opt = [[0] * m for _ in range(m)]

        for i in range(m - 1):
            opt[i][i + 1] = i + 1

        for l in range(2, m):
            for i in range(0, m - l):
                j = i + l
                left = opt[i][j - 1]
                right = opt[i + 1][j]
                best = float('inf')
                best_k = left
                for k in range(left, right + 1):
                    cost = dp[i][k] + dp[k+1][j] + cuts[j] - cuts[i]
                    if cost < best:
                        best = cost
                        best_k = k
                dp[i][j] = best
                opt[i][j] = best_k

        return dp[0][m - 1]