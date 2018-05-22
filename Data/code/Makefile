FLAGS_OPT   = `/export/home/wg2162/tools/itpp-4.2/bin/itpp-config --cflags`
LIBS_OPT    = `/export/home/wg2162/tools/itpp-4.2/bin/itpp-config --static --libs`


CC = g++
DEBUG = -g 
CFLAGS = -Wall -O3 -c $(DEBUG) $(FLAGS_OPT)
LFLAGS = -Wall -O3 $(DEBUG) $(FLAGS_OPT) $(LIBS_OPT)

#OBJECTS = wtmf-corpus.o wtmf-model.o wtmf-learn.o run_wtmf.o eval-cdr.o eval-ss.o eval-par.o experiment.o 
OBJECTS = wtmf-corpus.o wtmf-model.o wtmf-learn.o run_wtmf.o
#OBJECTS = evaluate_cdr.o

all: 		$(OBJECTS)
		$(CC) $(LFLAGS) $(OBJECTS) -o wtmf
wtmf-corpus.o:	wtmf-corpus.cpp
		$(CC) $(CFLAGS) wtmf-corpus.cpp
wtmf-model.o:	wtmf-model.cpp
		$(CC) $(CFLAGS) wtmf-model.cpp
wtmf-learn.o:	wtmf-learn.cpp
		$(CC) $(CFLAGS) wtmf-learn.cpp
run_wtmf.o:	run_wtmf.cpp
		$(CC) $(CFLAGS) run_wtmf.cpp
#experiment.o:	experiment.cpp
#		$(CC) $(CFLAGS) experiment.cpp

clean:
		rm -f *.o *~ wtmf