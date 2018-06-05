
#include <iostream>
#include <fstream>

#include "movie.h"
#include "actor.h"



void Movie::addActors(Actor *actor){
    actors_.push_back(actor);
}

const std::vector<Actor*> Movie::getActors() const{
    return actors_;
}

const std::string Movie::getTitle() const{
    return title_;
}

const int Movie::getYear() const{
    return year_;
}

Movie::~Movie(){};
