#pragma once

#include "dictionaryADT.h"
#include "ABag.h"
#include "kvpair.h"
#include <memory>

template <typename Key, typename V>
class BDictionary : public Dictionary<Key, V> {
private:
	ABag<KVpair<Key, V>>* b_bag;
public:
	//Base constructor
	BDictionary<Key, V>(int size) {
		size = defaultSize;
		b_bag = new ABag<KVpair<Key, V>>(size);
	}

	//Base deconstructor
	~BDictionary() {
		delete b_bag;
	}

	// Reinitialize dictionary
	void clear() {
		b_bag->emptyBag();
	}

	// Insert a record
	// k: The key for the record being inserted.
	// v: The record being inserted.
	// Return true if insert is successful and false otherwise
	bool insert(const Key& k, const V& v) {
		std::unique_ptr<KVpair<Key, V>> temp = std::make_unique<KVpair<Key, V>>(k, v);
		if (b_bag->size() != b_bag->bagCapacity())		//Bag capacity is not yet reached
		{
			if (b_bag->addItem(*temp) == true)
			{
				return true;
			}
		}
		return false;
	}

	// Looks for a record using the key and if found does the following:
	// - updates the V& rtnVal
	// - removes the record from the dictionary
	// - returns true
	// If the record is not found the function returns false.
	bool remove(const Key& k, V& rtnVal) {
		std::unique_ptr<KVpair<Key, V>> temp = std::make_unique<KVpair<Key, V>>(k, rtnVal);
		if (b_bag->remove(*temp) == true) {			//Record is found and removed
			rtnVal = temp->value();
			return true;
		}
		return false;		//Record not found
	}

	// Takes an arbitrary record from the dictionary and does the following:
	// - updates the V& returnValue
	// - removes the record from the dictionary
	// - returns true
	// If the dictionary is empty the function returns false.
	bool removeAny(V& returnValue) {
		std::unique_ptr<KVpair<Key, V>> temp = std::make_unique<KVpair<Key, V>>();
		if (b_bag->inspectTop(*temp) == true) {		//Bag is not empty and has top value
			if (b_bag->removeTop(*temp) == true) {		//Successfully removed top value from bag
				returnValue = temp->value();
				return true;
			}
		}
		return false;			//Bag is empty
	}

	// Looks for a record using the key and if found does the following:
	// - updates the V& returnValue
	// - returns true
	// If the record is not found the function returns false.
	bool find(const Key& k, V& returnValue) const {
		std::unique_ptr<KVpair<Key, V>> temp = std::make_unique<KVpair<Key, V>>(k, returnValue);
		if (b_bag->find(*temp) == true) {
			returnValue = temp->value();
			return true;
		}
		return false;
	}

	// Return the number of records in the dictionary.
	int size() {
		return b_bag->size();
	}
};