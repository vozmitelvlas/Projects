import unittest
import PIAA_4_1
import PIAA_4_2


class TestMethods(unittest.TestCase):
    def test_1(self):
        self.assertEqual(PIAA_4_1.main("abab", "ab"), ",".join(map(str, [0, 2])))
        self.assertEqual(PIAA_4_2.kmp_search("abcdef", "defabc"), [3])

    def test_2(self):
        self.assertEqual(PIAA_4_1.main('qwertyqw', 'qw'), ",".join(map(str, [0, 6])))
        self.assertEqual(PIAA_4_2.kmp_search("abc", "abc"), [0])

    def test_3(self):
        self.assertEqual(PIAA_4_1.main('aaaaaaa', 'aa'), ",".join(map(str, [0, 1, 2, 3, 4, 5])))
        self.assertEqual(PIAA_4_2.kmp_search("ae", "c"), [-1])

    def test_5(self):
        self.assertEqual(PIAA_4_1.main('abc', 'f'), "-1")
        self.assertEqual(PIAA_4_2.kmp_search("", ""), [-1])


if __name__ == "__main__":
    unittest.main()
