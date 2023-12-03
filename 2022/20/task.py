def parse(file):
    lines = [int(line.replace("\n", "")) for line in file.readlines()]
    return lines


def shift(data: list, element: int, amount: int):
    index = data.index(element)
    if amount == 0:
        return data
    del data[index]
    insert_spot = (index + amount) % len(data)
    if insert_spot <= 0:
        insert_spot += len(data)

    data.insert(insert_spot, element)
    return data


def task1(data):
    operations = data.copy()
    arr = [i for i in range(len(data))]
    for i, operation in enumerate(operations):
        arr = shift(arr, i, operation)

    out = []
    for i in range(len(data)):
        out.append(data[arr[i]])
    start_index = out.index(0)

    return out[(start_index + 1000) % len(out)] + out[(start_index + 2000) % len(out)] + out[
        (start_index + 3000) % len(out)]


def task2(data):
    key = 811589153
    operations = [d * key for d in data]
    arr = [i for i in range(len(data))]
    for n in range(10):
        for i, operation in enumerate(operations):
            arr = shift(arr, i, operation)

    out = []
    for i in range(len(data)):
        out.append(operations[arr[i]])
    start_index = out.index(0)

    return out[(start_index + 1000) % len(out)] + out[(start_index + 2000) % len(out)] + out[
        (start_index + 3000) % len(out)]


def main():
    with open("input.txt", "r") as f:
        data = parse(f)

    print("result1:", task1(data))
    print("#" * 100)
    print("result2:", task2(data))


if __name__ == "__main__":
    main()
