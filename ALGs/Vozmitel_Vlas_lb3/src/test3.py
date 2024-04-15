import unittest
from algos3 import *


class TestMethods(unittest.TestCase):
    def test_1(self):
        self.assertEqual(main(2, 5, [1, 2, 3, 4, 5]), [[0, 0], [1, 0], [0, 1], [1, 2], [0, 4]])

    def test_2(self):
        self.assertEqual(main(2, 0, []), [])

    def test_3(self):
        self.assertEqual(main(5, 5, [1, 1, 1, 1, 1]), [[0, 0], [1, 0], [2, 0], [3, 0], [4, 0]])

    def test_4(self):
        self.assertEqual(main(1, 4, [1, 1, 1, 1]), [[0, 0], [0, 1], [0, 2], [0, 3]])


if __name__ == "__main__":
    unittest.main()
