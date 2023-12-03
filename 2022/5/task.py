def get_top(state):
    out = ""
    for key, row in state.items():
        out += row[0]
    return out


def task1(start_state, moves):
    print("-" * 100)
    print(start_state, moves)
    print("-" * 100)

    state = start_state
    for move in moves:
        amount, rows = move
        for i in range(amount):
            state[rows[1]].insert(0, state[rows[0]][0])
            del state[rows[0]][0]
        print(state)
    return get_top(state)


def task2(start_state, moves):
    print("-" * 100)
    print(start_state, moves)
    print("-" * 100)

    state = start_state
    for move in moves:
        amount, rows = move
        position = 0
        for i in range(amount):
            state[rows[1]].insert(position, state[rows[0]][0])
            del state[rows[0]][0]
            position += 1
        print(state)
    return get_top(state)


def main():
    with open("input.txt", "r") as f:
        in_start_state = True
        start_state = {}
        move = []
        for line in f.readlines():
            line = line.replace("\n", "")
            if line == "":
                print("switching to moves")
                in_start_state = False
            elif in_start_state:
                if "-" in line:
                    continue

                for i in range(9, 0, -1):
                    line = line.replace(i * "    ", "#" * i)
                line = line.replace(" ", "").replace("[", "").replace("]", "")

                for i, element in enumerate([char for char in line]):
                    if i not in start_state.keys():
                        start_state[i] = []
                    if element != "#":
                        start_state[i].append(element)

                print("hi", start_state)

            else:
                line = line.replace("move", "")
                line = line.split("from")
                line[1] = line[1].split("to")
                line[0] = int(line[0])
                line[1][0] = int(line[1][0]) - 1
                line[1][1] = int(line[1][1]) - 1
                move.append(line)

        print(start_state)
        print(move)

        start_state2 = {}
        for key, val in start_state.items():
            start_state2[key] = start_state[key][:]

        print("#" * 100)
        print("result1:", task1(start_state, move))
        print(start_state, start_state2)
        print("#" * 100)
        print("result2:", task2(start_state2, move))


if __name__ == "__main__":
    main()
