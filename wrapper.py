import ctypes
import os
import platform
from utils import get_lib_name

lib = ctypes.CDLL(get_lib_name())


class Player(ctypes.Structure):
    """
    Represents a player in the game, defined by their piece and name.
    """
    _fields_ = [("piece", ctypes.c_char), ("name", ctypes.c_char * 30)]

    def __init__(self, piece: str, name: str) -> None:
        super().__init__()
        self.piece = piece.encode("utf-8")
        self.name = name.encode("utf-8")


BOARDSIZE = 3


def init_board() -> ctypes.Array:
    """
    Initializes the game board using the shared library.
    """
    board = (ctypes.c_char * BOARDSIZE * BOARDSIZE)()
    lib.init_board(board)
    return board


def print_board(board: ctypes.Array) -> None:
    """
    Prints the current state of the board using the shared library.
    """
    lib.print_board(board)


def play_turn(player: Player, board: ctypes.Array, move: list[int]) -> None:
    """
    Executes a player's move on the board.
    """
    move_array = (ctypes.c_int * 2)(*move)
    lib.play_turn(ctypes.byref(player), board, move_array)


def check_winner(piece: bytes, board: ctypes.Array) -> bool:
    """
    Checks if the given piece has won the game.
    """
    return lib.check_winner(ctypes.c_char(piece), board)


def best_move(player: Player, opponent: Player, board: ctypes.Array) -> tuple[int, int]:
    """
    Determines the best move for the given player using the minimax algorithm.
    """

    def minimax(
        board: ctypes.Array, depth: int, is_maximizing: bool, alpha: int, beta: int
    ) -> int:
        if check_winner(player.piece, board):
            return 10 - depth
        if check_winner(opponent.piece, board):
            return depth - 10
        if is_draw(board):
            return 0

        if is_maximizing:
            max_eval = -float("inf")
            for row in range(BOARDSIZE):
                for col in range(BOARDSIZE):
                    if board[row][col] == b" ":
                        board[row][col] = player.piece
                        eval = minimax(board, depth + 1, False, alpha, beta)
                        board[row][col] = b" "
                        max_eval = max(max_eval, eval)
                        alpha = max(alpha, eval)
                        if beta <= alpha:
                            return max_eval
            return max_eval
        else:
            min_eval = float("inf")
            for row in range(BOARDSIZE):
                for col in range(BOARDSIZE):
                    if board[row][col] == b" ":
                        board[row][col] = opponent.piece
                        eval = minimax(board, depth + 1, True, alpha, beta)
                        board[row][col] = b" "
                        min_eval = min(min_eval, eval)
                        beta = min(beta, eval)
                        if beta <= alpha:
                            return min_eval
            return min_eval

    best_val = -float("inf")
    move = (-1, -1)
    for row in range(BOARDSIZE):
        for col in range(BOARDSIZE):
            if board[row][col] == b" ":
                board[row][col] = player.piece
                move_val = minimax(board, 0, False, -float("inf"), float("inf"))
                board[row][col] = b" "
                if move_val > best_val:
                    best_val = move_val
                    move = (row, col)

    return move


def is_draw(board: ctypes.Array) -> bool:
    """
    Checks if the game is a draw (no empty spaces on the board).
    """
    return all(board[row][col] != b" " for row in range(BOARDSIZE) for col in range(BOARDSIZE))


if __name__ == "__main__":
    board = init_board()
    player1 = Player(piece="X", name="Player1")
    player2 = Player(piece="O", name="Player2")

    play_turn(player1, board, [0, 0])
    print_board(board)

    play_turn(player2, board, best_move(player2, player1, board))
    print_board(board)

    play_turn(player1, board, [2, 2])
    print_board(board)

    play_turn(player2, board, best_move(player2, player1, board))
    print_board(board)

    play_turn(player1, board, [2, 0])
    print_board(board)

    play_turn(player2, board, best_move(player2, player1, board))
    print_board(board)

    if check_winner(player1.piece, board):
        print(f"{player1.name.decode()} wins!")
    elif check_winner(player2.piece, board):
        print(f"{player2.name.decode()} wins!")
    else:
        print("No winner yet.")