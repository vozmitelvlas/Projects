import unittest
from PIAA_AVBG import Graph as AVBG
from PIAA_MVIG import Graph as MVIG


class TestMethods(unittest.TestCase):
    def test_1(self):
        graph = AVBG()
        graph.matrix = []
        graph.length = 0
        graph.start = 0
        graph.chain_search([graph.start, graph.start], (0, 0, 0))
        self.assertEqual(graph.weight, 0)

    def test_2(self):
        graph = AVBG()
        graph.matrix = [[0, 1, 2, 2], [0, 0, 1, 2], [0, 1, 0, 1], [1, 1, 0, 0]]
        graph.start = 2
        graph.length = 4
        graph.chain_search([graph.start, graph.start], (0, 0, 0))
        self.assertEqual((graph.chain, graph.weight), ([2, 3, 0, 1, 2], 4))

    def test_3(self):
        graph = AVBG()
        graph.matrix = [[0, 0, 5, 1, 0], [0, 0, 2, 0, 3], [5, 2, 0, 2, 2], [1, 0, 2, 0, 4], [0, 3, 2, 4, 0]]
        graph.start = 2
        graph.length = 5
        graph.chain_search([graph.start, graph.start], (0, 0, 0))
        self.assertEqual((graph.chain, graph.weight), ([2, 0, 3, 4, 1, 2], 15))

    def test_4(self):
        graph = MVIG()
        graph.matrix = []
        graph.length = 0
        graph.start = 0
        graph.chain_search(graph.start, [], [graph.start], 0, 0)
        self.assertEqual((graph.chain, graph.weight), ([], float('inf')))

    def test_5(self):
        graph = MVIG()
        graph.matrix = [[0, 3, 2, 9], [3, 0, 5, 5], [2, 5, 0, 2], [9, 5, 2, 0]]
        graph.length = 4
        graph.start = 3
        graph.chain_search(graph.start, [], [graph.start], 0, 0)
        self.assertEqual((graph.chain, graph.weight), ([3, 1, 0, 2, 3], 12))

    def test_6(self):
        graph = MVIG()
        graph.matrix = [[0, 1, 0, 1], [1, 0, 1, 0], [0, 1, 0, 1], [1, 0, 1, 0]]
        graph.length = 4
        graph.start = 0
        graph.chain_search(graph.start, [], [graph.start], 0, 0)
        self.assertEqual((graph.chain, graph.weight), ([0, 1, 2, 3, 0], 4))


if __name__ == "__main__":
    unittest.main()
