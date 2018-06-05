# A simple makefile for CSE 100 PA4

CC=g++ 
CXXFLAGS=-std=c++11
LDFLAGS=

# if passed "type=opt" at command-line, compile with "-O3" flag (otherwise use "-g" for debugging)

ifeq ($(type),opt)
    CPPFLAGS += -O3
    LDFLAGS += -O3
else
    CPPFLAGS += -gdwarf-3
    LDFLAGS += -g
endif

all: pathfinder

# include what ever source code *.h files pathfinder relies on (these are merely the ones that were used in the solution)

pathfinder: ActorGraph.o Actor.o Movie.o Edge.o pathfinder.cpp
# pathfinder: g++ ActorGraph.cpp Actor.cpp Movie.cpp Edge.cpp pathfinder.cpp

actorconnections: ActorGraph.o ActorTree.o Actor.o Movie.o Edge.o actorconnections.cpp util.o

extension: extension.cpp

# include what ever source code *.h files ActorGraph relies on (these are merely the ones that were used in the solution)

ActorGraph.o: ActorGraph.h

ActorTree.o: ActorTree.h

Actor.o: Actor.h

Movie.o: Movie.h

Edge.o: Edge.h

util.o: util.h 

# Note: you do not have to include a *.cpp file if it aleady has a paired *.h file that is already included with class/method headers

# ActorGraph.o: UnionFind.hpp Movie.h ActorNode.h ActorEdge.h ActorGraph.h

# ActorGraph.o: Movie.h Actor.h Edge.h ActorGraph.h pathfinder.cpp

clean:
	rm -f pathfinder *.o core* a.out actorconnections extension

