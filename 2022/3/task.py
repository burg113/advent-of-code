def task1(in_lines):
    sum = 0
    for line in in_lines:
        first_falf = line[:int(len(line) / 2)]
        second_half = line[int(len(line) / 2):]
        for c in first_falf:
            if c in second_half:
                n = ord(c) - 38 if ord(c) < 95 else ord(c) - 96
                print(c, n)
                sum += n
                break

    return sum


def task2(in_lines):
    sum = 0
    current_elf_num = 0
    chars = ""
    for line in in_lines:
        if current_elf_num == 0:
            chars = line
        else:
            new_chars = ""
            for c in line:
                if c in chars:
                    new_chars += c
            chars = new_chars

        if current_elf_num == 2:
            c = chars[0]
            n = ord(c) - 38 if ord(c) < 95 else ord(c) - 96
            print(c,n)
            sum += n

            current_elf_num = 0
        else:
            current_elf_num += 1

    return sum


def main():
    with open("input.txt", "r") as f:
        lines = [line.replace("\n", "") for line in f.readlines()]

        print("result1:", task1(lines))
        print("#" * 100)
        print("result2:", task2(lines))


if __name__ == "__main__":
    main()
