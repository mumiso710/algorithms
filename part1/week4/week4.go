package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
)
const arraySize = 200

func main() {
	arr := readFileAndMakeArray("kargerMinCut.txt")
	fmt.Println(arr)
}


func readFileAndMakeArray(name string) (xs []string) {
	xs = make([]string, 0, arraySize)
	f, err := os.Open(name)
	if err != nil {
		log.Fatalln(err)
	}
	defer f.Close()

	scanner := bufio.NewScanner(f);
	for scanner.Scan() {
		line := scanner.Text()
		xs = append(xs, line)
	}
	return xs
}

