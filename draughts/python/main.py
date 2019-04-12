from __future__ import print_function

from board import *
from play  import *

from human import *
from mcts import *
from minimax import *

SEE = False
depth_max = 120

board = 0
first_player = False

####################################################

p1 = MCTS(1000, first_player);
# p2 = MCTS(10000, first_player);

# p1 = Minimax(6,first_player);
p2 = Minimax(4,first_player);

# p1 = Human(first_player);
# p2 = Human(first_player);

####################################################

ngames = 100
w = 0
d = 0
l = 0
plays = 0
win = 0

while ngames > 0:
    ngames -= 1
    board = Board()
    player = first_player

    p1.init(board)
    p2.init(board)

    plays = 0
    if SEE: board.printBoard()
    while True:
        if board.gameOver(player):
            win = board.whoWins(player)
            if win == -1:
                l += 1
                print("False wins ({:2d}::{:2d}::{:2d}) {}".format(w,d,l,plays))
            elif win == 1:
                w += 1
                print("True wins  ({:2d}::{:2d}::{:2d}) {}".format(w,d,l,plays))
            else:
                d += 1
                print("draw       ({:2d}::{:2d}::{:2d})".format(w,d,l))
            break

        if plays > depth_max:
            d += 1
            print("draw       ({:2d}::{:2d}::{:2d})".format(w,d,l))
            break

        if player: p1.search()
        else:      p2.search()

        if SEE :
            if player: print("True plays")
            else: print("False plays")

        board.play(board.best_play)
        p1.play(board.best_play)
        p2.play(board.best_play)

        if SEE: board.printBoard()

        player = not player
        plays += 1
    #del board

print("w: {}\nd: {}\nl: {}".format(w,d,l))
