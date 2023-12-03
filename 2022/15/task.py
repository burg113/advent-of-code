def task1(in_lines):
    check_height = 2000000
    checked_on_height = set()

    for line in in_lines:
        sensor, beacon = line
        dist = abs(sensor[0] - beacon[0]) + abs(sensor[1] - beacon[1])
        amount = dist - abs(sensor[1] - check_height) + 1

        for x in range(amount):
            if (sensor[0] + x) not in checked_on_height:
                checked_on_height.add(sensor[0] + x)
                # print(len(checked_on_height))

            if (sensor[0] - x) not in checked_on_height:
                checked_on_height.add(sensor[0] - x)
                # print(len(checked_on_height))
    for line in in_lines:
        sensor, beacon = line

        if beacon[1] == check_height and beacon[0] in checked_on_height:
            print("hi")
            checked_on_height.remove(beacon[0])
    for i in range(-10, 100):
        if i in checked_on_height:
            print("#", end="")
        else:
            print(".", end="")
    print()
    return len(checked_on_height)


def task2(in_lines):
    field_size = 4000000
    data = []

    for line in in_lines:
        sensor, beacon = line
        dist = abs(sensor[0] - beacon[0]) + abs(sensor[1] - beacon[1])
        data.append([sensor, dist])

    pos = [0, 0]
    while True:
        skip = True
        for point in data:
            p, dist = point
            x, y = p

            amount = dist - abs(y - pos[1])
            if amount > 0 and x - amount <= pos[0] <= x + amount:
                # print("#", pos, point, amount, "set to", x + amount + 1)
                # print("--",dist, abs(y - pos[1]))
                pos[0] = x + amount + 1
                if pos[0] > field_size:
                    pos[0] = 0
                    pos[1] += 1
                    print(pos[1])
                skip = False
                break

        if skip:
            return pos


def main():
    with open("input.txt", "r") as f:
        lines = []
        for line in f.readlines():
            line = line.replace("\n", "").replace("Sensor at", "").replace("closest beacon is at", "")
            line = line.replace("x=", "").replace("y=", "")
            line = line.split(":")
            for i, part in enumerate(line):
                line[i] = [int(num) for num in part.split(",")]
            lines.append(line)
        print("result1:", task1(lines))
        print("#" * 100)
        # tales roughly (3 min run in terminal)
        print("result2:", task2(lines))


if __name__ == "__main__":
    main()
