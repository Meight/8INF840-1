#pragma once

#include <vector>
#include <map>
#include <string>

using namespace std;

enum GroupingStrategy { BY_PAGE, BY_DOMAIN, BY_HOST };

typedef vector<string> VertexSetType;
typedef map<string, VertexSetType> VertexSetsType;

class Hypergraphe
{
	GroupingStrategy strategy;
	VertexSetsType vertexSets;

	string createLabelFromLink(string& url);
	string getVertexLabel(string& url);
public:
	~Hypergraphe();
	Hypergraphe(GroupingStrategy strategy);
	void addPage(string& url);
	void print();
};

