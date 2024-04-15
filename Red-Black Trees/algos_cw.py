import graphviz

BLACK = 'black'
RED = 'red'


class Node:
    def __init__(self, item):
        self.item = item
        self.parent = None
        self.left = None
        self.right = None
        self.color = RED

    def __str__(self):
        left = self.left.item if self.left else None
        right = self.right.item if self.right else None
        parent = self.parent.item if self.parent else None
        return 'key: {}, left: {}, right: {}, color: {}, parent: {}'.format(self.item, left, right, self.color, parent)


class RBTree:
    def __init__(self):
        self.nil = Node("nil")
        self.nil.color = BLACK
        self.root = self.nil

    def search_tree_helper(self, node, key):
        if node == self.nil or key == node.item:  # если элемента нет или элемент найден то возвращем его
            return node

        if key < node.item:  # иначе рекурсивно спускаемся вниз и ищем его
            return self.search_tree_helper(node.left, key)
        return self.search_tree_helper(node.right, key)

    def delete_fix(self, x):
        while x != self.root and x.color == BLACK:
            if x == x.parent.left:  # если x является левым ребенком
                s = x.parent.right  # s - брат x
                if s.color == RED:  # меняем цвет брата и его родителя на черный
                    s.color = BLACK
                    x.parent.color = RED
                    self.left_rotate(x.parent)  # выполняется левый поворот с родителем x
                    s = x.parent.right

                if s.left.color == BLACK and s.right.color == BLACK:  # если дети брата черные, то меняем цвет брата
                    # на красный, чтобы свойство выполнялось
                    s.color = RED
                    x = x.parent
                else:
                    if s.right.color == BLACK:
                        # если сын брата черный, то левого сына красим в красный, производим
                        # правый поворот и обратно присваиваем переменной s брата x
                        s.left.color = BLACK
                        s.color = RED
                        self.right_rotate(s)
                        s = x.parent.right

                    # присваиваем соответствующие цвета и выполняем левый поворот
                    s.color = x.parent.color
                    x.parent.color = BLACK
                    s.right.color = BLACK
                    self.left_rotate(x.parent)
                    x = self.root
            else:  # тоже самое симметрично выполняем если x является правым ребенком
                s = x.parent.left
                if s.color == RED:
                    s.color = BLACK
                    x.parent.color = RED
                    self.right_rotate(x.parent)
                    s = x.parent.left

                if s.right.color == BLACK and s.right.color == BLACK:
                    s.color = RED
                    x = x.parent
                else:
                    if s.left.color == BLACK:
                        s.right.color = BLACK
                        s.color = RED
                        self.left_rotate(s)
                        s = x.parent.left

                    s.color = x.parent.color
                    x.parent.color = BLACK
                    s.left.color = BLACK
                    self.right_rotate(x.parent)
                    x = self.root
        x.color = BLACK

    def __rb_transplant(self, node, child):
        if node.parent is None:
            self.root = child

        elif node == node.parent.left:
            node.parent.left = child

        else:
            node.parent.right = child
        child.parent = node.parent

    def minimum(self, node):
        # поиск самого нижнего левого элемента
        while node.left != self.nil:
            node = node.left
        return node

    def delete_node_helper(self, node, key):
        z = self.nil
        while node != self.nil:  # спускаемся от корня вниз пока не найдем элемент с нужным ключом
            if node.item == key:
                z = node

            if node.item <= key:
                node = node.right
            else:
                node = node.left

        if z == self.nil:  # случай для отсутствия узла с данным ключом в дереве
            print("Cannot find key in the tree")
            return

        y = z
        y_original_color = y.color
        if z.left == self.nil:  # если отсутсвует у найденного элемента левый ребенок
            x = z.right  # текущий правый ребенок
            self.__rb_transplant(z, z.right)  # производим замены указателей между нужными узлами

        elif z.right == self.nil:  # если отсутсвует у найденного элемента правый ребенок
            x = z.left  # текущий левый ребенок
            self.__rb_transplant(z, z.left)  # производим замены указателей между нужными узлами

        else:  # если все дети на месте
            y = self.minimum(z.right)  # ползем вниз и ищем самый нижний левый элемент
            y_original_color = y.color
            x = y.right
            if y.parent == z:  # если родитель мин элемент совпадает с нужным
                x.parent = y  # присваиваем листу на место родителя y
            else:
                self.__rb_transplant(y, y.right)  # иначе замена сына мин элемента и мин элемента
                y.right = z.right
                y.right.parent = y

            self.__rb_transplant(z, y)
            y.left = z.left
            y.left.parent = y
            y.color = z.color

        if y_original_color == BLACK:
            # Исходный цвет элемента для удаления был черным; необходимо сбалансировать дерево после удаления
            self.delete_fix(x)

    def rb_insert_fix(self, k):
        # если родитель нового узла  не черный, необходима балансировка (2 случая)
        while k.parent.color == RED:  # цикл выполняется пока родитель не станет черным
            if k.parent == k.parent.parent.right:
                u = k.parent.parent.left
                if u.color == RED:  # 1) дядя узла красный
                    u.color = BLACK
                    k.parent.color = BLACK
                    k.parent.parent.color = RED
                    k = k.parent.parent
                else:  # 2) дядя узла черный
                    if k == k.parent.left:  # Проверяем, не нарушена ли балансировка для “Деда”
                        k = k.parent
                        self.right_rotate(k)
                    k.parent.color = BLACK
                    k.parent.parent.color = RED
                    self.left_rotate(k.parent.parent)
            else:  # те же самые проверки, если родитель является правым потомком
                u = k.parent.parent.right

                if u.color == RED:
                    u.color = BLACK
                    k.parent.color = BLACK
                    k.parent.parent.color = RED
                    k = k.parent.parent
                else:
                    if k == k.parent.right:
                        k = k.parent
                        self.left_rotate(k)
                    k.parent.color = BLACK
                    k.parent.parent.color = RED
                    self.right_rotate(k.parent.parent)
            if k == self.root:
                break
        self.root.color = BLACK

    def search_tree(self, k):
        return self.search_tree_helper(self.root, k)

    def delete_node(self, item):
        self.delete_node_helper(self.root, item)

    def left_rotate(self, x):
        y = x.right
        x.right = y.left
        if y.left != self.nil:
            y.left.parent = x

        y.parent = x.parent
        if x.parent is None:
            self.root = y
        elif x == x.parent.left:
            x.parent.left = y
        else:
            x.parent.right = y
        y.left = x
        x.parent = y

    def right_rotate(self, x):
        y = x.left
        x.left = y.right
        if y.right != self.nil:
            y.right.parent = x

        y.parent = x.parent
        if x.parent is None:
            self.root = y
        elif x == x.parent.right:
            x.parent.right = y
        else:
            x.parent.left = y
        y.right = x
        x.parent = y

    def rb_insert(self, key):
        node = Node(key)  # создаём новый узел красного цвета
        node.parent = None
        node.item = key
        node.left = self.nil
        node.right = self.nil
        node.color = RED

        y = None
        x = self.root

        while x != self.nil:  # спускаемся от корня до фиктивного листа, куда будет вставлен элемент
            y = x
            if node.item < x.item:
                x = x.left
            else:
                x = x.right
        # к данному моменту y - является родителем для нового узла
        node.parent = y
        if y is None:  # случай если дерево пустое
            self.root = node
        # далее( если дерево не пустое) сравниваем значения узлов для реализации бинарного дерева
        elif node.item < y.item:
            y.left = node
        else:
            y.right = node

        if node.parent is None:  # корень окрашен в черный цвет
            node.color = BLACK
            return

        if node.parent.parent is None:
            return

        self.rb_insert_fix(node)  # метод для восстановления сво-в RB tree

    def showing(self, index, tree):
        root = tree.root
        queue = [root]
        graph = graphviz.Digraph(directory="Result_files")
        cnt_nil = 0

        graph.node(str(id(root)), label=str(root.item), color=BLACK)
        while queue:
            tmp_queue = []
            for element in queue:
                node_id = str(id(element))
                if element != self.nil:
                    id_element = str(id(element))
                    if element.left != self.nil:
                        graph.node(str(id(element.left)), label=str(element.left.item), color=element.left.color)
                        graph.edge(node_id, str(id(element.left)))
                        tmp_queue.append(element.left)

                    else:
                        cnt_nil += 1
                        graph.node(str(cnt_nil), label="nil", color=BLACK)
                        graph.edge(id_element, str(cnt_nil))

                    if element.right != self.nil:
                        graph.node(str(id(element.right)), label=str(element.right.item), color=element.right.color)
                        graph.edge(node_id, str(id(element.right)))
                        tmp_queue.append(element.right)

                    else:
                        cnt_nil += 1
                        graph.node(str(cnt_nil), label="nil", color=BLACK)
                        graph.edge(id_element, str(cnt_nil))

            queue = tmp_queue
        name = 'fileout_№_{}'.format(index)
        name = name
        graph.render(name)


if __name__ == "__main__":
    RBtree = RBTree()

    RBtree.rb_insert(3)
    RBtree.showing(2, RBtree)

    for i in range(3, 48, 6):
        RBtree.rb_insert(i)
        RBtree.showing(i, RBtree)

    RBtree.delete_node(3)
    RBtree.showing(48, RBtree)
    RBtree.delete_node(15)
    RBtree.showing(49, RBtree)
