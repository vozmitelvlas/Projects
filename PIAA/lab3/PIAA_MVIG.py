import copy
from generator import *


class Graph:
    def __init__(self):
        self.start = 0
        self.matrix = []
        self.chain = []
        self.weight = float('inf')
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

    def mod(self, viewed, tmp_ver, path_weight):
        viewed = copy.deepcopy(viewed)
        viewed.insert(0, self.start)
        edge = self.matrix[viewed[-1]][tmp_ver]
        viewed.append(tmp_ver)

        while len(viewed) < self.length:
            min_weight = float('inf')
            for ver in viewed:
                for i in range(self.length):
                    if i not in viewed and self.matrix[ver][i] != 0 and self.matrix[ver][i] < min_weight:
                        tmp_ver = i
                        min_weight = self.matrix[ver][i]

            edge += min_weight
            viewed.append(tmp_ver)

        path_weight += edge
        return path_weight

    def lightest(self, viewed, tmp_ver, path_weight):
        viewed = copy.deepcopy(viewed)
        viewed.insert(0, self.start)
        edge = self.matrix[viewed[-1]][tmp_ver]
        bound = edge
        viewed.append(tmp_ver)
        min_s, min_f = float('inf'), float('inf')
        for i in range(self.length):
            if (self.matrix[viewed[0]][i] > 0) and (min_s > self.matrix[viewed[0]][i]):
                min_s = self.matrix[viewed[0]][i]
            if (self.matrix[viewed[-1]][i] > 0) and (min_f > self.matrix[viewed[-1]][i]):
                min_f = self.matrix[viewed[-1]][i]

            if i not in viewed:
                min_weight1, min_weight2 = float('inf'), float('inf')
                for j in range(self.length):
                    if min_weight1 > self.matrix[i][j] > 0:
                        min_weight1 = self.matrix[i][j]
                    if min_weight1 < min_weight2:
                        tmp = min_weight1
                        min_weight1 = min_weight2
                        min_weight2 = tmp
                bound += min_weight1 + min_weight2
        bound += min_s + min_f
        bound /= 2
        bound += path_weight
        return bound

    def chain_search(self, tmp_ver, viewed1, chain1, chain_weight, edge_weight):
        if tmp_ver == self.start and 1 < len(chain1) < self.length:
            return

        viewed = copy.deepcopy(viewed1)
        chain = copy.deepcopy(chain1)
        if tmp_ver != self.start:
            viewed.append(tmp_ver)
            chain.append(tmp_ver)
            chain_weight += edge_weight

        if chain_weight >= self.weight:
            return

        if tmp_ver == self.start and len(chain) == self.length and chain_weight < self.weight:
            self.ok = 1
            chain.append(self.start)
            self.chain = chain
            self.weight = chain_weight + edge_weight
            return

        while True:
            closest = []
            for i in range(self.length):
                if self.matrix[tmp_ver][i] > 0:
                    closest.append(i)
            for ver in closest:
                if ver not in viewed:
                    if self.ok == 0 or (self.mod(viewed, ver, chain_weight) < self.weight
                                        and self.lightest(viewed, ver, chain_weight) < self.weight):
                        self.chain_search(ver, viewed, chain, chain_weight, self.matrix[tmp_ver][ver])
            return

    def my_print(self):
        if self.ok == 1:
            print("Chain: ", self.chain, "\nCost: ", self.weight)
        else:
            print("There's no the Hamilton's path in the matrix.")


if __name__ == '__main__':
    graph = Graph()
    graph.my_input()
    graph.chain_search(graph.start, [], [graph.start], 0, 0)
    graph.my_print()
