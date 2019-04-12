from play import *
from board import *

import random

class Minimax:
    __slots__ = ['depth', 'first_player', 'board', 'player']

    def __init__(self, depth, first_player):
        self.depth = depth
        self.first_player = first_player
        random.seed(42)
        return

    def init(self, board):
        self.board = board
        self.player = self.first_player
        return

    def play(self, p):
        self.player = not self.player
        return

    def search(self):
        plays = self.board.getPlays(self.player)
        self.board.best_play = plays[0]

        alfa = -10000000
        beta =  10000000

        if self.player:
            self.max_value(alfa, beta)
        else:
            self.min_value(alfa, beta)
        return

    def max_value(self, alfa, beta):
        if self.board.gameOver(True) :
            if self.board.whoWins(True): return -10000
            return 0

        if self.board.depth >= self.depth: return self.board.eval_board()

        val = -10000000
        valx = 0
        podar = False

        plays = self.board.getPlays(True)
        random.shuffle(plays)

        for p in plays:
            if podar: break

            self.board.play(p)
            self.board.depth += 1
            valx = self.min_value(alfa, beta)
            self.board.depth -= 1
            self.board.rmplay()

            if val < valx:
                if self.board.depth == 0: self.board.best_play = p
                val = valx

            if val >= beta: podar = True
            alfa = max(alfa,val)

        return val

    def min_value(self, alfa, beta):
        if self.board.gameOver(False) :
            if self.board.whoWins(False): return 10000
            return 0

        if self.board.depth >= self.depth: return self.board.eval_board()

        val = 10000000
        valx = 0
        podar = False

        plays = self.board.getPlays(False)
        random.shuffle(plays)

        for p in plays:
            if podar: break

            self.board.play(p)
            self.board.depth += 1
            valx = self.max_value(alfa, beta)
            self.board.depth -= 1
            self.board.rmplay()

            if val > valx:
                if self.board.depth == 0: self.board.best_play = p
                val = valx

            if val <= alfa: podar = True
            beta = min(beta,val)

        return val
