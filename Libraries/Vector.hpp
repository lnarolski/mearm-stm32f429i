/*
 * Vector.hpp
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
class Vector {
private:
	struct VectorItem {
		VectorItem *nextItem = NULL;
		VectorItem *previousItem = NULL;

		T item;
	};
public:
	Vector();
	virtual ~Vector();
	bool push_back(T);
	VectorItem *firstItem = NULL;
	VectorItem *lastItem = NULL;

	size_t size();

	size_t sizeValue = 0;
};
}

#endif /* APPLICATION_USER_VECTOR_HPP_ */
