with open('turtle.in') as f:
    with open('turtle.out', 'w') as ff:
        a = f.readline().split()
        rows, cols = int(a[0]), int(a[1])
        res, sums = [[] for i in range(rows)], [[0 for j in range(cols)] for i in range(rows)]
        for i in range(rows):
            row = f.readline().split()
            for j in row:
                res[i].append(int(j))
        sums[-1][0] = res[-1][0]
        for i in range(rows - 2, -1, -1):
            sums[i][0] = sums[i + 1][0] + res[i][0]
        for i in range(1, cols):
            for j in range(rows - 1, -1, -1):
                if j != rows - 1:
                    sums[j][i] = res[j][i] + max(sums[j + 1][i], sums[j][i - 1])
                else:
                    sums[j][i] = res[j][i] + sums[j][i - 1]
        ff.write(str(sums[0][-1]))
