import array


def parse(file):
    lines = [line.replace("\n", "") for line in file.readlines()]
    field = []
    for line in lines[:-2]:
        row = []
        for c in line:
            if c == " ":
                row.append(-1)
            elif c == ".":
                row.append(0)
            elif c == "#":
                row.append(1)
            else:
                raise Exception("code shouldn't reach")
        field.append(row)
    longest = 0
    for row in field:
        longest = max(len(row), longest)

    for row in field:
        row += [-1] * (longest - len(row))
    field_arr = []
    for row in field:
        field_arr += row
    print(field_arr)
    field_arr = array.array("i", field_arr)

    instruction_line = lines[-1]
    instructions = []
    while "R" in instruction_line or "L" in instruction_line:
        m = []
        if "R" in instruction_line:
            m.append(instruction_line.index("R"))
        if "L" in instruction_line:
            m.append(instruction_line.index("L"))
        n = min(m)

        instructions.append(int(instruction_line[:n]))
        instructions.append((instruction_line[n] == "R") - 2)
        instruction_line = instruction_line[n + 1:]
    instructions.append(int(instruction_line))
    print(instructions)
    return field_arr, longest, instructions


def rotate(side: list, size: int, amount_clockwise=1):
    new_side = [[[] for i2 in range(size)] for i in range(size)]
    if amount_clockwise == 1:
        for y, row in enumerate(side):
            for x, e in enumerate(row):
                new_side[x][size - y - 1] = e
        return new_side

    for i in range(amount_clockwise):
        side = rotate(side, size)
    return side


movement_dict = {
    0: [(2, 1), (1, 1), (4, 1), (3, 1)],
    1: [(2, 0), (5, 3), (4, 2), (0, 3)],
    2: [(3, 0), (5, 0), (1, 2), (0, 2)],
    3: [(4, 0), (5, 1), (2, 2), (0, 1)],
    4: [(1, 0), (5, 2), (3, 2), (0, 0)],
    5: [(4, 3), (1, 3), (2, 3), (3, 3)]
}


def parse_cube(file, size=50):
    lines = [line.replace("\n", "") for line in file.readlines()]
    cube_net = [[[] for i in range(4)] for i2 in range(4)]
    cube = [None for i in range(6)]
    current_side = []
    current_h = 0
    for i, line in enumerate(lines[:-2]):
        row = []
        if i % size == 0:
            current_h = int(i / size)
        for i2, c in enumerate(line):
            if i2 % size == 0:
                if len(row) > 0:
                    current_side.append(row)
                current_side = cube_net[current_h][int(i2 / size)]
                row = []
            if c == " ":
                continue
            elif c == ".":
                row.append(0)
            elif c == "#":
                row.append(1)
            else:
                raise Exception("code shouldn't reach")

        if len(row) > 0:
            current_side.append(row)

    instruction_line = lines[-1]
    instructions = []
    while "R" in instruction_line or "L" in instruction_line:
        m = []
        if "R" in instruction_line:
            m.append(instruction_line.index("R"))
        if "L" in instruction_line:
            m.append(instruction_line.index("L"))
        n = min(m)

        instructions.append(int(instruction_line[:n]))
        instructions.append((instruction_line[n] == "R") - 2)
        instruction_line = instruction_line[n + 1:]
    instructions.append(int(instruction_line))

    for y, row in enumerate(cube_net):
        for x, e in enumerate(row):
            print(len(e), end="\t")
        print()

    # hardcoded for my input mesh form: 0 - top; 1234 - sides counter_clockwise; 5 bottom
    cube[0] = cube_net[0][1]
    cube[1] = cube_net[1][1]
    cube[2] = rotate(cube_net[0][2], 50, 1)
    cube[3] = rotate(cube_net[3][0], 50, 1)
    cube[4] = rotate(cube_net[2][0], 50, 1)
    cube[5] = rotate(cube_net[2][1], 50, 2)
    for i, side in enumerate(cube):
        print(i)
        a = []
        for row in side:
            a += row
        print_field(a, 50)
        print(("#" * 100 + "\n") * 5)

    return cube, size, instructions


p_lookup = [">", "v", "<", "^"]


def print_field(field_arr, line_length, path=None, player_pos=None):
    field = [field_arr[i: i + line_length] for i in range(0, len(field_arr), line_length)]

    for y, row in enumerate(field):
        for x, e in enumerate(row):
            printed = False
            if player_pos is not None and player_pos == y * line_length + x:
                print("#", end="")
                printed = True

            if path is not None and not printed:
                in_path = False
                for t in path:
                    facing, pos = t
                    if pos == y * line_length + x:
                        print(p_lookup[facing], end="")
                        printed = True
                        break

            if not printed:
                if e == -1:
                    print(" ", end="")

                if e == 0:
                    print(".", end="")

                if e == 1:
                    print("#", end="")

        print()


# -2 == L
# -1 == R
def task1(data):
    path = []
    field, line_length, instruction_line = data
    field_size = len(field)

    print_field(field, line_length)
    facing = 0
    move_by = 1
    pos = 0
    for i, e in enumerate(field):
        if e == 0:
            pos = i
            break
    for instruction in instruction_line:
        # move
        if instruction > 0:
            print("x:", pos % line_length, "y:", int(pos / line_length))
            print(instruction, facing)
            for _ in range(instruction):
                new_pos = pos + move_by
                wrap_x = abs(move_by) == 1
                new_pos = (new_pos + field_size) % field_size
                if wrap_x and int(new_pos / line_length) > int(pos / line_length):
                    new_pos -= line_length
                if wrap_x and int(new_pos / line_length) < int(pos / line_length):
                    new_pos += line_length
                while field[new_pos] == -1:
                    print(new_pos, field[new_pos], move_by)
                    new_pos += move_by
                    new_pos = (new_pos + field_size) % field_size
                    if wrap_x and int(new_pos / line_length) > int(pos / line_length):
                        new_pos -= line_length
                    if wrap_x and int(new_pos / line_length) < int(pos / line_length):
                        new_pos += line_length
                    print(new_pos, field[new_pos], move_by)
                # prevent moving into wall
                if field[new_pos] == 1:
                    print("blocked by wall at:", "x:", new_pos % line_length, "y:", int(new_pos / line_length))
                    break
                pos = new_pos
                path.append((facing, pos))
            # print_field(field, line_length, path,pos)
        # rotate
        elif instruction < 0:
            facing += (instruction + 1) * 2 + 1
            facing = (facing + 4) % 4
            if facing == 3: move_by = -line_length
            if facing == 0: move_by = 1
            if facing == 1: move_by = line_length
            if facing == 2: move_by = -1
        else:
            raise Exception("Code shouldn't reach")
    print(path)
    print("pos:", pos)
    x, y = pos % line_length + 1, int(pos / line_length) + 1
    print("x:", x, "y:", y)
    print("facing:", facing)
    return 1000 * y + 4 * x + facing


def task2(data):
    cube, line_length, instruction_line = data

    facing = 0
    move_by = (1, 0)
    current_face = cube[0]
    current_face_index = 0
    pos = [0, 0]

    for instruction in instruction_line:
        # move
        if instruction > 0:

            for _ in range(instruction):
                # move
                new_face_index, new_face = current_face_index, current_face
                new_facing = facing
                print(pos, move_by)
                new_pos = (pos[0] + move_by[0], pos[1] + move_by[1])
                print("n", new_pos)
                # hit side of cube; move to other side
                if not (0 <= new_pos[0] < line_length and 0 <= new_pos[1] < line_length):
                    print("moving to other face", 0 <= new_pos[0], new_pos[0] < line_length, 0 <= new_pos[1],
                          new_pos[1] < line_length)
                    new_face_index, new_facing = movement_dict[current_face_index][facing]
                    new_face = cube[new_face_index]
                    rotation = (new_facing - facing + 4) % 4
                    if facing % 2 == 1:  # moving vertically
                        if rotation == 0: new_pos = [pos[0], line_length - 1 - pos[1]]
                        if rotation == 1: new_pos = [pos[1], pos[0]]
                        if rotation == 2: new_pos = [line_length - 1 - pos[0], pos[1]]
                        if rotation == 3: new_pos = [line_length - 1 - pos[1], line_length - 1 - pos[0]]

                    if facing % 2 == 0:  # moving horizontally
                        if rotation == 0: new_pos = [line_length - 1 - pos[0], pos[1]]
                        if rotation == 1: new_pos = [line_length - 1 - pos[1], line_length - 1 - pos[0]]
                        if rotation == 2: new_pos = [pos[0], line_length - 1 - pos[1]]
                        if rotation == 3: new_pos = [pos[1], pos[0]]

                print(new_pos[0], new_pos[1])
                # prevent moving into wall
                if new_face[new_pos[1]][new_pos[0]] == 1:
                    break

                facing = new_facing
                pos = new_pos
                current_face = new_face
                current_face_index = new_face_index

                if new_facing == 0: move_by = (1, 0)
                if new_facing == 1: move_by = (0, 1)
                if new_facing == 2: move_by = (-1, 0)
                if new_facing == 3: move_by = (0, -1)
                pass
            # print_field(field, line_length, path,pos)
        # rotate
        elif instruction < 0:
            facing += (instruction + 1) * 2 + 1
            facing = (facing + 4) % 4
            if facing == 0: move_by = (1, 0)
            if facing == 1: move_by = (0, 1)
            if facing == 2: move_by = (-1, 0)
            if facing == 3: move_by = (0, -1)
        else:
            raise Exception("Code shouldn't reach")

    print("faceindex:", current_face_index)
    print("pos:", pos)
    print("facing:", facing)

    return None


def main():
    with open("input.txt", "r") as f:
        data = parse(f)

    print("result1:", task1(data))
    print("#" * 100)
    with open("input.txt", "r") as f:
        data2 = parse_cube(f)
    print("result2:", task2(data2))


""" 
wrong: - to low

106095
faceindex: 4
pos: (44, 22)
facing: 3
-> would have guessed  106094

"""

if __name__ == "__main__":
    main()
