class Node:
    def __init__(self, link=None):
        self.child = {}
        self.suffix_link = link
        self.words = []


def create_tree(pttrns):
    root = Node()

    for index, pattern in enumerate(pttrns):
        node = root
        for c in pattern:
            node = node.child.setdefault(c, Node(root))

        node.words.append(index)

    return root


def create_links(tree):
    queue = [value for key, value in tree.child.items()]

    while queue:
        current_node = queue.pop(0)

        for key, value_node in current_node.child.items():
            queue.append(value_node)
            link_node = current_node.suffix_link

            while link_node is not None and key not in link_node.child:
                link_node = link_node.suffix_link

            value_node.suffix_link = link_node.child[key] if link_node else tree
            value_node.words += value_node.suffix_link.words

    return tree


def Aho(string, pttrns):
    tree_root = create_links(create_tree(pttrns))
    res = []
    node = tree_root

    for i in range(len(string)):
        while node is not None and string[i] not in node.child:
            node = node.suffix_link

        if node is None:
            node = tree_root
            continue

        node = node.child[string[i]]

        for pattern in node.words:
            res.append((i - len(pttrns[pattern]) + 2, pattern + 1))

    return res


def create_patterns(pttrn, wild_card):
    ptrns = list(filter(None, pttrn.split(wild_card)))
    start_indices = []
    start_index = 0

    for p in ptrns:
        tmp = pttrn[start_index:]
        index = tmp.index(p)
        start_indices.append(index + (len(pttrn) - len(tmp)))
        start_index = index + len(p) + (len(pttrn) - len(tmp))

    return ptrns, start_indices


txt = input()
ptrn = input()
wild_card = input()

ptrns, start_indices = create_patterns(ptrn, wild_card)
result = sorted(Aho(txt, ptrns))

c = [0] * len(txt)
for i in result:
    index = i[0] - 1 - start_indices[i[1] - 1]
    if (index >= 0) and (index < len(c)):
        c[index] += 1

for i in range(len(c) - len(ptrn) + 1):
    if c[i] == len(ptrns):
        print(i + 1)
