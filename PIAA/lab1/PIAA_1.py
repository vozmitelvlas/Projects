def even(square_size, res):
    min_cnt = 4

    for i in range(min_cnt // 2):
        for j in range(min_cnt // 2):
            res.append([i * square_size // 2 + 1, j * square_size // 2 + 1, square_size // 2])

    return res, min_cnt


def backtracking(square_field, square, square_number):
    square_size = len(square_field)
    corn_x = 0
    corn_y = 0
    for i in range(square_size // 2, square_size):
        for j in range(square_size // 2, square_size):
            if square_field[i][j] == 0:  # looking for the first upper left corner == 0
                corn_x = j
                corn_y = i
                break
        if corn_x != 0:
            break

    if corn_x == 0:
        if square_number - 1 < square[0]:  # minimum check
            square[0] = square_number - 1
            square[1] = square_field
        return square
    else:
        if square_number == square[0]:
            return square

    field_copy = []
    sum_x = 0
    sum_y = 0
    for i in range(square_size):
        field_copy.append([])
        for j in range(square_size):
            field_copy[i].append(square_field[i][j])

    for i in range(square_size // 2, square_size):  # search for free space to insert
        if field_copy[i][corn_x] == 0:
            sum_y += 1
    for i in range(square_size // 2, square_size):
        if field_copy[corn_y][i] == 0:
            sum_x += 1
        elif sum_x > 0 and field_copy[corn_y][i] != 0:
            break

    max_size = min(sum_y, sum_x)

    for size in range(max_size):
        for i in range(size + 1):
            for j in range(size + 1):
                field_copy[corn_y + i][corn_x + j] = square_number
        square = backtracking(field_copy, square, square_number + 1)

    return square


def square_creator(square_size):  # fill the field with three squares (optimization)
    square_field = []
    for i in range(square_size):
        square_field.append([])
        for j in range(square_size):
            if (i <= (square_size // 2)) and (j <= (square_size // 2)):
                square_field[i].append(1)
            elif (i > (square_size // 2)) and j < square_size // 2:
                square_field[i].append(2)
            elif (i < (square_size // 2)) and (j > square_size // 2):
                square_field[i].append(3)
            else:
                square_field[i].append(0)

    return square_field


def formatted_output(square):
    cnt_of_squares = list(range(1, square[0] + 1))
    res = []
    for i in range(len(square[1])):
        for j in range(len(square[1])):
            if square[1][i][j] in cnt_of_squares:
                res.append([i + 1, j + 1, square[1][i].count(square[1][i][j])])
                cnt_of_squares.remove(square[1][i][j])

    return res


def find_square(square_size, square):
    square_field = square_creator(square_size)
    square = backtracking(square_field, square, 4)

    return formatted_output(square), square[0]


def divisor_is_three(square_size, square):
    res, min_cnt = find_square(3, square)

    for i in range(len(res)):
        res[i][0] = (res[i][0] - 1) * (square_size // 3) + 1
        res[i][1] = (res[i][1] - 1) * (square_size // 3) + 1
        res[i][2] = res[i][2] * (square_size // 3)

    return res, min_cnt


def begin(N):
    min_cnt = N * N  # part's len is 1x1
    square = [min_cnt, [[]]]
    res = []

    if N % 2 == 0:  # Size of square is even
        res, min_cnt = even(N, res)

    elif N % 3 == 0 and N > 3:  # divisor is three
        res, min_cnt = divisor_is_three(N, square)

    else:  # prime numbers (простые)
        res, min_cnt = find_square(N, square)

    return res, min_cnt


def main():
    N = int(input())
    res, cnt = begin(N)
    print(cnt)
    for i in range(cnt):
        print(*res[i], sep=' ')


if __name__ == '__main__':
    main()
