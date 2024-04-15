from generator import init_matrix


class Graph:
    def __init__(self):
        self.start = 0
        self.matrix = []
        self.chain = []
        self.weight = 0
        self.ok = 0
        self.length = 0

    def my_input(self):
        key = int(input("0 - generate random matrix, 1 - use file's matrix\n"))
        if key == 0:
            n = int(input("how many vertexes: "))
            limit = int(input("What is the limit for edge's weight: "))
            init_matrix(n, limit)
        self.start = int(input("Start vertex: "))
        f = open('mtrx.txt')
        for line in f:
            tmp = list(map(int, line.split()))
            self.matrix.append(tmp)
        self.length = len(self.matrix)
        if self.length > 0:
            print("\nmatrix:")
            for i in range(self.length):
                print(*self.matrix[i])

    def weight_count(self):
        for i in range(len(self.chain) - 1):
            self.weight += self.matrix[self.chain[i]][self.chain[i + 1]]

    def next_vertex(self, chain):
        mb_vertex = []
        item = (0, 0, 0)
        for elem in chain[:len(chain) - 1:]:
            ind = chain.index(elem)
            for j in range(self.length):
                if j not in chain and self.matrix[elem][j] != 0 and self.matrix[j][chain[ind + 1]]:
                    mb_vertex.append((elem, j, self.matrix[elem][j]))
        if mb_vertex:
            item = min(mb_vertex, key=lambda x: x[2])
        return item

    def chain_search(self, chain, edge):
        if edge != (0, 0, 0):
            ind = chain.index(edge[0])
            chain.insert(ind + 1, edge[1])
        if len(chain) == self.length + 1:
            self.chain = chain
            self.weight_count()
            self.ok = 1
            return

        mb_vertex = self.next_vertex(chain)
        if mb_vertex == (0, 0, 0):
            return
        self.chain_search(chain, mb_vertex)

    def my_print(self):
        if self.ok == 1:
            print("Chain: ", self.chain, "\nCost: ", self.weight)
        else:
            print("There's no the Hamilton's path in the matrix.")


if __name__ == '__main__':
    graph = Graph()
    graph.my_input()
    graph.chain_search([graph.start, graph.start], (0, 0, 0))
    graph.my_print()
