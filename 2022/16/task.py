STEPS = 30


def parse(lines):
    nodes = {}
    connections = {}

    for line in lines:
        line = line.replace("\n", "").replace("Valve ", "").replace("has flow rate", "") \
            .replace("tunnels lead to valves", "").replace("tunnel leads to valve", "")
        line = line.split(";")
        line[0] = line[0].split("=")
        line[1] = line[1].split(",")
        line[0][0] = sum([(ord(c) - 65) * 32 ** i for i, c in enumerate(line[0][0].strip())])

        for i, e in enumerate(line[1]):
            line[1][i] = sum([(ord(c) - 65) * 32 ** i for i, c in enumerate(e.strip())])
        nodes[line[0][0]] = int(line[0][1])
        connections[line[0][0]] = line[1]

    return preprocess_graph(nodes, connections)


# breath firs search
def dist(connections, start_node, end_node, max_depth):
    nodes = []
    traversed = []
    new_nodes = [start_node]
    for depth in range(max_depth):
        for node in new_nodes:
            nodes.append(node)
            traversed.append(node)
        new_nodes = []

        for node in nodes:
            for neighbour in connections[node]:
                if neighbour == end_node:
                    return depth + 1
                if neighbour not in traversed:
                    new_nodes.append(neighbour)


def preprocess_graph(nodes, connections):
    important_nodes = {}
    dist_from_start = {}
    important_connections = {}
    for index, val in nodes.items():
        curr_con = connections[index]
        if val > 0:
            important_nodes[index] = val
            important_connections[index] = {}
            dist_from_start[index] = dist(connections, 0, index, 30)

    # finds distances between important points
    for node1, val1 in important_nodes.items():
        for node2, val2 in important_nodes.items():
            if node1 < node2:
                d = dist(connections, node1, node2, 30)
                important_connections[node1][node2] = d
                important_connections[node2][node1] = d

    for key, val in important_connections.items():
        print(get_node_name(key))
        print(" ", dist_from_start[key])
        for key2, val2, in val.items():
            print(" ", get_node_name(key2), val2)

    return important_nodes, important_connections, dist_from_start


def get_node_name(num: int):
    return chr(num % 32 + 65) + chr(int(num / 32) + 65)


def maximize(curr_node, nodes, connections, steps, nodes_traversed):
    # print(curr_node)
    if steps == 0:
        return 0, [-1]
    if steps < 0:
        raise Exception("please dont")
    nodes_traversed.append(curr_node)

    c = nodes[curr_node]
    options = []
    debugs = {}
    for neighbour in connections[curr_node]:
        connection = connections[curr_node][neighbour]
        if steps > connection + 1 and neighbour not in nodes_traversed:
            # print(curr_node, neighbour)

            m, debug = maximize(neighbour, nodes, connections, steps - 1 - connections[curr_node][neighbour],
                                nodes_traversed.copy())
            m += c * (steps - 1)
            options.append(m)

            debug.append((curr_node, steps))
            debug.append(steps - 1 - connections[curr_node][neighbour])
            debugs[m] = debug
    if len(options) == 0:
        return c * (steps - 1), [-2]

    return max(options), debugs[max(options)]


def maximize2(curr_node, curr_node2, nodes, connections, steps, steps2, nodes_traversed, disable_switch=False):
    # print(curr_node)
    switch = None
    if not disable_switch:
        switch = steps < steps2
        if switch:
            curr_node, curr_node2 = curr_node2, curr_node
            steps, steps2 = steps2, steps

    add_amount = 0
    if curr_node not in nodes_traversed:
        nodes_traversed.add(curr_node)
        add_amount += nodes[curr_node] * (steps-1)

    if curr_node2 not in nodes_traversed:
        nodes_traversed.add(curr_node2)
        add_amount += nodes[curr_node2] * (steps2-1)

    c = nodes[curr_node]
    options = [0]
    debugs = {0: [2]}
    for neighbour in connections[curr_node]:
        connection = connections[curr_node][neighbour]
        if steps > connection + 1 and neighbour not in nodes_traversed:
            # print("calling", neighbour, " " * (20 - len(str(neighbour))),
            #       [get_node_name(num) for num in nodes_traversed])
            m, debug = maximize2(neighbour, curr_node2, nodes, connections,
                                 steps - 1 - connections[curr_node][neighbour], steps2,
                                 nodes_traversed.copy())
            options.append(m)

            debug.append((curr_node, steps))
            debug.append(steps - 1 - connections[curr_node][neighbour])
            debugs[m] = debug

    return max(options) + add_amount, debugs[max(options)]


def task1(nodes, connections, dists_from_start):
    maximum = []
    for node, val in nodes.items():
        turn = 30
        d = dists_from_start[node]
        turn -= d
        maximum.append(maximize(node, nodes, connections, turn, []))
    for m in maximum:
        res, debug = m
        print(res)
        for d in debug:
            if type(d) is int:
                print(d)
            else:
                n, turn = d
                print("", get_node_name(n), turn)
    return max(maximum)


def task2(nodes, connections, dists_from_start):
    maximum = []
    for node, val in nodes.items():
        turn = 26
        d = dists_from_start[node]
        turn -= d
        for node2, val2 in nodes.items():
            if node2 > node:
                turn2 = 26
                d2 = dists_from_start[node2]
                turn2 -= d2
                print("starting", get_node_name(node), get_node_name(node2))
                maximum.append(maximize2(node, node2, nodes, connections, turn, turn2, set()))
    for m in maximum:
        print("-" * 100)
        res, debug = m
        print(res)
        for d in debug:
            if type(d) is int:
                print(d)
            else:
                n, turn = d
                print("", get_node_name(n), turn)
    return max(maximum)


def main():
    with open("input.txt", "r") as f:
        lines = [line.replace("\n", "") for line in f.readlines()]

    important_nodes, important_connections, dist_from_start = parse(lines)
    print("#" * 100)
    # print("result1:", task1(important_nodes.copy(), important_connections.copy(), dist_from_start.copy()))
    print("#" * 100)
    print("result2:", task2(important_nodes.copy(), important_connections.copy(), dist_from_start.copy()))


if __name__ == "__main__":
    main()
