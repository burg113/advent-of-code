def task1(file_sys):
    sum = 0
    for folder, content in file_sys.items():
        if getsizes(folder, file_sys) < 100000:
            sum += getsizes(folder, file_sys)
            print(folder, getsizes(folder, file_sys))
            print(getsizes(folder, file_sys))
    return sum


def task2(file_sys):
    all_space = getsizes("/",file_sys)

    print("&",all_space)

    lowest = 100000000
    for folder, content in file_sys.items():
        if lowest > getsizes(folder, file_sys) >= -40000000 + all_space:
            lowest = getsizes(folder, file_sys)
    return lowest


def getsizes(folder: str, file_sys: dir):
    sum = 0

    for f, content in file_sys[folder]:
        if content == "dir":
            sum += getsizes(f, file_sys)
        else:
            sum += int(content)
    return sum


def main():
    file_sys = {}
    current_folder = ""

    with open("input.txt", "r") as f:
        lines = [line.replace("\n", "") for line in f.readlines()]

        for line in lines:
            if line[0] == "$":

                if line.__contains__("cd"):
                    arg = line[2:].split(" ")[1]
                    if arg == "..":
                        print("#" * 100)
                        print(current_folder)
                        temp = current_folder[:current_folder.rfind('/')]
                        print(temp)
                        current_folder = temp[:temp.rfind('/') + 1]
                        print(current_folder)
                        print(f"-1")
                    else:
                        if arg == "/":
                            current_folder = "/"
                            print(f"0")
                        else:
                            current_folder += arg + "/"
                            print(f"1")
                    if current_folder not in file_sys:
                        file_sys[current_folder] = []
                    print(f"current_folder set to {current_folder}")

                else:

                    pass

            else:
                content, name = line.split(" ")
                if content == "dir":
                    name = current_folder + name + "/"
                print(line, current_folder)

                file_sys[current_folder].append([name, content])

        for folder, content in file_sys.items():
            print(folder, content)

        for folder, content in file_sys.items():
            print(folder, content)
            print(getsizes(folder, file_sys))

        print("result1:", task1(file_sys))
        print("#" * 100)
        print("result2:", task2(file_sys))


if __name__ == "__main__":
    main()
