package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
)

const integerNum = 100000

func main() {
	xs := readFileAndMakeArray("IntegerArray.txt")
	_, numInv := sortAndCountInv(xs)
	fmt.Println(numInv)
}

func sortAndCountInv(xs []int) (sortedArr []int, numInv int) {
	n := len(xs)

	if n == 0 || n == 1 {
		return xs, 0
	}

	leftxs, leftInv := sortAndCountInv(xs[:n/2])
	rightxs, rightInv := sortAndCountInv(xs[n/2:])
	sortedArr, splitInv := mergeAndCountSplitInv(leftxs, rightxs)
	return sortedArr, leftInv + rightInv + splitInv

}

func mergeAndCountSplitInv(left []int, right []int) (mergeArr []int, splitInv int) {
	n := len(left) + len(right)
	mergeArr = make([]int, 0, n)
	splitInv = 0
	leftIndex := 0
	rightIndex := 0
	for i := 0; i < n; i++ {
		if rightIndex == len(right) || (leftIndex < len(left) && left[leftIndex] < right[rightIndex]) {
			mergeArr = append(mergeArr, left[leftIndex])
			leftIndex++
		} else {
			mergeArr = append(mergeArr, right[rightIndex])
			splitInv += len(left) - leftIndex
			rightIndex++
		}
	}
	return mergeArr, splitInv
}

func readFileAndMakeArray(name string) (xs []int) {
	xs = make([]int, 0, integerNum)
	f, err := os.Open(name)
	if err != nil {
		log.Fatalln(err)
	}
	defer f.Close()

	scanner := bufio.NewScanner(f)
	for scanner.Scan() {
		line, err := strconv.Atoi(scanner.Text())
		if err != nil {
			log.Fatalln(err)
		}
		xs = append(xs, line)
	}
	return xs
}
