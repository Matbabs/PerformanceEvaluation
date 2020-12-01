#!/usr/bin/make
#

BINPREFIX =bin/

all: PI

PI: CProg CPP JAVA

JAVA: JavaS JavaP

JavaP: Java/src/main/java/Parallel.java Java/src/main/java/ParallelStream.java
	javac Java/src/main/java/Parallel.java -d $(BINPREFIX)
	javac Java/src/main/java/ParallelStream.java -d $(BINPREFIX)

JavaS: Java/src/main/java/Sequential.java Java/src/main/java/SequentialStream.java
	javac Java/src/main/java/Sequential.java -d $(BINPREFIX)
	javac Java/src/main/java/SequentialStream.java -d $(BINPREFIX)

CProg: C/pthread_pi.c
	gcc C/pthread_pi.c -o $(BINPREFIX)pthread_pi -Wall -Wextra -lpthread -lm

CPP:
	@echo "No CPP for now"

GO:
	go get -u github.com/matbabs/gofast
	go build ./Go/*.go
#	go run ./Go/*.go

clean:
	rm ./*~ ./*# $(BINPREFIX)pthread_pi  $(BINPREFIX)*.class

