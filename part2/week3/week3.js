const fs = require('fs');

const ELEMENT_NUM = 10000;

const queue = [];

const maxHeap = [];
const minHeap = [];

const makeQueue = () => {
    let lines = fs.readFileSync('Median.txt', 'utf-8');

    lines = lines.split(/\r\n/);
    lines = lines.slice(0, lines.length-1);

    for (const line of lines) {
        queue.push(parseInt(line));
    }
}

const insertMaxHeap = element => {
    const swap = i => {
        const childIndex = i;
        const parentIndex = Math.floor((childIndex+1) / 2)- 1;
        if (childIndex !== 0 && maxHeap[childIndex] > maxHeap[parentIndex]) {
            [maxHeap[childIndex], maxHeap[parentIndex]] = [maxHeap[parentIndex], maxHeap[childIndex]];
            swap(parentIndex);
        }
    }

    maxHeap.push(element);
    swap(maxHeap.length-1);
}

const insertMinHeap = element => {
    const swap = i => {
        const childIndex = i;
        const parentIndex = Math.floor((childIndex+1) / 2) - 1;
        if (childIndex !== 0 && minHeap[childIndex] < minHeap[parentIndex]) {
            [minHeap[childIndex], minHeap[parentIndex]] = [minHeap[parentIndex], minHeap[childIndex]];
            swap(parentIndex);
        }
    }

    minHeap.push(element);
    swap(minHeap.length-1);
}



const extractMax = () => {
    const swap = i => {
        const parentIndex = i;
        const childLeftIndex = (parentIndex + 1) * 2 - 1;
        const childRightIndex = (parentIndex + 1) * 2;
        let maxChild, maxChildIndex;
        if (childLeftIndex >= maxHeap.length) return;
        if (childRightIndex < maxHeap.length) {
            maxChild = Math.max(maxHeap[childLeftIndex], maxHeap[childRightIndex]);
            maxChildIndex = maxHeap[childLeftIndex] > maxHeap[childRightIndex] ? childLeftIndex : childRightIndex;
        } else {
            maxChild = maxHeap[childLeftIndex];
            maxChildIndex = childLeftIndex;
        }
        if (maxHeap[parentIndex] < maxChild) {
            [maxHeap[maxChildIndex], maxHeap[parentIndex]] = [maxHeap[parentIndex], maxHeap[maxChildIndex]];
            swap(maxChildIndex);
        }
    }

    const maxElement = maxHeap[0];
    maxHeap[0] = maxHeap.pop();
    swap(0);

    return maxElement;
}

const extractMin = () => {
    const swap = i => {
        const parentIndex = i;
        const childLeftIndex = (parentIndex + 1) * 2 - 1;
        const childRightIndex = (parentIndex + 1) * 2;
        let minChild, minChildIndex;
        if (childLeftIndex >= minHeap.length) return;
        if (childRightIndex < minHeap.length) {
            minChild = Math.min(minHeap[childLeftIndex], minHeap[childRightIndex]);
            minChildIndex = minHeap[childLeftIndex] < minHeap[childRightIndex] ? childLeftIndex : childRightIndex;
        } else {
            minChild = minHeap[childLeftIndex];
            minChildIndex = childLeftIndex;
        }
        if (minHeap[parentIndex] > minChild) {
            [minHeap[minChildIndex], minHeap[parentIndex]] = [minHeap[parentIndex], minHeap[minChildIndex]];
            swap(minChildIndex);
        }
    }

    const minElement = minHeap[0];
    minHeap[0] = minHeap.pop();
    swap(0);

    return minElement;
}


const main = () => {
    let k = 0;
    makeQueue();
    const medians = [];
    const e1 = queue.shift();
    medians.push(e1);
    minHeap.push(e1);
    k++;
    const e2 = queue.shift();
    medians.push(e2);
    maxHeap.push(e2);
    k++;
    while(queue.length) {
        const element = queue.shift();
        const maxElement = maxHeap[0];
        const minElement = minHeap[0];
        if (element < minElement) {
            insertMaxHeap(element);
        } else {
            insertMinHeap(element);
        }

        k++;

        if (maxHeap.length - minHeap.length >= 2) {
            const movedElement = extractMax();
            insertMinHeap(movedElement);
        } else if (minHeap.length - maxHeap.length >= 2) {
            const movedElement = extractMin();
            insertMaxHeap(movedElement);
        }

        if (k % 2 == 0) {
            medians.push(maxHeap[0]);
        } else if (maxHeap.length > minHeap.length) {
            medians.push(maxHeap[0]);
        } else {
            medians.push(minHeap[0]);
        }

    }
    const sumMedians = medians.reduce((median, acc) => acc + median);
    let sum = 0;
    for (median of medians) {
        sum += median;
    }
    console.log('med : ', sum);
    return sumMedians % 10000;

}

const medians = main();

console.log(medians)