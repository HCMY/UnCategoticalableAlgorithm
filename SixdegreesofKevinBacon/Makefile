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

all: pathfinder actorconnections refpathfinder refactorconnections

# include what ever source code *.h files pathfinder relies on (these are merely the ones that were used in the solution)

pathfinder: ActorGraph.o actor.o movie.o edge.o pathfinder.cpp
# pathfinder: g++ ActorGraph.cpp Actor.cpp Movie.cpp Edge.cpp pathfinder.cpp
refpathfinder: ActorGraph.o actor.o movie.o edge.o repathfinder.cpp
actorconnections: ActorGraph.o unionfind.o actor.o movie.o edge.o actorconnections.cpp
refactorconnections: ActorGraph.o unionfind.o actor.o movie.o edge.o refactorconnections.cpp
# include what ever source code *.h files ActorGraph relies on (these are merely the ones that were used in the solution)



unionfind.o: unionfind.h
ActorGraph.o: ActorGraph.h
actor.o: actor.h

movie.o: movie.h

edge.o: edge.h 

# Note: you do not have to include a *.cpp file if it aleady has a paired *.h file that is already included with class/method headers

# ActorGraph.o: UnionFind.hpp Movie.h ActorNode.h ActorEdge.h ActorGraph.h

# ActorGraph.o: Movie.h Actor.h Edge.h ActorGraph.h pathfinder.cpp

clean:
	rm -f pathfinder *.o core* a.out actorconnections extension

