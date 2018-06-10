#include <iostream>
#include "edge.h"
#include "movie.h"
#include "actor.h"
#include "actorgraph.h"

using namespace std;

/// test grapth nodes
void test_graph_nodes(){
    ActorGraph graph;
    graph.loadFromFile("movie_casts.tsv",false,true);

    std::vector<int> check_nodes_nums = graph.getAllSize();
    std::cout<<"actor nodes= "<<check_nodes_nums[0]<<std::endl;
    std::cout<<"movies= "<<check_nodes_nums[1]<<std::endl;
    std::cout<<"edges= "<<check_nodes_nums[2]<<std::endl;

}

void test_load_pairs(){
    ActorGraph graph;
    graph.loadFromFile("movie_casts.tsv",false,true);

    std::vector<std::pair<std::string, std::string> > pair_vec = graph.loadPairs("test_pairs.tsv");
    for(int idx=0; idx<pair_vec.size(); idx++)
        std::cout<<pair_vec.at(idx).first<<"<-->"<<pair_vec.at(idx).second<<std::endl;
}

/*
int main()
{
    //test_graph_nodes();
    test_load_pairs();
    return 0;
}*/
