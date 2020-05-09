#pragma once 
// breadth-first search of graph 

// the state of vertices
enum class State {
    WHITE,  // UNDISCOVERED
    GRAY,   // DISCOVERING, the frontier
    BLACK,  // DISCOVERED
};

struct Vertex {
    State state;
    int distance;
    Vertex* predecessor;
    Vertex() {
        state = State::WHITE;
        distance = 0;
    }
}

void breadth_first_search(Graph<Vertex>* graph, Vertex* vertex) {
    
}
