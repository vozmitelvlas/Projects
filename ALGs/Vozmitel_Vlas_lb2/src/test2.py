import unittest
from algos2 import *


class TestMethods(unittest.TestCase):
    def test_1(self):
        arr1 = [Pair(0, 32), Pair(1, 11), Pair(2, 3)]
        self.assertEqual(merge(arr1), [2, 1, 0])

    def test_2(self):
        arr2 = []
        self.assertEqual(merge(arr2), None)

    def test_3(self):
        arr3 = [Pair(0, 10), Pair(1, 10), Pair(2, 10)]
        self.assertEqual(merge(arr3), [0, 1, 2])


if __name__ == "__main__":
    unittest.main()
