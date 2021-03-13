/*
 * Vector.hpp
 *
 *  Created on: 13 mar 2021
 *      Author: Lukasz
 */

#ifndef APPLICATION_USER_GUI_VECTOR_HPP_
#define APPLICATION_USER_GUI_VECTOR_HPP_

#include <stddef.h>

template <class T>
class Vector {
public:
	Vector();
	virtual ~Vector();
	size_t push_back(T*);
	T* firstItem = NULL;
	T* lastItem = NULL;

	size_t size();

private:
	struct VectorItem
	{
		T* nextItem = NULL;
		T* previousItem = NULL;
	};

	size_t sizeValue = 0;
};

#endif /* APPLICATION_USER_GUI_VECTOR_HPP_ */
