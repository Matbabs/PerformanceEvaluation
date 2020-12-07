#!/usr/bin/make
#

BINPREFIX=bin/
DATAPREFIX=rez/

all: Sorting

Sorting: CSorting CPPSorting JAVASorting GOSorting

JAVASorting: folders JavaS JavaP

JavaP: Java/src/main/java/ParallelSort.java
	javac -cp Java/src/main/java Java/src/main/java/ParallelSort.java -d $(BINPREFIX)

JavaS: Java/src/main/java/NonParallelSort.java
	javac -cp Java/src/main/java Java/src/main/java/NonParallelSort.java -d $(BINPREFIX)

CSorting: folders C/pthread_sorting.c
	gcc C/pthread_sorting.c -o $(BINPREFIX)pthread_sorting -Wall -Wextra -lpthread -lm

CPPSorting: folders
# 	g++ CPP/preprocessing.hpp CPP/singlethread.cpp -o $(BINPREFIX)cppSeq_sorting -Wall -Wextra -lm
# Adding the - to ignore errors if boost isn't installed
#	-g++ CPP/preprocessing.hpp CPP/multithread.cpp -o $(BINPREFIX)cppBoost_sorting -Wall -Wextra -lm -lboost
	-cd $(BINPREFIX) ; mkdir -p CPP ; cd CPP ; cmake -B. -S../../CPP/ && make

GOSorting: folders
# Adding the - to ignore errors if go isn't installed
	-go get -u github.com/matbabs/gofast
	-go build ./Go/gofast_sorting.go -o $(BINPREFIX)gofast
	-go build ./Go/sequential_sorting.go -o $(BINPREFIX)goseq
#	go run ./Go/*.go

clean: folders
	#-rm ./*~ ./*#
	-rm -r $(BINPREFIX)
	-rm -r $(DATAPREFIX)

folders:
	-mkdir -p $(BINPREFIX)
	-mkdir -p $(DATAPREFIX)

runSorting: Sorting
	-mkdir $(DATAPREFIX)
	-rm $(DATAPREFIX)*
	./runner.sh "python Projet_Python/main.py" "$(DATAPREFIX)pySeq.csv"
	./runner.sh "python Projet_Python/main_parallel.py" "$(DATAPREFIX)pyPara.csv"
	./runner.sh "java -cp $(BINPREFIX) Sequential" "$(DATAPREFIX)javaSeq.csv"
	./runner.sh "java -cp $(BINPREFIX) SequentialStream" "$(DATAPREFIX)javaSeqStream.csv"
	./runner.sh "java -cp $(BINPREFIX) Parallel" "$(DATAPREFIX)javaPara.csv"
	./runner.sh "java -cp $(BINPREFIX) ParallelStream" "$(DATAPREFIX)javaParaStream.csv"
	./runner.sh "./$(BINPREFIX)/pthread_sorting" "$(DATAPREFIX)cPThread.csv"
	./runner.sh "ruby Ruby/rbSorting_seq.rb" "$(DATAPREFIX)rbSeq.csv"
	./runner.sh "ruby Ruby/rbSorting_seqStream.rb" "$(DATAPREFIX)rbSeqStream.csv"
	./runner.sh "ruby Ruby/rbSorting_par.rb" "$(DATAPREFIX)rbPar.csv"

