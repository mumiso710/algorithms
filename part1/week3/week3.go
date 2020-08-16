package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
)

const arraySize = 10000

func main() {
	a := readFileAndMakeArray("test.txt")
	ans := quickSort(a, 0, len(a) - 1)
	fmt.Println(ans)

}

func quickSort(a []int, l int, r int) (compNum int) {
	if l >= r {
		return 0
	}
	compNum = r - l
	i := choosePivot(a, l, r)
	a[l], a[i] = a[i], a[l]
	j := partition(a, l, r)
	compNum += quickSort(a, l, j - 1)
	compNum += quickSort(a, j+1, r)

	return compNum
}

// We choose first element of array as pivot
func choosePivot(a []int, l int, r int) (pivot int) {
	return l
}

func partition(a []int, l int, r int) (int) {
	pivot := a[l]
	i := l+1
	for j := l+1; j <= r; j++ {
		if a[j] < pivot {
			a[j], a[i] = a[i], a[j]
			i++
		}
	}
	a[l], a[i-1] = a[i-1], a[l]
	return i-1
}

func readFileAndMakeArray(name string) (xs []int) {
	xs = make([]int, arraySize)
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

