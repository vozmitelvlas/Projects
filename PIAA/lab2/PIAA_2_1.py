def for_unitest(start, end, arr):
    nodes = {}
    for elem in arr:
        if not nodes.get(elem[0]):
            nodes[elem[0]] = []
        nodes[elem[0]].append([elem[1], elem[2]])

    return ''.join(greedy_star(start, end, nodes))


def my_input():
    start, end = input().split()
    nodes = {}
    while True:
        try:
            tmp_node1, tmp_node2, tmp = input().split()
            weight = float(tmp)

            if not nodes.get(tmp_node1):
                nodes[tmp_node1] = []

            nodes[tmp_node1].append([tmp_node2, weight])

        except (ValueError, EOFError):
            break

    return greedy_star(start, end, nodes)


def greedy_star(node, end, graph):
    res = []
    res += node
    key = node

    while key != end:
        min = (10000, 0)
        for i in range(len(graph[key])):
            if graph[key][i][1] < min[0]:
                min = (graph[key][i][1], i)

        if len(graph[key]) > 0:
            if graph[key][min[1]][0] in graph or graph[key][min[1]][0] == end:
                key = graph[key][min[1]][0]
                res += key
            else:
                graph[key].remove([graph[key][min[1]][0], graph[key][min[1]][1]])
                continue
        else:
            del graph[key]
            if key in res:
                res.remove(key)
            key = res[-1]
            continue
    return res


def main():
    res = my_input()
    print(*res, sep='')


if __name__ == '__main__':
    main()
