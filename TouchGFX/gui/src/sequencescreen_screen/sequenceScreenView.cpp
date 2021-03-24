#include <gui/sequencescreen_screen/sequenceScreenView.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>

extern uint32_t xAxisPWMDuty;
extern uint32_t yAxisPWMDuty_L;
extern uint32_t yAxisPWMDuty_R;
extern uint32_t manipulatorPWMDuty;

sequenceScreenView::sequenceScreenView()
{
	char positionUnicodeChar[17];
	memset(positionUnicodeChar, '\0', 17);
	snprintf(positionUnicodeChar, 17, "%d,%d,%d,%d", 100, 100, 100, 1);
	positionContainersList[0].SetText(positionUnicodeChar);
	++numOfListItems;

	memset(positionUnicodeChar, '\0', 17);
	snprintf(positionUnicodeChar, 17, "%d,%d,%d,%d", 200, 200, 200, 2);
	positionContainersList[1].SetText(positionUnicodeChar);
	++numOfListItems;

	for (size_t i = 0; i < numOfListItems; ++i)
	{
		positionsList.add(positionContainersList[i]);
	}
	positionsList.invalidate();
	scrollableContainer.invalidate();
}

void sequenceScreenView::setupScreen()
{
    sequenceScreenViewBase::setupScreen();
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
	char positionUnicodeChar[17];
	memset(positionUnicodeChar, '\0', 17);
	snprintf(positionUnicodeChar, 17, "%d,%d,%d,%d", 300, 300, 300, 1);
	positionContainersList[numOfListItems].SetText(positionUnicodeChar);
	positionsList.add(positionContainersList[numOfListItems]);
	++numOfListItems;

	positionsList.invalidate();
	scrollableContainer.invalidate();
}

void sequenceScreenView::DeletePositionButton_Clicked()
{

}
