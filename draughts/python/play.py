from __future__ import print_function

from collections import deque
from common import *

class Play:
    __slots__ = ['piece','codes']

    def __eq__(self, other):
        if not self.piece == other.piece: return False
        if not (len(self.codes) == len(other.codes)): return False

        return self.codes == other.codes

    def dup(self):
        p = Play()
        p.piece = self.piece.dup()
        p.codes = deque(self.codes)
        return p

def printPlay(p):
    print("({},{})".format(p.piece.i,p.piece.j),end="")
    for code in p.codes: print(" {}".format(code),end="")
    print("")
    return
