#!/usr/bin/make
#

BINPREFIX =bin/
TEMPPREFIX = rez/
DATAPREFIX = data/

all: PI

PI: CPi CPPPi JAVAPi GOPi RUST

JAVAPi: JavaS JavaP

JavaP: Java/src/main/java/Parallel.java Java/src/main/java/ParallelStream.java
	javac -cp Java/src/main/java Java/src/main/java/Parallel.java -d $(BINPREFIX)
	javac -cp Java/src/main/java Java/src/main/java/ParallelStream.java -d $(BINPREFIX)

JavaS: Java/src/main/java/Sequential.java Java/src/main/java/SequentialStream.java
	javac -cp Java/src/main/java Java/src/main/java/Sequential.java -d $(BINPREFIX)
	javac -cp Java/src/main/java Java/src/main/java/SequentialStream.java -d $(BINPREFIX)

CPi: C/pthread_pi.c
	gcc C/pthread_pi.c -o $(BINPREFIX)pthread_pi -Wall -Wextra -lpthread -lm

CPPPi:
# 	g++ CPP/preprocessing.hpp CPP/singlethread.cpp -o $(BINPREFIX)cppSeq_pi -Wall -Wextra -lm
# Adding the - to ignore errors if boost isn't installed
#	-g++ CPP/preprocessing.hpp CPP/multithread.cpp -o $(BINPREFIX)cppBoost_pi -Wall -Wextra -lm -lboost
	-cd CPP && cmake . && make && mv multithread ../bin/cppSeq_pi && mv singlethread ../bin/cppBoost_pi

GOPi:
# Adding the - to ignore errors if go isn't installed
#	-cd Go && go get -u github.com/matbabs/gofast && go build ./*.go
	go get -u github.com/matbabs/gofast
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
	./runner.sh "python Projet_Python/main.py" "$(TEMPPREFIX)pySeq.csv"
	./runner.sh "python Projet_Python/main_parallel.py" "$(TEMPPREFIX)pyPara.csv"
	./runner.sh "java -cp $(BINPREFIX) Sequential" "$(TEMPPREFIX)javaSeq.csv"
	./runner.sh "java -cp $(BINPREFIX) SequentialStream" "$(TEMPPREFIX)javaSeqStream.csv"
	./runner.sh "java -cp $(BINPREFIX) Parallel" "$(TEMPPREFIX)javaPara.csv"
	./runner.sh "java -cp $(BINPREFIX) ParallelStream" "$(TEMPPREFIX)javaParaStream.csv"
	./runner.sh "./$(BINPREFIX)/pthread_pi" "$(TEMPPREFIX)cPThread.csv"
	./runner.sh "./$(BINPREFIX)/cppSeq_pi" "$(TEMPPREFIX)CPPSeq.csv"
	./runner.sh "./$(BINPREFIX)/cppBoost_pi" "$(TEMPPREFIX)CPPBoost.csv"
	./runner.sh "./$(BINPREFIX)/goseq_pi" "$(TEMPPREFIX)GoSeq.csv"
	./runner.sh "./$(BINPREFIX)/gofast_pi" "$(TEMPPREFIX)GoPara.csv"
	./runner.sh "./$(BINPREFIX)/release/sequential_pi" "$(TEMPPREFIX)rustSeq.csv"
	./runner.sh "./$(BINPREFIX)/release/parallel_pi" "$(TEMPPREFIX)rustPara.csv"
	./runner.sh "ruby Ruby/rbPi_seq.rb" "$(TEMPPREFIX)rbSeq.csv"
	./runner.sh "ruby Ruby/rbPi_seqStream.rb" "$(TEMPPREFIX)rbSeqStream.csv"
	./runner.sh "ruby Ruby/rbPi_par.rb" "$(TEMPPREFIX)rbPar.csv"

buildRez: runPi
	-mkdir $(DATAPREFIX)
	-for i in `ls $(TEMPPREFIX)`;do ./analyseRez.rb $(TEMPPREFIX)$$i $(DATAPREFIX)`basename $$i`; done

