def is_sorted(left, right) -> bool:
    # print("#", left, right)
    if type(left) != type(right):
        if type(left) == int:
            left = [left]
            # print("hi 1")
        elif type(right) == int:
            right = [right]
            # print("hi 2")
        else:
            raise Exception("code should not reach")

    if type(left) == int:
        if left == right:
            return None
        return left < right

    for index, element in enumerate(left):
        try:
            s = is_sorted(element, right[index])
            if s is None:
                continue
            if not s:
                # print("not sorted")
                return False
            else:
                # print("sorted")
                return True
        # right ran out first
        except IndexError:
            return False
    # left ran out first
    if len(left) < len(right):
        return True
    return None


def task1(in_lines):
    correct = []
    for index, pair in enumerate(in_lines):
        left, right = pair
        print("-" * 100)
        print(index + 1, left, right)
        if is_sorted(left, right):
            correct.append(index + 1)
            print("correct")
        else:
            print("false")

    print(correct)
    return sum(correct)


def task2(in_lines):
    indices = list(range(len(in_lines)))
    for i,line in enumerate(in_lines):
        print(indices[i],line)

    for n in range(len(in_lines)-1, 0, -1):
        for i in range(n):
            if not is_sorted(in_lines[n], in_lines[i]):
                in_lines[n], in_lines[i] = in_lines[i], in_lines[n]
                indices[n], indices[i] = indices[i], indices[n]
    in_lines.reverse()
    indices.reverse()
    print()
    for i,line in enumerate(in_lines):
        print(indices[i],line)

    return (indices.index(0)+1) * (indices.index(1)+1)


def interpret_string(in_string: str, d=0):
    if in_string[0] == ",":
        in_string = in_string[1:]
    try:
        return int(in_string)
    except ValueError:
        pass

    if in_string[0] != "[" or in_string[-1] != "]":
        raise Exception("problem?\n", in_string)

    in_string = in_string[1:len(in_string) - 1]

    if len(in_string) == 0:
        return []

    print("\t" * d, "called:", in_string)
    depth = 0

    slice_indices = [0]

    for i, c in enumerate(in_string):
        if c == "[":
            depth += 1
        if c == "]":
            depth -= 1
        if c == "," and depth == 0:
            slice_indices.append(i)

    print("\t" * d, "slice_indices", slice_indices)
    parts = [in_string[i:j] for i, j in zip(slice_indices, slice_indices[1:] + [None])]
    print("\t" * d, "parts", parts)
    out = [interpret_string(s, depth + 1) for s in parts]
    print("\t" * d, "returns", out)
    return out


def main():
    with open("input.txt", "r") as f:
        lines = [a.split("\n") for a in f.read().split("\n\n")]

        input_data = []
        input_data2 = [[[2]], [[6]]]
        for pair in lines:
            print(len(pair), pair)
            left, right = pair
            left_data, right_data = interpret_string(left), interpret_string(right)

            input_data.append((left_data, right_data))
            input_data2.append(left_data)
            input_data2.append(right_data)

        print("result1:", task1(input_data))
        print("#" * 100)

        print("result2:", task2(input_data2))


if __name__ == "__main__":
    main()
