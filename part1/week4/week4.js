const fs = require('fs');

const SIMULATION_NUM = 10000;
let adjacencyList;

const makeAdjacencyList = () => {
    adjacencyList = fs.readFileSync('kargerMinCut.txt', 'utf-8');
    // adjacencyList = fs.readFileSync('test.txt', 'utf-8');
    adjacencyList = adjacencyList.toString().split(/\r\n|\n/);
    // remove '' element
    adjacencyList = adjacencyList.slice(0, adjacencyList.length-1);
    adjacencyList = adjacencyList.map(array => array.split(/\t/).filter(node => node));
    adjacencyList = adjacencyList.map(([vertex, ...adjacents]) => ({vertex: vertex, adjacents: adjacents}));
}

const chooseVertices = () => {
    const baseIndex = Math.floor(Math.random() * adjacencyList.length);
    const {vertex, adjacents} = adjacencyList[baseIndex];
    const baseVertex = vertex;
    let mergedIndex = Math.floor(Math.random() * adjacents.length);
    const mergedVertex = adjacents[mergedIndex];
    return {baseVertex, mergedVertex};
}


function getAdjacents(targetVertex) {
    return adjacencyList.filter(({vertex}) => vertex === targetVertex)[0].adjacents;
}

function getIndex(targetVertex) {
    return adjacencyList.findIndex(({vertex}) => vertex === targetVertex);
}


function updateAdjacents(targetVertex, baseVertex, mergedVertex) {
    if (targetVertex === baseVertex) {
        adjacencyList[getIndex(baseVertex)].adjacents = getAdjacents(baseVertex).concat(getAdjacents(mergedVertex));
        adjacencyList = adjacencyList.filter(({vertex}) => vertex !== mergedVertex);
    }
    const beforeAdjacents = getAdjacents(targetVertex);
    const updatedAdjacents = beforeAdjacents.map(vertex => {
        if (vertex === mergedVertex) {
            return baseVertex;
        } else {
            return vertex
        }
    })
    adjacencyList[getIndex(targetVertex)].adjacents = updatedAdjacents;
    adjacencyList[getIndex(baseVertex)].adjacents = getAdjacents(baseVertex).filter((vertex) => vertex !== baseVertex);
}

const mergeVertices = ({baseVertex, mergedVertex}) => {
    let mergedAdjacents = new Set(getAdjacents(mergedVertex));
    for (let target of mergedAdjacents) {
        updateAdjacents(target, baseVertex, mergedVertex)
    }
}

function main() {
    let minCut = Infinity;
    for (let i=0; i < SIMULATION_NUM; i++) {
        makeAdjacencyList();
        while (adjacencyList.length > 2) {
            mergeVertices(chooseVertices());
        }
        let cutNum = adjacencyList[0].adjacents.length

        if (minCut > cutNum) {
            minCut = cutNum;
        }
        console.log('now : ', i, 'th simulation and minCut is ', minCut);
    }
    console.log(minCut);
}

main();