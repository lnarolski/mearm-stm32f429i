/*
 * SequencePlaybackControl.cpp
 *
 *  Created on: 1 kwi 2021
 *      Author: Lukasz Narolski
 */

#include "SequencePlaybackControl.h"

SequencePlaybackControl::SequencePlaybackControl()
{
	// TODO Auto-generated constructor stub

}

SequencePlaybackControl::~SequencePlaybackControl()
{
	// TODO Auto-generated destructor stub
}

bool SequencePlaybackControl::sequenceRunning = false;
uint32_t SequencePlaybackControl::sequenceSpeed = 1;
uint32_t SequencePlaybackControl::minSequenceSpeed = 1;
uint32_t SequencePlaybackControl::maxSequenceSpeed = 128;
bool SequencePlaybackControl::stopSequence = false;
bool SequencePlaybackControl::pauseSequence = false;
sequenceScreenView* SequencePlaybackControl::sequenceScreenViewClass = NULL;

size_t SequencePlaybackControl::currentPositionNumber = 0;
TaskHandle_t* SequencePlaybackControl::playbackThread = NULL;

void SequencePlaybackControl::Play()
{
	xTaskCreate(PlaybackThreadFunction, /* Function that implements the task. */
	"PlaybackThreadFunction", /* Text name for the task. */
	256, /* Stack size in words, not bytes. */
	NULL, /* Parameter passed into the task. */
	tskIDLE_PRIORITY,/* Priority at which the task is created. */
	playbackThread); /* Used to pass out the created task's handle. */
}

void SequencePlaybackControl::Stop()
{
	stopSequence = true;
}

void SequencePlaybackControl::Pause()
{
	SequencePlaybackControl::pauseSequence = true;
}

void SequencePlaybackControl::Resume()
{
	SequencePlaybackControl::pauseSequence = false;
}

void SequencePlaybackControl::GoToPosition(size_t positionNumber)
{
	// TODO
}

void SequencePlaybackControl::PlaybackThreadFunction(void* pvParameters)
{
	sequenceScreenViewClass->ShowSequenceSpeed();
	stopSequence = false;
	sequenceRunning = true;
	while (!stopSequence)
	{
		for (size_t i = 0; i < DataStorageModel::numOfListItems && !stopSequence; ++i)
		{
			colortype previousColor;
			if (sequenceScreenViewClass != NULL)
			{
				previousColor = ((touchgfx::TextAreaWithOneWildcard*)sequenceScreenViewClass->positionContainersList[i].getFirstChild())->getColor();
				((touchgfx::TextAreaWithOneWildcard*)sequenceScreenViewClass->positionContainersList[i].getFirstChild())->setColor(touchgfx::Color::getColorFrom24BitRGB(9, 137, 182));
				sequenceScreenViewClass->invalidateScrollableContainer = true;
			}

			currentPositionNumber = i;
			ArmPosition desiredArmPosition = Char2ArmPosition(DataStorageModel::positionsList[i]);
			uint32_t desiredArmPositionArray[3] =
			{ desiredArmPosition.xAxisPWMDuty, desiredArmPosition.yAxisPWMDuty_L, desiredArmPosition.yAxisPWMDuty_R };
			SequencePlaybackControl::Direction directionArray[3];

			if (desiredArmPositionArray[0] > xAxisPWMDuty)
			{
				directionArray[0] = UP;
			}
			else
			{
				directionArray[0] = DOWN;
			}
			if (desiredArmPositionArray[1] > yAxisPWMDuty_L)
			{
				directionArray[1] = UP;
			}
			else
			{
				directionArray[1] = DOWN;
			}
			if (desiredArmPositionArray[2] > yAxisPWMDuty_R)
			{
				directionArray[2] = UP;
			}
			else
			{
				directionArray[2] = DOWN;
			}

			bool desiredArmPositionReached;
			do
			{
				desiredArmPositionReached = true;

				if (!pauseSequence)
				{
					for (size_t j = 0; j < 3; j++)
					{
						uint32_t tempValue;

						switch (j)
						{
						case 0:
							tempValue = xAxisPWMDuty;
							break;
						case 1:
							tempValue = yAxisPWMDuty_L;
							break;
						case 2:
							tempValue = yAxisPWMDuty_R;
							break;
						default:
							break;
						}

						tempValue += directionArray[j] * sequenceSpeed;

						if (directionArray[j] == UP)
						{
							if (tempValue >= desiredArmPositionArray[j])
							{
								tempValue = desiredArmPositionArray[j];
							}
							else
							{
								desiredArmPositionReached = false;
							}
						}
						else
						{
							if (tempValue <= desiredArmPositionArray[j])
							{
								tempValue = desiredArmPositionArray[j];
							}
							else
							{
								desiredArmPositionReached = false;
							}
						}

						switch (j)
						{
						case 0:
							xAxisPWMDuty = tempValue;
							break;
						case 1:
							yAxisPWMDuty_L = tempValue;
							break;
						case 2:
							yAxisPWMDuty_R = tempValue;
							break;
						default:
							break;
						}
					}
					vTaskDelay(100);
				}
				else
				{
					desiredArmPositionReached = false;
					vTaskDelay(100);
				}

			} while (!stopSequence && !desiredArmPositionReached);
			if (!stopSequence && manipulatorPWMDuty != desiredArmPosition.manipulatorPWMDuty)
			{
				vTaskDelay(100);
				manipulatorPWMDuty = desiredArmPosition.manipulatorPWMDuty;
				vTaskDelay(900);
			}

			if (sequenceScreenViewClass != NULL)
			{
				((touchgfx::TextAreaWithOneWildcard*)sequenceScreenViewClass->positionContainersList[i].getFirstChild())->setColor(previousColor);
				sequenceScreenViewClass->invalidateScrollableContainer = true;
			}
		}
	}

	sequenceRunning = false;
	stopSequence = false;
	pauseSequence = false;
	vTaskDelete(NULL);
}

ArmPosition SequencePlaybackControl::Char2ArmPosition(char* position)
{
	ArmPosition robotPosition;
	char buffer[17];
	size_t j = 0, PWMDutyType = 0;
	for (size_t i = 0; i < 17 && position[i] != '\0'; ++i)
	{
		if (isdigit(position[i]))
		{
			buffer[j] = position[i];
			++j;
		}
		else
		{
			buffer[j] = '\0';
			uint32_t tempValue = (uint32_t) atoi(buffer);
			switch (PWMDutyType)
			{
			case 0:
				robotPosition.xAxisPWMDuty = tempValue;
				++PWMDutyType;
				break;
			case 1:
				robotPosition.yAxisPWMDuty_L = tempValue;
				++PWMDutyType;
				break;
			case 2:
				robotPosition.yAxisPWMDuty_R = tempValue;
				++PWMDutyType;
				break;
			default:
				break;
			}

			j = 0;
		}
	}
	robotPosition.manipulatorPWMDuty = (buffer[0] == '1' ? 275 : 700);
	return robotPosition;
}
