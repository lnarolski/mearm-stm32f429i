#include <gui/sequencescreen_screen/sequenceScreenView.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_flash_ex.h"

extern uint32_t xAxisPWMDuty;
extern uint32_t yAxisPWMDuty_L;
extern uint32_t yAxisPWMDuty_R;
extern uint32_t manipulatorPWMDuty;

sequenceScreenView::sequenceScreenView() {

}

void sequenceScreenView::setupScreen() {
	sequenceScreenViewBase::setupScreen();

	positionsList.removeAll();
	scrollableContainer.invalidate();

	if (DataStorageModel::screenViewFirstOpen) {
		uint32_t *startSectorAddress = (uint32_t*)0x081E0000; // Address of Sector 23
		DataStorageModel::numOfListItems = *startSectorAddress;
		if (DataStorageModel::numOfListItems <= DataStorageModel::maxNumOfPositions) // Check if numOfListItems was initialized in flash memory
		{
			char *charAddress = (char*)startSectorAddress;
			charAddress += 4;
			for (size_t i = 0; i < DataStorageModel::numOfListItems; ++i) {
				for (size_t j = 0; j < 17; ++j) // 17 - size of char array
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

	for (size_t i = 0; i < DataStorageModel::numOfListItems; ++i) {
		positionContainersList[i].SetText(
				DataStorageModel::positionsList[i]);
		positionsList.add(positionContainersList[i]);
		scrollableContainer.invalidate();
	}
}

void sequenceScreenView::tearDownScreen() {
	sequenceScreenViewBase::tearDownScreen();
}

void sequenceScreenView::SaveSequenceButton_Clicked() {
	HAL_FLASH_Unlock();

	uint32_t sectorError;

	/* Fill EraseInit structure*/
	static FLASH_EraseInitTypeDef pEraseInit;
	pEraseInit.TypeErase = FLASH_TYPEERASE_SECTORS;
	pEraseInit.VoltageRange = FLASH_VOLTAGE_RANGE_3;
	pEraseInit.Sector = FLASH_SECTOR_23;
	pEraseInit.NbSectors = 1;

	if (HAL_FLASHEx_Erase(&pEraseInit, &sectorError) != HAL_OK) {
		Unicode::snprintf(infoTextAreaBuffer, INFOTEXTAREA_SIZE,
				"ERROR:\nError during sector erase!");
		infoTextArea.setWideTextAction(WIDE_TEXT_WORDWRAP);
		infoTextArea.invalidate();

		HAL_FLASH_Lock();
		return;
	}

	uint32_t startSectorAddress = 0x081E0000; // Address of Sector 23

	if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, startSectorAddress,
			(uint32_t) DataStorageModel::numOfListItems) == HAL_OK) {
		startSectorAddress += 4;
	} else {
		Unicode::snprintf(infoTextAreaBuffer, INFOTEXTAREA_SIZE,
				"ERROR:\nError during save number of list items!");
		infoTextArea.setWideTextAction(WIDE_TEXT_WORDWRAP);
		infoTextArea.invalidate();

		HAL_FLASH_Lock();
		return;
	}
	for (size_t i = 0; i < DataStorageModel::numOfListItems; ++i) { // 17 - size of char array
		for (size_t j = 0; j < 17; ++j)
		{
			if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, startSectorAddress,
					(uint64_t)DataStorageModel::positionsList[i][j]) == HAL_OK) {
				startSectorAddress += 1;
			} else {
				Unicode::snprintf(infoTextAreaBuffer, INFOTEXTAREA_SIZE,
						"ERROR:\nError during saving positions!");
				infoTextArea.setWideTextAction(WIDE_TEXT_WORDWRAP);
				infoTextArea.invalidate();

				HAL_FLASH_Lock();
				return;
			}
		}
	}

	Unicode::snprintf(infoTextAreaBuffer, INFOTEXTAREA_SIZE,
			"INFO:\nSequence saved");
	infoTextArea.setWideTextAction(WIDE_TEXT_WORDWRAP);
	infoTextArea.invalidate();
	HAL_FLASH_Lock();
}

void sequenceScreenView::PlaySequenceButton_Clicked() {

}

void sequenceScreenView::AddNewPositionButton_Clicked() {
	if (DataStorageModel::numOfListItems
			< DataStorageModel::maxNumOfPositions) {
		static unsigned int temp = 3;

		char positionChar[17];
		memset(positionChar, '\0', 17);
		snprintf(positionChar, 17, "%d,%d,%d,%d", 100 * temp, 100 * temp,
				100 * temp, 1 * temp);
		memcpy(
				DataStorageModel::positionsList[DataStorageModel::numOfListItems],
				positionChar, 17);
		positionContainersList[DataStorageModel::numOfListItems].SetText(
				positionChar);
		positionsList.add(
				positionContainersList[DataStorageModel::numOfListItems]);
		scrollableContainer.invalidate();
		++DataStorageModel::numOfListItems;

		++temp;
	} else {
		Unicode::snprintf(infoTextAreaBuffer, INFOTEXTAREA_SIZE,
				"ERROR:\nMaximum number of positions!");
		infoTextArea.setWideTextAction(WIDE_TEXT_WORDWRAP);
		infoTextArea.invalidate();
	}
}

void sequenceScreenView::DeletePositionButton_Clicked() {
	positionsList.removeAll();
	scrollableContainer.invalidate();

	Unicode::snprintf(infoTextAreaBuffer, INFOTEXTAREA_SIZE, "INFO:");
	infoTextArea.setWideTextAction(WIDE_TEXT_WORDWRAP);
	infoTextArea.invalidate();

	DataStorageModel::numOfListItems = 0;
}
