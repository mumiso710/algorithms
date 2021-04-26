package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"sort"
	"strconv"
)

const arraySize = 10000

func main() {
	a := readFileAndMakeArray("quicksort.txt")
	ans := quickSort(a, 0, len(a) - 1)
	fmt.Println(ans)

}

func quickSort(a []int, l int, r int) (compNum int) {
	if l >= r {
		return 0
	}
	compNum = r - l
	//fmt.Println("l:", l, "r:", r)
	i := choosePivot(a, l, r)
	a[l], a[i] = a[i], a[l]
	j := partition(a, l, r)
	compNum += quickSort(a, l, j - 1)
	compNum += quickSort(a, j+1, r)

	return compNum
}

// We choose first element of array as pivot Q.1
// We choose last element of array as pivot Q.2
// We choose median element in first mid last as pivot Q.3
func choosePivot(a []int, l int, r int) (pivot int) {
	arr := make([]int ,3, 3)
	m := make(map[int]int)
	first := l
	last := r
	mid := (first + last) / 2
	m[a[first]] = first
	m[a[last]] = last
	m[a[mid]] = mid
	arr[0] = a[first]
	arr[1] = a[last]
	arr[2] = a[mid]
	sort.Ints(arr)
	//return m[arr[1]]
	//return l
	//return r
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
	xs = make([]int, 0, arraySize)
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

