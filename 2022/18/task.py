import numpy as np
from matplotlib import pyplot as plt


def parse(file):
    lines = [[int(c) for c in line.replace("\n", "").split(",")] for line in file.readlines()]
    max_x, max_y, max_z = 0, 0, 0
    out = set()
    for line in lines:
        x, y, z = line
        max_x = max(x + 1, max_x)
        max_y = max(y + 1, max_y)
        max_z = max(z + 1, max_z)

        out.add((x + 1, y + 1, z + 1))

    return out, (max_x, max_y, max_z)


diffs = {(1, 0, 0), (-1, 0, 0), (0, 1, 0), (0, -1, 0), (0, 0, 1), (0, 0, -1)}


def task1(data_set, max_data):
    count = 0
    for x in range(max_data[0] + 1):
        for y in range(max_data[1] + 1):
            for z in range(max_data[2] + 1):
                # print(x, y, z)
                if (x, y, z) in data_set:
                    # print("--",x,y,z)
                    for dif in diffs:
                        # print(tuple([sum(x) for x in zip((x, y, z), dif)]), data_set)
                        if tuple([sum(x) for x in zip((x, y, z), dif)]) not in data_set:
                            # print("hi")
                            count += 1
    return count


def task2(data_set, max_data):
    # default: -2
    # active: -1
    # checked: count of neighbouring cubes
    area = [[[-2 for k in range(max_data[2] + 2)] for j in range(max_data[1] + 2)] for i in range(max_data[0] + 2)]
    area[0][0][0] = -1

    changed = True
    total_count = 0
    while changed:
        changed = False
        for x in range(max_data[0] + 2):
            for y in range(max_data[1] + 2):
                for z in range(max_data[2] + 2):
                    if area[x][y][z] == -1:
                        changed = True
                        # print(x,y,z)
                        count_neighbouring_sides = 0
                        for dif in diffs:
                            new_point = tuple([sum(s) for s in zip((x, y, z), dif)])
                            nx, ny, nz = new_point
                            if 0 <= nx <= max_data[0]+1 and 0 <= ny <= max_data[1]+1 and 0 <= nz <= max_data[2]+1:
                                # print("#", nx, ny, nz, area[nx][ny][nz], new_point not in data_set)

                                if area[nx][ny][nz] == -2 and new_point not in data_set:
                                    area[nx][ny][nz] = -1
                                    # print("activating", nx, ny, nz)

                                if new_point in data_set:
                                    # print("hi")
                                    count_neighbouring_sides += 1

                        # print("setting", x, y, z, area[x][y][z], "to", count_neighbouring_sides)
                        area[x][y][z] = count_neighbouring_sides
                        total_count += count_neighbouring_sides

    """fig = plt.figure()
    ax = plt.axes(projection='3d')
    for x in range(max_data[0] + 2):
        for y in range(max_data[1] + 2):
            for z in range(max_data[2] + 2):
                if (x,y,z) in data_set:
                    plt.plot(x, y, z, marker="o", markersize=4, markeredgecolor="red", markerfacecolor="red")
                elif area[x][y][z] == -2:
                    plt.plot(x, y, z, marker="o", markersize=4, markeredgecolor="black",markerfacecolor= "black")"""

    plt.show()


    return total_count


def main():
    with open("input.txt", "r") as f:
        data_set, max_data = parse(f)

    print("result1:", task1(data_set, max_data))
    print("#" * 100)
    print("result2:", task2(data_set, max_data))


if __name__ == "__main__":
    main()
