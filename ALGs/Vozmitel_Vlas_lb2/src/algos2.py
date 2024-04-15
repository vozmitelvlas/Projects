#python
class Pair:
    def __init__(self, index=0, data=0):
        self.index = index
        self.data = data


def merge(arr):
    answer = []
    if len(arr) <= 1:
        return

    middle = len(arr) // 2
    left, right = arr[:middle], arr[middle:]
    merge(left)
    merge(right)
    index_left = index_right = index_result = 0

    result = [Pair(0, 0) for i in range(len(left) + len(right))]

    while index_left < len(left) and index_right < len(right):

        if left[index_left].data <= right[index_right].data:
            result[index_result].data = left[index_left].data
            result[index_result].index = left[index_left].index
            index_left += 1

        else:
            result[index_result].data = right[index_right].data
            result[index_result].index = right[index_right].index
            index_right += 1

        index_result += 1

    while index_left < len(left):
        result[index_result].data = left[index_left].data
        result[index_result].index = left[index_left].index
        index_left += 1
        index_result += 1

    while index_right < len(right):
        result[index_result].data = right[index_right].data
        result[index_result].index = right[index_right].index
        index_right += 1
        index_result += 1

    for i in range(len(arr)):
        arr[i] = result[i]
        answer.append(arr[i].index)

    for j in range(len(result)):
        print(result[j].index, end=' ')

    print()

    return answer


if __name__ == "__main__":
    n = int(input())
    arr = []
    for i in range(n):
        arr.append(Pair(i))
        size = int(input())
        cur_sum = 0

        for j in range(size):
            line = list(map(int, input().split()))
            cur_sum += line[j]

        arr[i].data = cur_sum
    print(*merge(arr))