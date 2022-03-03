def counting_sort(array, sort_index, number_of_keys):
    a = [0 for i in range(number_of_keys)]
    for i in range(len(array)):
        a[int(ord(array[i][sort_index]) - 97)] += 1
    for i in range(1, len(a)):
        a[i] += a[i - 1]
    to_print = [None for i in range(len(array))]
    for i in range(len(array) - 1, -1, -1):
        to_print[a[int(ord(array[i][sort_index]) - 97)] - 1] = array[i]
        a[int(ord(array[i][sort_index]) - 97)] -= 1
    return to_print
 
 
def radixsort(arr, length, step):
    for i in range(1, 1 + step):
        arr = counting_sort(arr, -i, 26)
    return arr
 
 
with open("radixsort.in") as fin:
    with open("radixsort.out", "w") as fout:
        info = fin.readline().split()
        rows, columns, steps = int(info[0]), int(info[1]), int(info[2])
        a = []
        for i in range(rows):
            b = fin.readline().split('\n')
            a.append(b[0])
        a = radixsort(a, columns, steps)
        for i in range(rows - 1):
            fout.write(str(a[i]) + '\n')
        fout.write(str(a[-1]))
