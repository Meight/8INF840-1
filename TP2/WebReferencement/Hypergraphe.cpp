#include "stdafx.h"
#include "Hypergraphe.h"
#include "LUrlParser.h"
#include <windows.h>
#include <fstream>
#include <sstream>
#include <algorithm>

using LUrlParser::clParseURL;


Hypergraphe::Hypergraphe(GroupingStrategy groupingStrategy)
{
	strategy = groupingStrategy;
}

Hypergraphe::~Hypergraphe()
{
}

#include <iostream>

string Hypergraphe::createLabelFromLink(string & url)
{
	clParseURL URL = clParseURL::ParseURL(url);

	if (!URL.IsValid())
		return url;

	switch (strategy) {
	case BY_PAGE:
		return url;
		break;
	case BY_DOMAIN:
		return URL.m_Host;
		break;
	case BY_HOST:
		return URL.m_Host;
		break;
	default:
		return url;
		break;
	}
}

string Hypergraphe::getVertexLabel(string & url)
{
	return createLabelFromLink(url);
}



void Hypergraphe::addPage(Vertex* vertex)
{
	// Determine the label of the new vertex's target set.
	string label = getVertexLabel(vertex->url);

	vertexSets[label].push_back(vertex);

	cout << "Added page " << vertex->url << " to label " << label << endl;
}

void Hypergraphe::print()
{
	VertexSetsType::iterator it;

	HANDLE  hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	cout << endl << "Printing hypergraph..." << endl << endl;

	string lastLabel;
	for (it = vertexSets.begin(); it != vertexSets.end(); ++it)
	{
		SetConsoleTextAttribute(hConsole, 12);
		cout << "[" << it->first << "]" << " - outDegree: " << clusterOutDegree[it->first] <<endl;

		SetConsoleTextAttribute(hConsole, 15);
		for (auto& vertex : it->second)
			cout << "--- " << vertex->url << endl;

		cout << endl;
	}
	
	for (auto& p : pointedByCluster) {
		cout << "Page " << p.first << " pointed by" << endl;
		for (auto& c : p.second) {
			cout << "--- " << c << endl;
		}
		cout << endl;
	}
}


void Hypergraphe::load(string pathNodes, string pathEdges) 
{
	ifstream fileNodes(pathNodes, ios::in);
	ifstream fileEdges(pathEdges, ios::in);

	// Create clusters
	if (fileNodes)
	{
		string line;

		// Skip the first 2 lines
		getline(fileNodes, line);
		getline(fileNodes, line);

		// Create vertices
		while (getline(fileNodes, line)) {
			// Split the line
			istringstream iss(line);
			vector<string> elements;
			while (iss) {
				string word;
				iss >> word;
				elements.push_back(word);
			}

			// Add vertex to the map
			Vertex* v = new Vertex;
			v->id = stoi(elements.at(0));
			v->outDegree = stoi(elements.at(1));
			v->inDegree = 0;
			v->url = elements.at(2);
			vertices[v->id] = v;
			addPage(v);
			cout << "Vertice " << v->id << " added" << endl;

			elements.clear();
		}

		fileNodes.close();
	}
	else
	{
		cerr << "Could not open the nodes file !" << endl;
	}

	// Create hyperEdges
	if (fileEdges)
	{
		string line;

		// Skip the first 2 lines
		getline(fileEdges, line);
		getline(fileEdges, line);

		
		while (getline(fileEdges, line)) {
			// Find the source and destination of the edge
			istringstream iss(line);
			vector<string> elements;
			while (iss) {
				string word;
				iss >> word;
				elements.push_back(word);
			}
			int fromVertex = stoi(elements.at(0));
			int toVertex = stoi(elements.at(1));

			if (fromVertex != toVertex) {
				// Get the label of the cluster of the two vertices
				string labelFrom = getVertexLabel(vertices[fromVertex]->url);
				string labelTo = getVertexLabel(vertices[toVertex]->url);

				if (labelFrom != labelTo) {
					// Check if the pages is not already pointed by the cluster
					if (find(pointedByCluster[toVertex].begin(), pointedByCluster[toVertex].end(), labelFrom) == pointedByCluster[toVertex].end()) {
						pointedByCluster[toVertex].push_back(labelFrom);
						++clusterOutDegree[labelFrom];
					}
				}
			}

			elements.clear();
		}

		fileEdges.close();
	}
	else
	{
		cerr << "Could not open the edges file !" << endl;
	}

}
