directions = {
    "U": (0, 1),
    "D": (0, -1),
    "L": (-1, 0),
    "R": (1, 0)
}


def task1(in_lines):
    tail_pos_history = [(0, 0)]
    tx, ty = [0, 0]
    hx, hy = [0, 0]

    for line in in_lines:
        direction, amount = line
        move_x, move_y = directions[direction]
        for i in range(int(amount)):
            hx += move_x
            hy += move_y

            dx = hx - tx
            dy = hy - ty
            print(dx, dy)
            if dx ** 2 + dy ** 2 > 2:
                print("hi")
                if abs(dx) > 1 != abs(dy) > 1:
                    tx += dx / 2
                    ty += dy / 2
                else:
                    if abs(dx) > abs(dy):
                        tx += dx / 2
                        ty += dy
                    else:
                        tx += dx
                        ty += dy / 2
                tail_pos_history.append((tx, ty))
    return len(list(set(tail_pos_history)))


def task2(in_lines):
    elements = 9
    tail_pos_history = [(0, 0)]
    tx, ty = ([], [])
    for i in range(elements):
        tx.append(0)
        ty.append(0)
    hx, hy = [0, 0]

    for line in in_lines:
        direction, amount = line
        move_x, move_y = directions[direction]
        for i in range(int(amount)):
            hx += move_x
            hy += move_y

            for j in range(elements):
                px, py = None, None
                if j == 0:
                    px, py = hx, hy
                else:
                    px, py = tx[j - 1], ty[j - 1]

                dx = px - tx[j]
                dy = py - ty[j]

                if dx ** 2 + dy ** 2 > 2:
                    if abs(dx) > 1 != abs(dy) > 1:
                        tx[j] += dx / 2
                        ty[j] += dy / 2
                    else:
                        if abs(dx) > abs(dy):
                            tx[j] += dx / 2
                            ty[j] += dy
                        else:
                            tx[j] += dx
                            ty[j] += dy / 2
            tail_pos_history.append((tx[elements-1], ty[elements-1]))

    return len(list(set(tail_pos_history)))


def main():
    with open("input.txt", "r") as f:
        lines = [line.replace("\n", "").split(" ") for line in f.readlines()]
        print(lines)
        print("result1:", task1(lines))
        print("#" * 100)
        print("result2:", task2(lines))


if __name__ == "__main__":
    main()
