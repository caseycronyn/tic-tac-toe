import ctypes
import os

# Load the shared library
lib_path = os.path.abspath("game.cpython-313-darwin.so")  # Update extension to .dll if on Windows
tic_tac_toe_lib = ctypes.CDLL(lib_path)

# Define argument and return types for the C functions
tic_tac_toe_lib.play_turn.argtypes = [ctypes.c_char, ctypes.c_char_p, ctypes.POINTER(ctypes.c_char)]
tic_tac_toe_lib.play_turn.restype = ctypes.c_bool

tic_tac_toe_lib.print_board.argtypes = [ctypes.POINTER(ctypes.c_char)]
tic_tac_toe_lib.print_board.restype = None

tic_tac_toe_lib.check_winner.argtypes = [ctypes.c_char, ctypes.POINTER(ctypes.c_char)]
tic_tac_toe_lib.check_winner.restype = ctypes.c_bool

tic_tac_toe_lib.check_end.argtypes = [ctypes.POINTER(ctypes.c_char)]
tic_tac_toe_lib.check_end.restype = ctypes.c_bool

# Create the location array
location = (ctypes.c_char * 9)()
for i in range(9):
    location[i] = b' '

# Example usage
player1_name = b"Player1"
player2_name = b"Player2"
player1_c = player1_name[0]
player2_c = player2_name[0]

# Alternate turns until game over
print("Example move: a1")
tic_tac_toe_lib.print_board(location)

while True:
    # get the input in python then pass to c function. get scanf and printf coming from main
    if tic_tac_toe_lib.play_turn(player1_c, player1_name, location):
        tic_tac_toe_lib.print_board(location)
        break
    tic_tac_toe_lib.print_board(location)

    if tic_tac_toe_lib.play_turn(player2_c, player2_name, location):
        tic_tac_toe_lib.print_board(location)
        break
    tic_tac_toe_lib.print_board(location)

    if tic_tac_toe_lib.check_end(location):
        print("Game Over")
        break
