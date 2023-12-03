char_dir_lookup = {
    "^": 0,
    ">": 1,
    "v": 2,
    "<": 3
}

directioins = {
    0: (0, -1),
    1: (1, 0),
    2: (0, 1),
    3: (-1, 0)
}


def parse(file):
    lines = [line.replace("\n", "") for line in file.readlines()]
    start = (0, -1)
    finish = (len(lines[0]) - 3, len(lines) - 2)
    field_size = (len(lines[0]) - 2, len(lines) - 2)
    print(finish)
    blizzards = []
    for y, line in enumerate(lines[1:-1]):
        for x, c in enumerate(line[1:-1]):
            if c in char_dir_lookup:
                blizzards.append([[x, y], char_dir_lookup[c]])

    return blizzards, start, finish, field_size


def task1(data):
    blizzards, start, finish, field_size = data
    blizzard_positions = set()
    print("start", start)
    print("finish", finish)
    print("field_size", field_size)

    for blizzard in blizzards:
        pos, direction = blizzard
        blizzard_positions.add(tuple(pos))

    player_positions = set([start])
    count = 0
    finish_after_turn = False
    while True:
        count += 1
        print(count)
        """for y in range(field_size[1]):
            for x in range(field_size[0]):
                print("#" if (x, y) in blizzard_positions else ".", end="")
            print()
        print()"""
        # print(player_positions)
        for pos in player_positions.copy():
            for key, direction in directioins.items():
                new_pos = (pos[0] + direction[0], pos[1] + direction[1])
                """ print(new_pos, 0 <= new_pos[0] < field_size[0],
                      0 <= new_pos[1] < field_size[1],
                      new_pos not in blizzard_positions)"""
                if new_pos == finish:
                    finish_after_turn = True
                if 0 <= new_pos[0] < field_size[0] and 0 <= new_pos[1] < field_size[1]:
                    player_positions.add(new_pos)

        blizzard_positions = set()
        for blizzard in blizzards:
            pos, direction = blizzard
            d = abs(directioins[direction][1]) == 1
            blizzard[0][d] += directioins[direction][d]
            if blizzard[0][d] < 0:
                blizzard[0][d] += field_size[d]
            if blizzard[0][d] >= field_size[d]:
                blizzard[0][d] -= field_size[d]

            pos_t = tuple(pos)
            if pos_t in player_positions:
                player_positions.remove(pos_t)
            blizzard_positions.add(pos_t)
        if finish_after_turn:
            return count
        """for y in range(field_size[1]):
            for x in range(field_size[0]):
                print("E" if (x, y) in player_positions else ".", end="")
            print()
        print()"""


def task2(data):
    blizzards, start, finish, field_size = data
    points = [start, finish]
    sum = 0
    for i in range(3):
        sum += task1((blizzards, points[i % 2], points[(i + 1) % 2], field_size))
        print(sum)
    return sum

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
