#!/usr/bin/make
#

BINPREFIX=bin/
TEMPPREFIX = rez/
DATAPREFIX = data/

all: Sorting

Sorting: CPPSorting JAVASorting GOSort RUST

JAVASorting: folders JavaS JavaP

JavaP: Java/src/main/java/ParallelSort.java
	javac -cp Java/src/main/java Java/src/main/java/ParallelSort.java -d $(BINPREFIX)

JavaS: Java/src/main/java/NonParallelSort.java
	javac -cp Java/src/main/java Java/src/main/java/NonParallelSort.java -d $(BINPREFIX)

CPPSorting: folders
# 	g++ CPP/preprocessing.hpp CPP/singlethread.cpp -o $(BINPREFIX)cppSeq_sorting -Wall -Wextra -lm
# Adding the - to ignore errors if boost isn't installed
#	-g++ CPP/preprocessing.hpp CPP/multithread.cpp -o $(BINPREFIX)cppBoost_sorting -Wall -Wextra -lm -lboost
	-cd $(BINPREFIX) ; mkdir -p CPP ; cd CPP ; cmake -B. -S../../CPP/ && make

GOSort:
# Adding the - to ignore errors if go isn't installed
#	-cd Go && go get -u github.com/matbabs/gofast && go build ./*.go
	-go get -u github.com/matbabs/gofast
#	-go build -o $(BINPREFIX)gofast_sort ./Go/processing/processing.go 
	-go build -o $(BINPREFIX)goseq_sort ./Go/sequential_sort/sequential_sort.go
#	go run ./Go/*.go

RUST:
	-cd Rust/sequential_sort && cargo build --target-dir=../../bin/ --release

clean: folders
#-rm ./*~ ./*#
	-rm -r $(BINPREFIX)
	-rm -r $(DATAPREFIX)
	-rm -r $(TEMPPREFIX)

folders:
	-mkdir -p $(BINPREFIX)
	-mkdir -p $(DATAPREFIX)
	-mkdir -p $(TEMPPREFIX)

runSorting: Sorting
	-mkdir $(TEMPPREFIX)
	-rm $(TEMPPREFIX)*
	-./runnerSeq.sh "python Python/sortSeq.py" "$(TEMPPREFIX)pySeq.csv"
	-./runnerPara.sh "python Python/sortPara.py" "$(TEMPPREFIX)pyPara.csv"
	-./runnerSeq.sh "java -cp $(BINPREFIX) NonParallelSort" "$(TEMPPREFIX)javaNonPara.csv"
	-./runnerPara.sh "java -cp $(BINPREFIX) ParallelSort" "$(TEMPPREFIX)javaPara.csv"
	-./runnerPara.sh "./$(BINPREFIX)/CPP/block_indirect_sort" "$(TEMPPREFIX)CPPBlock.csv"
	-./runnerPara.sh "./$(BINPREFIX)/CPP/parallel_stable_sort" "$(TEMPPREFIX)CPPPara.csv"
	-./runnerPara.sh "./$(BINPREFIX)/CPP/sample_sort" "$(TEMPPREFIX)CPPSample.csv"
	-./runnerSeq.sh "./$(BINPREFIX)/CPP/singlethread" "$(TEMPPREFIX)CPPSeq.csv"
	-./runnerSeq.sh "./$(BINPREFIX)/goseq_sort" "$(TEMPPREFIX)GoSeq.csv"
	-./runnerSeq.sh "./$(BINPREFIX)/release/sequential_pi" "$(TEMPPREFIX)rustSeq.csv"
	-./runnerSeq.sh "ruby Ruby/sortSeq.rb" "$(TEMPPREFIX)rbSeq.csv"

buildRez: runSorting
	-mkdir $(DATAPREFIX)
	-for i in `ls $(TEMPPREFIX)`;do echo $$i; ./analyseRez.rb $(TEMPPREFIX)$$i $(DATAPREFIX)`basename $$i`; done


