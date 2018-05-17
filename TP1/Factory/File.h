#pragma once

template <typename T>
class File {
public: // constructeurs et destructeurs:
	File();
	/*File(const File &);*/
	~File();
	// modificateurs
	void enfiler(const T&);
	T defiler();
	// sélecteurs
	/*int taille() const;
	bool estVide() const;
	bool estPleine() const;
	const T& premier() const; // tête de la file
	const T& dernier() const; // queue de la file 
	// surcharges d'opérateurs
	const File<T>& operator = (const File<T>&) throw (bad_alloc);
	template <typename U> friend std::ostream& operator << (std::ostream& f, const File<U>& q);*/
private: // modèle d'implantation
	T* tab;
	int tete;
	int queue;
	int tailleMax;
	int cpt;
};

