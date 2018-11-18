#include <string>
#include <list>
#include <map>
#include <fstream>

#define INFINITY 100000

// This version of bfs uses a pointer representation.
// Each vertex contains within it a list of pointers
// to the other vertices the vertex is connected to.
template <typename T> class vertex
{
public:
	T key;
	enum color {white,gray,black};
	color c;
	int d, f;
	vertex<T> *p;
	std::list<vertex<T>*> edges;

	vertex() {}
	vertex(const T& v) { key = v; c = white; d = INFINITY; p = NULL; f = INFINITY; }
};

template <typename T> class graph
{
public:
	graph(const std::string& fileName);
	~graph();

	void dfs(std::list<T>& L, const T& s);
	void dfs();
	
	void topoSort(std::list<T>& L, const T& s);
private:
	// Since the edges are stored in the vertices, we only need
	// a list of vertices in the graph. For convenience, this is
	// stored as a map.
	std::map<T, vertex<T>*> V;
};

template <typename T>
graph<T>::graph(const std::string& filename)
{
	std::ifstream in;
	in.open(filename.c_str());

	int vertex_count = 0;
	in >> vertex_count;
	for(int n = 0;n < vertex_count;n++) {
		T key;
		in >> key;
		V[key] = new vertex<T>(key);
	}

	int edge_count = 0;
	in >> edge_count;
	for(int n = 0;n < edge_count;n++) {
		T first, second;
		in >> first >> second;
		V[first]->edges.push_back(V[second]);
	}
}

template <typename T>
graph<T>::~graph() {
	auto itr = V.begin();
	while(itr != V.end()) {
		delete itr->second;
		itr++;
	}
}

template <typename T>
void graph<T>::dfs() {
	auto itr = V.begin();
	while (itr != V.end()) {
		itr->second->c = vertex<T>::white;
		itr->second->p = itr->second;
		itr++;
	}
	int time = 0;

	std::list<vertex<T>*> S;
	for (itr = V.begin(); itr != V.end(); itr++) {
		if (itr->second->c == vertex<T>::white) {
			S.push_back(itr->second);

			while (S.size() != 0) {
				vertex<T> *u = S.back();

				time++;
				if (u->c == vertex<T>::gray) {
					u->c = vertex<T>::black;
					u->f = time;
					S.pop_back();
				}
				else if (u->c == vertex<T>::white) {
					u->c = vertex<T>::gray;
					u->d = time;
				}
				else if (u->c == vertex<T>::black) {
					time--;
					S.pop_back();
				}

				std::list<vertex<T>*>& edges = u->edges;
				auto itr2 = edges.begin();
				while (itr2 != edges.end()) {
					vertex<T>* v = *itr2;
					if (v->c == vertex<T>::white) {
						v->p = u;
						S.push_back(v);
					}
					itr2++;
				}
			}
		}
	}
}


//Depth First Search that stores each vertex in a given list as it turns black
template <typename T>
void graph<T>::dfs(std::list<T>& L, const T& s) {
	auto itr = V.begin();
	while (itr != V.end()) {
		itr->second->c = vertex<T>::white;
		itr->second->p = itr->second;
		itr++;
	}
	int time = 0;

	std::list<vertex<T>*> S;
	for (itr = V.begin(); itr != V.end(); itr++) {
		if (itr->second->c == vertex<T>::white) {
			S.push_back(itr->second);
			S.push_back(V[s]);
			while (S.size() != 0) {
				vertex<T> *u = S.back();
				time++;
				if (u->c == vertex<T>::gray) {
					u->c = vertex<T>::black;
					u->f = time;
					L.push_front(u->key);
					S.pop_back();
				}
				else if (u->c == vertex<T>::white) {
					u->c = vertex<T>::gray;
					u->d = time;
				}
				else if (u->c == vertex<T>::black) {
					time--;
					S.pop_back();
				}

				std::list<vertex<T>*>& edges = u->edges;
				auto itr2 = edges.begin();
				while (itr2 != edges.end()) {
					vertex<T>* v = *itr2;
					if (v->c == vertex<T>::white) {
						v->p = u;
						S.push_back(v);
					}
					itr2++;
				}
			}
		}
	}
}

template <typename T>
void graph<T>::topoSort(std::list<T>& L,const T& s) {
	dfs(L,s);

	auto itr = L.begin();
	while (itr != L.end()) {
		std::cout << *itr << std::endl;
		itr++;
	}
}