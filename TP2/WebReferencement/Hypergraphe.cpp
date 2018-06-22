#include "stdafx.h"
#include "Hypergraphe.h"
#include "LUrlParser.h"
#include <windows.h>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <time.h>


using LUrlParser::clParseURL;


Hypergraphe::Hypergraphe(GroupingStrategy groupingStrategy)
{
	strategy = groupingStrategy;
}

Hypergraphe::~Hypergraphe()
{
	for (auto& v : vertices)
		delete v.second;
}

#include <iostream>

string Hypergraphe::createLabelFromLink(string & url)
{
	if (url.size() > 0) {
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

	return string("Invalid URL");
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
		double treatedLines = 0;

		string line;

		// Skip the first 2 lines
		getline(fileNodes, line);

		int lines = stoi(line);

		getline(fileNodes, line);

		long t = time(0);

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
			if (elements.size() >= 3) {
				Vertex* v = new Vertex;
				v->id = stoi(elements.at(0));
				v->outDegree = stoi(elements.at(1));
				v->inDegree = 0;
				v->url = elements.at(2);
				vertices[v->id] = v;
				addPage(v);
			}

			treatedLines++;

			elements.clear();

			if (time(0) > t) {
				cout << "Loading nodes: " << vertices.size() << " (" << (treatedLines / lines) * 100. << "%)" << endl;

				t = time(0);
			}
		}

		fileNodes.close();
	}
	else
	{
		cerr << "Could not open the nodes file !" << endl;
	}

	cout << "Done loading nodes. Amount of nodes: " << vertices.size() << endl;

	// Create hyperEdges
	if (fileEdges)
	{
		double treatedLines = 0;
		string line;

		// Skip the first 2 lines
		getline(fileEdges, line);
		int lines = stoi(line);

		getline(fileEdges, line);

		long t = time(0);
		
		while (getline(fileEdges, line)) {
			// Find the source and destination of the edge
			istringstream iss(line);
			vector<string> elements;
			while (iss) {
				string word;
				iss >> word;
				elements.push_back(word);
			}

			if (elements.size() >= 2) {
				int fromVertexID = stoi(elements.at(0));
				int toVertexID = stoi(elements.at(1));

				if (fromVertexID != toVertexID) {
					Vertex* vertexFrom = vertices[fromVertexID];
					Vertex* vertexTo = vertices[toVertexID];

					if (vertexFrom != nullptr && vertexTo != nullptr) {
						// Get the label of the cluster of the two vertices
						string labelFrom = getVertexLabel(vertexFrom->url);
						string labelTo = getVertexLabel(vertexTo->url);

						if (labelFrom != labelTo) {
							// Check if the pages is not already pointed by the cluster
							if (find(pointedByCluster[toVertexID].begin(), pointedByCluster[toVertexID].end(), labelFrom) == pointedByCluster[toVertexID].end()) {
								pointedByCluster[toVertexID].push_back(labelFrom);
								++clusterOutDegree[labelFrom];
							}
						}
					}
				}

				treatedLines++;

				if (time(0) > t) {
					cout << "Loading eges: " << pointedByCluster.size() << " (" << (treatedLines / lines) * 100. << "%)" << endl;

					t = time(0);
				}
			}


			elements.clear();
		}

		cout << "Done loading edges." << endl;

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
		}

		// Compute score of the cluster
		scoreClusters[name] = 0;
		for (auto& score : scorePages[name]) {
			scoreClusters[name] = scoreClusters[name] + score.second;
		}

	}
	
	// Compute the reputation of the clusters until convergence
	bool done = false;
	map<string, float> delta;
	do 
	{

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
			}

			// Update the score of the cluster
			scoreClusters[name] = 0;
			for (auto& score : scorePages[name]) {
				scoreClusters[name] = scoreClusters[name] + score.second;
			}
		}
		
		// Has it converged ?
		done = true;
		for (auto& val : delta) {
			if ( fabs(val.second-scoreClusters[val.first]) > epsilon) {
				done = false;
			}
			else {
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
