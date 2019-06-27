#include <vector>
#include <list>
#include <unordered_map>



template <typename Vertex>
class Graph {
public:
	void insert(Vertex* from, Vertex* to) {
		m_data[from].push_back(to);
	}

	void erase(Vertex* from, Vertex* to) {

	}

private:
	std::unordered_map<Vertex*, std::list<Vertex*>> m_data;
};
