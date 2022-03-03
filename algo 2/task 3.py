inversions = 0
 
 
def merge_sort(A, left, right):
    if left < right:
        merge_sort(A, left, left - 1 + (right - left + 1) // 2)
        merge_sort(A, left + (right - left + 1) // 2, right)
        merge(A, left, left - 1 + (right - left + 1) // 2, left + (right - left + 1) // 2, right)
 
 
def merge(A, l1, r1, l2, r2):
    global inversions
    new1, new2 = A[l1: r1 + 1], A[l2: r2 + 1]
    taken1, taken2, i = 0, 0, l1
    while (len(new1) - taken1) * (len(new2) - taken2) != 0:
        if new1[taken1] <= new2[taken2]:
            A[i] = new1[taken1]
            taken1 += 1
        else:
            A[i] = new2[taken2]
            taken2 += 1
            inversions += len(new1) - taken1
        i += 1
    if len(new1) - taken1 == 0:
        for j in range(taken2, len(new2)):
            A[i] = new2[j]
            i += 1
    else:
        for j in range(taken1, len(new1)):
            A[i] = new1[j]
            i += 1
 
 
 
with open("inversions.in") as fin:
    with open("inversions.out", "w") as fout:
        n = int(fin.readline())
        nums = fin.readline().split()
        for i in range(n):
            nums[i] = int(nums[i])
        merge_sort(nums, 0, n - 1)
        fout.write(str(inversions))
