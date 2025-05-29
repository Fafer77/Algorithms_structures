from collections import deque


def dfs(u, p, adj_list, not_centroid, size):
    size[u] = 1
    for v, _ in adj_list[u]:
        if v == p or not_centroid[v]:
            continue
        size[u] += dfs(v, u, adj_list, not_centroid, size)
    return size[u]


def find_tree_centroid(u, adj_list, not_centroid):
    n = len(adj_list)
    size = [0] * n
    n_subtree = dfs(u, -1, adj_list, not_centroid, size)
    centroid = u
    prev = -1
    changed = True
    while changed:
        changed = False
        for v, _ in adj_list[centroid]:
            if v == prev or not_centroid[v]:
                continue
            if size[v] > n_subtree // 2:
                prev = centroid
                centroid = v
                changed = True
                break
    return centroid


def distances(start, centroid, initial_dist, adj_list, not_centroid):
    dist_list = []
    visited = set()
    visited.add(start)

    queue = deque([(start, initial_dist)])

    while queue:
        v, dist_c = queue.popleft()
        dist_list.append(dist_c)

        for (u, w) in adj_list[v]:
            if u not in visited and not not_centroid[u] and u != centroid:
                visited.add(u)
                queue.append((u, dist_c + w))
    
    return dist_list



