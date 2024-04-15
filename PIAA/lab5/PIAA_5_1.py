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


def Aho(string, ptrns):
    tree_root = create_links(create_tree(ptrns))
    res = []
    node = tree_root

    for i in range(len(string)):
        while node is not None and string[i] not in node.child:
            node = node.suffix_link

        if node is None:
            node = tree_root
            continue

        node = node.child[string[i]]

        for pttrn in node.words:
            res.append((i - len(ptrns[pttrn]) + 2, pttrn + 1))

    return res


txt = input()
n = int(input())
ptrns = []

for i in range(n):
    ptrns.append(input())

res = sorted(Aho(txt, ptrns))
for i in res:
    print(i[0], i[1])
