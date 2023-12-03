import math


def parse(file):
    lines = [line.replace("\n", "") for line in file.readlines()]
    return lines


def task1(in_lines):
    decimals = []
    for line in in_lines:
        decimals.append(
            sum([e * 5 ** i for i, e in
                 enumerate(reversed([-2 if c == "=" else (-1 if c == "-" else int(c)) for c in line]))]))
    s = sum(decimals)

    base5_digits = [int((s % (5 ** (i + 1)) / (5 ** i))) for i in range(math.ceil(math.log(s, 5)))]

    print(base5_digits)
    snafu = []

    carry = 0
    for digit in base5_digits:
        print(digit,carry)
        digit += carry
        carry = 0
        if digit + carry >= 3:
            print("hi")
            carry = 1
            digit -= 5
        print("->",digit)
        if digit == -1:
            snafu.append("-")
        elif digit == -2:
            snafu.append("=")
        else:
            snafu.append(str(digit))
    snafu.reverse()
    return "".join(snafu)


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
