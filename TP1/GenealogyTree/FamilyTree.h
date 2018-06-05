/*
 * @author Matthieu Le Boucher <matt.leboucher@gmail.com>
 */

#include "NTree.h"
#include "Person.h"
#include "NPersonTree.h"

class FamilyTree {
private:
    NPersonTree *tree;

public:
    FamilyTree(Person &person);
	~FamilyTree();

    int getSize();
	void print(TraversalMethod method);
    void addMember(const Person & parent, const Person &person);
	void addMember(const Person & person);
    void listDescendants(Person person, TraversalMethod method);
    void listByEyesColor(Color color, TraversalMethod method);
	void listAncestorsWithSameEyeColor(Person person);
    float getMeanAge();
};