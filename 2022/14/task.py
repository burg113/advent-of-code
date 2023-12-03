import array

START_POINT = (500, 0)


def debug_field(field: list, width: int):
    deb = []
    for i, e in enumerate(field):
        if i % width == 0:
            print()
        if e == 0:
            print(".", end="")

        if e == 1:
            print("#", end="")
            deb.append(i)

        if e == 2:
            print("o", end="")
    print()
    print(deb)


def parse(lines) -> dict:
    field = array.array("i", [0] * (200 * 400))
    print("%", len(field))
    points = []
    for line in lines:
        points.append([c.split(",") for c in line.split(" -> ")])
    for line in points:
        for i in range(len(line) - 1):
            x1, y1 = line[i]
            x2, y2 = line[i + 1]
            x1, x2, y1, y2 = int(x1), int(x2), int(y1), int(y2)

            if x1 == x2:
                direction = (y2 - y1) / abs(y2 - y1)
                for i2 in range(abs(y1 - y2) + 1):
                    x, y = x1, y1 + i2 * direction
                    field[int(x - 300 + y * 400)] = 1
            elif y1 == y2:
                direction = (x2 - x1) / abs(x2 - x1)
                for i2 in range(abs(x1 - x2) + 1):
                    x, y = x1 + i2 * direction, y1
                    field[int(x - 300 + y * 400)] = 1

            else:
                raise Exception("code should not reach")

    return field


def task1(field):
    count = 0
    while True:
        count += 1

        curr_sand = (START_POINT[0] - 300) + START_POINT[1] * 400

        #
        #         debug_field(field,400)

        while True:
            curr_sand += 400

            if curr_sand > 80000:
                debug_field(field, 400)
                return count - 1

            # print(curr_sand)
            # print(field[curr_sand])

            if field[curr_sand] > 0:
                left = curr_sand - 1
                right = curr_sand + 1
                if field[left] == 0:
                    curr_sand = left
                    continue
                if field[right] == 0:
                    curr_sand = right
                    continue
                field[curr_sand - 400] = 2
                break


def task2(field):
    lowest = 0
    for i, e in enumerate(field):
        if e == 1:
            lowest = max(lowest, int(i / 400))
    print("lowest", lowest)
    count = 0

    # width 400
    # height 200
    while field[200] == 0:
        count += 1
        print(count)
        curr_sand = 200

        # print()
        # debug_field(450, 0, 100, 20, stones, sand)
        while True:  # field[curr_sand] == 0
            curr_sand += 400
            # print(curr_sand, curr_sand / 400, lowest + 1)
            if field[curr_sand] != 0:
                left = curr_sand - 1
                right = curr_sand + 1
                if field[left] == 0:
                    curr_sand = left
                    continue
                if field[right] == 0:
                    curr_sand = right
                    continue

                field[curr_sand - 400] = 2
                break
            if curr_sand / 400 > lowest + 2:
                field[curr_sand - 400] = 2
                break

    debug_field(field, 400)
    return count


def main():
    # f = open('output.txt', 'w')
    # sys.stdout = f
    with open("input.txt", "r") as f:
        lines = [line.replace("\n", "") for line in f.readlines()]

        input_data = parse(lines)
        # debug_field(input_data,400)

        print()
        print("result1:", task1(input_data))

        print("#" * 200)

        input_data = parse(lines)

        print("result2:", task2(input_data))


if __name__ == "__main__":
    main()
