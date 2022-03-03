def left_child(k):
    return 2 * k + 1
 
 
def right_child(k):
    return 2 * k + 2
 
 
def max_heapify(A, i):
    global heap_size
    left, right = left_child(i), right_child(i)
    if left < heap_size and A[left] > A[i]:
        largest = left
    else:
        largest = i
    if right < heap_size and A[right] > A[largest]:
        largest = right
    if largest != i:
        A[largest], A[i] = A[i], A[largest]
        max_heapify(A, largest)
 
 
def build_heap(A):
    global heap_size
    heap_size = len(A)
    for i in range(len(A) // 2 - 1, -1, -1):
        max_heapify(A, i)
 
 
def heap_sort(A):
    build_heap(A)
    global heap_size
    for i in range(len(A) - 1, 0, -1):
        A[i], A[0] = A[0], A[i]
        heap_size -= 1
        max_heapify(A, 0)
 
 
with open("sort.in") as fin:
    with open("sort.out", "w") as fout:
        n = int(fin.readline())
        a = fin.readline().split()
        for i in range(n):
            a[i] = int(a[i])
        heap_sort(a)
        for i in range(n - 1):
            fout.write(str(a[i]) + ' ')
        fout.write(str(a[-1]))
