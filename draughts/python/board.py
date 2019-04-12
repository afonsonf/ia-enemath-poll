from __future__ import print_function

import sys
from collections import deque

from common import *
from play  import *

valueOfKing = 5

values = [
  [1, 1, 1, 1, 1, 1, 1, 1],
  [1, 1, 1, 1, 1, 1, 1, 1],
  [1, 1, 1, 1, 1, 1, 1, 1],
  [1, 1, 1, 1, 1, 1, 1, 1],
  [1, 1, 1, 1, 1, 1, 1, 1],
  [1, 1, 1, 1, 1, 1, 1, 1],
  [1, 1, 1, 1, 1, 1, 1, 1],
  [1, 1, 1, 1, 1, 1, 1, 1]
]

valuesKing = [
  [1, 1, 1, 1, 1, 1, 1, 1],
  [1, 1, 1, 1, 1, 1, 1, 1],
  [1, 1, 3, 3, 3, 3, 1, 1],
  [1, 1, 3, 4, 4, 3, 1, 1],
  [1, 1, 3, 4, 4, 3, 1, 1],
  [1, 1, 3, 3, 3, 3, 1, 1],
  [1, 1, 1, 1, 1, 1, 1, 1],
  [1, 1, 1, 1, 1, 1, 1, 1]
]

class Board:
    #add more if needed
    __slots__ = ['playsStack','best_play','depth','board','movesStack']

    def __init__(self):
        self.playsStack = []
        self.movesStack = []
        self.depth = 0

        self.board = []
        #initialize board
        for a in xrange(0,8):
            line = []
            for b in xrange(0,8):
                if   b<3 and (b+a)%2 == 0: line.append(1)
                elif b>4 and (b+a)%2 == 0: line.append(-1)
                else: line.append(0)
            self.board.append(line)

        return

    def dup(self):
        board = Board()
        if len(self.playsStack) > 0: board.playsStack.append(self.playsStack[len(self.playsStack)-1])
        board.depth = self.depth

        #copy board
        for i in xrange(0,8):
            for j in xrange(0,8): board.board[i][j] = self.board[i][j]

        return board

    def validMove(self, p, code):
        if not self.inBounds(p):
            print("Error: pos not in bounds ({},{})".format(p.i,p.j))
            return False
        if self.open(p):
            print("Error: no piece in pos ({},{})".format(p.i,p.j))
            return False
        if code == 0 and not self.open(Pos(p.i-1,p.j+1)):
            print("Error: try step right up, pos not open ({},{})".format(p.i,p.j))
            return False
        if code == 1 and not self.open(Pos(p.i+1,p.j+1)):
            print("Error: try step right down, pos not open ({},{})".format(p.i,p.j))
            return False
        if code == 4 and not self.open(Pos(p.i-1,p.j-1)):
            print("Error: try step left up, pos not open ({},{})".format(p.i,p.j))
            return False
        if code == 5 and not self.open(Pos(p.i+1,p.j-1)):
            print("Error: try step left down, pos not open ({},{})".format(p.i,p.j))
            return False

        if code == 2 and not self.jumpOK(p,Pos(p.i-1,p.j+1)):
            print("Error: try jump right up, pos not open ({},{})".format(p.i,p.j))
            return False
        if code == 3 and not self.jumpOK(p,Pos(p.i+1,p.j+1)):
            print("Error: try jump right down, pos not open ({},{})".format(p.i,p.j))
            return False
        if code == 6 and not self.jumpOK(p,Pos(p.i-1,p.j-1)):
            print("Error: try jump left up, pos not open ({},{})".format(p.i,p.j))
            return False
        if code == 7 and not self.jumpOK(p,Pos(p.i+1,p.j-1)):
            print("Error: try jump left down, pos not open ({},{})".format(p.i,p.j))
            return False
        return True

    def play_aux(self, pos, code):
        if not self.validMove(pos,code):
            self.printBoard()
            sys.exit(1)

        mv = Move()

        value = self.board[pos.i][pos.j]
        self.board[pos.i][pos.j] = 0

        px = pos.dup()

        if code == 0:
            px.i-=1; px.j+=1
        elif code == 1:
            px.i+=1; px.j+=1
        elif code == 2:
            mv.last_eat = self.board[pos.i-1][pos.j+1]
            self.board[pos.i-1][pos.j+1] = 0
            px.i-=2; px.j+=2
        elif code == 3:
            mv.last_eat = self.board[pos.i+1][pos.j+1]
            self.board[pos.i+1][pos.j+1] = 0
            px.i+=2; px.j+=2
        elif code == 4:
            px.i-=1; px.j-=1
        elif code == 5:
            px.i+=1; px.j-=1
        elif code == 6:
            mv.last_eat = self.board[pos.i-1][pos.j-1]
            self.board[pos.i-1][pos.j-1] = 0
            px.i-=2; px.j-=2
        elif code == 7:
            mv.last_eat = self.board[pos.i+1][pos.j-1]
            self.board[pos.i+1][pos.j-1] = 0
            px.i+=2; px.j-=2
        else:
            print("Error: code for play invalid {}").format(code)
            sys.exit(1)

        self.board[px.i][px.j] = value
        if (px.j == 0 and value == -1) or (px.j == 7 and value == 1): #king it
            self.board[px.i][px.j] *= valueOfKing
            mv.last_up = True
        else: mv.last_up = False

        mv.last_pos = px
        mv.last_code = code

        self.movesStack.append(mv)
        return px

    def rmplay_aux(self):
        mv = self.movesStack[len(self.movesStack)-1]
        self.movesStack.pop()

        value = self.board[mv.last_pos.i][mv.last_pos.j]
        self.board[mv.last_pos.i][mv.last_pos.j] = 0

        if mv.last_up: value /= valueOfKing

        if mv.last_code == 0:
            mv.last_pos.i+=1; mv.last_pos.j-=1
        elif mv.last_code == 1:
            mv.last_pos.i-=1; mv.last_pos.j-=1
        elif mv.last_code == 2:
            mv.last_pos.i+=2; mv.last_pos.j-=2
            self.board[mv.last_pos.i-1][mv.last_pos.j+1] = mv.last_eat
        elif mv.last_code == 3:
            mv.last_pos.i-=2; mv.last_pos.j-=2
            self.board[mv.last_pos.i+1][mv.last_pos.j+1] = mv.last_eat
        elif mv.last_code == 4:
            mv.last_pos.i+=1; mv.last_pos.j+=1
        elif mv.last_code == 5:
            mv.last_pos.i-=1; mv.last_pos.j+=1
        elif mv.last_code == 6:
            mv.last_pos.i+=2; mv.last_pos.j+=2
            self.board[mv.last_pos.i-1][mv.last_pos.j-1] = mv.last_eat
        elif mv.last_code == 7:
            mv.last_pos.i-=2; mv.last_pos.j+=2
            self.board[mv.last_pos.i+1][mv.last_pos.j-1] = mv.last_eat
        else:
            print("Error: code for play invalid {}").format(code)
            sys.exit(1)

        self.board[mv.last_pos.i][mv.last_pos.j] = value

    def play(self, p):
        self.playsStack.append(p.dup())

        piece = p.piece.dup()

        #play p in board
        for code in p.codes:
            piece = self.play_aux(piece, code)
        return


    def rmplay(self):
        p = self.playsStack[len(self.playsStack)-1]
        self.playsStack.pop()

        #rm play p from board
        for code in p.codes: self.rmplay_aux()
        return

    def inBounds(self, pos):
        return pos.i>=0 and pos.i<8 and pos.j>=0  and pos.j<8

    def open(self, pos):
        return self.inBounds(pos) and self.board[pos.i][pos.j] == 0

    def jumpOK(self, pos1, pos2):
        return self.open(Pos(2*pos2.i-pos1.i, 2*pos2.j - pos1.j)) and self.inBounds(pos2) and (sign(self.board[pos1.i][pos1.j]) == -sign(self.board[pos2.i][pos2.j]))

    def canJump(self, pos):
        value = self.board[pos.i][pos.j]
        if (value>0 or value ==-valueOfKing) and (self.jumpOK(pos,Pos(pos.i-1,pos.j+1)) or self.jumpOK(pos, Pos(pos.i+1,pos.j+1))): return True
        if (value<0 or value ==valueOfKing)  and (self.jumpOK(pos,Pos(pos.i-1,pos.j-1)) or self.jumpOK(pos, Pos(pos.i+1,pos.j-1))): return True
        return False

    def canStep(self, pos):
        value = self.board[pos.i][pos.j]
        if (value>0 or value ==-valueOfKing) and (self.open(Pos(pos.i-1,pos.j+1)) or self.open(Pos(pos.i+1,pos.j+1))): return True
        if (value<0 or value ==valueOfKing)  and (self.open(Pos(pos.i-1,pos.j-1)) or self.open(Pos(pos.i+1,pos.j-1))): return True
        return False

    def getMovablePieces(self, player):
        res = []
        p = Pos()
        for i in xrange(0,8):
            for j in xrange(0,8):
                p.i = i; p.j = j
                if sign(self.board[i][j]) == (1 if player else -1) and self.canJump(p): res.append(p.dup())

        if len(res) == 0:
            for i in xrange(0,8):
                for j in xrange(0,8):
                    p.i = i; p.j = j
                    if sign(self.board[i][j]) == (1 if player else -1) and self.canStep(p): res.append(p.dup())

        return res

    def getPlays(self, player):
        res = []
        pieces = self.getMovablePieces(player)
        moves = deque()

        #add playable plays to res
        play = Play()
        for p in pieces:
            moves = self.getMoves(p)
            for codes in moves:
                play.piece = p
                play.codes = codes
                res.append(play.dup())

        return res

    def whoWins(self, next_player):
        # next player is false and loses return  1 (true wins)
        # next player is true  and loses return -1 (false wins)
        # else return 0

        if len(self.getMovablePieces(next_player)) == 0:
            if next_player: return -1
            return 1
        return 0

    def isDraw(self):
        #check if draw

        return False

    def gameOver(self, next_player):
        if self.whoWins(next_player) or self.isDraw(): return True
        return False

    def getJumpMoves(self, pos):
        moves = []
        mx = []
        value = self.board[pos.i][pos.j]

        px = Pos()
        if value>0 or value == -valueOfKing:
            if self.jumpOK(pos, Pos(pos.i-1, pos.j+1)):
                px = self.play_aux(pos, 2)
                mx = self.getJumpMoves(px)
                self.rmplay_aux()

                if len(mx) == 0:
                    aux = deque(); aux.append(2)
                    moves.append(aux)
                else:
                    for m in mx:
                        m.appendleft(2)
                        moves.append(m)

            if self.jumpOK(pos, Pos(pos.i+1, pos.j+1)):
                px = self.play_aux(pos, 3)
                mx = self.getJumpMoves(px)
                self.rmplay_aux()

                if len(mx) == 0:
                    aux = deque(); aux.append(3)
                    moves.append(aux)
                else:
                    for m in mx:
                        m.appendleft(3)
                        moves.append(m)

        if value<0 or value == valueOfKing:
            if self.jumpOK(pos, Pos(pos.i-1, pos.j-1)):
                px = self.play_aux(pos, 6)
                mx = self.getJumpMoves(px)
                self.rmplay_aux()

                if len(mx) == 0:
                    aux = deque(); aux.append(6)
                    moves.append(aux)
                else:
                    for m in mx:
                        m.appendleft(6)
                        moves.append(m)

            if self.jumpOK(pos, Pos(pos.i+1, pos.j-1)):
                px = self.play_aux(pos, 7)
                mx = self.getJumpMoves(px)
                self.rmplay_aux()

                if len(mx) == 0:
                    aux = deque(); aux.append(7)
                    moves.append(aux)
                else:
                    for m in mx:
                        m.appendleft(7)
                        moves.append(m)

        return moves

    def getStepMoves(self, pos):
        moves = []
        value = self.board[pos.i][pos.j]

        if value>0 or value == -valueOfKing:
            if self.open(Pos(pos.i-1, pos.j+1)):
                aux = deque(); aux.append(0)
                moves.append(aux)
            if self.open(Pos(pos.i+1, pos.j+1)):
                aux = deque(); aux.append(1)
                moves.append(aux)
        if value<0 or value == valueOfKing:
            if self.open(Pos(pos.i-1, pos.j-1)):
                aux = deque(); aux.append(4)
                moves.append(aux)
            if self.open(Pos(pos.i+1, pos.j-1)):
                aux = deque(); aux.append(5)
                moves.append(aux)

        return moves

    def getMoves(self, pos):
        if self.canJump(pos): return self.getJumpMoves(pos)
        if self.canStep(pos): return self.getStepMoves(pos)

    def eval_board(self):
        value = 0
        for i in xrange(0,8):
            for j in xrange(0,8):
                pieceValue = self.board[i][j]
                if abs(pieceValue) == valueOfKing:
                    value += valuesKing[i][j] * pieceValue
                elif pieceValue > 0:
                    value += values[i][j] * pieceValue
                elif pieceValue < 0:
                    value += values[i][j] * pieceValue

        return value

    def printBoard(self):
        print(" | ", end="")
        for i in xrange(0,8): print("{} ".format(i),end="")
        print(" |")
        for i in xrange(0,8):
            print("{}| ".format(i),end="")
            for j in xrange(0,8):
                value = self.board[i][j]
                if value == -valueOfKing: print("B ",end="")
                elif value == -1: print("b ",end="")
                elif value ==  0: print("_ ",end="")
                elif value ==  1: print("r ",end="")
                elif value == valueOfKing: print("R ",end="")
                else: print("invalid symbol in board"); sys.exit(1)
            print(" |{}".format(i))
        print(" | ", end="")
        for i in xrange(0,8): print("{} ".format(i),end="")
        print(" |\n")
        return
