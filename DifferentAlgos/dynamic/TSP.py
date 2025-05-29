"""
Memory complexity: O(n*2^n), because we have to keep
(i) visited nodes
(ii) index of the last visited node in the path
There are n possible nodes that we could have visited last and 2^n 
possible subsets of visited nodes (for each vertex it can be either
visited or not visited)

Time complexity: O(n^2*2^n)
To iterate through all possible masks (set of visited nodes) it takes O(2^n)
Within mask loop we iterate through each vertex and for each chosen vertex
we iterate once again through each vertex trying to extend path
"""


INF = float('inf')

def held_karp_tsp(n, m):
    S = 0
    dp = [[INF] * n for _ in range(1 << n)]
    dp[1 << S][S] = 0 # first bit mask, second last visited vertex

    # fill paths
    for mask in range(1 << n):
        # start points ain't visited
        if not (mask & (1 << S)):
            continue
        
        for u in range(n):
            # not visited then continue
            if not (mask & (1 << u)):
                continue
            cost_u = dp[mask][u]
            if cost_u == INF:
                continue

            for v in range(n):
                # potential new edge can't be visited
                if mask & (1 << v):
                    continue
                new_mask = mask | (1 << v)
                c = cost_u + m[u][v]
                # check whether it is shortest
                if c < dp[new_mask][v]:
                    dp[new_mask][v] = c
    
    # find lowest cost and last vertex that goes to S
    lowest_cost = INF
    last = -1
    end_state = (1 << n) - 1
    for u in range(n):
        if u == S:
            continue
        cost = dp[end_state][u] + m[u][S]
        if cost < lowest_cost:
            lowest_cost = cost
            last = u
    
    if lowest_cost >= INF:
        return None, None

    # reconstruct path
    tour = [0] * (n + 1)
    tour[-1] = tour[0] = S
    tour[-2] = last
    mask = end_state
    curr = last

    for i in range(n-1, 0, -1):
        prev_mask = mask ^ (1 << curr)
        for u in range(n):
            if not (prev_mask & (1 << u)):
                continue
            if dp[mask][curr] == dp[prev_mask][u] + m[u][curr]:
                tour[i] = curr
                curr = u
                mask = prev_mask
                break
    
    return lowest_cost, tour
