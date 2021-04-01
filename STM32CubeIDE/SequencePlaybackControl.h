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

class SequencePlaybackControl {
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

private:
	static size_t currentPositionNumber;

};

#endif /* SEQUENCEPLAYBACKCONTROL_H_ */
