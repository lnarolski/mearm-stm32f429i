/*
 * SequencePlaybackControl.h
 *
 *  Created on: 1 kwi 2021
 *      Author: Lukasz
 */

#ifndef SEQUENCEPLAYBACKCONTROL_H_
#define SEQUENCEPLAYBACKCONTROL_H_

#include <cstddef>
#include <stdint.h>
#include "cmsis_os.h"
#include <../STM32CubeIDE/DataStorageModel.h>
#include <gui/sequencescreen_screen/sequenceScreenView.hpp>
#include <cctype>
#include <cstdlib>

extern uint32_t xAxisPWMDuty;
extern uint32_t yAxisPWMDuty_L;
extern uint32_t yAxisPWMDuty_R;
extern uint32_t manipulatorPWMDuty;

struct RobotPosition
{
	uint32_t xAxisPWMDuty;
	uint32_t yAxisPWMDuty_L;
	uint32_t yAxisPWMDuty_R;
	uint32_t manipulatorPWMDuty;
};

class SequencePlaybackControl
{
public:
	SequencePlaybackControl();
	virtual ~SequencePlaybackControl();

	static void Play();
	static void Stop();
	static void Pause();
	static void Resume();
	static void GoToPosition(size_t positionNumber);

	static bool sequenceRunning;
	static uint32_t sequenceSpeed;

	static sequenceScreenView* sequenceScreenViewClass;
	static bool stopSequence;
	static bool pauseSequence;

private:
	static size_t currentPositionNumber;

	static void PlaybackThreadFunction(void* pvParameters);
	static TaskHandle_t* playbackThread;
	RobotPosition Char2RobotPosition(char* position);
};

#endif /* SEQUENCEPLAYBACKCONTROL_H_ */
