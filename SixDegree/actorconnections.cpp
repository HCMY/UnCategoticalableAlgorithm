#include <fstream>
#include <iostream>
#include <string>
#include <time.h>

#include "actorgraph.h"
#include "actor.h"

int main(int argc, char const *argv[])
{
	char *file = "movie_casts.tsv";//argv[1];
	char *pairs_file = "test_pairs.tsv";
	char *outfile = "out.tsv";

	bool use_bfs = true;
	if(argc==5){
		std::string c(argv[4]);
		use_bfs = (c.compare("gfind")==0)? true:false;
	}

	std::ofstream output;
	output.open(outfile);

	ActorGraph graph1;
	std::vector<std::pair<std::string, std::string>> vec = graph1.loadPairs(pairs_file);

	output<<"Actor1"<<'\t'<<"Actor2"<<'\t'<<"Year"<<std::endl;
	std::cout<<"Actor1"<<'\t'<<"Actor2"<<'\t'<<"Year"<<std::endl;

	int year = 0;
	clock_t start_t, end_t;
	for(int idx=0; idx<vec.size(); idx++){
		
		start_t=clock();

		Actor *actor1 = new Actor(vec.at(idx).first);
		Actor *actor2 = new Actor(vec.at(idx).second);

		if(use_bfs){
			ActorGraph graph;
			graph.loadFromFile(file, true, true);
			year = graph.finfConnecttionUsingBFS(actor1, actor2);
		}else{
			std::cout<<"TODO"<<std::endl;
		}

		end_t = clock();
		std::cout<<actor1->getName()<<'\t';
		std::cout<<actor2->getName()<<'\t'<<year<<std::endl;
		 std::cout<<"tooks time "<<(end_t-start_t)/CLOCKS_PER_SEC<<" seconds"<<std::endl;
	}

	return 0;
}

