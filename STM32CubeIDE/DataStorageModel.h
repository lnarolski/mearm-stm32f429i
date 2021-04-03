/*
 * DataStorageModel.h
 *
 *  Created on: 29 mar 2021
 *      Author: Lukasz
 */

#ifndef DATASTORAGEMODEL_H_
#define DATASTORAGEMODEL_H_

#define MAX_NUM_OF_POSITIONS 50

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

	static uint32_t xAxisSliderValue;
	static uint32_t yAxisSliderValue_L;
	static uint32_t yAxisSliderValue_R;
	static bool manipulatorState;
};

#endif /* DATASTORAGEMODEL_H_ */
