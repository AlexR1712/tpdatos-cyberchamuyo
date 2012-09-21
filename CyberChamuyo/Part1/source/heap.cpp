#include "heap.h"

#include <vector>

#include <iostream>

#include <queue>

Heap::Heap(){
}

std::vector<Record>& Heap::getHeap() {
	return this->heap;
}

void Heap::replaceRoot(const Record& record) {
	unsigned int parentIndex;
	unsigned int childIndex;
	bool swaped;

std::queue<Record> buffer;

	this->getHeap()[0] = record;
	parentIndex = 1;
	childIndex = this->getSmallestChildIndex(parentIndex);
	swaped = true;
	while ( (childIndex <= this->getHeap().size()) && (swaped) ) {
		if (this->getHeap()[parentIndex - 1] > this->getHeap()[childIndex - 1]) {
			this->swapRecord(this->getHeap()[parentIndex - 1],this->getHeap()[childIndex - 1]);
			this->getHeap()[parentIndex - 1];
			this->getHeap()[childIndex - 1];
			parentIndex = childIndex;
			childIndex = this->getSmallestChildIndex(parentIndex);
		} else {
			swaped = false;
		}
	}



	std::cout << "Heap: " << std::endl;
	for (unsigned int i = 0; i < this->getHeap().size(); i++) {
		std::cout << this->getHeap()[i];
	}
	std::cout << std::endl;



}

void Heap::insert(const Record& record) {
	unsigned int parentIndex;
	unsigned int childIndex;
	bool swaped;

	this->getHeap().push_back(record);
	childIndex = this->getHeap().size();
	parentIndex = childIndex / 2;
	swaped = true;
	while ( (parentIndex != 0) && (swaped) ) {
		if (this->getHeap()[parentIndex - 1] > this->getHeap()[childIndex - 1]) {
			this->swapRecord(this->getHeap()[parentIndex - 1],this->getHeap()[childIndex - 1]);
			childIndex = parentIndex;
			parentIndex = childIndex / 2;
		} else {
			swaped = false;
		}
	};

		std::cout << "Heap: " << std::endl;
	for (unsigned int i = 0; i < this->getHeap().size(); i++) {
		std::cout << this->getHeap()[i];
	}
	std::cout << std::endl;
}

unsigned int Heap::getSmallestChildIndex(unsigned int parentIndex) {
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

void Heap::swapRecord(Record& x, Record& y) {
	Record aux;
	aux = x;
	x = y;
	y = aux;
}

Heap::~Heap(){
}
