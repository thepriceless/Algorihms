with open("isheap.in") as fin:
    with open("isheap.out", "w") as fout:
        n = int(fin.readline())
        a = fin.readline().split()
        for i in range(n):
            a[i] = int(a[i])
        for i in range(1, n + 1):
            if 2 * i <= n:
                if a[i - 1] > a[2 * i - 1]:
                    fout.write('NO')
                    break
            if 2 * i + 1 <= n:
                if a[i - 1] > a[2 * i]:
                    fout.write('NO')
                    break
        else:
            fout.write('YES')
