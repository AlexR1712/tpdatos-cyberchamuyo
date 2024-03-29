#ifndef HEAP_H_
#define HEAP_H_

#include <vector>

#include "record.h"

template<class T> class Heap {
private:
	std::vector<T> heap;

	std::vector<T>& getHeap();

	unsigned int getSmallestChildIndex(unsigned int parentIndex);

	void swap(T& x, T& y);

public:
	Heap();

	unsigned int size();

	bool empty();

	T& get(unsigned int index);

	void popBack();

	void replaceRoot(const T& record);

	void insert(const T& record);

	~Heap();
};

template<class T> Heap<T>::Heap(){
}

template<class T> std::vector<T>& Heap<T>::getHeap() {
	return this->heap;
}

template<class T> unsigned int Heap<T>::size() {
	return this->getHeap().size();
}

template<class T> bool Heap<T>::empty() {
	return this->getHeap().empty();
}

template<class T> void Heap<T>::replaceRoot(const T& record) {
	unsigned int parentIndex;
	unsigned int childIndex;
	bool swaped;

	this->getHeap()[0] = record;
	parentIndex = 1;
	childIndex = this->getSmallestChildIndex(parentIndex);
	swaped = true;
	while ( (childIndex <= this->getHeap().size()) && (swaped) ) {
		if (this->getHeap()[parentIndex - 1] > this->getHeap()[childIndex - 1]) {
			this->swap(this->getHeap()[parentIndex - 1],this->getHeap()[childIndex - 1]);
			parentIndex = childIndex;
			childIndex = this->getSmallestChildIndex(parentIndex);
		} else {
			swaped = false;
		}
	}
}

template<class T> void Heap<T>::insert(const T& record) {
	unsigned int parentIndex;
	unsigned int childIndex;
	bool swaped;

	this->getHeap().push_back(record);
	childIndex = this->getHeap().size();
	parentIndex = childIndex / 2;
	swaped = true;
	while ( (parentIndex != 0) && (swaped) ) {
		if (this->getHeap()[parentIndex - 1] > this->getHeap()[childIndex - 1]) {
			this->swap(this->getHeap()[parentIndex - 1],this->getHeap()[childIndex - 1]);
			childIndex = parentIndex;
			parentIndex = childIndex / 2;
		} else {
			swaped = false;
		}
	};
}

template<class T> unsigned int Heap<T>::getSmallestChildIndex(unsigned int parentIndex) {
	if (2* parentIndex <= this->getHeap().size()) {
		if (2* parentIndex + 1 > this->getHeap().size())
			return 2 * parentIndex;
		if ( (2* parentIndex + 1 <= this->getHeap().size()) && (this->getHeap()[2 * parentIndex - 1] < this->getHeap()[2 * parentIndex]) )
			return 2 * parentIndex;
		else
			return 2 * parentIndex + 1;
	} else {
		return this->getHeap().size() + 1;
	}
}

template<class T> void Heap<T>::swap(T& x, T& y) {
	T aux;
	aux = x;
	x = y;
	y = aux;
}

template<class T> void Heap<T>::popBack() {
	this->getHeap().pop_back();
}

template<class T> T& Heap<T>::get(unsigned int index) {
	return this->getHeap()[index];
}

template<class T> Heap<T>::~Heap(){
}


#endif /* HEAP_H_ */
