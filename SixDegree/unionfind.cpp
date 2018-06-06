#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <climits>
#include <cstdlib>
#include <cstdio>

#include "unionfind.h"
#include "actor.h"
#include "edge.h"
#include "movie.h"


bool UnionFind::loadFromFile(char const* in_filename, bool use_weighted_edges, bool actorConnection){
	std::ifstream infile(in_filename);
	bool have_header = false;

	while(infile){
		std::string s;
		if(!getline(infile, s)) break;
		if(!have_header){have_header=true; continue;}//skip header

		std::istringstream ss(s);
		std::vector<std::string> record;

		while(ss){
			std::string next;
			if(!getline(ss, next, '\t'))break;
			record.push_back(next);
		}

		if(record.size()!=3)continue;

		std::string actor_name(record[0]);
		std::string movie_name(record[1]);
		int movie_year = atoi(record[2].c_str());

		Actor *actor = new Actor(actor_name);
		Movie *movie = new Movie(movie_name, movie_year);

		if(actors_.find(actor)==actors_.end()){
			actors_.insert(actor);
		}else{
			std::set<Actor*>::iterator ita = actors_.find(actor);
			delete(actor);
			actor = *ita;
		}

		if(movies_.find(movie)==movies_.end()){
			movies_.insert(movie);
		}else{
			std::set<Movie*>::iterator itm = movies_.find(movie);
			delete(movie);
			movie = *itm;
		}
		movie->addActors(actor);
	}

	for(std::set<Actor*>::iterator it=actors_.begin(); it!=actors_.end(); it++)
		(*it)->parent_ = NULL;
	if(!infile.eof()){
		std::cerr<<"failed to read"<<in_filename<<std::endl;
		return false;
	}

	infile.close();
}


/*
 * Method that creates the set structure that defines the tree.
 * @param: the movie which the actors in this movie will traverse through
 * @return: void
 */

void UnionFind::createSet(Movie* movie){
	std::vector<Actor*> movie_actors = movie->getActors();
	Actor *actor = *(movie_actors.begin());

	std::vector<Actor*>::iterator it = movie_actors.begin();
	it++;
	while(it!=movie_actors.end())
		unioner((actor), (*it++));
}


/**
 * A recursive method that finds the sentinel node of an actor.
 * @param: the actor whose sentinel node is to be found
 * @return: the sentinel node
 */
void UnionFind::unioner(Actor* act1, Actor* act2){
	Actor *sent1 = finder(act1);
	Actor *sent2 = finder(act2);
	if(sent1!=sent2)
		sent1->parent_ = sent2;
}

/**
 * method that finds the year when two actors become connected. Returns
 * the year after that year is dicovered.
 * @param: the two actors which we will find if there exist a connection
 * @return: the year of which these two actors are connected
 */
Actor* UnionFind::finder(Actor* actor){
	if(actor->parent_==NULL)
		return actor;
	actor->parent_ = finder(actor->parent_);
	return actor->parent_;
}


int UnionFind::findConnectionTree(Actor* from_copy, Actor* to_copy){
	std::set<Actor*>::iterator from = actors_.find(from_copy);
	std::set<Actor*>::iterator to = actors_.find(to_copy);
	Actor *from_act = *from;
	Actor *to_act = *to;

	std::priority_queue<Movie*, std::vector<Movie*>, ConnectionCompare> mypq = pq_;

	while(!mypq.empty()){
		int year = mypq.top()->getYear();
		Movie *mov = mypq.top();
		mypq.pop();
		int next_year = year;

		while(!mypq.empty()){
			createSet(mov);
			mov = mypq.top();
			next_year = mov->getYear();

			if(next_year!=year)break;
			mypq.pop();
		}

		if(finder(from_act)==finder(to_act))
			return year;
	}
	return INT_MAX;
 }
