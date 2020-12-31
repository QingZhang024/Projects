CXX      = clang++
CXXFLAGS = -Wall -Wextra -g
LDFLAGS  = -g

gorobots: main.o Board.o Tree.o
	$(CXX) $(LDFLAGS) -o gorobots main.o Board.o Tree.o
test: test.o Board.o Tree.o
	$(CXX) $(LDFLAGS) -o test test.o Board.o Tree.o

main.o:  main.cpp Tree.h Board.h
test.o: test.cpp Tree.h Board.h
Board.o:  Board.cpp Board.h
Tree.o: Tree.cpp Tree.h

clean:
	rm -f *.o core* *~ gorobots
