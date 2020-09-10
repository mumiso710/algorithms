const fs = require('fs');

const NODE_NUM = 875714;
// const NODE_NUM = 11;
let adjacencyList = new Map();
let adjacencyListRev = new Map();
let explored = new Set();
let curLabel = NODE_NUM;
let f = new Array(NODE_NUM+1);
let scc = new Array(NODE_NUM);
let numSCC;


const makeAdjacencyList = () => {
    // initialize adjacencyList
    for (let i = 1; i <= NODE_NUM; i++) {
        adjacencyList[i] = [];
        adjacencyListRev[i] = [];
    }

    let lines = fs.readFileSync('SCC.txt', 'utf-8');

    // adjacencyList = fs.readFileSync('test.txt', 'utf-8');
    lines = lines.toString().split(/\r\n|\n/);
    // remove '' element
    lines = lines.map(line => line.split(" ").filter(line => line));
    for (const line of lines) {
        adjacencyList[parseInt(line[0])] = adjacencyList[parseInt(line[0])].concat(parseInt(line[1]));
        adjacencyListRev[parseInt(line[1])] = adjacencyListRev[parseInt(line[1])].concat(parseInt(line[0]));
    }
}


async function topoSort(G) {
    explored = new Set();
    for (let v = 1; v <= NODE_NUM; v++) {
        if (!explored.has(v)) {
            explored.add(v);
            await dfsTopo(G, v);
        }
    }
}

async function dfsTopo(G, v) {
    explored.add(v);
    for (const node of G[v]) {
        if (!explored.has(node)) {
            await dfsTopo(G, node);
        }
    }
    f[curLabel] = v;
    curLabel--;
}




async function kosaraju() {
    makeAdjacencyList();
    await topoSort(adjacencyListRev);
    numSCC = 0;
    explored = new Set();
    for (let i = 1; i <= NODE_NUM; i++) {
        // console.log('now ', i, 'th node');
        // let v = f.indexOf(i) + 1;
        let v= f[i];
        if (!explored.has(v)) {
            numSCC++;
            await dfsSCC(adjacencyList, v);
        }
    }
}

async function dfsSCC(G, v) {
    explored.add(v);
    scc[v - 1] = numSCC;
    for (const node of G[v]) {
        if (!explored.has(node)) {
            await dfsSCC(G, node);
        }
    }
}


async function printAnswer() {
    await kosaraju();

    let sccSum = new Map();
    let ans = [];

    for (sccNum of scc) {
        sccSum[sccNum] = 0;
    }

    for (sccNum of scc) {
        sccSum[sccNum]++;
    }

    let maxScc;
    for (let i = 0; i < 5; i++) {
        let max = -Infinity;
        for (const sccNum in sccSum) {
            if (sccSum[sccNum] >= max && !ans.includes(sccSum[sccNum])) {
                max = sccSum[sccNum];
                maxScc = sccNum;
            }
        }
        ans.push(max);
    }

    console.log(ans);
}
printAnswer();
// console.log(adjacencyList);
// console.log(adjacencyList.size);