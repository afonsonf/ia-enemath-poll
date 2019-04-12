from __future__ import print_function
import sys

from play import *

class Human:
    __slots__ = ['first_player','board','player']

    def __init__(self, first_player):
        self.first_player = first_player
        return

    def init(self, board):
        self.board = board
        self.player = self.first_player
        return

    def play(self, p):
        self.player = not self.player
        return

    def search(self):
        index = -1

        plays = self.board.getPlays(self.player)
        sz = len(plays)

        self.board.printBoard()

        for i in xrange(0,sz):
            print("{}:".format(i),end = '')
            printPlay(plays[i])
        print("")

        while True:
            print("Choose a move: ",end = "")
            sys.stdout.flush()
            index = -1
            try:
                index = int(raw_input())
            except ValueError:
                print("Invalid move"); continue

            if not self.inRange(index, 0, sz-1): print("Invalid move")
            else: break

        self.board.best_play = plays[index]
        return

    def inRange(self, x, i, j):
        return x>=i and x<=j
