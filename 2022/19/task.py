import math
import re

"""
1 geode = 1 p
1 geode-robot = <turn> points

x ore+ y obsidian = <turn> points
x ore robots + y obsidian robots = 1/2 <turn>^2 points

c ore + d clay = obsidian robot

b ore = clay robot = <turn> clay

a ore = ore robot = <turn> ore


"""


# BLUEPRINT:        1           2       3   4   5   6
# blueprint_id, ore_robot, clay_robot, o1, o2, g1, g2


def parse(file):
    lines = [[int(n) for n in re.findall(r'\d+', line)] for line in file.readlines()]
    return lines


traversed = {}
first = 0
# path = [-1, 4, 4, 4, 3, 4, 4, 3, 4, 4, 2, 4, 4, 1, 2, 4, 4, 4, 1, 4, 1, 4, 1, 4, 4]

max_ore = 0
max_clay = 0
max_obsidian = 0
best_answer = 0


def max_geodes(ore, clay, obsidian, ore_robot, clay_robot, obsidian_robot, geode_robot, blueprint, time, geodes):
    global best_answer, max_ore, max_clay, max_obsidian
    if time > 22:
        print(time)
    # print(ore, clay, obsidian, ore_robot, clay_robot, obsidian_robot, geode_robot, blueprint, time, current_robot)
    if time == 0:
        return 0
    if (time+2) * (time+1) < best_answer - geodes:
        return 0

    h = (ore, clay, obsidian, ore_robot, clay_robot, obsidian_robot, geode_robot, time, geodes).__hash__()
    if h in traversed.keys():
        return traversed[h]

    options = []
    if ore >= blueprint[1] and ore_robot < max_ore:
        options.append(
            max_geodes(ore - blueprint[1] + ore_robot, clay + clay_robot, obsidian + obsidian_robot,
                       ore_robot + 1, clay_robot, obsidian_robot, geode_robot,
                       blueprint, time - 1, geodes + geode_robot) + geode_robot)

    if ore >= blueprint[2] and clay_robot < max_clay:
        options.append(
            max_geodes(ore - blueprint[2] + ore_robot, clay + clay_robot, obsidian + obsidian_robot,
                       ore_robot, clay_robot + 1, obsidian_robot, geode_robot,
                       blueprint, time - 1, geodes + geode_robot) + geode_robot)

    if ore >= blueprint[3] and clay >= blueprint[4] and obsidian_robot < max_obsidian:
        options.append(
            max_geodes(ore - blueprint[3] + ore_robot, clay - blueprint[4] + clay_robot, obsidian + obsidian_robot,
                       ore_robot, clay_robot, obsidian_robot + 1, geode_robot,
                       blueprint, time - 1, geodes + geode_robot) + geode_robot)

    if ore >= blueprint[5] and obsidian >= blueprint[6]:
        options.append(
            max_geodes(ore - blueprint[5] + ore_robot, clay + clay_robot, obsidian - blueprint[6] + obsidian_robot,
                       ore_robot, clay_robot, obsidian_robot, geode_robot + 1,
                       blueprint, time - 1, geodes + geode_robot) + geode_robot)

    if len(options) < 4:
        options.append(
            max_geodes(ore + ore_robot, clay + clay_robot, obsidian + obsidian_robot, ore_robot, clay_robot,
                       obsidian_robot, geode_robot, blueprint, time - 1, geodes + geode_robot) + geode_robot)

    m = max(options)
    traversed[h] = m
    best_answer = max(m, best_answer)
    return m


def task1(in_lines):
    sum = 0
    for line in in_lines:
        global traversed
        traversed = {}

        global max_ore, max_clay, max_obsidian
        max_ore, max_clay, max_obsidian = max(line[1], line[2], line[3], line[5]), line[4], line[6]
        m = max_geodes(0, 0, 0, 1, 0, 0, 0, line, 24,0)
        print("max", m)
        sum += m * line[0]
        print(line)
    return sum


def task2(in_lines):
    product = 1
    for i in range(3):
        line = in_lines[i]
        global traversed
        traversed = {}

        global max_ore, max_clay, max_obsidian, best_answer
        max_ore, max_clay, max_obsidian = max(line[1], line[2], line[3], line[5]), line[4], line[6]
        best_answer = 0
        m = max_geodes(0, 0, 0, 1, 0, 0, 0, line, 32, 0)
        print("max", m)
        product *= m
        print(line)
    return product


def main():
    with open("input.txt", "r") as f:
        data = parse(f)

    # print("result1:", task1(data))
    # print("#" * 100)
    print("result2:", task2(data))


if __name__ == "__main__":
    main()
