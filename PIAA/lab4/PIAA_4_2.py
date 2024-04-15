def prefix_search(str):
    res = [0] * len(str)
    for i in range(1, len(str)):
        k = res[i - 1]
        while k > 0 and str[k] != str[i]:
            k = res[k - 1]
        if str[k] == str[i]:
            k += 1
        res[i] = k
    return res


def kmp_search(txt, ptrn):
    ptrn_len = len(ptrn)
    txt_len = len(txt)
    res = []
    j = 0

    prefix = prefix_search(ptrn)
    if ptrn_len == txt_len:
        for i in range(0, 2 * txt_len):
            while j > 0 and txt[i % txt_len] != ptrn[j]:
                j = prefix[j - 1]
                if j == 0:
                    break

            if txt[i % txt_len] == ptrn[j]:
                j += 1

            if j == ptrn_len:
                res.append(i - ptrn_len + 1)
                break

    if not res:
        res.append(-1)

    return res


def main():
    res = kmp_search(input(), input())
    print(*res, sep=',')


if __name__ == '__main__':
    main()
