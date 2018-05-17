#pragma once

#include <iostream>

template <typename T>

class Stack
{
public:
	// constructeurs et destructeurs
	Stack(int max = MAX_STACK); //constructeur
	Stack(const Stack&); //constructeur copie
	~Stack(); //destructeur

	// Modificateurs
	void push(const T&); // pas de position
	T pop();
	
	//Sélecteurs
	bool isEmpty()const;
	int getSize() const;
	const T& getTop() const; // consulte l’élément au sommet 
						 // const: laisse la pile inchangé
	
	//surcharge d'opérateurs
	const Stack<T>& operator = (const Stack<T>);
	/*template <typename U> friend std::ostream& operator <<
		(std::ostream&, const Stack<U>&);*/


private:
	T* tab;
	int top; // indice de l’élément au sommet
	int sizeMax;
	static const int MAX_STACK = 100;
};

template <typename T>
Stack<T>::Stack(int max)
{
	tab = new T[max];
	top = -1; //valeur dummy pour indiquer que la pile est vide.
	sizeMax = max;
	//size = 0;
}

template <class T>
Stack<T> :: ~Stack()
{
	delete[] tab;
}

template <typename T>
T Stack<T> ::pop()
{
	if (!isEmpty()) return tab[top--];
	else
		std::cout << "Depiler: la pile est vide!";
}
template <typename T>
bool Stack<T> ::isEmpty() const
{
	return (top == -1);
}

template <typename T>
void Stack<T>::push(const T& e)
{
	if (top + 1 < sizeMax)
	{
		top += 1; // a += b -> a = a+ b
		tab[top] = e;
	}
	else
		std::cout << "Empiler:la pile est pleine\n";
}

/*template <typename T>
void Stack<T> ::resize()
{
	int nouvelleTaille = top++ x 2;
	tab = new T[nouvelleTaille];
	for (int i = 0; i< top; i++)
		tab[i] = p.tab[i];
	sizeMax = nouvelleTaille;
}*/

/*template <typename T>
const Stack<T>& Stack<T>::operator = (const Stack<T>& p)
{
	if (tab != 0) delete[] tab; //on nettoie l’objet qu’on veux écraser
	tab = new T[p.sizeMax];
	sizeMax = p.sizeMax;
	for (int i = 0; i< sizeMax; i += 1)
		tab[i] = p.tab[i];
	top = p.top;
	return (*this);
	//retourner : une référence sur l ’objet courant
}*/

template <typename T>
Stack<T> ::Stack(const Stack<T>& p)
{
	tab = new X[p.sizeMax];
	sizeMax = p.sizeMax;
	for (int i = 0; i< sizeMax; i += 1)
		tab[i] = p.tab[i];
	top = p.top;
}