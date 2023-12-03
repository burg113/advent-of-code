# Note:
#   A  Rock             X
#   B  Paper            Y
#   C  Scissors         Z
#
score_loss = 0
score_draw = 3
score_win = 6
points = {
    "X": 1,
    "A": 1,
    "Y": 2,
    "B": 2,
    "Z": 3,
    "C": 3

}


def task1():
    score = 0
    with open("input.txt", "r") as f:
        lines = f.readlines()
        for line in lines:
            opponent, me = line[0], line[2]

            score += points[me]

            if points[opponent] == points[me]:  # draw
                score += score_draw
            elif points[opponent] % 3 + 1 == points[me]:  # win
                score += score_win
            else:  # loss
                score += score_loss

            print(score)

    print(f"Answer1: {score}")


def task2():
    score = 0
    with open("input.txt", "r") as f:
        lines = f.readlines()
        for line in lines:
            opponent, me = line[0], line[2]

            print(opponent, me)
            print(opponent == me)
            if me == "Y":  # draw
                score += score_draw
                score += points[opponent]
            if me == "Z":  # win
                score += score_win
                score += points[opponent] % 3 + 1
            if me == "X":  # lose
                score += score_loss
                score += (points[opponent] % 3 + 1) % 3 + 1

            print(score)

    print(f"Answer2: {score}")


def main():
    task1()
    print("#" * 100)
    task2()


if __name__ == "__main__":
    main()
