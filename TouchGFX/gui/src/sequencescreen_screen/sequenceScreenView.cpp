#include <gui/sequencescreen_screen/sequenceScreenView.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_flash_ex.h"

extern uint32_t xAxisPWMDuty;
extern uint32_t yAxisPWMDuty_L;
extern uint32_t yAxisPWMDuty_R;
extern uint32_t manipulatorPWMDuty;

sequenceScreenView::sequenceScreenView() :
		deleteCallback(this, &sequenceScreenView::onDeleteButton_Clicked), positionListCallback(this,
				&sequenceScreenView::onPositionList_Clicked)
{
	SequencePlaybackControl::sequenceScreenViewClass = this;
}

sequenceScreenView::~sequenceScreenView()
{
	SequencePlaybackControl::stopSequence = true;
}

void sequenceScreenView::setupScreen()
{
	sequenceScreenViewBase::setupScreen();

	deletePositionButton.setClickAction(deleteCallback);

	for (size_t i = 0; i < MAX_NUM_OF_POSITIONS; ++i)
	{
		((touchgfx::ClickListener< touchgfx::TextAreaWithOneWildcard >*)positionContainersList[i].getFirstChild())->setClickAction(positionListCallback);
	}

	positionsList.removeAll();
	scrollableContainer.invalidate();

	if (DataStorageModel::screenViewFirstOpen)
	{
		uint32_t* startSectorAddress = (uint32_t*) 0x081E0000; // Address of Sector 23
		DataStorageModel::numOfListItems = *startSectorAddress;
		if (DataStorageModel::numOfListItems <= DataStorageModel::maxNumOfPositions) // Check if numOfListItems was initialized in flash memory
		{
			startSectorAddress += 1;
			SequencePlaybackControl::sequenceSpeed = *startSectorAddress;

			char* charAddress = (char*) startSectorAddress;
			charAddress += 4;
			for (size_t i = 0; i < DataStorageModel::numOfListItems; ++i)
			{
				for (size_t j = 0; j < POSITION_TEXT_BUFFER_SIZE; ++j) // POSITION_TEXT_BUFFER_SIZE - size of char array
				{
					DataStorageModel::positionsList[i][j] = *charAddress;
					charAddress += 1;
				}
			}
		}
		else
		{
			DataStorageModel::numOfListItems = 0;
		}

		DataStorageModel::screenViewFirstOpen = false;
	}

	for (size_t i = 0; i < DataStorageModel::numOfListItems; ++i)
	{
		positionContainersList[i].SetText(DataStorageModel::positionsList[i]);
		positionsList.add(positionContainersList[i]);
		scrollableContainer.invalidate();
	}
}

bool deleteButtonClicked = false;
uint32_t longPressCounter = 0;

void sequenceScreenView::handleTickEvent()
{
	if (invalidateScrollableContainer)
	{
		scrollableContainer.invalidate();
		invalidateScrollableContainer = false;
	}
	if (invalidateInfoTextArea)
	{
		infoTextArea.invalidate();
		invalidateInfoTextArea = false;
	}

	if (deleteButtonClicked)
	{
		if (longPressCounter > 50)
		{
			deleteButtonClicked = false;
			LongPressDeleteButton_Clicked();
		}

		++longPressCounter;
	}
}

void sequenceScreenView::tearDownScreen()
{
	DataStorageModel::xAxisSliderValue = (uint32_t)(((float)xAxisPWMDuty - 275 * 6) / (6 * 9.05));
	DataStorageModel::yAxisSliderValue_L = (uint32_t)(((float)yAxisPWMDuty_L - 842.0 * 6) / (6 * 4.4));
	DataStorageModel::yAxisSliderValue_R = (uint32_t)(((float)yAxisPWMDuty_R - 842.0 * 6) / (6 * 3.42));
	DataStorageModel::manipulatorState = (manipulatorPWMDuty == 700 * 6 ? true : false);

	sequenceScreenViewBase::tearDownScreen();
}

void sequenceScreenView::SaveSequenceButton_Clicked()
{
	HAL_FLASH_Unlock();

	uint32_t sectorError;

	/* Fill EraseInit structure*/
	static FLASH_EraseInitTypeDef pEraseInit;
	pEraseInit.TypeErase = FLASH_TYPEERASE_SECTORS;
	pEraseInit.VoltageRange = FLASH_VOLTAGE_RANGE_3;
	pEraseInit.Sector = FLASH_SECTOR_23;
	pEraseInit.NbSectors = 1;

	if (HAL_FLASHEx_Erase(&pEraseInit, &sectorError) != HAL_OK)
	{
		Unicode::snprintf(infoTextAreaBuffer, INFOTEXTAREA_SIZE, "ERROR:\nError during sector erase!");
		infoTextArea.setWideTextAction(WIDE_TEXT_WORDWRAP);
		infoTextArea.invalidate();

		HAL_FLASH_Lock();
		return;
	}

	uint32_t startSectorAddress = 0x081E0000; // Address of Sector 23

	if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, startSectorAddress, (uint32_t) DataStorageModel::numOfListItems)
			== HAL_OK)
	{
		startSectorAddress += 4;
	}
	else
	{
		Unicode::snprintf(infoTextAreaBuffer, INFOTEXTAREA_SIZE, "ERROR:\nError during save number of list items!");
		infoTextArea.setWideTextAction(WIDE_TEXT_WORDWRAP);
		infoTextArea.invalidate();

		HAL_FLASH_Lock();
		return;
	}

	if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, startSectorAddress, (uint32_t) SequencePlaybackControl::sequenceSpeed)
			== HAL_OK)
	{
		startSectorAddress += 4;
	}
	else
	{
		Unicode::snprintf(infoTextAreaBuffer, INFOTEXTAREA_SIZE, "ERROR:\nError during save sequence speed!");
		infoTextArea.setWideTextAction(WIDE_TEXT_WORDWRAP);
		infoTextArea.invalidate();

		HAL_FLASH_Lock();
		return;
	}

	for (size_t i = 0; i < DataStorageModel::numOfListItems; ++i)
	{ // POSITION_TEXT_BUFFER_SIZE - size of char array
		for (size_t j = 0; j < POSITION_TEXT_BUFFER_SIZE; ++j)
		{
			if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, startSectorAddress,
					(uint64_t) DataStorageModel::positionsList[i][j]) == HAL_OK)
			{
				startSectorAddress += 1;
			}
			else
			{
				Unicode::snprintf(infoTextAreaBuffer, INFOTEXTAREA_SIZE, "ERROR:\nError during saving positions!");
				infoTextArea.setWideTextAction(WIDE_TEXT_WORDWRAP);
				infoTextArea.invalidate();

				HAL_FLASH_Lock();
				return;
			}
		}
	}

	Unicode::snprintf(infoTextAreaBuffer, INFOTEXTAREA_SIZE, "INFO:\nSequence saved");
	infoTextArea.setWideTextAction(WIDE_TEXT_WORDWRAP);
	infoTextArea.invalidate();
	HAL_FLASH_Lock();
}

void sequenceScreenView::PlaySequenceButton_Clicked()
{
	playSequenceButton.setVisible(false);
	playSequenceButton.invalidate();
	saveSequenceButton.setVisible(false);
	saveSequenceButton.invalidate();
	deletePositionButton.setVisible(false);
	deletePositionButton.invalidate();

	stopSequenceButton.setVisible(true);
	stopSequenceButton.invalidate();
	pauseSequenceButton.setVisible(true);
	pauseSequenceButton.invalidate();
	changeSequenceSpeedButton.setVisible(true);
	changeSequenceSpeedButton.invalidate();

	SequencePlaybackControl::Play();
}

void sequenceScreenView::StopSequenceButton_Clicked()
{
	SequencePlaybackControl::Stop();

	while (SequencePlaybackControl::stopSequence)
	{
		vTaskDelay(100);
	};

	playSequenceButton.setVisible(true);
	playSequenceButton.invalidate();
	saveSequenceButton.setVisible(true);
	saveSequenceButton.invalidate();
	deletePositionButton.setVisible(true);
	deletePositionButton.invalidate();

	stopSequenceButton.setVisible(false);
	stopSequenceButton.invalidate();
	pauseSequenceButton.setVisible(false);
	pauseSequenceButton.invalidate();
	resumeSequenceButton.setVisible(false);
	resumeSequenceButton.invalidate();
	changeSequenceSpeedButton.setVisible(false);
	changeSequenceSpeedButton.invalidate();
}

void sequenceScreenView::ChangeSequenceSpeedButton_Clicked()
{
	uint32_t tempSpeed = SequencePlaybackControl::sequenceSpeed * 2;

	if (tempSpeed > SequencePlaybackControl::maxSequenceSpeed)
	{
		SequencePlaybackControl::sequenceSpeed = SequencePlaybackControl::minSequenceSpeed;

		Unicode::snprintf(infoTextAreaBuffer, INFOTEXTAREA_SIZE, "INFO:\nSequence speed: %d",
				SequencePlaybackControl::sequenceSpeed);
		infoTextArea.setWideTextAction(WIDE_TEXT_WORDWRAP);
		infoTextArea.invalidate();
	}
	else
	{
		SequencePlaybackControl::sequenceSpeed = tempSpeed;

		Unicode::snprintf(infoTextAreaBuffer, INFOTEXTAREA_SIZE, "INFO:\nSequence speed: %d",
				SequencePlaybackControl::sequenceSpeed);
		infoTextArea.setWideTextAction(WIDE_TEXT_WORDWRAP);
		infoTextArea.invalidate();
	}

}

void sequenceScreenView::PauseSequenceButton_Clicked()
{
	pauseSequenceButton.setVisible(false);
	pauseSequenceButton.invalidate();
	resumeSequenceButton.setVisible(true);
	resumeSequenceButton.invalidate();

	SequencePlaybackControl::Pause();
}

void sequenceScreenView::ResumeSequenceButton_Clicked()
{
	pauseSequenceButton.setVisible(true);
	pauseSequenceButton.invalidate();
	resumeSequenceButton.setVisible(false);
	resumeSequenceButton.invalidate();

	SequencePlaybackControl::Resume();
}

void sequenceScreenView::ShowSequenceSpeed()
{
	Unicode::snprintf(infoTextAreaBuffer, INFOTEXTAREA_SIZE, "INFO:\nSequence speed: %d",
			SequencePlaybackControl::sequenceSpeed);
	infoTextArea.setWideTextAction(WIDE_TEXT_WORDWRAP);
	invalidateInfoTextArea = true;
}

void sequenceScreenView::AddNewPositionButton_Clicked()
{
	if (DataStorageModel::numOfListItems < DataStorageModel::maxNumOfPositions)
	{
		char positionChar[POSITION_TEXT_BUFFER_SIZE];
		memset(positionChar, '\0', POSITION_TEXT_BUFFER_SIZE);
		snprintf(positionChar, POSITION_TEXT_BUFFER_SIZE, "%d,%d,%d,%d", xAxisPWMDuty, yAxisPWMDuty_L, yAxisPWMDuty_R,
				manipulatorPWMDuty == 275 * 6 ? 1 : 0);
		memcpy(DataStorageModel::positionsList[DataStorageModel::numOfListItems], positionChar, POSITION_TEXT_BUFFER_SIZE);
		positionContainersList[DataStorageModel::numOfListItems].SetText(positionChar);
		positionsList.add(positionContainersList[DataStorageModel::numOfListItems]);
		scrollableContainer.invalidate();
		++DataStorageModel::numOfListItems;

		Unicode::snprintf(infoTextAreaBuffer, INFOTEXTAREA_SIZE, "INFO:\nItem in list: %d",
				DataStorageModel::numOfListItems);
		infoTextArea.setWideTextAction(WIDE_TEXT_WORDWRAP);
		infoTextArea.invalidate();
	}
	else
	{
		Unicode::snprintf(infoTextAreaBuffer, INFOTEXTAREA_SIZE, "ERROR:\nMaximum number of positions!");
		infoTextArea.setWideTextAction(WIDE_TEXT_WORDWRAP);
		infoTextArea.invalidate();
	}
}

void sequenceScreenView::onPositionList_Clicked(const touchgfx::TextAreaWithOneWildcard& text, const ClickEvent& evt)
{
	static int16_t startPosition = 0;

	if (evt.getType() == ClickEvent::PRESSED)
	{
		startPosition = scrollableContainer.getY();
	}
	else if (evt.getType() == ClickEvent::RELEASED && startPosition == scrollableContainer.getY())
	{
		Unicode::UnicodeChar* tempText = ((positionContainer*)text.getParent())->GetText();
		ArmPosition armPosition = SequencePlaybackControl::Char2ArmPosition(tempText);
		xAxisPWMDuty = armPosition.xAxisPWMDuty;
		yAxisPWMDuty_L = armPosition.yAxisPWMDuty_L;
		yAxisPWMDuty_R = armPosition.yAxisPWMDuty_R;
		manipulatorPWMDuty = armPosition.manipulatorPWMDuty;
	}
	else
		startPosition = 0;
}

void sequenceScreenView::onDeleteButton_Clicked(const touchgfx::ButtonWithIcon&, const ClickEvent& evt)
{
	if (evt.getType() == ClickEvent::RELEASED)
	{
		deleteButtonClicked = false;

		if (longPressCounter <= 50)
		{
			ShortPressDeleteButton_Clicked();
		}
	}
	else if (evt.getType() == ClickEvent::PRESSED)
	{
		longPressCounter = 0;
		deleteButtonClicked = true;
	}
}

void sequenceScreenView::LongPressDeleteButton_Clicked()
{
	deleteAllModalWindow.setVisible(true);
	deleteAllModalWindow.invalidate();
}

void sequenceScreenView::ShortPressDeleteButton_Clicked()
{
	if (DataStorageModel::numOfListItems != 0)
	{
		positionsList.remove(positionContainersList[DataStorageModel::numOfListItems - 1]);
		scrollableContainer.invalidate();

		Unicode::snprintf(infoTextAreaBuffer, INFOTEXTAREA_SIZE, "INFO:\nDeleted last position");
		infoTextArea.setWideTextAction(WIDE_TEXT_WORDWRAP);
		infoTextArea.invalidate();

		--DataStorageModel::numOfListItems;
	}
}

void sequenceScreenView::YesDeleteAllButton_Clicked()
{
	positionsList.removeAll();
	scrollableContainer.invalidate();

	Unicode::snprintf(infoTextAreaBuffer, INFOTEXTAREA_SIZE, "INFO:\nDeleted all positions");
	infoTextArea.setWideTextAction(WIDE_TEXT_WORDWRAP);
	infoTextArea.invalidate();

	DataStorageModel::numOfListItems = 0;

	deleteAllModalWindow.setVisible(false);
	deleteAllModalWindow.invalidate();
}
