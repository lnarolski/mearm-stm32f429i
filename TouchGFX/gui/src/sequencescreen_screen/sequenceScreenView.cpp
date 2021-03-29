#include <gui/sequencescreen_screen/sequenceScreenView.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>

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

	if (!DataStorageModel::screenViewFirstOpen) {
		for (size_t i = 0; i < DataStorageModel::numOfListItems; ++i) {
			positionContainersList[i].SetText(DataStorageModel::positionsList[i]);
			positionsList.add(positionContainersList[i]);
			scrollableContainer.invalidate();
		}
	} else {
		DataStorageModel::screenViewFirstOpen = false;
	}
}

void sequenceScreenView::tearDownScreen() {
	sequenceScreenViewBase::tearDownScreen();
}

void sequenceScreenView::SaveSequenceButton_Clicked() {

}

void sequenceScreenView::PlaySequenceButton_Clicked() {

}

void sequenceScreenView::AddNewPositionButton_Clicked() {
	if (DataStorageModel::numOfListItems < DataStorageModel::maxNumOfPositions) {
		static unsigned int temp = 3;

		char positionChar[17];
		memset(positionChar, '\0', 17);
		snprintf(positionChar, 17, "%d,%d,%d,%d", 100 * temp, 100 * temp,
				100 * temp, 1 * temp);
		memcpy(DataStorageModel::positionsList[DataStorageModel::numOfListItems], positionChar, 17);
		positionContainersList[DataStorageModel::numOfListItems].SetText(positionChar);
		positionsList.add(positionContainersList[DataStorageModel::numOfListItems]);
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
