#include <string>
#include <vector>
using namespace std;

struct Node {
	Node* parent;
	char value;
	Node* leftChild;
	Node* rightChild;
	bool endWord;
};

class Dictionnary {

private:
	Node* dictionnary;

	/**
	* Explore the tree recursively
	**/
	bool modifiedDepthFirstSearch(Node* node, string word, vector<string> wordsFound, bool searchWord, string wordToFind);

	/**
	* Recursion used to add a word in the dictionnary
	**/
	void addWordRec(string subWord, Node* subNode, bool arrange);


public:
	Dictionnary();

	/**
	* Add a word to the dictionnary
	**/
	void addWord(string word);

	/**
	* Delete a word to the dictionnary
	**/
	void deleteWord(string word);

	/**
	* Search a word to the dictionnary.
	* Return true if the word is present; else False.
	**/
	bool searchWord(string word);

	/**
	* Display all the words of the dictionnary in the lexicographical order
	**/
	void displayWords();

};