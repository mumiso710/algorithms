const fs = require('fs');

const INF = 1000000;
const NODE_NUM = 200;
const START = 1;

const adjacencyList = new Map();

const makeAdjacencyList = () => {
    // initialize adjacencyList
    for (let i = 1; i <= NODE_NUM; i++) {
        adjacencyList[i] = [];
    }

    let lines = fs.readFileSync('dijkstraData.txt', 'utf-8');


    // adjacencyList = fs.readFileSync('test.txt', 'utf-8');
    lines = lines.split(/\r\n|\n/);
    lines = lines.slice(0,200);

    // remove '' element
    lines = lines.map(line => line.split(/\t/).filter(line => line));

    for (const line of lines) {
        adjacencyList[line[0]] = line.slice(1).map(element => element.split(','));
        adjacencyList[parseInt(line[0])] = adjacencyList[line[0]].map(([vertex, l]) => ({vertex: parseInt(vertex), l: parseInt(l)}))
    }

}

makeAdjacencyList()


function dijkstra(destination) {
    let a = new Array(201);
    a[1] = 0;
    let x = new Set();
    x.add(START);
    while(!x.has(destination)) {
        let w = START;
        let minWeight = Infinity;
        let from = START;
        for (const v of x) {
            for (const edge of adjacencyList[v]) {
               if (minWeight > a[v]+edge.l && !x.has(edge.vertex)) {
                   minWeight = a[v] + edge.l;
                   w = edge.vertex;
                   from = v;
               }
            }
        }
        // console.log(destination, from, minWeight, w)
        x.add(w);
        a[w] = minWeight;
    }
    return a[destination];
}

function solve() {
    const ans = [];
    const destinations = [7,37,59,82,99,115,133,165,188,197];

    for (const dest of destinations) {
        ans.push(dijkstra(dest));
    }
    console.log(ans);
}

solve();
