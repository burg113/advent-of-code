def task1(monkeys):
    inspected_count = []
    for i in range(len(monkeys)):
        inspected_count.append(0)
    for i in range(20):
        print("-" * 100)
        for i, monkey in enumerate(monkeys):
            items, formula, check = monkey
            check, where = check
            monkey[0] = []

            for worry_level in items:
                inspected_count[i] += 1
                new_worry_level = int(eval(formula.replace("old", str(worry_level))) / 3)
                pass_to = where[int(not new_worry_level % check == 0)]
                monkeys[pass_to][0].append(new_worry_level)
        for m in monkeys:
            print(m)

    highest = max(inspected_count)
    inspected_count.remove(highest)
    second_highest = max(inspected_count)

    return highest * second_highest


def task2(monkeys):
    sum_of_conditions = 1
    for monkey in monkeys:
        sum_of_conditions *= monkey[2][0]

    inspected_count = []
    for i in range(len(monkeys)):
        inspected_count.append(0)
    for i in range(10000):
        """print(f"inspected {i}",inspected_count)
        print("-" * 100)"""
        for i, monkey in enumerate(monkeys):
            items, formula, check = monkey
            check, where = check
            monkey[0] = []

            for worry_level in items:
                inspected_count[i] += 1
                new_worry_level = eval(formula.replace("old", str(worry_level))) % sum_of_conditions
                pass_to = where[int(not new_worry_level % check == 0)]
                monkeys[pass_to][0].append(new_worry_level)
        """for m in monkeys:
            print(m)"""

    print(inspected_count)

    highest = max(inspected_count)
    inspected_count.remove(highest)
    second_highest = max(inspected_count)

    return highest * second_highest


def parse(lines):
    curr = -1
    data = []
    for line in lines:
        if line == "":
            pass
        else:
            if "Monkey " in line:
                curr += 1
                data.append([])

            else:
                header, content = line.split(":")
                if header.strip() == "Starting items":
                    data[curr].append([int(e) for e in content.split(", ")])
                elif header.strip() == "Operation":
                    data[curr].append(content.split(" = ")[1])
                elif header.strip() == "Test":
                    data[curr].append([int(content.replace(" divisible by ", "")), []])
                else:
                    data[curr][len(data[curr]) - 1][1].append(int(content.split(" ")[-1]))

    for d in data:
        print(d)

    return data


def main():
    with open("input.txt", "r") as f:
        lines = [line.replace("\n", "") for line in f.readlines()]
        parsed = parse(lines)

        parsed2 = parse(lines)

        print("result1:", task1(parsed))
        print("#" * 100)
        print("result2:", task2(parsed2))


if __name__ == "__main__":
    main()
