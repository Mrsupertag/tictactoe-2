import flet as ft
import subprocess
import os

def run_cpp_ai(board):
    with open("board_input.txt", "w") as f:
        for row in board:
            f.write(" ".join(row) + "\n")
    
    subprocess.run("./tictactoe_ai", shell=True)
    
    with open("board_output.txt", "r") as f:
        new_board = [line.strip().split() for line in f.readlines()]
    
    return new_board

def main(page: ft.Page):
    page.title = "Tic-Tac-Toe"
    page.theme_mode = ft.ThemeMode.DARK
    
    board = [[" " for _ in range(3)] for _ in range(3)]
    buttons = []
    
    def update_board():
        for i in range(3):
            for j in range(3):
                buttons[i][j].text = board[i][j]
        page.update()
    
    def on_click(e):
        i, j = e.control.data
        if board[i][j] == " ":
            board[i][j] = "X"
            update_board()
            if any(" " in row for row in board):
                new_board = run_cpp_ai(board)
                for x in range(3):
                    for y in range(3):
                        board[x][y] = new_board[x][y]
                update_board()
    
    grid = ft.Column()
    for i in range(3):
        row = ft.Row()
        row_buttons = []
        for j in range(3):
            btn = ft.TextButton(text=" ", on_click=on_click, data=(i, j), width=100, height=100)
            row.controls.append(btn)
            row_buttons.append(btn)
        buttons.append(row_buttons)
        grid.controls.append(row)
    
    page.add(grid)
    update_board()

ft.app(target=main)
