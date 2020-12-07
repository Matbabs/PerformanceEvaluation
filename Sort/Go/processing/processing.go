package processing

import (
	"fmt"
	"os"
	"strconv"
	"time"
)

var err error

//NbElements iteratuions of the processing
var NbElements int

//NbThreads number of threads of the processing
var NbThreads int

var startTime time.Time
var endTime time.Time

//InitProcessing ...
func InitProcessing() {
	if len(os.Args) != 3 {
		fmt.Println("Usage: <number of elements> <number of threads>")
		os.Exit(1)
	}
	NbElements, err = strconv.Atoi(os.Args[1])
	NbThreads, err = strconv.Atoi(os.Args[2])
}

//TimerStart ...
func TimerStart() {
	startTime = time.Now()
}

//TimerStop ...
func TimerStop() {
	endTime = time.Now()
}

//TimerDuration ...
func TimerDuration() time.Duration {
	return endTime.Sub(startTime)
}
