from PrettyPrint import PrettyPrintTree

class Node:
    def __init__(self, value):
        self.val = value
        self.adj = []
    def addChild(self, child):
        self.adj.append(child)
pt = PrettyPrintTree(lambda x: x.adj, lambda x: x.val)
with open("../Logs/log.txt") as file:
    node_count = int(file.readline().strip())
    nodes = [Node(i) for i in range(1, node_count + 1)]
    for line in file:
        edge = line.strip().split()
        u, v = map(int, edge)
        nodes[u - 1].addChild(nodes[v - 1])
    pt(nodes[0])

