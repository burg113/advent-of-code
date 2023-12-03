def main():
    task1()
    print("#" * 200)
    task2()


def task1():
    maximum = 0
    with open("input.txt", "r") as f:
        elf_foods = f.read().split("\n\n")
        for food in elf_foods:
            foods = food.split("\n")

            foods = [int(f) for f in food.split("\n")]
            print(foods)
            amount = sum([int(f) for f in food.split("\n")])
            if amount > maximum:
                maximum = amount

    print()
    print(f"Answer: {maximum}")


def task2():
    maximum = [0,0,0]
    with open("input.txt", "r") as f:
        elf_foods = f.read().split("\n\n")
        for food in elf_foods:
            foods = food.split("\n")

            foods = [int(f) for f in food.split("\n")]
            print(foods)
            amount = sum([int(f) for f in food.split("\n")])
            for i in range(3):
                if amount > maximum[i]:
                    maximum[i] = amount
                    break

    print(maximum)
    print()
    print(f"Answer: {sum(maximum)}")


if __name__ == "__main__":
    main()
