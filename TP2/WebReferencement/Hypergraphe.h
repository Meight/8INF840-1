#pragma once

#include <vector>
#include <map>
#include <string>

using namespace std;

enum GroupingStrategy { BY_PAGE, BY_DOMAIN, BY_HOST };

struct Vertex {
	int id;
	int outDegree;
	int inDegree;
	string url;
};

typedef vector<Vertex*> VertexSetType;
typedef map<string, VertexSetType> VertexSetsType;

typedef map<int, vector<string>> PagesPointedType;

class Hypergraphe
{
	GroupingStrategy strategy;
	VertexSetsType vertexSets;

	map<int, Vertex*> vertices;

	PagesPointedType pointedByCluster;
	map<string, int> clusterOutDegree;

	string createLabelFromLink(string& url);
	string getVertexLabel(string& url);
public:
	~Hypergraphe();
	Hypergraphe(GroupingStrategy strategy);
	void addPage(Vertex* vertex);
	void print();
	void load(string pathNodes, string pathEdges);
};

