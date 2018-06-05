#ifndef ACTORGRAPTH_H_INCLUDED
#define ACTORGRAPTH_H_INCLUDED

#include <iostream>
#include <utility>
#include <string>
#include <queue>
#include <vector>
#include <set>

#include "actor.h"
#include "movie.h"
#include "edge.h"

struct ActorCompare{
	bool operator() (Actor *const &act1, Actor* const &act2){
		return act1->getName().compare(act2->getName()) < 0;
	}
};


struct MovieCompara{
	/// if two movie have the same name, then compare their years
	/// else they could be compared, direct return
	/// see C++11 compare function.(i.e. if one obj is equal to another, which return 0)
	bool operator()(Movie *const &mov1, Movie* const &mov2){
		if(!(mov1->getTitle().compare(mov2->getTitle())))
			return mov1->getYear() < mov2->getYear();
        return (mov1->getTitle().compare(mov2->getTitle()))<0;
	}
};


struct DistCompare{
	bool operator()(std::pair<int, Actor*> n1, std::pair<int ,Actor*> n2){
		return n1.first > n2.first;
	}
};

struct ConnectionCompare{
	bool operator()(Movie *const &mov1, Movie* const &mov2){
		return mov1->getYear() > mov2->getYear();
	}
};


class ActorGraph
{
public:
	//ActorGraph();
	//~ActorGraph();

	bool loadFromFile(char const *in_filename, bool use_weight_edges,
					  bool actor_connection);
	
	///create graph's edges
	void graphify();
	std::string BFS(Actor *from, Actor *to);
	std::vector<std::pair<std::string, std::string>> loadPairs(char const *pairs);
    /// get movie numbers of movies, actors, and edges
    const std::vector<int> getAllSize() const;

	// ADD here something for final submission

protected:
	std::set<Movie*, MovieCompara> movies_;
	std::set<Actor*, ActorCompare> actors_;
	std::priority_queue<Movie*, std::vector<Movie*>, ConnectionCompare> pq;
};


#endif // ACTORGRAPTH_H_INCLUDED
