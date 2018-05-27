/*
 * @author Matthieu Le Boucher <matt.leboucher@gmail.com>
 */

#include "NTree.h"
#include "Person.h"

class FamilyTree {
private:
    NTree<Person> *tree;

public:
    FamilyTree(const Person &person);
	~FamilyTree();

    int getSize();
	void print(TraversalMethod method);
    void addMember(const Person & parent, const Person &person);
	void addMember(const Person & person);
    void listDescendants(Person person, TraversalMethod method);
    void listByEyesColor(Color color);
    float getMeanAge();
};