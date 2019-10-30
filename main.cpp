#include <iostream>
#include <fstream>
#include <chrono>
#include "Snap.h"

using namespace std::chrono;
using namespace std;
typedef PNGraph Graph;

void graphML(Graph g);
void GEXF(Graph g);
void GDF(Graph g);
void graphSon(Graph g);

int main() {
    cout << ">>Importando Grafica..." << endl;
    Graph graph = TSnap::LoadEdgeList<Graph>("twitter.txt",0,1);
    
    
    graphML(graph);
    cout << ">>GraphML generado " << endl;
    
    GEXF(graph);
    cout << ">>GEFX generado " << endl;
    
    GDF(graph);
    cout << ">>GDF generado " << endl;
    
    graphSon(graph);
    cout << ">>GraphSON generado " << endl;

    cout << ">>Archivos generados con exito" << endl;
    return 0;
}




void graphML(Graph g) {
    std::ofstream file;
    file.open("graph.graphml");
    if (file.is_open()) {
        file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
        file << "<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd\">\n";
        file << "<graph id=\"G\" edgedefault=\"undirected\">\n";
        
        for (Graph::TObj::TNodeI NI = g->BegNI(); NI < g->EndNI(); NI++)
            file << "<node id=\"" << NI.GetId() << "\"/>\n";
        
        int i = 1;
        for (Graph::TObj::TEdgeI EI = g->BegEI(); EI < g->EndEI(); EI++, ++i)
            file << "<edge id=\"e" << i << "\" source=\"" << EI.GetSrcNId() << "\" target=\"" << EI.GetDstNId() << "\"/>\n";
        
        file << "</graph>\n";
        file << "</graphml>\n";
        file.close();
    }
}

void GEXF(Graph g) {
    std::ofstream file;
    file.open("graph.gexf");
    if (file.is_open()) {
        file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
        file << "<gexf xmlns=\"http://www.gexf.net/1.2draft\" version=\"1.2\">\n";
        file << "<graph mode=\"static\" defaultedgetype=\"undirected\">\n";
        
        file << "<nodes>\n";
        for (Graph::TObj::TNodeI NI = g->BegNI(); NI < g->EndNI(); NI++)
            file << "<node id=\"" << NI.GetId() << "\" />\n";
        file << "</nodes>\n";
        
        file << "<edges>\n";
        int i = 1;
        for (Graph::TObj::TEdgeI EI = g->BegEI(); EI < g->EndEI(); EI++, ++i)
            file << "<edge id=\"" << i << "\" source=\"" << EI.GetSrcNId() << "\" target=\"" << EI.GetDstNId() << "\" />\n";
        file << "</edges>\n";
        
        file << "</graph>\n";
        file << "</gexf>\n";
        file.close();
    }
}

void GDF(Graph g) {
    std::ofstream file;
    file.open("graph.gdf");
    if (file.is_open()) {
        file << "nodedef>id VARCHAR\n";
        for (Graph::TObj::TNodeI NI = g->BegNI(); NI < g->EndNI(); NI++)
            file << NI.GetId() << "\n";
        
        file << "edgedef>source VARCHAR, destination VARCHAR\n";
        for (Graph::TObj::TEdgeI EI = g->BegEI(); EI < g->EndEI(); EI++)
            file << EI.GetSrcNId() << ", " << EI.GetDstNId() << "\n";
        
        file.close();
    }
}

void graphSon(Graph g) {
    std::ofstream file;
    file.open("graph.json");
    if (file.is_open()) {
        file << "{ \"graph\": {\n";
        file << "\"nodes\": [\n";
        for (Graph::TObj::TNodeI NI = g->BegNI(); NI < g->EndNI(); ) {
            file << "{ \"id\": \"" << NI.GetId() << "\" }";
            if (NI++ == g->EndNI())
                file << " ],\n";
            else
                file << ",\n";
        }
        
        file << "\"edges\": [\n";
        for (Graph::TObj::TEdgeI EI = g->BegEI(); EI < g->EndEI(); ) {
            file << "{ \"source\": \"" << EI.GetSrcNId() << "\", \"target\": \"" << EI.GetDstNId() << "\" }";
            if (EI++ == g->EndEI())
                file << " ]\n";
            else
                file << ",\n";
        }
        file << "} }";
        
        file.close();
    }
}
