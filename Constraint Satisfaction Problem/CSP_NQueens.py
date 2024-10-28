import numpy as np

def is_safe(queen_positions, row, col):
    for r in range(row):
        if (queen_positions[r] == col or
            queen_positions[r] - r == col - row or
            queen_positions[r] + r == col + row):
            return False
    return True

def solve_n_queens(n):
    def backtrack(row, queen_positions, solutions):
        if row == n:
            solutions.append(queen_positions[:])
            return
        for col in range(n):
            if is_safe(queen_positions, row, col):
                queen_positions[row] = col
                backtrack(row + 1, queen_positions, solutions)
                queen_positions[row] = -1

    solutions = []
    queen_positions = [-1] * n
    backtrack(0, queen_positions, solutions)
    return solutions

def print_solutions(solutions, shape):
    num = 1
    for solution in solutions:
        print(f"Solution {num} {solution}:")
        WHITE_TILE = "\033[47m   \033[0m"  # White tile background
        BLACK_TILE = "\033[40m   \033[0m"  # Black tile background
        QUEEN_WHITE_TILE = "\033[47m\033[30m Q \033[0m"  # White background with black 'Q'
        QUEEN_BLACK_TILE = "\033[40m\033[37m Q \033[0m"  # Black background with white 'Q'

        board = np.fromfunction(lambda i, j: (i + j) % 2, (shape, shape), dtype=int)
        for row, col in enumerate(solution):
            board[row, col] += 2
        for row in board:
            print("".join(WHITE_TILE if tile == 0 else BLACK_TILE if tile == 1 else QUEEN_WHITE_TILE
                           if tile == 2 else QUEEN_BLACK_TILE for tile in row))
        num+=1
        print()

def input_n(prompt="Please enter a positive number for the board size: "):
    while True:
        try:
            user_input = input(prompt)
            number = int(user_input)
            # Check if the number is positive
            if number > 0:
                return number
            else:
                print("That's not a positive number. Try again.")
        except ValueError:
            print("That's not a number. Try again.")

n = input_n()
solutions = solve_n_queens(n)
print(f"Number of solutions for {n}-Queens problem: {len(solutions)}")
print()
print_solutions(solutions, n)
