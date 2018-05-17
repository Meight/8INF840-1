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
	// s�lecteurs
	/*int taille() const;
	bool estVide() const;
	bool estPleine() const;
	const T& premier() const; // t�te de la file
	const T& dernier() const; // queue de la file 
	// surcharges d'op�rateurs
	const File<T>& operator = (const File<T>&) throw (bad_alloc);
	template <typename U> friend std::ostream& operator << (std::ostream& f, const File<U>& q);*/
private: // mod�le d'implantation
	T* tab;
	int tete;
	int queue;
	int tailleMax;
	int cpt;
};

