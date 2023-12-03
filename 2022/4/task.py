def task1(in_lines):
    count = 0
    for line in in_lines:
        interval1, interval2 = line.split(",")
        a, b = [int(x) for x in interval1.split("-")]
        c, d = [int(x) for x in interval2.split("-")]

        if (a <= c and b >= d) or (a >= c and b <= d):
            print(interval1, interval2)
            count += 1

    return count


def task2(in_lines):
    count = 0
    for line in in_lines:
        interval1, interval2 = line.split(",")
        a, b = [int(x) for x in interval1.split("-")]
        c, d = [int(x) for x in interval2.split("-")]

        if (a <= c <= b) or (a <= d <= b) or (c <= a <= d) or (c <= b <= d):
            print(interval1, interval2)
            count += 1

    return count


def main():
    with open("input.txt", "r") as f:
        lines = [line.replace("\n", "") for line in f.readlines()]

        print("result1:", task1(lines))
        print("#" * 100)
        print("result2:", task2(lines))


if __name__ == "__main__":
    main()
