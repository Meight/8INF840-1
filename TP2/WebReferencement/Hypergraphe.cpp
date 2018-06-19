#include "stdafx.h"
#include "Hypergraphe.h"
#include "LUrlParser.h"
#include <windows.h>

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



void Hypergraphe::addPage(string & url)
{
	// Determine the label of the new vertex's target set.
	string label = getVertexLabel(url);

	vertexSets[label].push_back(url);

	cout << "Added page " << url << " to label " << label << endl;
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
		cout << "[" << it->first << "]" << endl;

		SetConsoleTextAttribute(hConsole, 15);
		for (auto& vertex : it->second)
			cout << "--- " << vertex << endl;

		cout << endl;
	}
}
