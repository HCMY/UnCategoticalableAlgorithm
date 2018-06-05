#include <fstream>
#include <iostream>
#include <string>

#include "actorgraph.h"


int main(int argc, char const *argv[])
{
	/*if(argc!=5){
		std::err_notice = "incorrect number of arguments,
							required number of arguments are 4,
							including
							-movie_casts file<file path should be given>,
							-whether loading egdes' weights<bool>,
							-test pairs file,
							-output file name"
		std::cout<<err_notice<<std::endl;

	}*/


	std::cout<<"shortest path accroding to 'move_casts.tsv' \
	between two actors in 'test_pairs.tsv' are here:"<<std::endl;

	char *file = "movie_casts.tsv";
	char *pairs_file = "test_pairs.tsv";
	char *outfile = "out_without_weight.tsv";
	bool weighted_egdes = true;

	std::ofstream output;
	output.open(outfile);

	ActorGraph graph;
	graph.loadFromFile(file, weighted_egdes, true);
	std::vector<std::pair<std::string, std::string> > pair_vec = graph.loadPairs(pairs_file);

    output << "(actor)--[movie#@year]-->(actor)--..." << std::endl;

	for(int idx=0; idx<pair_vec.size(); idx++){
		Actor *actor_from = new Actor(pair_vec.at(idx).first);
		Actor *actor_to = new Actor(pair_vec.at(idx).second);

		std::string s;
		if(!weighted_egdes)
			s = graph.BFS(actor_from, actor_to);
        else
            s = graph.Dijkstra(actor_from, actor_to);
		//output<<s<<std::endl;///uncomment it while use command line
		std::cout<<s<<std::endl;
	}

	return 0;
}
