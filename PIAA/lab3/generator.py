from random import randint


def init_matrix(n, lim):
    mtrx = []
    f = open('mtrx.txt', 'w')

    for i in range(n):
        line = []
        for j in range(n):
            line.append(randint(0, lim))
        mtrx.append(line)

    for i in range(n):
        for j in range(i, n):
            mtrx[j][i] = mtrx[i][j]

    for i in range(n):
        mtrx[i][i] = 0
        f.write(' '.join(map(str, mtrx[i])))
        f.write('\n')
