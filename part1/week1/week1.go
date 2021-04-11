package main

import (
	"fmt"
	"strconv"
)

func main() {
	x := "3141592653589793238462643383279502884197169399375105820974944592"
	y := "2718281828459045235360287471352662497757247093699959574966967627"


	fmt.Println(karatsuba(x, y))

}

func karatsuba(x, y string) string {
	if x == "0" {
		return "0"
	}
	var n int
	if len(x) > len(y) {
		n = len(x)
		y = padding(y, len(x)-len(y))
	} else {
		n = len(y)
		x = padding(x, len(y)-len(x))
	}

	if n == 1 {
		x_int, _ := strconv.Atoi(x)
		y_int, _ := strconv.Atoi(y)
		ans := x_int * y_int
		return strconv.Itoa(ans)
	}
	if n%2 != 0 {
		x = padding(x, 1)
		y = padding(y, 1)
		n++
	}
		a := x[:n/2]
		fmt.Println("a:", a)
		b := x[n/2:]
		fmt.Println("b:", b)
		c := y[:n/2]
		fmt.Println("c:", c)
		d := y[n/2:]
		fmt.Println("d:", d)

		p := karatsubaAdd(a, b)
		q := karatsubaAdd(c, d)


		ac := karatsuba(a, c)
		bd := karatsuba(b, d)
		pq := karatsuba(p, q)

		adbc := karatsubaSub(karatsubaSub(pq, ac), bd)

		return trimZero(karatsubaAdd(karatsubaAdd(karatsubaMulti10(ac, n), karatsubaMulti10(adbc, n/2)), bd))


}

func karatsubaAdd(x, y string) string {
	sum := 0
	carry := 0
	ans := ""
	var n int

	if len(x) > len(y) {
		n = len(x)
		y = padding(y, len(x)-len(y))
	} else {
		n = len(y)
		x = padding(x, len(y)-len(x))
	}

	for i := n-1 ; i >= 0; i-- {
		x_int, _ := strconv.Atoi(string(x[i]))
		y_int, _ := strconv.Atoi(string(y[i]))
		sum = x_int + y_int + carry
		carry = 0
		if sum >= 10 {
			carry = 1
			sum -= 10
		}
		ans = strconv.Itoa(sum) + ans
	}
	if carry == 1 {
		ans = "1" + ans
	}
	return ans
}

func karatsubaSub(x, y string) string {
	sub := 0
	carry := 0
	ans := ""
	var n int

	if len(x) > len(y) {
		n = len(x)
		y = padding(y, len(x)-len(y))
	} else {
		n = len(y)
		x = padding(x, len(y)-len(x))
	}

	for i := n-1 ; i >= 0; i-- {
		x_int, _ := strconv.Atoi(string(x[i]))
		y_int, _ := strconv.Atoi(string(y[i]))
		sub = x_int - (y_int + carry)
		carry = 0
		if sub < 0 {
			carry = 1
			sub += 10
		}
		ans = strconv.Itoa(sub) + ans
	}
	return ans
}

func karatsubaMulti10(x string, n int) string {
	padding := ""
	for i := 0; i < n; i++ {
		padding += "0"
	}
	return x + padding
}

func padding(x string, n int) string {
	padding := ""
	for i := 0; i < n; i++ {
		padding += "0"
	}
	return padding + x
}

func trimZero(x string) string {
	for i := 0; i < len(x); i++ {
		if string(x[i]) == "0" {
			continue
		} else {
			return x[i:]
		}
	}
	return x
}
