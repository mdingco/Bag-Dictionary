#pragma once
#include <memory>			
#include "bagADT.h"

template <typename E>
class ABag : protected Bag<E> {
private:
	E* bag;
	int maxSize;
	int top;

public:
	// Base constructor
	ABag(const int size = 10) {
		maxSize = size;
		bag = new E[maxSize];
		top = 0;
	}

	//Base deconstructor
	~ABag() {
		delete[] bag;
	}

	// Insert a new item into the bag -- return false if fails and true if
	// successful		USED
	bool addItem(const E& item) {
		if (top == bagCapacity()) {		//Bag's capacity is exceeded
			return false;
		}
		else {
			bag[top++] = item;
			return true;
		}
	}

	// Looks for 'item' in the bag and if found updates 'item' with the 
	// bag value and returns true.  Otherwise 'item' is left unchanged
	// and the method returns false.
	bool remove(E& item) {		//USED
		for (int i = top; i > 0; i--) {
			if (bag[i] == item) {			//Item is found
				item = bag[i];
				for (int j = i++; j < top; j++) {
					bag[i] = bag[j];
				}
				top--;
				return true;
			}
		}
		return false;
	}

	// Removes the top record from the bag, puts it in returnValue, and
	// returns true if the bag is not empty.  If the bag is empty the 
	// function returns false and returnValue remains unchanged.		USED
	bool removeTop(E& returnValue) {
		if (top == 0) {			//Bag is empty
			return false;
		}
		else {
			returnValue = bag[--top];
			return true;
		}
	}

	// Finds the record using returnValue and if the record is found updates
	// returnValue based on the contents of the bag and returns true.  If the
	// record is not found the function returns false.  Works just like remove()
	// except that the found record is not removed from the bag.		USED
	bool find(E& returnValue) const {
		for (int i = top; i > 0; i--) {
			if (bag[i] == returnValue) {			//Found item in bag
				returnValue = bag[i];
				return true;
			}
		}
		return false;
	}

	// Inspect the top of the bag.  If the bag is empty return
	// false and leave 'item' unchanged; otherwise, return true and update 
	// 'item' with the contents of the bag.			USED
	bool inspectTop(E& item) const {
		if (top == 0) {		//Bag is empty
			return false;
		}
		else {
			item = bag[size() - 1];
			return true;
		}
	}

	// empties the bag USED
	void emptyBag() {
		top = 0;
	}

	// use the += operator to add an item to the bag USED
	bool operator+=(const E& addend) {
		return addItem(addend);
	}

	// get the number of items in the bag		USED
	int size() const {
		return top;
	}

	// get the capacity of the bag (size of your bag's array)
	int bagCapacity() const {
		return maxSize;
	}
};