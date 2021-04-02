/*
 * SequencePlaybackControl.cpp
 *
 *  Created on: 1 kwi 2021
 *      Author: Lukasz
 */

#include "SequencePlaybackControl.h"

SequencePlaybackControl::SequencePlaybackControl() {
	// TODO Auto-generated constructor stub

}

SequencePlaybackControl::~SequencePlaybackControl() {
	// TODO Auto-generated destructor stub
}

bool SequencePlaybackControl::sequenceRunning = false;
uint32_t SequencePlaybackControl::sequenceSpeed = 1;
bool SequencePlaybackControl::stopSequence = false;
bool SequencePlaybackControl::pauseSequence = false;
sequenceScreenView* SequencePlaybackControl::sequenceScreenViewClass = NULL;

size_t SequencePlaybackControl::currentPositionNumber = 0;
TaskHandle_t* SequencePlaybackControl::playbackThread = NULL;

void SequencePlaybackControl::Play() {
	xTaskCreate(PlaybackThreadFunction, /* Function that implements the task. */
	"PlaybackThreadFunction", /* Text name for the task. */
	256, /* Stack size in words, not bytes. */
	NULL, /* Parameter passed into the task. */
	tskIDLE_PRIORITY,/* Priority at which the task is created. */
	playbackThread); /* Used to pass out the created task's handle. */
}

void SequencePlaybackControl::Stop() {

	stopSequence = true;
}

void SequencePlaybackControl::Pause() {

}

void SequencePlaybackControl::Resume() {

}

void SequencePlaybackControl::GoToPosition(size_t positionNumber) {

}

void SequencePlaybackControl::PlaybackThreadFunction(void* pvParameters) {
	sequenceRunning = true;
	while (!stopSequence)
	{
		for (size_t i = 0; i < DataStorageModel::numOfListItems && !stopSequence; ++i)
		{
			currentPositionNumber = i;

			if (sequenceScreenViewClass != NULL)
			{
				sequenceScreenViewClass->positionContainersList[i].setVisible(false);
				sequenceScreenViewClass->invalidateScrollableContainer = true;
				vTaskDelay(1000);
				sequenceScreenViewClass->positionContainersList[i].setVisible(true);
				sequenceScreenViewClass->invalidateScrollableContainer = true;
			}
		}
	}

	sequenceRunning = false;
	stopSequence = false;
	vTaskDelete(NULL);
}

RobotPosition SequencePlaybackControl::Char2RobotPosition(char *position) {
	RobotPosition robotPosition;

	char buffer[17];
	size_t j = 0, PWMDutyType = 0;
	for(size_t i = 0; i < 17 && *position != '\0'; ++i)
	{
		if (isdigit(*position[i]))
		{
			buffer[j] = *position[i];
			++j;
		}
		else
		{
			buffer[]
			switch (PWMDutyType) {
				case value:

					break;
				default:
					break;
			}
			j = 0;
		}
	}

	return robotPosition;
}
