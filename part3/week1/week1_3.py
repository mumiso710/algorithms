FILENAME = 'edges.txt'
STARTVERTEX = 1


class Edge():

    def __init__(self, to, weight):
        self.to     = to
        self.weight = weight

def readFileAndCreateAdjacencyList():
    file = open(FILENAME, 'r')
    lines = file.read().splitlines()
    file.close()
    nodeAndEdgeNum = lines[0].split(' ')
    edges = lines[1:]  
    nodeNum, edgeNum = int(nodeAndEdgeNum[0]), int(nodeAndEdgeNum[1])
    adjacencyList = [[]] * (nodeNum + 1) # Python list is 0-Index
    for n in range(nodeNum):
        adjacencyList[n] = []
    for edge in edges:
        edge = edge.split(' ')
        n1, n2, w = int(edge[0]), int(edge[1]), int(edge[2])
        adjacencyList[n1].append(Edge(n2, w))
        adjacencyList[n2].append(Edge(n1, w))
    return adjacencyList

def prim():
    X = [STARTVERTEX] # This is processed vertices set
    T = []
    while len(X) < len(adjacencyList) - 1: # Python list is 0-Index
        minWeight = float('inf')
        for v in X:
            for e in adjacencyList[v]:
                if e.weight <= minWeight and (not e.to in X):
                    minWeight = e.weight
                    minEdge = e
        if not minEdge.to in X:
            X.append(minEdge.to)
            T.append(minEdge)
    return T



if __name__ == '__main__':
    adjacencyList = readFileAndCreateAdjacencyList()
    T = prim()           # the edges in T span X
    ans = 0
    for e in T:
        ans += e.weight
    print(ans)
    
