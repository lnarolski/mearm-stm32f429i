#include <gui/sequencescreen_screen/sequenceScreenView.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>

extern uint32_t xAxisPWMDuty;
extern uint32_t yAxisPWMDuty_L;
extern uint32_t yAxisPWMDuty_R;
extern uint32_t manipulatorPWMDuty;

sequenceScreenView::sequenceScreenView()
{

}

void sequenceScreenView::setupScreen()
{
    sequenceScreenViewBase::setupScreen();

	positionsList.removeAll();
	scrollableContainer.invalidate();

	char positionChar[17];
	memset(positionChar, '\0', 17);
	snprintf(positionChar, 17, "%d,%d,%d,%d", 100, 100, 100, 1);
	positionContainersList[numOfListItems].SetText(positionChar);
	positionsList.add(positionContainersList[numOfListItems]);
	scrollableContainer.invalidate();
	++numOfListItems;

	memset(positionChar, '\0', 17);
	snprintf(positionChar, 17, "%d,%d,%d,%d", 200, 200, 200, 2);
	positionContainersList[numOfListItems].SetText(positionChar);
	positionsList.add(positionContainersList[numOfListItems]);
	scrollableContainer.invalidate();
	++numOfListItems;
}

void sequenceScreenView::tearDownScreen()
{
    sequenceScreenViewBase::tearDownScreen();
}

void sequenceScreenView::SaveSequenceButton_Clicked()
{

}

void sequenceScreenView::PlaySequenceButton_Clicked()
{

}

void sequenceScreenView::AddNewPositionButton_Clicked()
{
	if (numOfListItems < maxNumOfPositions)
	{
		static unsigned int temp = 3;

		char positionChar[17];
		memset(positionChar, '\0', 17);
		snprintf(positionChar, 17, "%d,%d,%d,%d", 100 * temp, 100 * temp, 100 * temp, 1 * temp);
		positionContainersList[numOfListItems].SetText(positionChar);
		positionsList.add(positionContainersList[numOfListItems]);
		scrollableContainer.invalidate();
		++numOfListItems;

		++temp;
	}
	else
	{
		Unicode::snprintf(infoTextAreaBuffer, INFOTEXTAREA_SIZE, "ERROR:\nMaximum number of positions!");
		infoTextArea.setWideTextAction(WIDE_TEXT_WORDWRAP);
		infoTextArea.invalidate();
	}
}

void sequenceScreenView::DeletePositionButton_Clicked()
{
	positionsList.removeAll();
	scrollableContainer.invalidate();

	Unicode::snprintf(infoTextAreaBuffer, INFOTEXTAREA_SIZE, "INFO:");
	infoTextArea.setWideTextAction(WIDE_TEXT_WORDWRAP);
	infoTextArea.invalidate();

	numOfListItems = 0;
}
