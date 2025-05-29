from typing import List

class Solution:
    def lengthOfLIS(self, nums: List[int]) -> int:
        n = len(nums)
        k = 1
        dp = [float('inf')] * n

        for num in nums:
            idx = self.bin_search(dp, k, num)
            dp[idx] = num
            if idx == k:
                k += 1
        return k

    def bin_search(self, dp, n, x):
        L, R = 0, n
        while (L < R):
            mid = (L + R) // 2
            if dp[mid] < x:
                L = mid + 1
            else:
                R = mid
        
        return L
        

sol = Solution()
sol.lengthOfLIS([0,1,0,3,2,3])
