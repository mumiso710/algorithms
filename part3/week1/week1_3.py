FILENAME = 'edges.txt'
STARTVERTEX = 0


class Edge():

    def __init__(self, to, weight):
        self.to     = to
        self.weight = weight

if __name__ == '__main__':
    file = open(FILENAME, 'r')
    lines = file.read().splitlines()
    file.close()
    nodeAndEdgeNum = lines[0].split(' ')
    edges = lines[1:]  
    nodeNum, edgeNum = int(nodeAndEdgeNum[0]), int(nodeAndEdgeNum[1])
    adjacencyList = [[]] * nodeNum
    for edge in edges:
        edge = edge.split(' ')
        n1, n2, w = int(edge[0]), int(edge[1]), int(edge[2])
        adjacencyList[n1-1] = Edge(n2, w)
        adjacencyList[n2-1] = Edge(n1, w)
