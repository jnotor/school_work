# referenced: https://medium.com/@avik.das/dynamic-programming-deep-dive-chain-matrix-multiplication-a3b8e207b201

def prettyPrint(matrix, size_n):
    print("Min num multiplications:", matrix[(0, size_n - 1)], '\n')

    for i in range(size_n):
        row = []
        for j in range(size_n):
            if j < i:
                row.append('X')
            elif j == i:
                row.append('0')
            else:
                row.append(matrix[(i, j)])
        print(row)

def chain_matrix(matrices):
    def cols(i): return matrices[i][1]
    def rows(i): return matrices[i][0]

    recordings = {}
    f = {}  # cached values of the recurrence relation
    n = len(matrices)
    for l in range(1, n + 1):
        for start in range(0, n - l + 1):
            # Base case
            if l == 1:
                f[(start, start)] = 0
                continue

            # Recursive case
            end = start + l - 1

            # Default min value to something very high
            f[(start, end)] = 99999999
            for mid in range(start, end):
                Min = f[(start, mid)] + f[(mid + 1, end)] + rows(start) * cols(mid) * cols(end)
                if Min < f[(start, end)]:
                    f[(start, end)] = Min
                    key = '%i, %i position\'s cut was:' % (start, end)
                    recordings[key] = mid

    for record in recordings:
        print(record, recordings[record])
    return f, n


f, n = chain_matrix([(5, 6), (6, 8), (8, 3), (3, 10), (10, 4)])
prettyPrint(f, n)