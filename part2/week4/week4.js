const fs = require('fs');

let numbers = [];

const makeNumbers = () => {
    let lines = fs.readFileSync('algo1-programming_prob-2sum.txt', 'utf-8');

    lines = lines.split(/\n/);
    lines = lines.slice(0, lines.length - 1);

    for (const line of lines) {
        numbers.push(parseInt(line));
    }

    numbers.sort((a, b) => {
        if (a < b) return -1;
        if (a > b) return 1;
        return 0;
    });

}

makeNumbers();


let ans = new Set();
let minIndex = 0;
let maxIndex = numbers.length - 1;
while (minIndex < maxIndex) {
    if (numbers[minIndex] + numbers[maxIndex] < -10000) {
        minIndex++;
    }
    else if (numbers[minIndex] + numbers[maxIndex] > 10000) {
        maxIndex--;
    }
    if (minIndex === maxIndex) break;

    let tempIndex = minIndex;
    let sum = numbers[tempIndex] + numbers[maxIndex];
    while (sum <= 10000) {
        if (-10000 <= sum) {
            ans.add(sum);
        }
        tempIndex++;
        if (tempIndex === maxIndex) break;
        sum = numbers[tempIndex] + numbers[maxIndex]
    }
    maxIndex--;
}

console.log(ans.size);