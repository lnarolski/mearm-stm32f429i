/*
 * SequencePlaybackControl.h
 *
 *  Created on: 1 kwi 2021
 *      Author: Lukasz Narolski
 */

#ifndef SEQUENCEPLAYBACKCONTROL_H_
#define SEQUENCEPLAYBACKCONTROL_H_

#define POSITION_TEXT_BUFFER_SIZE 25

#include <cstddef>
#include <stdint.h>
#include "cmsis_os.h"
#include <../STM32CubeIDE/DataStorageModel.h>
#include <gui/sequencescreen_screen/sequenceScreenView.hpp>
#include <cctype>
#include <cstdlib>
#include <touchgfx/Color.hpp>

extern uint32_t xAxisPWMDuty;
extern uint32_t yAxisPWMDuty_L;
extern uint32_t yAxisPWMDuty_R;
extern uint32_t manipulatorPWMDuty;

struct ArmPosition
{
	uint32_t xAxisPWMDuty;
	uint32_t yAxisPWMDuty_L;
	uint32_t yAxisPWMDuty_R;
	uint32_t manipulatorPWMDuty;
};

class SequencePlaybackControl
{
public:
	enum Direction
	{
		UP = 1,
		DOWN = -1
	};

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
	static uint32_t maxSequenceSpeed;
	static uint32_t minSequenceSpeed;

	static ArmPosition Char2ArmPosition(char* position);
	static ArmPosition Char2ArmPosition(Unicode::UnicodeChar* position);

private:
	static size_t currentPositionNumber;

	static void PlaybackThreadFunction(void* pvParameters);
	static TaskHandle_t* playbackThread;
};

#endif /* SEQUENCEPLAYBACKCONTROL_H_ */
