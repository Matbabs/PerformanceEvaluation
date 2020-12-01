package main

import (
	"fmt"
	"math"

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

var nbTREADS = 50
var scatter = make(chan step, nbTREADS)
var gather = make(chan float64, nbTREADS)

func main() {
	var steps = 1000000
	pi := 0.0
	gofast.WorkerPool(nbTREADS, gofastPi)
	block := ((steps) / nbTREADS)
	for i := 0; i < nbTREADS; i++ {
		scatter <- step{block * i, block}
	}
	for i := 0; i < nbTREADS; i++ {
		pi += <-gather
	}
	fmt.Println(pi)
	gofast.WaitAll()
}
