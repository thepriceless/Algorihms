def merge_sort(A, left, right):
    if left < right:
        merge_sort(A, left, left - 1 + (right - left + 1) // 2)
        merge_sort(A, left + (right - left + 1) // 2, right)
        merge(A, left, left - 1 + (right - left + 1) // 2, left + (right - left + 1) // 2, right)
 
 
def merge(A, l1, r1, l2, r2):
    new1, new2 = A[l1: r1 + 1], A[l2: r2 + 1]
    taken1, taken2, i = 0, 0, l1
    while (len(new1) - taken1) * (len(new2) - taken2) != 0:
        if new1[taken1] < new2[taken2]:
            A[i] = new1[taken1]
            taken1 += 1
        else:
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
 
 
with open("sort.in") as fin:
    with open("sort.out", "w") as fout:
        n = fin.readline()
        a = fin.readline().split()
        for i in range(len(a)):
            a[i] = int(a[i])
        merge_sort(a, 0, int(n) - 1)
        for i in range(len(a) - 1):
            fout.write(str(a[i]) + ' ')
        fout.write(str(a[-1]))
