def highest(arr: list, x: int, y: int, dx: int, dy: int, offset=0) -> int:
    m = -1
    for i in range(offset):
        x += dx
        y += dy

    while True:
        if x < 0 or y < 0 or x >= len(arr[0]) or y >= len(arr):
            return m

        m = max(m, int(arr[y][x]))
        x += dx
        y += dy


def viewing_dist(arr: list, x: int, y: int, dx: int, dy: int) -> int:
    start_height = int(arr[y][x])
    m = 0
    x += dx
    y += dy

    while True:
        if x < 0 or y < 0 or x >= len(arr[0]) or y >= len(arr):
            return m

        if int(arr[y][x]) >= start_height:
            return m + 1

        m += 1
        x += dx
        y += dy


def task1(in_lines):
    count = 0
    for y in range(len(in_lines)):
        for x in range(len(in_lines[0])):
            current_height = int(in_lines[y][x])
            lowest_height = min(highest(in_lines, x, y, 1, 0, 1),
                                highest(in_lines, x, y, 0, 1, 1),
                                highest(in_lines, x, y, -1, 0, 1),
                                highest(in_lines, x, y, 0, -1, 1))

            if current_height > lowest_height:
                count += 1

    return count


def task2(in_lines):
    best = (-1, -1)
    best_score = -1
    for y in range(len(in_lines)):
        for x in range(len(in_lines[0])):
            current_score = viewing_dist(in_lines, x, y, 1, 0) * viewing_dist(in_lines, x, y, 0, 1)
            current_score *= viewing_dist(in_lines, x, y, -1, 0) * viewing_dist(in_lines, x, y, 0, -1)

            if current_score > best_score:
                best_score = current_score
                best = (x, y)

    return best_score, best


def main():
    with open("input.txt", "r") as f:
        lines = [list(line.replace("\n", "")) for line in f.readlines()]
        for line in lines:
            print(line)

        print(highest(lines, 0, 0, -1, 0))

        print("result1:", task1(lines))
        print("#" * 100)
        print("result2:", task2(lines))


if __name__ == "__main__":
    main()
