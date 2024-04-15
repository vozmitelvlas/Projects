# put your python code here

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


def kmp_search(ptrn, txt):
    i = 0  # text
    j = 0  # pattern
    lsp = prefix_search(ptrn)
    res = []
    while i < len(txt):
        if txt[i] == ptrn[j]:
            i += 1
            j += 1
        else:
            if j != 0:
                j = lsp[j - 1]
            else:
                i += 1
        if j == len(ptrn):
            res.append(i - j)
            j = lsp[j - 1]

    return res


def main(txt="", ptrn=""):
    if txt == "" and ptrn == "":
        ptrn = input()
        txt = input()
    res = kmp_search(ptrn, txt)
    return ",".join(map(str, res)) if res else "-1"


if __name__ == '__main__':
    print(main())
