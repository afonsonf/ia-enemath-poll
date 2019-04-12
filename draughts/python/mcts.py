import math
import random
import sys

EXPLOR_PARAM = 1.3
depth_mcts = 60

class Node:
    __slots__ = ['parent', 'next_player', 'games', 'reward', 'nexpanded', 'terminal', 'res', 'board', 'lst_plays', 'lst_childs']

    def __init__(self, node, player, board):
        self.parent = node
        self.board = board

        self.next_player = player
        self.games = 0
        self.reward = 0

        self.nexpanded = 0
        self.terminal = False
        self.res = 0

        self.lst_plays = []
        self.lst_childs = []
        return

    def hasChilds(self):
        return len(self.lst_childs)>0

class MCTS:
    __slots__ = ['ngames', 'first_player', 'root', 'board']

    def __init__(self, ngames, first_player):
        random.seed(42)
        self.ngames = ngames
        self.first_player = first_player
        return

    def init(self, board):
        self.root = Node(None, self.first_player, board.dup())
        self.expand(self.root)
        self.board = board
        return

    def play(self, p):
        i = 0
        for x in self.root.lst_plays:
            if x == p: break
            i += 1
        if i == len(self.root.lst_plays):
            print("MCTS::play play not found")
            sys.exit(1)

        child = self.root.lst_childs[i]
        self.root.lst_childs[i] = None
        #clean root

        self.root = child
        self.root.parent = None

        if not self.root.hasChilds(): self.expand(self.root)
        return

    def search(self):
        jogos = 0

        while jogos < self.ngames:
            child = self.select(self.root)
            if not child.terminal: self.expand(child)

            dup = child.board.dup()
            res = 0
            if child.terminal: res = child.res
            else: res = self.simulate(dup,child.next_player,depth_mcts,child)

            self.backpropagate(child, res)
            #clean dup
            jogos += 1

        best_i = 0
        best_value = -100000
        sz = len(self.root.lst_plays)

        for i in xrange(0,sz):
            child = self.root.lst_childs[i]
            val = self.eval(self.root, child, 0)
            if val > best_value:
                best_i = i
                best_value = val

        self.board.best_play = self.root.lst_plays[best_i]
        return

    def eval(self, parent, node, const):
        if not node.hasChilds(): return 0.5 + const*math.sqrt(math.log(parent.games+1))

        wr = node.reward*1.0/(node.games+1)
        return wr + const*math.sqrt(2.0*math.log(parent.games+1)/(node.games+1))

    def select_child(self, node):
        sz = len(node.lst_childs)

        v = []
        if not sz == node.nexpanded:
            for i in xrange(0,sz):
                if not node.lst_childs[i].hasChilds(): v.append(i)
            random.shuffle(v)
            node.nexpanded += 1
            return v[0]

        best_val = -100000
        for i in xrange(0,sz):
            child = node.lst_childs[i]

            val = self.eval(node, child, EXPLOR_PARAM)
            if val > best_val:
                best_val = val
                v = []
                v.append(i)
            elif val == best_val: v.append(i)

        random.shuffle(v)
        return v[0]

    def select(self, node):
        if node is None:
            print("Erro null")
            sys.exit(1)

        if not node.hasChilds(): return node

        best = self.select_child(node)
        return node.lst_childs[best]

    def expand(self, node):
        node.lst_plays = node.board.getPlays(node.next_player)
        sz = len(node.lst_plays)
        for i in xrange(0,sz):
            dup = node.board.dup()
            dup.play(node.lst_plays[i])
            node.lst_childs.append(Node(node, not node.next_player, dup))

        return

    def simulate(self, board, player, depth, child):
        if board.gameOver(player):
            k = board.whoWins(player)
            if depth == depth_mcts:
                child.terminal = True
                child.res = k
            return k
        if depth == 0: return 0

        plays = board.getPlays(player)
        random.shuffle(plays)
        board.play(plays[0])

        return self.simulate(board, not player, depth-1, child)

    def backpropagate_aux(self, node, val):
        if node is None: return

        node.reward += val
        node.games += 1

        self.backpropagate_aux(node.parent, val)
        return

    def backpropagate(self, node, res):
        if (self.root.next_player and res>0) or ((not self.root.next_player) and res<0):
            if node.terminal: self.backpropagate_aux(node, 5.0)
            else: self.backpropagate_aux(node, 1.0)
        elif (self.root.next_player and res<0) or ((not self.root.next_player) and res>0):
            if node.terminal: self.backpropagate_aux(node, -10.0)
            else: self.backpropagate_aux(node, -1.0)
        elif res == 0:
            self.backpropagate_aux(node, 0)
        return
