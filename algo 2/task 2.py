def merge_sort(A, left, right):
    if left < right:
        merge_sort(A, left, left - 1 + (right - left + 1) // 2)
        merge_sort(A, left + (right - left + 1) // 2, right)
        merge(A, left, left - 1 + (right - left + 1) // 2, left + (right - left + 1) // 2, right)
 
 
def merge(A, l1, r1, l2, r2):
    new1, new2 = A[l1: r1 + 1], A[l2: r2 + 1]
    taken1, taken2, i = 0, 0, l1
    while (len(new1) - taken1) * (len(new2) - taken2) != 0:
        if new1[taken1][0] <= new2[taken2][0]:
            A[i] = new1[taken1]
            taken1 += 1
        elif new1[taken1][0] > new2[taken2][0]:
            A[i] = new2[taken2]
            taken2 += 1
        i += 1
    if len(new1) - taken1 == 0:
        for j in range(taken2, len(new2)):
            A[i] = new2[j]
            i += 1
    else:
        for j in range(taken1, len(new1)):
            A[i] = new1[j]
            i += 1
 
 
with open("race.in") as fin:
    with open("race.out", "w") as fout:
        names, countries, full = [], [], []
        n = int(fin.readline())
        for i in range(n):
            a = fin.readline().split()
            full.append([a[0], a[1]])
        merge_sort(full, 0, len(full) - 1)
        previous = None
        for i in full:
            if i[0] != previous:
                fout.write('=== ' + i[0] + ' ===' + '\n')
                previous = i[0]
            fout.write(i[1])
            if i != full[-1]:
                fout.write('\n')
        print(full)
