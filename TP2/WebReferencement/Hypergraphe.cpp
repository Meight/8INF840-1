#include "stdafx.h"
#include "Hypergraphe.h"


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
	switch (strategy) {
	case BY_PAGE:
		return url;
		break;
	case BY_DOMAIN:
		return string();
		break;
	case BY_HOST:
		return string();
		break;
	default:
		return string();
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
