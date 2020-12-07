package processing

import (
	"fmt"
	"os"
	"strconv"
	"time"
)

var err error

//NbIterations iteratuions of the processing
var NbIterations int

//NbThreads number of threads of the processing
var NbThreads int

var startTime time.Time
var endTime time.Time

func InitProcessing() {
	if len(os.Args) != 3 {
		fmt.Println("Usage: <number of iterations> <number of threads>")
		os.Exit(1)
	}
	NbIterations, err = strconv.Atoi(os.Args[1])
	NbThreads, err = strconv.Atoi(os.Args[2])
}

func TimerStart() {
	startTime = time.Now()
}

func TimerStop() {
	endTime = time.Now()
}

func TimerDuration() time.Duration {
	return endTime.Sub(startTime)
}
