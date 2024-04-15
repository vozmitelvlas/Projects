#python
def max_height(tree):
    tree = tuple(map(int, tree.split()))
    node_heights = dict()
    res = 0

    for node in tree:
        tmp_node = node
        tmp_h = 1
        while True:
            if tmp_node == -1:
                break

            tmp_node = tree[tmp_node]
            cached_node_height = node_heights.get(tmp_node, None)

            if cached_node_height is not None:
                tmp_h += cached_node_height
                break
            tmp_h += 1

        if node_heights.get(node, None) is None:
            node_heights[node] = tmp_h

        if tmp_h > res:
            res = tmp_h

    return res


N = input()
values = input()
print(max_height(values))