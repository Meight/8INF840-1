// Dictionnary.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Dictionnary.h"
#include <iostream>
#include <vector>

using namespace std;

inline const char * const BoolToString(bool b)
{
	return b ? "TRUE" : "FALSE";
}

Dictionnary::Dictionnary() {
	dictionnary = new Node;
	dictionnary->parent = NULL;
	dictionnary->value = NULL;
	dictionnary->leftChild = NULL;
	dictionnary->rightChild = NULL;
	dictionnary->endWord = false;
}

void Dictionnary::addWord(string word) {
	addWordRec(word, dictionnary, false);
	std::cout << "Word added: " + word << endl;
}


void Dictionnary::addWordRec(string subWord, Node* subNode, bool arrange) {

	// Get the first letter of the subword
	char letter = subWord[0];

	if (!arrange) {
		if (subNode->leftChild == NULL) {
			Node* node = new Node;
			node->parent = subNode;
			node->value = letter;
			node->leftChild = NULL;
			node->rightChild = NULL;
			node->endWord = subWord.length() == 1;
			subNode->leftChild = node;
			if (node->endWord) {
				return;
			}
			else {
				addWordRec(subWord.substr(1, subWord.length() - 1), node, false);
			}
		}
		else {
			if (subNode->leftChild->value == letter) {
				// It's the same later
				if (subWord.length() - 1 == 0) {
					// Word completely added
					subNode->leftChild->endWord = true;
					return;
				}
				else {
					// We continue to add the rest of the word
					addWordRec(subWord.substr(1, subWord.length() - 1), subNode->leftChild, false);
				}
			}
			else {
				// New child must be created
				if (subNode->leftChild->rightChild == NULL) {
					// Respect the lexicographical order ?
					if (letter > subNode->leftChild->value) {
						//std::cout << "test: no" << endl;
						// No need to re-arrange
						Node* node = new Node;
						node->parent = subNode->leftChild;
						node->value = letter;
						node->leftChild = NULL;
						node->rightChild = NULL;
						node->endWord = subWord.length() == 1;
						subNode->leftChild->rightChild = node;
						if (node->endWord) {
							return;
						}
						else {
							addWordRec(subWord.substr(1, subWord.length() - 1), node, false);
						}
					}
					else {
						// Need to re-arrange the tree
						Node* node = new Node;
						node->parent = subNode;
						node->value = letter;
						node->leftChild = NULL;
						node->rightChild = subNode->leftChild;
						subNode->leftChild = node;
						node->endWord = subWord.length() == 1;

						if (node->endWord) {
							return;
						}
						else {
							addWordRec(subWord.substr(1, subWord.length() - 1), node, false);
						}
					}
				}
				else {
					if (letter < subNode->leftChild->value) {
						// The subNode needs to be shifted to the right
						Node* node = new Node;
						node->parent = subNode;
						node->value = letter;
						node->leftChild = NULL;
						node->rightChild = subNode->leftChild;
						subNode->leftChild = node;
						node->endWord = subWord.length() == 1;

						if (node->endWord) {
							return;
						}
						else {
							addWordRec(subWord.substr(1, subWord.length() - 1), node, false);
						}
					}
					else {
						// The new node needs to be added on the right
						addWordRec(subWord, subNode->leftChild, true);
					}
				}
			}
		}
	}
	else {
		if (subNode->rightChild != NULL) {
			if (letter == subNode->rightChild->value) {
				addWordRec(subWord.substr(1, subWord.length() - 1), subNode->rightChild, false);
			}
			else if (letter < subNode->rightChild->value) {
				// The subNode needs to be shifted to the right
				Node* node = new Node;
				node->parent = subNode;
				node->rightChild = subNode->rightChild;
				node->rightChild->parent = node;
				subNode->rightChild = node;
				node->value = letter;
				node->leftChild = NULL;
				node->endWord = subWord.length() == 1;
				if (node->endWord) {
					return;
				}
				else {
					addWordRec(subWord.substr(1, subWord.length() - 1), node, false);
				}
			}
			else {
				// The new node needs to be added on the right
				addWordRec(subWord, subNode->rightChild, true);
			}
		}
		else {
			// Just add on the right
			Node* node = new Node;
			node->parent = subNode;
			node->leftChild = NULL;
			node->rightChild = NULL;
			node->value = letter;
			node->endWord = subWord.length() == 1;
			subNode->rightChild = node;
			if (node->endWord) {
				return;
			}
			else {
				addWordRec(subWord.substr(1, subWord.length() - 1), node, false);
			}
		}
	}
}


void Dictionnary::deleteWord(string word) {

	// Go to the node of the last letter
	Node* currentNode = dictionnary;
	for (int i = 0; i < word.length(); i++) {
		currentNode = currentNode->leftChild;
		while (currentNode->value != word[i]) {
			currentNode = currentNode->rightChild;
		}
	}

	// Case 1 : we can create other words with that word (last letter node has a left child
	if (currentNode->leftChild != NULL) {
		currentNode->endWord = false;
	}
	else {
		bool done = false;
		int iter = 0;
		while (!done && iter < word.length() - 2) {
			// Case 2 : no alternative letter, we just delete the node and keep going
			if (currentNode->rightChild == NULL) {
				currentNode = currentNode->parent;
				currentNode->leftChild = NULL;
				done = currentNode->endWord;
			}
			// Case 3 : alternative letter(s), we re-arrange the tree and we're done
			else {
				currentNode->parent->leftChild = currentNode->rightChild;
				done = true;
			}
			iter++;
		}
	}
	std::cout << "Word deleted: " << word << endl;
}


void Dictionnary::displayWords() {
	vector<string> wordsFound;
	std::cout << endl << "------------- WORDS -------------" << endl;
	modifiedDepthFirstSearch(dictionnary->leftChild, "", wordsFound, false, "");
	std::cout << "---------------------------------" << endl << endl;
}


bool Dictionnary::modifiedDepthFirstSearch(Node* node, string word, vector<string> wordsFound, bool searchWord, string wordToFind) {
	bool wordFound = false;
	if (node != NULL) {
		// Word found
		if (node->endWord) {
			wordsFound.push_back(word + node->value);
			if (searchWord && wordsFound.at(wordsFound.size() - 1) == wordToFind) {
				return true;
			}
			else if (!searchWord) {
				std::cout << " - " + wordsFound.at(wordsFound.size() - 1) << endl;
			}
		}
		// Explore left
		if (node->leftChild != NULL) {
			wordFound = modifiedDepthFirstSearch(node->leftChild, word + node->value, wordsFound, searchWord, wordToFind);
		}
		// Explore right
		if (node->rightChild != NULL && !wordFound) {
			wordFound = modifiedDepthFirstSearch(node->rightChild, word, wordsFound, searchWord, wordToFind);
		}
	}
	return wordFound;
}


bool Dictionnary::searchWord(string word) {
	vector<string> wordsFound;
	return modifiedDepthFirstSearch(dictionnary->leftChild, "", wordsFound, true, word);
}


int main(void) {

	Dictionnary d;

	d.addWord("lit");
	d.addWord("abas");
	d.addWord("arbuste");
	d.addWord("lasse");
	d.addWord("arbre");
	d.addWord("bas");
	d.addWord("las");

	d.displayWords();

	string wordToFind = "lit";
	std::cout << "Word \"" << wordToFind << "\" is in the dictionnary: " << BoolToString(d.searchWord(wordToFind)) << endl;
	wordToFind = "lot";
	std::cout << "Word \"" << wordToFind << "\" is in the dictionnary: " << BoolToString(d.searchWord(wordToFind)) << endl;

	d.deleteWord("lit");

	d.displayWords();

	system("PAUSE");
	return 0;
}