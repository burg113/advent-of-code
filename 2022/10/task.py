check_on_clocks = [20, 60, 100, 140, 180, 220]


def task1(in_lines):
    register_val = 1
    out_list = []
    cylce = 1
    for line in in_lines:
        if cylce in check_on_clocks:
            out_list.append(register_val)
        if line == "noop":
            cylce += 1

        elif "addx" in line:
            val = int(line.replace("addx ", ""))
            cylce += 1
            if cylce in check_on_clocks:
                out_list.append(register_val)
            cylce += 1
            register_val += val

    s = [out_list[i] * check_on_clocks[i] for i in range(len(check_on_clocks))]

    return out_list, s, sum(s)


def task2(in_lines):
    register_val = 1
    val_list = []
    cylce = 1
    for line in in_lines:
        val_list.append(register_val)
        if line == "noop":
            cylce += 1

        elif "addx" in line:
            val = int(line.replace("addx ", ""))
            cylce += 1
            val_list.append(register_val)
            cylce += 1
            register_val += val

    crt_output = ["#" if abs(val_list[i] - i % 40) <= 1 else "." for i in range(cylce - 1)]
    crt_output = "\n" + "\n".join([''.join(crt_output[i:i + 40]) for i in range(0, cylce - 1, 40)])

    return crt_output


def main():
    with open("input.txt", "r") as f:
        lines = [line.replace("\n", "") for line in f.readlines()]

        print("result1:", task1(lines))
        print("#" * 100)
        print("result2:", task2(lines))


if __name__ == "__main__":
    main()
