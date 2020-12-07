package main

import (
	"fmt"
	"math/rand"
	"sort"

	"../processing"
)

func main() {

	processing.InitProcessing()

	t := []int{}

	for i := 0; i < processing.NbElements; i++ {
		t = append(t, rand.Intn(processing.NbElements))
	}

	processing.TimerStart()

	sort.Slice(t, func(p, q int) bool { return t[p] < t[q] })

	processing.TimerStop()

	fmt.Println(processing.TimerDuration())
}
