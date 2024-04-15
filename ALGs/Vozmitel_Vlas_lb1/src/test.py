import unittest
from algos1 import *


class TestMethods(unittest.TestCase):
    def test_1(self):
        self.assertEqual(max_height([4, -1, 4, 1, 1]), 3)

    def test_2(self):
        self.assertEqual(max_height([9, 7, 5, 5, 2, 9, 9, 9, 2, -1]), 4)

    def test_3(self):
        self.assertEqual(max_height([-1]), 1)


if __name__ == "__main__":
    unittest.main()
