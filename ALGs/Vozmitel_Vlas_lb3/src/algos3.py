#python
class Heap:
    def __init__(self, heap):
        self.MAX_SIZE = 20
        self.heap = heap
        self.size = len(heap)
        self.res = []

    @staticmethod
    def get_parent(index):
        return (index - 1) // 2

    @staticmethod
    def get_left_child(index):
        return 2 * index + 1

    @staticmethod
    def get_right_child(index):
        return 2 * index + 2

    def insert(self, element):
        if self.size == self.MAX_SIZE:
            return -1
        self.heap[self.size] = element
        self.sift_up(self.size)
        self.size += 1

    def extract(self):
        max_element = self.heap[0]
        self.heap[0], self.heap[self.size - 1] = self.heap[self.size - 1], None
        self.size -= 1
        self.sift_down(0)
        return max_element

    def sift_up(self, index):
        parent = self.get_parent(index)
        while index > 0 and self.heap[index] < self.heap[parent]:
            self.heap[parent], self.heap[index] = self.heap[index], self.heap[parent]
            index = parent
            parent = self.get_parent(index)

    def sift_down(self, index):
        left = self.get_left_child(index)
        right = self.get_right_child(index)
        if left >= self.size and right >= self.size:
            return

        if right >= self.size:
            max_index = left if self.heap[left] < self.heap[index] else index

        else:
            max_index = left if self.heap[left] < self.heap[right] else right
            max_index = max_index if self.heap[max_index] < self.heap[index] else index

        if max_index != index:
            self.heap[max_index], self.heap[index] = self.heap[index], self.heap[max_index]
            self.sift_down(max_index)

    def __str__(self):
        return str(self.heap)


def main(n, m, arr):
    n = n
    m = m
    times = arr
    procs = [[0, i] for i in range(n)]
    heap = Heap(procs)

    for time in times:
        cur_time = heap.heap[0][0]

        heap.res.append([heap.heap[0][1], cur_time])
        heap.heap[0][0] += time

        heap.sift_down(0)

    return heap.res


n, m = map(int, input().split())
arr = list(map(int, input().split()))
res = main(n, m, arr)
for i in range(len(res)):
    print(res[i][0], res[i][1])