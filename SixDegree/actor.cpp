#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <fstream>

#include "actor.h"
#include "movie.h"



void Actor::addEdge(Edge* edge){
		edges_.push_back(edge);
}

std::string Actor::getName() const{
		return name_;
}

const std::vector<Edge*> Actor::getEdges() const{
		return edges_;
}

Actor::~Actor() {};
