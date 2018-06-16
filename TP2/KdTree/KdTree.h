#pragma once

#include <iostream>

template<int k, typename E>
class KdTree {
public:
	KdTree();
	~KdTree();

	void insert(E* p);
	bool search(E* p);
	void remove(E* p);

	template <int d, typename U> friend std::ostream& operator << (std::ostream& f, const KdTree<d, U>& q);

private:
	class KdNode {
	public:
		E * point;
		KdNode* leftChild;
		KdNode* rightChild;
		KdNode(E* p) : point(copyPoint(p)), leftChild(0), rightChild(0) {};
		friend std::ostream& operator << (std::ostream& f, const KdNode& q) {
			f << "[";
			for (int i = 0; i < k; i++)
				f << q.point[i] << " ";
			f << "]\n";
			if (q.leftChild == 0)	f << "null\n";
			else					f << *q.leftChild;
			if (q.rightChild == 0)	f << "null\n";
			else					f << *q.rightChild;
			return f;
		};
	};

	KdNode* rootNode;
	void _insertAux(KdNode*& node, int depth, E* p);
	bool _searchAux(KdNode*& node, int depth, E* p);
	bool _removeAux(KdNode*& node, int depth, E* p);
	E* _minimum(KdNode*& node, int depth, int d);

	static bool areEqual(E* p1, E* p2);
	static E* copyPoint(E* p);
};

template<int k, typename E>
inline KdTree<k, E>::KdTree() {
	rootNode = 0;
}

template<int k, typename E>
inline KdTree<k, E>::~KdTree() {
}

template<int k, typename E>
inline void KdTree<k, E>::insert(E* p) {
	_insertAux(rootNode, 0, p);
}

template<int k, typename E>
inline bool KdTree<k, E>::search(E* p) {
	return _searchAux(rootNode, 0, p);
}

template<int k, typename E>
inline void KdTree<k, E>::remove(E* p) {
	if (_removeAux(rootNode, 0, p)) {
		rootNode = 0;
	}
}

template<int k, typename E>
inline void KdTree<k, E>::_insertAux(KdNode*& node, int depth, E* p) {
	if (node == 0)
		node = new KdNode(p);
	else {
		int currentDim = depth % k;
		if (p[currentDim] < node->point[currentDim])
			_insertAux(node->leftChild, depth + 1, p);
		else
			_insertAux(node->rightChild, depth + 1, p);
	}
}

template<int k, typename E>
inline bool KdTree<k, E>::_searchAux(KdNode *& node, int depth, E * p) {
	if (node == 0)
		return false;
	else {
		if (areEqual(node->point, p))
			return true;

		int currentDim = depth % k;
		if (p[currentDim] < node->point[currentDim])
			return _searchAux(node->leftChild, depth + 1, p);
		else
			return _searchAux(node->rightChild, depth + 1, p);
	}
}

template<int k, typename E>
inline bool KdTree<k, E>::_removeAux(KdNode *& node, int depth, E * p) {
	if (node == 0)
		return false;
	else {
		int currentDim = depth % k;

		if (areEqual(node->point, p)) {
			if (node->rightChild != 0) {
				E* minRightChild = _minimum(node->rightChild, depth + 1, currentDim);
				int i;
				for (i = 0; i < k; i++) {
					node->point[i] = minRightChild[i];
				}
				if (_removeAux(node->rightChild, depth + 1, minRightChild)) {
					node->rightChild = 0;
					return false;
				}
			}
			else if (node->leftChild != 0) {
				E* minLeftChild = _minimum(node->leftChild, depth + 1, currentDim);
				int i;
				for (i = 0; i < k; i++) {
					node->point[i] = minLeftChild[i];
				}
				node->rightChild = node->leftChild;
				node->leftChild = 0;
				if (_removeAux(node->rightChild, depth + 1, minLeftChild)) {
					node->rightChild = 0;
					return false;
				}
			}
			else {
				delete node;
				return true;
			}
		}

		if (p[currentDim] < node->point[currentDim]) {
			if (_removeAux(node->leftChild, depth + 1, p))
				node->leftChild = 0;
		}
		else {
			if (_removeAux(node->rightChild, depth + 1, p))
				node->rightChild = 0;
		}

		return false;
	}
}

template<int k, typename E>
inline E * KdTree<k, E>::_minimum(KdNode *& node, int depth, int d) {
	if (node == 0)
		return 0;

	if (depth % k == d) {
		if (node->leftChild == 0)
			return node->point;
		else
			return _minimum(node->leftChild, depth + 1, d);
	}
	else {
		E* minLeft = _minimum(node->leftChild, depth + 1, d);
		E* minRight = _minimum(node->rightChild, depth + 1, d);
		E* current = node->point;

		if (minLeft != 0 && (minRight == 0 || minLeft[d] <= minRight[d]) && minLeft[d] <= current[d])
			return minLeft;
		else if (minRight != 0 && (minLeft == 0 || minRight[d] <= minLeft[d]) && minRight[d] <= current[d])
			return minRight;
		else
			return current;
	}
}

template<int k, typename E>
inline bool KdTree<k, E>::areEqual(E* p1, E* p2) {
	int i;
	for (i = 0; i < k; i++) {
		if (p1[i] != p2[i])
			return false;
	}
	return true;
}

template<int k, typename E>
inline E* KdTree<k, E>::copyPoint(E * p) {
	E* newPoint = new E[k];
	int i;
	for (i = 0; i < k; i++)
		newPoint[i] = p[i];
	return newPoint;
}

template<int d, typename U>
inline std::ostream & operator<<(std::ostream & f, const KdTree<d, U>& q) {
	if (q.rootNode == 0)
		f << "null";
	else
		f << *q.rootNode;
	return f;
}
