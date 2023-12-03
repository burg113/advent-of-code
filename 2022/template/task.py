def parse(file):
    lines = [line.replace("\n", "") for line in file.readlines()]
    return lines


def task1(in_lines):
    pass


def task2(in_lines):
    pass


def main():
    with open("input.txt", "r") as f:
        data = parse(f)

    print("result1:", task1(data))
    print("#" * 100)
    print("result2:", task2(data))


if __name__ == "__main__":
    main()
