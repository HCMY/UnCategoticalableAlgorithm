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

#include "ActorGraph.h"
#include "actor.h"
#include "edge.h"
#include "movie.h"


/*
Parse file, extract actors, movie to graph
at the end of this method, a graph will be generated

==================parameters explaintation==============
@in_filename: movie_casts
@use_weight_edges: wether loading weights while create Graph
@acotr_connection: wether create connect network while loading Graph
========================================================

------parameters----------|------type-----------|------required--|
@in_filename              |   str-like          | 		true 	 |
@use_weight_edges         |    boolean          |       true     |
@actor_connection         |    boolean          |       true     |


#return: bool, return true when loading process get succeed
		otherwise, return false
*/
bool ActorGraph::loadFromFile(char const *in_filename, bool use_weight_edges,
                    bool actor_connection){

    std::ifstream infile(in_filename);
    bool have_header = false;

    while(infile){
        std::string s;
        if(!getline(infile, s)) break;
        if(!have_header){have_header=true; continue;}//skip the header

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

		/// this step gonna use 'ActorCompare' function object in actorgpaph
		/// to verdict wether the target actor is already exists
		/// if doesn't exists, then insert it, else, delete it
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

    if(actor_connection) graphify();//loading graph weights

    if(!infile.eof()){
        std::cerr<<"Failed to read"<<in_filename<<std::endl;
        return false;
    }
    infile.close();
    return true;
}


/*
load test pairs used to test

==================parameters explaintation==============
@pairsfile: test_pairs.tsv
========================================================

------parameters----------|------type-----------|------required--|
@pairsfile                |   str-like          | 		true 	 |


#return: a vector contain elements like <actor, actor>
*/
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


/*
access graph's elements, including actors, edges and movies
notes: this methos will not be used in actual calculate
	   I just use it do demostrate the information has been
	   loading in Graph correctly or not

#return: a vector contains total nums of above elements
        index 0 is nums of actos in the graph
        index 1 is nums of movies in the graph
        index 2 is nums of movies in the graph
*/
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

/*
deploy edges of the Graph
if two actors play in same movie, they'll be a edge between
the edge was store in class Actor
*/
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
  BFS traversal to find the shortest path given two actors.

 ==================parameters explaintation==============
@from_copy: host actor
@to_copy: target actor you want to know
========================================================

------parameters----------|------type-----------|------required--|
@from_actor               |   Actor             | 		true 	 |
@to_actor                 |   Actor             |       true     |

#return: shortest path as string from host actor to target actor
		 the path's elements are movies
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


/*
Given actors X and Y, after which year did they become connected
the edges' weight are years foumulate result

return: string
*/
std::string ActorGraph::Dijkstra(Actor* from_copy, Actor* to_copy){
	std::set<Actor*>::iterator to  = actors_.find(to_copy);
	std::set<Actor*>::iterator from = actors_.find(from_copy);
	Actor *from_actor = *from;
	Actor *to_actor = *to;

	for(std::set<Actor*>::iterator a=actors_.begin(); a!=actors_.end(); a++){
		(*a)->visited_ = false;
		(*a)->dist_ = INT_MAX;
	}

	std::priority_queue<std::pair<int, Actor*>, std::vector<std::pair<int, Actor*>>, DistCompare> mypq;
	from_actor->dist_ = 0;
	mypq.push(std::make_pair(0, from_actor));

	while(!mypq.empty()){
		std::pair<int, Actor*> curr = mypq.top();
		mypq.pop();

		if(curr.second->visited_ == false){
			curr.second->visited_ = true;
			std::vector<Edge*> edges = curr.second->getEdges();
			for(std::vector<Edge*>::iterator e=edges.begin(); e!=edges.end(); e++){
				Edge* edge = *e;
				int c = curr.second->dist_+(1+(2015 - edge->movie_->getYear()));
				if(c < edge->actor_->dist_){
					edge->actor_->pre_visted_actor_ = curr.second;
					edge->actor_->pre_visted_movie_ = edge->movie_;
					edge->actor_->dist_ = c;
					mypq.push(std::make_pair(c, edge->actor_));
				}
			}
		}
	}

	std::string s = "";
	Actor* curr = to_actor;
	s.append("("+to_actor->getName()+")");
	while(curr!=from_actor){
		std::stringstream stream;
		stream<<curr->pre_visted_movie_->getYear();
		s.insert(0, "--["+curr->pre_visted_movie_->getTitle()+"#@"+stream.str()+"]-->");
		s.insert(0, "("+curr->pre_visted_actor_->getName()+")");
		curr = curr->pre_visted_actor_;
	}

	return s;
}


/**
 * Method that find whether there is a connection between two actors after 
 * all the movies in one year was added.
 * @param: the two actors where we will find if there exists a path between
 * @return: year of which these two actors are connected  
 */
int ActorGraph::finfConnecttionUsingBFS(Actor* from, Actor *to){
	// made a copy here so the global one does not get poped 
	std::priority_queue<Movie*, std::vector<Movie*>, ConnectionCompare> p = pq;
	
	// iterate each movie in a sorted queue 
	while(!p.empty()){
		int year = p.top()->getYear();// defaults to the first movie of that same year  
		Movie* mov = p.top();
		p.pop();

		int next_year = year;
		// Graphyify for each movie that is in the same year. i.e add more edges to each actor
		while(!p.empty()){
			graphifyFS(mov);
			mov = p.top();
			next_year = mov->getYear();
			if(next_year != year) break;
			p.pop();
		}

		/// run BFS to find whether this year gives us a valid path 
		/// if the returned result is not an empty string
		/// means a connection is established in this year
		if(BFS(from, to) != "")
			return year;
	}

	return INT_MAX;
}

/**
 * A graphify method made specifically for the actorconnection portion of the assignment.
 * Only adds the edges that was passed in by the movie.
 * @param: the movie whose actors in it are connected through this edge
 * @return: void 
 */
void ActorGraph::graphifyFS(Movie* movie){
	std::vector<Actor*> movie_actors = movie->getActors();
	for(std::vector<Actor*>::iterator a1=movie_actors.begin(); a1!=movie_actors.end(); a1++){
		for(std::vector<Actor*>::iterator a2=movie_actors.begin(); a2!=movie_actors.end();a2++){
			if(*a1 != *a2){
				Edge* edge = new Edge(movie, *a2);
				(*a1)->addEdge(edge);
			}
		}
	}
}


