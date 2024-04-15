import unittest
from PIAA_2_2 import *


class TestMethods(unittest.TestCase):
    def test_1(self):
        self.assertEqual(for_unitest('a', 'a', [['a', 'b', 1], ['a', 'c', 2]]), "a")

    def test_2(self):
        self.assertEqual(
            for_unitest('a', 'e', [['a', 'e', 4], ['a', 'b', 1], ['a', 'c', 2], ['c', 'j', 1], ['j', 'e', 1]]), "ae")

    def test_3(self):
        self.assertEqual(
            for_unitest('l', 'z',
                        [['l', 'n', 4], ['l', 'p', 3], ['p', 'v', 10], ['p', 't', 7], ['t', 'v', 2], ['n', 'o', 5],
                         ['n', 'v', 12], ['v', 'z', 5], ['o', 'z', 16]]), "lptvz")

    def test_4(self):
        self.assertEqual(
            for_unitest('a', 'e', [['a', 'b', 3], ['b', 'c', 1], ['c', 'd', 1], ['a', 'd', 5], ['d', 'e', 1]]), "ade")


if __name__ == "__main__":
    unittest.main()
