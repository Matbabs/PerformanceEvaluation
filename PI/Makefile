#!/usr/bin/make
#

BINPREFIX =bin/
TEMPPREFIX = rez/
DATAPREFIX = data/

all: PI

PI: CPi CPPPi JAVAPi GOPi RUST

JAVAPi: JavaS JavaP

JavaP: Java/src/main/java/Parallel.java Java/src/main/java/ParallelStream.java
	-javac -cp Java/src/main/java Java/src/main/java/Parallel.java -d $(BINPREFIX)
	-javac -cp Java/src/main/java Java/src/main/java/ParallelStream.java -d $(BINPREFIX)

JavaS: Java/src/main/java/Sequential.java Java/src/main/java/SequentialStream.java
	-javac -cp Java/src/main/java Java/src/main/java/Sequential.java -d $(BINPREFIX)
	-javac -cp Java/src/main/java Java/src/main/java/SequentialStream.java -d $(BINPREFIX)

CPi: C/pthread_pi.c
	-gcc C/pthread_pi.c -o $(BINPREFIX)pthread_pi -Wall -Wextra -lpthread -lm -O2

CPPPi:
# 	g++ CPP/preprocessing.hpp CPP/singlethread.cpp -o $(BINPREFIX)cppSeq_pi -Wall -Wextra -lm
# Adding the - to ignore errors if boost isn't installed
#	-g++ CPP/preprocessing.hpp CPP/multithread.cpp -o $(BINPREFIX)cppBoost_pi -Wall -Wextra -lm -lboost
# TODO : Take the line from Sort Makefile
	-cd CPP && cmake . && make && mv multithread ../bin/cppSeq_pi && mv singlethread ../bin/cppBoost_pi

GOPi:
# Adding the - to ignore errors if go isn't installed
#	-cd Go && go get -u github.com/matbabs/gofast && go build ./*.go
	-go get -u github.com/matbabs/gofast
	-go build -o $(BINPREFIX)gofast_pi ./Go/gofast_pi/gofast_pi.go 
	-go build -o $(BINPREFIX)goseq_pi ./Go/sequential_pi/sequential_pi.go
#	go run ./Go/*.go

RUST:
	-cd Rust/sequential_pi && cargo build --target-dir=../../bin/ --release
	-cd Rust/parallel_pi && cargo build --target-dir=../../bin/ --release

clean:
	-rm ./*~ ./*# $(BINPREFIX)pthread_pi $(BINPREFIX)*.class $(BINPREFIX)goseq_pi $(BINPREFIX)gofast_pi $(BINPREFIX)cppSeq_pi $(BINPREFIX)cppBoost_pi
	-rm -r bin/release
	-rm -r $(TEMPPREFIX)

runPi: PI
	-mkdir $(TEMPPREFIX)
	-rm $(TEMPPREFIX)*
	-./runnerSeq.sh "python Projet_Python/main.py" "$(TEMPPREFIX)pySeq.csv"
	-./runnerPara.sh "python Projet_Python/main_parallel.py" "$(TEMPPREFIX)pyPara.csv"
	-./runnerSeq.sh "java -cp $(BINPREFIX) Sequential" "$(TEMPPREFIX)javaSeq.csv"
	-./runnerSeq.sh "java -cp $(BINPREFIX) SequentialStream" "$(TEMPPREFIX)javaSeqStream.csv"
	-./runnerPara.sh "java -cp $(BINPREFIX) Parallel" "$(TEMPPREFIX)javaPara.csv"
	-./runnerPara.sh "java -cp $(BINPREFIX) ParallelStream" "$(TEMPPREFIX)javaParaStream.csv"
	-./runnerPara.sh "./$(BINPREFIX)/pthread_pi" "$(TEMPPREFIX)cPThread.csv"
	-./runnerSeq.sh "./$(BINPREFIX)/cppSeq_pi" "$(TEMPPREFIX)CPPSeq.csv"
	-./runnerPara.sh "./$(BINPREFIX)/cppBoost_pi" "$(TEMPPREFIX)CPPBoost.csv"
	-./runnerSeq.sh "./$(BINPREFIX)/goseq_pi" "$(TEMPPREFIX)GoSeq.csv"
	-./runnerPara.sh "./$(BINPREFIX)/gofast_pi" "$(TEMPPREFIX)GoPara.csv"
	-./runnerSeq.sh "./$(BINPREFIX)/release/sequential_pi" "$(TEMPPREFIX)rustSeq.csv"
	-./runnerPara.sh "./$(BINPREFIX)/release/parallel_pi" "$(TEMPPREFIX)rustPara.csv"
	-./runnerSeq.sh "ruby Ruby/rbPi_seq.rb" "$(TEMPPREFIX)rbSeq.csv"
	-./runnerSeq.sh "ruby Ruby/rbPi_seqStream.rb" "$(TEMPPREFIX)rbSeqStream.csv"
	-./runnerPara.sh "ruby Ruby/rbPi_par.rb" "$(TEMPPREFIX)rbPar.csv"

buildRez: runPi
	-mkdir $(DATAPREFIX)
	-for i in `ls $(TEMPPREFIX)`;do echo $$i; ./analyseRez.rb $(TEMPPREFIX)$$i $(DATAPREFIX)`basename $$i`; done

