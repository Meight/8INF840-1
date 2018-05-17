#include "stdafx.h"
#include "File.h"

template <typename T>
File<T>::File() {
	tailleMax = 20;
	tab = new T[tailleMax];
	tete = 0;
	queue = 0;
	cpt = 0;
}

template <class X>
File<X>::~File() {
	delete[] tab;
}

template <typename T>
T File<T>::defiler() {
	if (cpt > 0) {
		T elementaDefiler = tab[tete];
		tete = (tete + 1) % tailleMax;
		cpt--;
		return elementaDefiler;
	}
}

template <typename T>
void File<T>::enfiler(const T& e) {
	if (cpt < tailleMax) {
		tab[queue] = e;
		queue = (queue + 1) % tailleMax;
		cpt++;
	}
}

