/*
 * DataStorageModel.cpp
 *
 *  Created on: 29 mar 2021
 *      Author: Lukasz
 */

#include "DataStorageModel.h"

DataStorageModel::DataStorageModel() {
	// TODO Auto-generated constructor stub

}

DataStorageModel::~DataStorageModel() {
	// TODO Auto-generated destructor stub
}

bool DataStorageModel::screenViewFirstOpen = true;
size_t DataStorageModel::numOfListItems = 0;
const size_t DataStorageModel::maxNumOfPositions = MAX_NUM_OF_POSITIONS;
char DataStorageModel::positionsList[MAX_NUM_OF_POSITIONS][17];
