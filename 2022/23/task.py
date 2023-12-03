def parse(file):
    lines = [line.replace("\n", "") for line in file.readlines()]
    out_set = set()
    for y, line in enumerate(lines):
        for x, e in enumerate(line):
            if e == "#":
                out_set.add((x, y))

    return out_set


directions = [(0, -1), (1, -1), (1, 0), (1, 1), (0, 1), (-1, 1), (-1, 0), (-1, -1)]


def task1(in_lines: set):
    elf_pos_set = in_lines
    elf_move_priorities = [0, 2, 3, 1]
    for pos in elf_pos_set:
        print(pos)
    """print("initial:")
    for y in range(-3, 12):
        for x in range(-3, 12):
            if (x, y) in elf_pos_list:
                print("#", end="")
            else:
                print(".", end="")
        print()
    print()"""
    # simulate 10 turns
    for _ in range(10):
        # plan move
        moves = {}
        move_indices = {}
        duplicates = set()
        for elf_index, pos in enumerate(elf_pos_set):
            elfs = [0 for _ in range(8)]
            for i, direction in enumerate(directions):
                n_pos = (direction[0] + pos[0], direction[1] + pos[1])
                if n_pos in elf_pos_set:
                    elfs[i] = 1
                    # print("y", end="")
                # print(n_pos)
            # print(elfs)
            if 1 not in elfs:
                # print("no elfs near", pos)
                continue
            for i in elf_move_priorities:
                if elfs[i * 2 - 1] == 0 and elfs[i * 2] == 0 and elfs[i * 2 + 1] == 0:
                    new_pos = (directions[i * 2][0] + pos[0], directions[i * 2][1] + pos[1])
                    if new_pos in moves.values():
                        duplicates.add(new_pos)
                        # print("duplicate:")
                    moves[pos] = new_pos
                    move_indices[pos] = i
                    # print("move", pos, new_pos)
                    break
            else:
                pass
                # print("cannot move", pos)
        print("executing")
        # execute moves
        for pos, new_pos in moves.items():
            # print("looking at", pos, new_pos)
            if new_pos not in duplicates:
                elf_pos_set.remove(pos)
                elf_pos_set.add(new_pos)

        """for y in range(-3, 12):
            for x in range(-3, 12):
                if (x, y) in elf_pos_list:
                    print("#", end="")
                else:
                    print(".", end="")
            print()
        print()"""

        first = elf_move_priorities[0]
        elf_move_priorities.remove(first)
        elf_move_priorities.append(first)

    highest, lowest, right, left = 0, 0, 0, 0
    for pos in elf_pos_set:
        highest = max(pos[1], highest)
        lowest = min(pos[1], lowest)
        right = max(pos[0], right)
        left = min(pos[0], left)

    print("x", left, right)
    print("y", lowest, highest)
    return (right - left + 1) * (highest - lowest + 1) - len(elf_pos_set)


def task2(in_lines):
    elf_pos_set = in_lines
    elf_move_priorities = [0, 2, 3, 1]
    for pos in elf_pos_set:
        print(pos)

    count = 0
    # simulate 10 turns
    while True:
        count +=1
        # plan move
        moves = {}
        move_indices = {}
        duplicates = set()
        for elf_index, pos in enumerate(elf_pos_set):
            elfs = [0 for _ in range(8)]
            for i, direction in enumerate(directions):
                n_pos = (direction[0] + pos[0], direction[1] + pos[1])
                if n_pos in elf_pos_set:
                    elfs[i] = 1
                    # print("y", end="")
                # print(n_pos)
            # print(elfs)
            if 1 not in elfs:
                # print("no elfs near", pos)
                continue
            for i in elf_move_priorities:
                if elfs[i * 2 - 1] == 0 and elfs[i * 2] == 0 and elfs[i * 2 + 1] == 0:
                    new_pos = (directions[i * 2][0] + pos[0], directions[i * 2][1] + pos[1])
                    if new_pos in moves.values():
                        duplicates.add(new_pos)
                        # print("duplicate:")
                    moves[pos] = new_pos
                    move_indices[pos] = i
                    # print("move", pos, new_pos)
                    break
            else:
                pass
                # print("cannot move", pos)
        # print("executing")
        # execute moves
        moved = False
        for pos, new_pos in moves.items():
            # print("looking at", pos, new_pos)
            if new_pos not in duplicates:
                elf_pos_set.remove(pos)
                elf_pos_set.add(new_pos)
                moved = True
        if not moved:
            print("finished at round",count)
            return count

        first = elf_move_priorities[0]
        elf_move_priorities.remove(first)
        elf_move_priorities.append(first)


def main():
    with open("input.txt", "r") as f:
        data = parse(f)
    with open("input.txt", "r") as f:
        data2 = parse(f)
    print("result1:", task1(data))
    print("#" * 100)
    print("result2:", task2(data2))


if __name__ == "__main__":
    main()
