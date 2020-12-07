package main

import (
	"fmt"
	"math"

	"../processing"
)

func sequentialPi(n float64) float64 {
	pi := 0.0
	for k := 0.0; k <= float64(n); k++ {
		pi += 4 * math.Pow(-1, k) / (2*k + 1)
	}
	return pi
}

func main() {

	processing.InitProcessing()
	var steps = processing.NbIterations
	processing.TimerStart()
	pi := sequentialPi(float64(steps))
	processing.TimerStop()

	fmt.Println(pi)
	fmt.Println(processing.TimerDuration())
}
