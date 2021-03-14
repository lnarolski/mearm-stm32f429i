/*
 * Vector.cpp
 *
 *  Created on: 13 mar 2021
 *      Author: Lukasz
 */

#include "Vector.hpp"

template <class T>
mearm::Vector<T>::Vector() {
	// TODO Auto-generated constructor stub

}

template <class T>
mearm::Vector<T>::~Vector() {
	// TODO Auto-generated destructor stub
}

template <class T>
bool mearm::Vector<T>::push_back(T item) {
	if (firstItem == NULL)
	{
		firstItem = malloc(sizeof(VectorItem));

		if (firstItem == NULL)
			return false;

		lastItem = firstItem;
	}
	else
	{
		lastItem->nextItem = malloc(sizeof(VectorItem));

		if (firstItem == NULL)
			return false;

		lastItem->nextItem->previousItem = lastItem;
		lastItem = lastItem->nextItem;
	}

	lastItem->item = item;
	sizeValue++;

	return true;
}

template <class T>
size_t mearm::Vector<T>::size() {
	return sizeValue;
}

