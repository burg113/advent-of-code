def task1(string):
    for i in range(4,len(string)):
        char_list = list(string[i-4:i])
        if len(char_list) == len(list(set(char_list))):
            return i


def task2(string):
    for i in range(14, len(string)):
        char_list = list(string[i - 14:i])
        if len(char_list) == len(list(set(char_list))):
            return i


def main():
    with open("input.txt", "r") as f:
        string = f.readline()

        print("result1:", task1(string))
        print("#" * 100)
        print("result2:", task2(string))


if __name__ == "__main__":
    main()
