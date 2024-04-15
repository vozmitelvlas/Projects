import unittest
from PiyPiy1 import *


class TestMethods(unittest.TestCase):
    def test_1(self):
        self.assertEqual(begin(2), ([[1, 1, 1], [1, 2, 1], [2, 1, 1], [2, 2, 1]], 4))

    def test_2(self):
        self.assertEqual(begin(3), ([[1, 1, 2], [1, 3, 1], [2, 3, 1], [3, 1, 1], [3, 2, 1], [3, 3, 1]], 6))

    def test_3(self):
        self.assertEqual(begin(9), ([[1, 1, 6], [1, 7, 3], [4, 7, 3], [7, 1, 3], [7, 4, 3], [7, 7, 3]], 6))

    def test_4(self):
        self.assertEqual(begin(20), ([[1, 1, 10], [1, 11, 10], [11, 1, 10], [11, 11, 10]], 4))


if __name__ == "__main__":
    unittest.main()
