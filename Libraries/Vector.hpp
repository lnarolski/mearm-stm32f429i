/*
 * Vector.hpp
 *
 * Simple vector implementation for STM32
 *
 *  Created on: 13 mar 2021
 *      Author: Lukasz
 */

#ifndef APPLICATION_USER_VECTOR_HPP_
#define APPLICATION_USER_VECTOR_HPP_

#include <stddef.h>
#include <memory>

namespace mearm {
template<class T>
class vector {
private:
	struct VectorItem {
		VectorItem *nextItem = NULL;
		VectorItem *previousItem = NULL;

		T item;
	};
public:
	vector();
	~vector();
	bool push_back(T);
	VectorItem *firstItem = NULL;
	VectorItem *lastItem = NULL;

	size_t size();

	size_t sizeValue = 0;
};

template<class T>
mearm::vector<T>::vector() {
	// TODO Auto-generated constructor stub

}

template<class T>
mearm::vector<T>::~vector() {
	// TODO Auto-generated destructor stub
}

template<class T>
bool mearm::vector<T>::push_back(T item) {
	if (firstItem == NULL) {
		firstItem = (VectorItem*)malloc(sizeof(VectorItem));

		if (firstItem == NULL)
			return false;

		lastItem = firstItem;
	} else {
		lastItem->nextItem = (VectorItem*)malloc(sizeof(VectorItem));

		if (firstItem == NULL)
			return false;

		lastItem->nextItem->previousItem = lastItem;
		lastItem = lastItem->nextItem;
	}

	lastItem->item = item;
	sizeValue++;

	return true;
}

template<class T>
size_t mearm::vector<T>::size() {
	return sizeValue;
}

}

#endif /* APPLICATION_USER_VECTOR_HPP_ */
