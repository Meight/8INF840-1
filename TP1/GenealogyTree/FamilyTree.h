/*
 * @author Matthieu Le Boucher <matt.leboucher@gmail.com>
 */

#ifndef TP1_FAMILYTREE_H
#define TP1_FAMILYTREE_H


#include "NTree.h"
#include "Person.h"

class FamilyTree {
private:
    NTree<Person> *tree;

public:
    FamilyTree();
    int getSize();
    void addMember(const Person &person);
    void listDescendants(Person person, TraversalMethod method);
    void listByEyesColor(Color color);
    float getMeanAge();
};


#endif //TP1_FAMILYTREE_H
