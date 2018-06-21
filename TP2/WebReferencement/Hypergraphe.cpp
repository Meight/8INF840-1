#include "stdafx.h"
#include "Hypergraphe.h"
#include "LUrlParser.h"
#include <windows.h>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>

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

map<int, float> Hypergraphe::pageRank(float dampening, float epsilon)
{
	map<string, float> scoreClusters;
	map<string,map<int, float>> scorePages;

	// Count the number of pages with incoming hyperarcs in the collections
	map<string, int> pagesCount;
	for (auto& cluster : vertexSets) {
		pagesCount[cluster.first] = 0;
		for (auto& vertex : cluster.second) {
			if (pointedByCluster[vertex->id].size() > 0) {
				++pagesCount[cluster.first];
			}
		}
	}

	// Initialization
	cout << "--- Init :" << endl;
	for (auto& cluster : vertexSets) {
		string name = cluster.first;
		VertexSetType set = cluster.second;

		// Compute score of the pages
		for (auto& vertex : set) {
			scorePages[name][vertex->id] = (pagesCount[name] == 0) ? 0.0f : 1.0f / pagesCount[name];
			cout << "    Score page " << vertex->id << ": " << scorePages[name][vertex->id] << endl;
		}

		// Compute score of the cluster
		scoreClusters[name] = 0;
		for (auto& score : scorePages[name]) {
			scoreClusters[name] = scoreClusters[name] + score.second;
		}
		cout << "      => Score cluster \"" << name << "\": " << scoreClusters[name] << endl;
		cout << endl;
	}
	
	// Compute the reputation of the clusters until convergence
	bool done = false;
	map<string, float> delta;
	do 
	{
		system("Pause");
		cout << "--- Iter :" << endl;
		for (auto& cluster : vertexSets) {
			string name = cluster.first;
			VertexSetType set = cluster.second;

			// Keep the old score
			delta[name] = scoreClusters[name];

			// Update the score of the cluster
			for (auto& vertex : set) {
				float score = 0;
				for (auto& c : pointedByCluster[vertex->id]) {
					score += (scoreClusters[c] / clusterOutDegree[c]) + (dampening / pagesCount[name]);
				}
				score = score * (1 - dampening);
				scorePages[name][vertex->id] = score;
				cout << "    Score page " << vertex->id << ": " << scorePages[name][vertex->id] << endl;
			}

			// Update the score of the cluster
			scoreClusters[name] = 0;
			for (auto& score : scorePages[name]) {
				scoreClusters[name] = scoreClusters[name] + score.second;
			}
			cout << "      => Score cluster \"" << name << "\": " << scoreClusters[name] << endl;
			cout << endl;
		}
		
		// Has it converged ?
		cout << "    --- Does it converge ? " << endl;
		done = true;
		for (auto& val : delta) {
			cout << "        Cluster \"" << val.first << "\": delta = " << fabs(val.second - scoreClusters[val.first]);
			if ( fabs(val.second-scoreClusters[val.first]) > epsilon) {
				done = false;
				cout << "  --- NOT OK ---" << endl;
			}
			else {
				cout << "  --- OK ---" << endl;
			}
		}

	} while (!done);
	
	cout << endl << "----------------------- CONVERGENCE !! ----------------------- " << endl << endl;

	// Prepare result
	map<int, float> result;
	for (auto& c : scorePages) {
		for (auto& p : c.second) {
			result[p.first] = p.second;
		}
	}

	return result;
}

map<int, float> Hypergraphe::inDegree()
{
	map<int, float> scorePages;
	for (auto& c : pointedByCluster) {
		scorePages[c.first] = c.second.size();
	}
	return scorePages;
}
