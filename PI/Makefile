#!/usr/bin/make
#

BINPREFIX =bin/
DATAPREFIX = rez/

all: PI

PI: CPi CPPPi JAVAPi GOPi

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
	-cd CPP; cmake .; make

GOPi:
# Adding the - to ignore errors if go isn't installed
	-go get -u github.com/matbabs/gofast
	-go build ./Go/gofast_pi.go -o $(BINPREFIX)gofast
	-go build ./Go/sequential_pi.go -o $(BINPREFIX)goseq
#	go run ./Go/*.go

clean:
	-rm ./*~ ./*# $(BINPREFIX)pthread_pi $(BINPREFIX)*.class $(BINPREFIX)goseq $(BINPREFIX)gofast $(BINPREFIX)cppSeq_pi $(BINPREFIX)cppBoost_pi
	-rm -r $(DATAPREFIX)

runPi: PI
	-mkdir $(DATAPREFIX)
	-rm $(DATAPREFIX)*
	./runner.sh "python Projet_Python/main.py" "$(DATAPREFIX)pySeq.csv"
	./runner.sh "python Projet_Python/main_parallel.py" "$(DATAPREFIX)pyPara.csv"
	./runner.sh "java -cp $(BINPREFIX) Sequential" "$(DATAPREFIX)javaSeq.csv"
	./runner.sh "java -cp $(BINPREFIX) SequentialStream" "$(DATAPREFIX)javaSeqStream.csv"
	./runner.sh "java -cp $(BINPREFIX) Parallel" "$(DATAPREFIX)javaPara.csv"
	./runner.sh "java -cp $(BINPREFIX) ParallelStream" "$(DATAPREFIX)javaParaStream.csv"
	./runner.sh "./$(BINPREFIX)/pthread_pi" "$(DATAPREFIX)cPThread.csv"
	./runner.sh "ruby Ruby/rbPi_seq.rb" "$(DATAPREFIX)rbSeq.csv"
	./runner.sh "ruby Ruby/rbPi_seqStream.rb" "$(DATAPREFIX)rbSeqStream.csv"
	./runner.sh "ruby Ruby/rbPi_par.rb" "$(DATAPREFIX)rbPar.csv"

