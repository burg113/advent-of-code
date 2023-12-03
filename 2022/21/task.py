def parse(file):
    lines = [line.replace("\n", "").split(":") for line in file.readlines()]
    data = {}
    for i in range(len(lines)):
        data[lines[i][0]] = lines[i][1].strip().split(" ")
    return data


def task1(data):
    while len(data["root"]) > 1:
        for key, val in data.items():
            if len(val) > 1:
                a, operation, b = val
                if len(data[a]) == 1 and len(data[b]) == 1:
                    data[key] = [str(eval(data[a][0] + operation + data[b][0]))]
    return data["root"]


def task2(data):
    current_index = 14
    mynum = 10 ** current_index
    while True:
        copy = {}
        # print(data)
        for key, val in data.items():
            copy[key] = val.copy()

        copy["humn"] = [str(mynum)]

        # print(copy)
        while len(copy[copy["root"][0]]) > 1 or len(copy[copy["root"][2]]) > 1:
            for key, val in copy.items():
                if key != "root" and len(val) > 1:
                    # print(val)
                    a, operation, b = val
                    if len(copy[a]) == 1 and len(copy[b]) == 1:
                        copy[key] = [str(eval(copy[a][0] + operation + copy[b][0]))]

        diff = float(copy[copy["root"][0]][0]) - float(copy[copy["root"][2]][0])
        print(diff)
        if diff == 0:
            return mynum
        if diff < 0:
            mynum -= 10** current_index
            current_index -= 1
            mynum += current_index
        else:
            mynum += 10 ** current_index



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
