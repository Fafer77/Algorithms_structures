def insertion_sort(l):
    n = len(l)
    for i in range(1, n):
        curr = i
        while curr > 0 and l[curr] < l[curr - 1]:
            l[curr - 1], l[curr] = l[curr], l[curr - 1]
            curr -= 1
        print(l)
    return l

print(insertion_sort([5, 7, 4, 9, 12, 11]))
