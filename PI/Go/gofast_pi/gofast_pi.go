package main

import (
	"fmt"
	"math"

	"../processing"
	"github.com/matbabs/gofast"
)

type step struct {
	start int
	inc   int
}

func gofastPi(res gofast.Resolver) {
	step := <-scatter
	pi := 0.0
	for k := float64(step.start); k <= float64(step.inc); k++ {
		pi += 4 * math.Pow(-1, k) / (2*k + 1)
	}
	gather <- pi
	res.Done <- true
}

var nbTREADS int
var scatter chan step
var gather chan float64

func main() {

	processing.InitProcessing()

	var steps = processing.NbIterations
	nbTREADS = processing.NbThreads
	pi := 0.0

	scatter = make(chan step, nbTREADS)
	gather = make(chan float64, nbTREADS)

	processing.TimerStart()

	gofast.WorkerPool(nbTREADS, gofastPi)
	block := ((steps) / nbTREADS)
	for i := 0; i < nbTREADS; i++ {
		scatter <- step{block * i, block}
	}
	for i := 0; i < nbTREADS; i++ {
		pi += <-gather
	}

	gofast.WaitAll()

	processing.TimerStop()

	fmt.Println(pi)
	fmt.Println(processing.TimerDuration())

}
