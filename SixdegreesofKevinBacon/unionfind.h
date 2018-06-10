#ifndef UNIONFIND_H_INCLUDED
#define UNIONFIND_H_INCLUDED

#include <iostream>
#include <utility>
#include <string>
#include <queue>
#include <vector>
#include <set>

#include "actor.h"
#include "movie.h"
#include "edge.h"
#include "ActorGraph.h"


/*
the class's function is as same as the actorgraph's
but we used union-find ADT to implemet it
*/
class UnionFind
{
public:
	UnionFind(){};
	bool loadFromFile(char const* in_filename, bool use_weighted_edges, bool actorConnection);
	void createSet(Movie* movie);
	Actor *finder(Actor* actor);
	void unioner(Actor* act1, Actor* act2);
	int findConnectionTree(Actor* from_copy, Actor* to_copy);

protected:
	std::set<Movie*, MovieCompara> movies_;
	std::set<Actor*, ActorCompare> actors_;
	std::priority_queue<Movie*, std::vector<Movie*>, ConnectionCompare> pq_;

};


#endif // UNIONFIND_H_INCLUDED
