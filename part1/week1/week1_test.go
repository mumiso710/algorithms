package main

import (
	"testing"
)

func TestKaratsubaAdd(t *testing.T) {
	x := "6"
	y := "5"

	//x := "1234"
	//y := "5678"

	add := karatsubaAdd(x, y)
	//expected := "6912"
    expected := "11"

	if add != expected {
		t.Errorf("got %q, want %q", add, expected)
	}
}

func TestKaratsubaSub(t *testing.T) {
	x := "3231"
	y := "1295"

	add := karatsubaSub(x, y)
	expected := "1936"

	if add != expected {
		t.Errorf("got %q, want %q", add, expected)
	}
}

func TestKaratsubaMulti10(t *testing.T) {
	x := "1234"
	n := 4

	ans := karatsubaMulti10(x, n)
	expected := "12340000"

	if ans != expected {
		t.Errorf("got %q, want %q", ans, expected)
	}
}