class Pos:
    __slots__ = ['i','j']

    def __init__(self, i=0, j=0):
        self.i = i
        self.j = j
        return

    def dup(self):
        return Pos(self.i, self.j)

    def __eq__(self, other):
        return self.i == other.i and self.j == other.j

    def __lt__(self, other):
        if self.i == other.i: return self.j < other.j
        return self.i < other.i

    def __str__(self):
        return str(("{} {}").format(self.i, self.j))

class Move:
    __slots__ = ['last_pos', 'last_code', 'last_eat', 'last_up']

def sign(a):
    if   a<0: return -1
    elif a>0: return 1
    return 0
