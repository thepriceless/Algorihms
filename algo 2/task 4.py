with open("antiqs.in") as fin:
    with open("antiqs.out", "w") as fout:
        n = int(fin.readline())
        b = [i for i in range(1, n + 1)]
        for i in range(len(b)):
            b[i], b[i // 2] = b[i // 2], b[i]
        for i in range(n - 1):
            fout.write(str(b[i]) + ' ')
        fout.write(str(b[-1]))
