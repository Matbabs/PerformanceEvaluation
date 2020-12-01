#!/usr/bin/make
#

BINPREFIX =bin/

all: PI

PI: CPi CPPPi JAVAPi GOPi

JAVAPi: JavaS JavaP

JavaP: Java/src/main/java/Parallel.java Java/src/main/java/ParallelStream.java
	javac Java/src/main/java/Parallel.java -d $(BINPREFIX)
	javac Java/src/main/java/ParallelStream.java -d $(BINPREFIX)

JavaS: Java/src/main/java/Sequential.java Java/src/main/java/SequentialStream.java
	javac Java/src/main/java/Sequential.java -d $(BINPREFIX)
	javac Java/src/main/java/SequentialStream.java -d $(BINPREFIX)

CPi: C/pthread_pi.c
	gcc C/pthread_pi.c -o $(BINPREFIX)pthread_pi -Wall -Wextra -lpthread -lm

CPPPi:
	g++ CPP/singlethread.cpp -o $(BINPREFIX)cppSeq_pi -Wall -Wextra -lm
# Adding the - to ignore errors if boost isn't installed
	-g++ CPP/multithread.cpp -o $(BINPREFIX)cppBoost_pi -Wall -Wextra -lm -lboost

GOPi:
# Adding the - to ignore errors if go isn't installed
	-go get -u github.com/matbabs/gofast
	-go build ./Go/gofast_pi.go -o $(BINPREFIX)gofast
	-go build ./Go/sequential_pi.go -o $(BINPREFIX)goseq
#	go run ./Go/*.go

clean:
	rm ./*~ ./*# $(BINPREFIX)pthread_pi $(BINPREFIX)*.class $(BINPREFIX)goseq $(BINPREFIX)gofast $(BINPREFIX)cppSeq_pi $(BINPREFIX)cppBoost_pi

