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
        board = np.zeros((shape, shape), dtype=int)
        for row, col in enumerate(solution):
            board[row, col] = 1
        for row in board:
            print(" ".join(map(str, row)))
        num+=1
        print() 

# n x n Board
n = 5
solutions = solve_n_queens(n)
print(f"Number of solutions for {n}-Queens problem: {len(solutions)}")
print()
print_solutions(solutions, n)