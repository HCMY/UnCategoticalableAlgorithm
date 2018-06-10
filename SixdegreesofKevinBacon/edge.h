#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED


#include <string>
#include <vector>

class Movie;
class Actor;


class Edge
{
public:

	Movie *movie_; // this is for edge
	Actor *actor_; //this is for  nodes

	int weight_;

	Edge(Movie *movie, Actor *actor)
		:movie_{movie}, actor_{actor}
		{}

	~Edge();

};



#endif // EDGE_H_INCLUDED
