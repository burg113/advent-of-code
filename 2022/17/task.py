import array

PIECES = [((0, 0), (1, 0), (2, 0), (3, 0)),  # -
          ((0, 1), (1, 2), (1, 1), (1, 0), (2, 1)),  # +
          ((0, 0), (1, 0), (2, 0), (2, 1), (2, 2)),  # L
          ((0, 0), (0, 1), (0, 2), (0, 3)),  # I
          ((0, 0), (1, 0), (1, 1), (0, 1))]  # #

BITMASKS = [64, 32, 16, 8, 4, 2, 1]


def print_field(field: array, current_piece=None, current_piece_offset=None):
    lines = []
    empty_line_count = 0
    for line in field:
        curr = "|"
        # print("{0:b}".format(line))
        for i in range(len(BITMASKS) - 1, -1, -1):
            # print(i,(line >> i) & 1)
            curr += "#" if line & BITMASKS[i] else "."
        curr += "|"
        lines.append(curr)
        if line == 0:
            empty_line_count += 1
            if empty_line_count > 10:
                break

    # print the current piece
    if current_piece is not None:
        for piece in current_piece:
            x, y = piece
            x += current_piece_offset[0]
            y += current_piece_offset[1]
            # print(y)
            lines[y] = lines[y][:x + 1] + "P" + lines[y][x + 2:]

    lines.reverse()

    for line in lines:
        print(line)
    print("-" * 11)


def collides(rock: tuple, offset: list, field: array, check_sides=True, check_bottom=True, check_collision=True):
    for vertex in rock:
        x, y = vertex
        x += offset[0]
        y += offset[1]
        # print(y)
        if check_sides and not (0 <= x < len(BITMASKS)):
            return True
        if check_bottom and y < 0:
            return True
        if check_collision and (field[y] & BITMASKS[x]):
            return True
    return False


def task1(instructions):
    rocks_fallen_goal = 2022
    height_upper_bound = 4000
    turn = 0
    rocks_fallen = 0
    highest_level = 0
    field = array.array("b", [0] * height_upper_bound)

    current_rock = PIECES[0]
    current_rock_offset = [2, 3]
    print("starting:")
    print_field(field, current_rock, current_rock_offset)
    while True:
        print("-" * 20, turn, "-" * 20)
        instruction = instructions[turn % len(instructions)]

        # push
        # print("moving", instruction)
        current_rock_offset[0] += instruction
        if collides(current_rock, current_rock_offset, field, check_bottom=False):
            # print("not moving")
            current_rock_offset[0] -= instruction

        # print_field(field, current_rock, current_rock_offset)

        # falling
        current_rock_offset[1] -= 1

        # print("falling 1")

        if current_rock_offset[1] <= highest_level and collides(current_rock, current_rock_offset, field,
                                                                check_sides=False):
            # print("does not fall!")
            current_rock_offset[1] += 1

            # setting new highest level and adding to field
            highest_vertex = 0
            for vertex in current_rock:
                x, y = vertex
                x += current_rock_offset[0]
                y += current_rock_offset[1]
                # print(x, BITMASKS[x], end=",")
                # print(field, BITMASKS)
                field[y] += BITMASKS[x]

                highest_vertex = max(highest_vertex, y)

            print("highest: ", highest_level, highest_vertex)
            highest_level = max(highest_level, highest_vertex)

            rocks_fallen += 1
            print("rocks fallen", rocks_fallen)
            print(rocks_fallen)
            if rocks_fallen == rocks_fallen_goal:
                print_field(field)
                return highest_level + 1

            current_rock = PIECES[rocks_fallen % len(PIECES)]
            current_rock_offset = [2, 4 + highest_level]
            print("after placing:")

        # print_field(field, current_rock, current_rock_offset)

        turn += 1


def task2(instructions):
    rocks_fallen_goal = 10 ** 12
    array_size = 2000
    turn = 0
    rocks_fallen = 0
    highest_level = 0
    field = array.array("b", [0] * array_size)

    lookup = {}
    current_rock = PIECES[0]
    current_rock_offset = [2, 3]

    y_offset = 0
    skipped = False
    while True:

        # print("-" * 20, turn, "-" * 20)
        instruction = instructions[turn % len(instructions)]

        # push
        # print("moving", instruction)
        current_rock_offset[0] += instruction
        if collides(current_rock, current_rock_offset, field):
            # print("not moving")
            current_rock_offset[0] -= instruction

        # print_field(field, current_rock, current_rock_offset)

        # falling
        current_rock_offset[1] -= 1

        # print("falling 1")
        last_break = []
        if collides(current_rock, current_rock_offset, field):
            # print("does not fall!")
            current_rock_offset[1] += 1

            # setting new highest level and adding to field
            highest_vertex = 0
            cut_off = 0
            # print_field(field,current_rock,current_rock_offset)
            for vertex in current_rock:
                x, y = vertex
                x += current_rock_offset[0]
                y += current_rock_offset[1]
                # print(x, BITMASKS[x], end=",")
                # print(field, BITMASKS)
                field[y] += BITMASKS[x]

                highest_vertex = max(highest_vertex, y)

                if field[y] == 127:
                    cut_off = y
            if cut_off != 0:
                # print("before cut-of")
                # print()
                # print_field(field)
                highest_level = max(highest_level, highest_vertex) - cut_off - 1

                y_offset += cut_off + 1
                # print(y_offset)
                keep = []
                # t1 = time.time()
                for i in range(cut_off + 1):
                    field[i] = 0

                for i in range(cut_off + 1, array_size):
                    if field[i] == 0:
                        break
                    keep.append(field[i])
                    field[i] = 0

                h = (rocks_fallen % len(PIECES), turn % len(instructions), tuple(keep)).__hash__()
                # only allow one skip as that should be enough
                if h in lookup.keys() and not skipped:
                    skipped = True
                    last_y_offset, last_rocks_fallen = lookup[h]
                    y_offset_diff = y_offset - last_y_offset
                    rocks_fallen_diff = rocks_fallen - last_rocks_fallen
                    skip_times = int((rocks_fallen_goal - rocks_fallen) / rocks_fallen_diff)

                    print(f"found loop of length: {rocks_fallen_diff}; {y_offset_diff} lines")
                    print(f"skipping forward {skip_times} times")
                    rocks_fallen += rocks_fallen_diff * skip_times
                    y_offset += y_offset_diff * skip_times
                    print(f"continuing from {rocks_fallen} at line {y_offset}")

                lookup[h.__hash__()] = (y_offset, rocks_fallen)

                for i, val in enumerate(keep):
                    field[i] = val

                # print("after cut-of")
                # print("highest", highest_level)
                # print_field(field)
                # print("took ", time.time() - t1)
            # print("highest: ", highest_level, highest_vertex)
            else:
                highest_level = max(highest_level, highest_vertex)

            rocks_fallen += 1
            # print("rocks fallen", rocks_fallen)
            # print(rocks_fallen)
            if rocks_fallen == rocks_fallen_goal:
                # print_field(field)
                return highest_level + 1 + y_offset

            current_rock = PIECES[rocks_fallen % len(PIECES)]
            current_rock_offset = [2, 4 + highest_level]
            # print("after placing:")

        # print_field(field, current_rock, current_rock_offset)

        turn += 1


def main():
    with open("input.txt", "r") as f:
        instructions = [1 if c == ">" else -1 for c in f.readline()]

        print("result1:", task1(instructions))
        print("#" * 100)
        print("result2:", task2(instructions))


if __name__ == "__main__":
    main()
