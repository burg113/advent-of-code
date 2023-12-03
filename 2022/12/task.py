# -14 = start
# -28 = end
import sys

directions = [(1, 0), (0, 1), (-1, 0), (0, -1)]


def task1(in_lines):
    for line in in_lines:
        print(line)

    # note:
    #   already checked = 0
    #   not checked = 1
    #   active = 2
    #   active next turn 3

    x_size, y_size = len(in_lines[0]), len(in_lines)
    sy, sx = None, None
    ty, tx = None, None
    checked_map = []
    for y, line in enumerate(in_lines):
        checked_map.append([])
        for x, index in enumerate(line):
            checked_map[y].append(1)
            if index == -14:
                sx = x
                sy = y
                in_lines[y][x] = 0
            if index == -28:
                tx = x
                ty = y
                in_lines[y][x] = 26

    checked_map[sy][sx] = 2

    count = 0
    while True:
        if checked_map[ty][tx] == 2:
            break
        count += 1
        for x in range(x_size):
            for y in range(y_size):
                if checked_map[y][x] == 2:

                    checked_map[y][x] = 0
                    for direction in directions:
                        dy, dx = direction
                        if 0 <= y + dy < y_size and 0 <= x + dx < x_size and \
                                in_lines[y + dy][x + dx] - in_lines[y][x] <= 1 \
                                and checked_map[y + dy][x + dx] == 1:
                            checked_map[y + dy][x + dx] = 3

        changed = False
        for x in range(x_size):
            for y in range(y_size):
                if checked_map[y][x] == 3:
                    checked_map[y][x] = 2
                    changed = True

        if not changed:
            return -1

    return count


def task2(in_lines):

    # note:
    #   already checked = 0
    #   not checked = 1
    #   active = 2
    #   active next turn 3

    x_size, y_size = len(in_lines[0]), len(in_lines)
    sy, sx = None, None
    ty, tx = None, None
    checked_map = []
    for y, line in enumerate(in_lines):
        checked_map.append([])
        for x, index in enumerate(line):
            checked_map[y].append(1)
            if index == -14:
                sx = x
                sy = y
                in_lines[y][x] = 0
                checked_map[y][x] = 1
            if index == -28:
                tx = x
                ty = y
                in_lines[y][x] = 26

            if index == 0:
                checked_map[y][x] = 2

    print(sx, sy)
    checked_map[sy][sx] = 2

    count = 0
    while True:
        if checked_map[ty][tx] == 2:
            break
        count += 1
        for x in range(x_size):
            for y in range(y_size):
                if checked_map[y][x] == 2:

                    checked_map[y][x] = 0
                    for direction in directions:
                        dy, dx = direction
                        if 0 <= y + dy < y_size and 0 <= x + dx < x_size and \
                                in_lines[y + dy][x + dx] - in_lines[y][x] <= 1 \
                                and checked_map[y + dy][x + dx] == 1:
                            checked_map[y + dy][x + dx] = 3

        changed = False
        for x in range(x_size):
            for y in range(y_size):
                if checked_map[y][x] == 3:
                    checked_map[y][x] = 2
                    changed = True

        if not changed:
            return -1

    return count


def main():
    with open("input.txt", "r") as f:
        lines = [line.replace("\n", "") for line in f.readlines()]
        input_lines = []
        for line in lines:
            input_line = []
            for c in line:
                input_line.append(ord(c) - 97)
            input_lines.append(input_line)

        print("result1:", task1(input_lines))
        print("#" * 100)

        input_lines = []
        for line in lines:
            input_line = []
            for c in line:
                input_line.append(ord(c) - 97)
            input_lines.append(input_line)

        print("result2:", task2(input_lines))


if __name__ == "__main__":
    main()
