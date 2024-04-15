import math


def for_unitest(start, end, arr):
    nodes = {}
    for_node2 = []
    for elem in arr:
        for_node2.append(elem[1])
        if not nodes.get(elem[0]):
            nodes[elem[0]] = []
        nodes[elem[0]].append([elem[1], elem[2]])

    for elem in for_node2:
        if not nodes.get(elem):
            nodes[elem] = []
            nodes[elem].append([elem, 0])

    return ''.join(super_star(start, end, nodes))


def my_input():
    start, end = input().split()
    nodes = {}
    for_node2 = []
    while True:
        try:
            tmp_node1, tmp_node2, tmp = input().split()
            for_node2.append(tmp_node2)
            weight = float(tmp)

            if not nodes.get(tmp_node1):
                nodes[tmp_node1] = []

            nodes[tmp_node1].append([tmp_node2, weight])

        except (ValueError, EOFError):
            break

    for elem in for_node2:
        if not nodes.get(elem):
            nodes[elem] = []
            nodes[elem].append([elem, 0])

    nodes[end] = []
    nodes[end].append([end, 0])
    return start, end, nodes


def h(tmp, end):
    return ord(end) - ord(tmp)


def argmin(Q, end, start_cost):
    min_len = math.inf
    min_node = end
    for node in Q:
        f = start_cost[node] + h(node, end)
        if f < min_len:
            min_len = f
            min_node = node

        if f == min_len and ord(node) > ord(min_node):
            min_node = node

    return min_node


def super_star(start, end, graph):
    Q = []  # множество вершин, которые требуется рассмотреть
    V = []  # множество рассмотренных вершин
    start_cost = {}  # цена пути от начала до вершины (пройденный путь)
    res = {}  # результат

    Q.append(start)

    for key in graph:
        start_cost[key] = math.inf

    start_cost[start] = 0
    while len(Q) > 0:
        tmp_node = argmin(Q, end, start_cost)

        if tmp_node == end:
            return my_output(res, start, end)

        Q.remove(tmp_node)
        V.append(tmp_node)

        for i in range(len(graph[tmp_node])):

            distance = start_cost[tmp_node] + graph[tmp_node][i][1]
            if distance < start_cost[graph[tmp_node][i][0]]:  # !

                start_cost[graph[tmp_node][i][0]] = distance

                res[graph[tmp_node][i][0]] = tmp_node

                if not graph[tmp_node][i][0] in Q:
                    Q.append(graph[tmp_node][i][0])

    return my_output(res, start, end)


def my_output(list, start, end):
    res = [end]
    tmp_parent = end
    while tmp_parent != start:
        tmp_parent = list[tmp_parent]
        res.append(tmp_parent)
    return res[::-1]


def main():
    start, end, nodes = my_input()
    res = super_star(start, end, nodes)
    print(*res, sep='')


if __name__ == '__main__':
    main()
