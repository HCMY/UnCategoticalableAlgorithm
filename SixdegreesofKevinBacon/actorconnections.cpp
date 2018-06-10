#include <fstream>
#include <iostream>
#include <string>
#include <time.h>

#include "ActorGraph.h"
#include "actor.h"
#include "unionfind.h"

int main(int argc, char *argv[])
{
    /*
	char *file = argv[1];
	char *pairs_file = argv[2];
	char *outfile = argv[3];

	bool use_bfs = false;
	if(argc==5){
		std::string c(argv[4]);
		use_bfs = (c.compare("gfind")==0)? true:false;
	}*/

	char *file = "2-node_simple.tsv";//argv[1];
	char *pairs_file = "2-node_simple_pair.tsv";//argv[2];
	char *outfile = "out_connections.tsv";//argv[3];

	bool use_bfs = false;


	std::ofstream output;
	output.open(outfile);

	ActorGraph graph1;
	std::vector<std::pair<std::string, std::string>> vec = graph1.loadPairs(pairs_file);

	output<<"Actor1"<<'\t'<<"Actor2"<<'\t'<<"Year"<<std::endl;
	//std::cout<<"Actor1"<<'\t'<<"Actor2"<<'\t'<<"Year"<<std::endl;

	int year = 0;
	//clock_t start_t, end_t;
	for(int idx=0; idx<vec.size(); idx++){

		//start_t=clock();

		Actor *actor1 = new Actor(vec.at(idx).first);
		Actor *actor2 = new Actor(vec.at(idx).second);

		if(use_bfs){
			ActorGraph graph;
			graph.loadFromFile(file, true, true);
			year = graph.finfConnecttionUsingBFS(actor1, actor2);

		}else{
			UnionFind unionT;
			unionT.loadFromFile(file, true, true);
			year = unionT.findConnectionTree(actor1, actor2);
		}



		/*end_t = clock();
		std::cout<<actor1->getName()<<'\t';
		std::cout<<actor2->getName()<<'\t'<<year<<std::endl;
		std::cout<<"tooks time "<<(end_t-start_t)/CLOCKS_PER_SEC<<" seconds"<<std::endl;*/
		output<<actor1->getName()<<'\t'<<actor2->getName()<<'\t'<<year<<std::endl;

		delete actor1;
		delete actor2;

	}
	return 0;
}

