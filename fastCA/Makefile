#all:
#	g++ -g --std=c++11 -DNDEBUG -I ./minisat/include -I ./minisat/solver -O2 main.cc Options.cc SpecificationFile.cc PascalTriangle.cc Combinadic.cc  LocalSearch.cc Coverage.cc CoveringArray.cc TupleSet.cc mersenne.cc -o main_paws
#
#src = ${shell ls *.cc}
#objs = ${patsubst %.cc, %.o, $(src)}

objs = Options.o SpecificationFile.o PascalTriangle.o Combinadic.o  ConstraintFile.o TestSetFile.o io.o \
	   LocalSearch.o Coverage.o CoveringArray.o TupleSet.o OptionTupleSet.o LineVarTupleSet.o mersenne.o SAT.o Sovler.o ActsSolver.o main.o
CC = g++
CFLAGS = --std=c++0x -DNDEBUG -O2 -pthread

all : FastCA

FastCA : $(objs)
	$(CC) $(CFLAGS) -g -o $@ $^

main.o : main.cc
	$(CC) $(CFLAGS)  -g -c -o $@ $^

Sovler.o : ./minisat/solver/Solver.C
	$(CC) $(CFLAGS)  -I ./minisat/include  -g -c -o $@ $^

SAT.o : SAT.C
	$(CC) $(CFLAGS)  -g -c -o $@ $^

ConstraintFile.o : ConstraintFile.C
	$(CC) $(CFLAGS)  -g -c -o $@ $^

Options.o : Options.cc
	$(CC) $(CFLAGS)  -g -c -o $@ $^

SpecificationFile.o : SpecificationFile.cc
	$(CC) $(CFLAGS)  -g -c -o $@ $^

PascalTriangle.o : PascalTriangle.cc
	$(CC) $(CFLAGS)  -g -c -o $@ $^

Combinadic.o : Combinadic.cc
	$(CC) $(CFLAGS)  -g -c -o $@ $^

LocalSearch.o : LocalSearch.cc
	$(CC) $(CFLAGS)  -g -c -o $@ $^

Coverage.o : Coverage.cc
	$(CC) $(CFLAGS)  -g -c -o $@ $^

CoveringArray.o : CoveringArray.cc
	$(CC) $(CFLAGS)  -g -c -o $@ $^

TupleSet.o : TupleSet.cc
	$(CC) $(CFLAGS)  -g -c -o $@ $^

OptionTupleSet.o : OptionTupleSet.cc
	$(CC) $(CFLAGS)  -g -c -o $@ $^

LineVarTupleSet.o : LineVarTupleSet.cc
	$(CC) $(CFLAGS)  -g -c -o $@ $^

mersenne.o : mersenne.cc
	$(CC) $(CFLAGS)  -g -c -o $@ $^

ActsSolver.o : ActsSolver.cc
	$(CC) $(CFLAGS)  -g -c -o $@ $^

TestSetFile.o : TestSetFile.C
	$(CC) $(CFLAGS)  -g -c -o $@ $^

io.o : io.cc
	$(CC) $(CFLAGS)  -g -c -o $@ $^



#%.o : %.cc
#	$(CC) $(CFLAGS) -o $@ $^

clean :
	-rm *.o
	-rm FastCA
