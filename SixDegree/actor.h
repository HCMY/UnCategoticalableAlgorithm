#ifndef ACTOR_H_INCLUDED
#define ACTOR_H_INCLUDED

#include <string>
#include <vector>

#include "edge.h"
#include "movie.h"


class Movie;


class Actor
{
public:
	Actor(std::string &name)
		:name_{name}
		{}

	~Actor();
	void addEdge(Edge *edge);
	const std::vector<Edge *> getEdges() const;
	std::string getName() const;



public:
	std::string name_;
	std::vector<Edge *> edges_;
	bool visited_;
	Actor *pre_visted_actor_;
	Movie *pre_visted_movie_;

	
	//// used in Dijksta Algorithm, 
	/// which store shortest distance from original node to others
	int dist_;

	/// point to this nodes' parent node in shortest path from original node to target node
	Actor *parent_;
};

#endif // ACTOR_H_INCLUDED
