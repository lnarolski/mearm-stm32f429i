/*
 * DataStorageModel.h
 *
 *  Created on: 29 mar 2021
 *      Author: Lukasz
 */

#ifndef DATASTORAGEMODEL_H_
#define DATASTORAGEMODEL_H_

#define MAX_NUM_OF_POSITIONS 10

#include <cstddef>
#include <stdint.h>

class DataStorageModel
{
public:
	DataStorageModel();
	virtual ~DataStorageModel();

	static bool screenViewFirstOpen;
	static size_t numOfListItems;
	static const size_t maxNumOfPositions;
	static char positionsList[MAX_NUM_OF_POSITIONS][17];
};

#endif /* DATASTORAGEMODEL_H_ */
