#pragma once
#include <functional>
#include <map>
#include "String.h"
using namespace std;
namespace Test {
	template<class VertexValueType, class EdgeValueType> class Graph {
	protected:
		class Vertex {
		public:
			unsigned int id;
			VertexValueType value;
			Vertex(unsigned int id, VertexValueType value) : id(id), value(value) {}
		};

		class Edge {
		public:
			unsigned int id;
			EdgeValueType value;
			unsigned int from;
			unsigned int to;
			Edge(unsigned int id, unsigned int from, unsigned int to, EdgeValueType value)
				: id(id), from(from), to(to), value(value)
			{
			}
		};

		map<unsigned int, Vertex *> vertices;
		map<unsigned int, Edge *> edges;
		bool directed;

	public:
		Graph(void) : directed(true) {}
		Graph(bool directed) : directed(directed) {}
		virtual ~Graph(void)
		{
			map<unsigned int, Edge *>::iterator eit;
			for (eit = this->edges.begin(); eit != this->edges.end(); eit++) {
				delete eit->second;
			}

			map<unsigned int, Vertex *>::iterator vit;
			for (vit = this->vertices.begin(); vit != this->vertices.end(); vit++) {
				delete vit->second;
			}
		}

		virtual void InsertVertex(unsigned int id, VertexValueType value = 1)
		{
			if (this->vertices.find(id) != this->vertices.end())
				throw invalid_argument(String::Format("Vertex id %d already exists", id));

			this->vertices[id] = new Vertex(id, value);
		}

		virtual void InsertEdge(unsigned int id, unsigned int from, unsigned int to, EdgeValueType value = 1)
		{
			if (this->edges.find(id) != this->edges.end())
				throw invalid_argument(String::Format("Edge id %d already exists", id));

			if (this->vertices.find(from) == this->vertices.end())
				throw invalid_argument(String::Format("Vertex id %d does not exist", from));

			if (this->vertices.find(to) == this->vertices.end())
				throw invalid_argument(String::Format("Vertex id %d does not exist", to));

			this->edges[id] = new Edge(id, from, to, value);
		}
	};
}