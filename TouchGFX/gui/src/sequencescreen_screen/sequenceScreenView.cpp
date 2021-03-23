#include <gui/sequencescreen_screen/sequenceScreenView.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <memory>

extern uint32_t xAxisPWMDuty;
extern uint32_t yAxisPWMDuty_L;
extern uint32_t yAxisPWMDuty_R;
extern uint32_t manipulatorPWMDuty;

sequenceScreenView::sequenceScreenView()
{
	positionContainer* newPosition = (positionContainer*)malloc(sizeof(positionContainer));
//	*newPosition = positionContainer();
	touchgfx::Unicode::UnicodeChar positionUnicodeChar[17];
	Unicode::snprintf(positionUnicodeChar, 17, "%d,%d,%d,%d", 100, 100, 100, 1);
	newPosition->SetText(positionUnicodeChar);
	positionContainersList.push_back(newPosition);

	newPosition = (positionContainer*)malloc(sizeof(positionContainer));
	//	*newPosition = positionContainer();
	Unicode::snprintf(positionUnicodeChar, 17, "%d,%d,%d,%d", 200, 200, 200, 2);
	newPosition->SetText(positionUnicodeChar);
	positionContainersList.push_back(newPosition);

	for (mearm::VectorItem<positionContainer*>* i = positionContainersList.firstItem; i != NULL; i = i->nextItem)
	{
		positionsList.add(*i->item);
	}
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

}

void sequenceScreenView::DeletePositionButton_Clicked()
{

}
