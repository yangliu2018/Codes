#pragma once 
// breadth-first search of graph 

// the state of vertices
enum class State {
    UNDISCOVERED,
    DISCOVERING,
    DISCOVERED,
};

struct Vertex {
    State state;
    Vertex() {
        state = State::UNDISCOVERED;
    }
}

void breadth_first_search(Graph<Vertex>* graph, Vertex* vertex) {
    
}
