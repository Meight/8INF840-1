#pragma once

#include <iostream>

template <typename T>
class File {
public: // constructeurs et destructeurs:
	File(int m = MAX_FILE);
	File(const File &);
	~File();
	// modificateurs
	void enfiler(const T&);
	T defiler();
	// sélecteurs
	int taille() const;
	bool estVide() const;
	bool estPleine() const;
	const T& premier() const; // tête de la file
	const T& dernier() const; // queue de la file 
	// surcharges d'opérateurs
	const File<T>& operator = (const File<T>&)/* throw (bad_alloc)*/;
	template <typename U> friend std::ostream& operator << (std::ostream& f, const File<U>& q);

private: // modèle d'implantation
	T* tab;
	int tete;
	int queue;
	int tailleMax;
	int cpt;
	static const int MAX_FILE = 20;
	void _copier(T*);
};

template<typename T>
inline File<T>::File(int m) {
	tailleMax = m;
	tab = new T[tailleMax];
	tete = 0;
	queue = 0;
	cpt = 0;
}

template<typename T>
inline File<T>::File(const File & f) {
	tailleMax = f.tailleMax;
	_copier(f.tab);
	tete = f.tete;
	queue = f.queue;
	cpt = f.cpt;
}

template<typename T>
inline File<T>::~File() {
	delete[] tab;
}

template<typename T>
inline void File<T>::enfiler(const T & e) {
	if (cpt < tailleMax) {
		tab[queue] = e;
		queue = (queue + 1) % tailleMax;
		cpt++;
	}
	else {
		T* newTab = new T[2*tailleMax];
		int currIndex = 0;
		while (cpt > 0)
			newTab[currIndex++] = defiler();
		newTab[currIndex++] = e; // on enfile le nouvel élément
		tailleMax *= 2;
		tete = 0;
		queue = currIndex;
		cpt = currIndex;
		delete[] tab;
		tab = newTab;
	}
}

template<typename T>
inline T File<T>::defiler() {
	if (cpt > 0) {
		T elementaDefiler = tab[tete];
		tete = (tete + 1) % tailleMax;
		cpt--;
		return elementaDefiler;
	}
	else
		std::cout << "Defiler: la file est vide!";
}

template<typename T>
inline int File<T>::taille() const {
	return cpt;
}

template<typename T>
inline bool File<T>::estVide() const {
	return (cpt == 0);
}

template<typename T>
inline bool File<T>::estPleine() const {
	return (cpt == tailleMax);
}

template<typename T>
inline const T & File<T>::premier() const {
	if (cpt > 0)
		return tab[tete];
	else
		std::cout << "Premier: la file est vide!";
}

template<typename T>
inline const T & File<T>::dernier() const {
	if (cpt > 0)
		return tab[(tete + cpt - 1) % tailleMax];
	else
		std::cout << "Dernier: la file est vide!";
}

template<typename T>
inline const File<T>& File<T>::operator=(const File<T>& f) {
	if (tab != 0) // nettoyer
		delete[] tab;
	tailleMax = f.tailleMax;
	_copier(f.tab);
	tete = f.tete;
	queue = f.queue;
	cpt = f.cpt;
	return (*this);
}

template<typename U>
inline std::ostream & operator<<(std::ostream & f, const File<U>& q) {
	int i;
	f << "[";
	for (i = 0; i < q.cpt; i++) {
		f << q.tab[(q.tete + i) % q.tailleMax] << "->";
	}
	f << "]";
	return f;
}

template<typename T>
inline void File<T>::_copier(T * tabS) {
	int i;
	tab = new T[tailleMax];
	for (i = 0; i < tailleMax; i++)
		tab[i] = tabS[i];
}
