import os
from fastapi import FastAPI, HTTPException
from fastapi.middleware.cors import CORSMiddleware
from pydantic import BaseModel
import ctypes
import uvicorn

from wrapper import Player, BOARDSIZE, best_move, check_winner, is_draw

app = FastAPI()

app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)


class Move(BaseModel):
    """
    Represents a move in the game, including the current board state
    and the pieces of both the player and the opponent.
    """
    board: list[list[str]]
    player_piece: str
    opponent_piece: str


@app.post("/play-turn/")
def play_turn_endpoint(move: Move) -> dict:
    """
    Handles a POST request to process a player's move, determine the AI's response,
    and check for a winner or draw.

    Args:
        move (Move): The current board state and player/opponent pieces.

    Returns:
        dict: The updated board state and the winner, if any.
    """
    if len(move.board) != BOARDSIZE or any(len(row) != BOARDSIZE for row in move.board):
        raise HTTPException(status_code=400, detail="Invalid board size.")

    board = (ctypes.c_char * BOARDSIZE * BOARDSIZE)()
    for i in range(BOARDSIZE):
        for j in range(BOARDSIZE):
            board[i][j] = move.board[i][j].encode("utf-8")

    player = Player(piece=move.player_piece, name="Player")
    opponent = Player(piece=move.opponent_piece, name="AI")

    if check_winner(player.piece, board):
        return {"board": move.board, "winner": "Player"}

    ai_move = best_move(opponent, player, board)
    board[ai_move[0]][ai_move[1]] = opponent.piece

    updated_board = [[board[i][j].decode("utf-8") for j in range(BOARDSIZE)] for i in range(BOARDSIZE)]

    if check_winner(opponent.piece, board):
        return {"board": updated_board, "winner": "AI"}

    if is_draw(board):
        return {"board": updated_board, "winner": "Draw"}

    return {"board": updated_board, "winner": None}


if __name__ == "__main__":
    port = int(os.environ.get("PORT", 10000))
    uvicorn.run(app, host="0.0.0.0", port=port)
