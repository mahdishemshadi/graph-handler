#include <algorithm>
#include <iostream>

#include "graph_maintenance/DGraph.cc"

using namespace std;
using namespace graphns;

void trace (DGraph* graph , DGraph* subgraph , const int labels[8] , LabelSet labelSet){
    for (int i=0 ; i<7 ; i++){
        EdgeSet* edgeSet = graph->getEdgeset();
        int size = edgeSet->size();
        for (int j=0 ; j<size ; j++){
            int label = edgeSet->back().second.second;
            if (label == labels[i]){
                VertexID a = edgeSet->back().first;
                VertexID b = edgeSet->back().second.first;
                subgraph->addEdge(a , b , label);
            }
            edgeSet->pop_back();
        }
    }
}
void combination (DGraph* graph , DGraph* subgraph , const int labels[8] , LabelSet labelset , int counter){
    int start = counter % 8;
    for (int i = counter ; i<(8-counter+1) ; i++){
        int labelToTrace [counter];
        for (int j=0 ; j<counter ; j++ , start++){
            labelToTrace[j] = labels[start];
            trace(graph , subgraph , labels , labelset);
        }
    }
}
void createsubgraph (DGraph* graph , const int labels[8] , LabelSet labelSet){
    EdgeSet* edgeSet = new EdgeSet();
    const int loop_conter = pow(2.0 , graph->getNumberOfLabels());
0    int counter;
    for (counter=0 ; counter<loop_conter ; counter++){
        DGraph* subgraph = new DGraph(edgeSet);
        combination(graph , subgraph , labels , labelSet , counter);
    }
}
int main(int argc, char *argv[])
{
    if( argc < 2 )
    {
        cout << "./queryAll <edge_file>" << endl;
        return 1;
    }

    string edge_file = argv[1]; // the file containing the graph
    DGraph* dg = new DGraph(edge_file);

    int N = dg->getNumberOfVertices();
    int L = dg->getNumberOfLabels();
    int LABELS [dg->getNumberOfLabels()];
    for (int i=0 ; i<dg->getNumberOfLabels() ; i++){
        LABELS[i] = i;
    }

    if( L < 3 || N < 100 ) {
        cout << "L or N too small" << endl;
        return 1;
    }
    // createsubgraph(dg , LABELS , labelset);

    return 0;
}
