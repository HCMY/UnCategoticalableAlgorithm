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

#include "actorgraph.h"
#include "actor.h"
#include "edge.h"
#include "movie.h"


bool ActorGraph::loadFromFile(char const *in_filename, bool use_weight_edges,
                    bool actor_connection){

    std::ifstream infile(in_filename);
    bool have_header = false;

    while(infile){
        std::string s;
        if(!getline(infile, s)) break;
        if(!have_header){have_header=true; continue;}

        std::istringstream ss(s);
        std::vector<std::string> record;

        while(ss){
            std::string next;
            if(!getline(ss, next, '\t')) break;
            record.push_back(next);
        }

        if(record.size()<3) continue;// we should have 3 columns

        std::string actor_name(record[0]);
        std::string movie_title(record[1]);
        int movie_year = atoi(record[2].c_str());

        Actor *actor = new Actor(actor_name);
        Movie *movie = new Movie(movie_title, movie_year);

			// if the actor dose not already exists
        if((actors_.find(actor)==actors_.end())){
            actors_.insert(actor);
        }else{
            std::set<Actor*>::iterator ita = actors_.find(actor);
            delete(actor);
            actor = *ita;
        }
        if((movies_.find(movie)==movies_.end())){
            movies_.insert(movie);
            pq.push(movie);
        }else{
            std::set<Movie*>::iterator itm = movies_.find(movie);
            delete(movie);
            movie = *itm;
        }
        movie->addActors(actor);
    }

    if(actor_connection) graphify();

    if(!infile.eof()){
        std::cerr<<"Failed to read"<<in_filename<<std::endl;
        return false;
    }
    infile.close();
    return true;
}


std::vector<std::pair<std::string, std::string> > ActorGraph::loadPairs(char const *pairsfile){
	std::vector<std::pair<std::string, std::string> > pairs_vec;
	std::ifstream infile(pairsfile);
	std::string s;
	getline(infile, s);

	while(getline(infile, s)){
		std::vector<std::string> record;
		int tab =s.find('\t');
		pairs_vec.push_back(std::make_pair(s.substr(0,tab),s.substr(tab+1, s.length())));
	}
	infile.close();
	return pairs_vec;
}




 const std::vector<int> ActorGraph::getAllSize() const{
    std::vector<int> actors_vec;
    int actor_nodes = actors_.size();
    int movies = movies_.size();
    actors_vec.push_back(actor_nodes);
    actors_vec.push_back(movies);

    int edge_nums = 0;
    for(std::set<Actor*>::iterator m=actors_.begin(); m!=actors_.end(); m++){
			edge_nums += ((*m)->getEdges()).size();
	}

	actors_vec.push_back(edge_nums);
    return actors_vec;
}


void ActorGraph::graphify(){
	for(std::set<Movie*>::iterator m=movies_.begin(); m!=movies_.end(); m++){
		std::vector<Actor*> movie_actors=(*m)->getActors();//get numbers of actors in this movie
		for(std::vector<Actor*>::iterator a1=movie_actors.begin(); a1!=movie_actors.end();a1++){
			for(std::vector<Actor*>::iterator a2=movie_actors.begin(); a2!=movie_actors.end();a2++){
				if(*a1 != *a2){
					Edge* edge = new Edge(*m, *a2);
					(*a1)->addEdge(edge);
				}
			}

		}
	}
}



/**
 * BFS traversal to find the shortest path given two actors.
 * @param: the two actors who we will find the unweighted path between
 * @return: the string representation of the path
 */
std::string ActorGraph::BFS(Actor* from_copy, Actor* to_copy){
	std::set<Actor*>::iterator to = actors_.find(to_copy);
	std::set<Actor*>::iterator from = actors_.find(from_copy);
	Actor *to_actor = *to;
	Actor *from_actor = *from;

	// initialize visit matrix
	for(std::set<Actor*>::iterator a=actors_.begin(); a!=actors_.end(); a++){
		(*a)->visited_ = false;
		(*a)->pre_visted_actor_ = NULL;
	}

	std::queue<Actor*> q;
	q.push(from_actor);
	from_actor->visited_ = true;

	while(!q.empty()){
		Actor *curr = q.front();
		q.pop();
		if(curr==to_actor) break;//finded

		std::vector<Edge*> edges = curr->getEdges();
		for(std::vector<Edge*>::iterator e=edges.begin(); e!=edges.end(); e++){
			Edge* edge = *e;
			if(!(edge->actor_->visited_)){
				q.push(edge->actor_);
				edge->actor_->visited_ = true;
				edge->actor_->pre_visted_movie_ = edge->movie_;
				edge->actor_->pre_visted_actor_ = curr;
			}
		}
	}

	std::string s = "";
	if((*actors_.find(to_actor))->pre_visted_actor_ == NULL)
		return s;

	Actor* curr = to_actor;
	s.append("("+to_actor->getName()+")");

	while(curr!=from_actor){
		std::stringstream stream;
		stream<<curr->pre_visted_movie_->getYear();

		s.insert(0,"--["+curr->pre_visted_movie_->getTitle()+"#@"+stream.str()+"]-->");
		s.insert(0,"("+curr->pre_visted_actor_->getName()+")");
		curr = curr->pre_visted_actor_;
	}

	return s;
}


