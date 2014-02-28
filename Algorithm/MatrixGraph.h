#pragma once
#include "Graph.h"
namespace Test {
	template<class VertexValueType, class EdgeValueType> class MatrixGraph : public Graph<VertexValueType, EdgeValueType> {
	private:
		struct Less : binary_function <pair<unsigned int, unsigned int>, pair<unsigned int, unsigned int>, bool> {
			bool operator() (const pair<unsigned int, unsigned int> & first, const pair<unsigned int, unsigned int> & second)
			{
				if (first.first < second.first) return true;
				if (first.first == second.first && first.second < second.second) return true;
				return false;
			}
		};

		map<pair<unsigned int, unsigned int>, unsigned int, Less> matrix;
	public:
		MatrixGraph(void) : Graph() {}
		MatrixGraph(bool directed) : Graph(directed) {}
		~MatrixGraph(void) {}

		void InsertEdge(unsigned int id, unsigned int from, unsigned int to, EdgeValueType value = 1)
		{
			Graph::InsertEdge(id, from, to, value);
			pair<unsigned int, unsigned int> key = make_pair(from, to);
			this->matrix[key] = id;
			if (!this->directed && from != to) {
				key = make_pair(to, from);
				this->matrix[key] = id;
			}
		}

		void Print(void)
		{
			map<unsigned int, Vertex *>::iterator to;
			for (to = this->vertices.begin(); to != this->vertices.end(); to++) {
				cout << "\t" << to->first;
			}

			cout << endl;

			map<unsigned int, Vertex *>::iterator from;
			pair<unsigned int, unsigned int> key;
			for (from = this->vertices.begin(); from != this->vertices.end(); from++) {
				cout << from->first;
				for (to = this->vertices.begin(); to != this->vertices.end(); to++) {
					key = make_pair(from->first, to->first);
					cout << "\t";
					if (this->matrix.find(key) != this->matrix.end()) {
						cout << this->edges[this->matrix[key]]->value;
					}
				}

				cout << endl;
			}
		}
	};
}