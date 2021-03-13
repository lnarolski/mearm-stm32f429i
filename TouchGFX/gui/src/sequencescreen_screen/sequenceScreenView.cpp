#include <gui/sequencescreen_screen/sequenceScreenView.hpp>
#include <gui/containers/positionContainer.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <memory>
//#include <Vector.hpp>

extern uint32_t xAxisPWMDuty;
extern uint32_t yAxisPWMDuty_L;
extern uint32_t yAxisPWMDuty_R;
extern uint32_t manipulatorPWMDuty;

static touchgfx::Vector<positionContainer*, 50> positionContainersList;

sequenceScreenView::sequenceScreenView()
{

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
	if (positionContainersList.size() != positionContainersList.maxCapacity())
	{
		positionContainer *newPosition = (positionContainer*)malloc(sizeof(positionContainer));
		touchgfx::Unicode::UnicodeChar positionUnicodeChar[17];
		Unicode::snprintf(positionUnicodeChar, 17, "%d,%d,%d,%d", xAxisPWMDuty, yAxisPWMDuty_L, yAxisPWMDuty_R, manipulatorPWMDuty == 700 ? 1 : 0);
		newPosition->SetText(positionUnicodeChar);
		positionContainersList[positionContainersList.size()] = newPosition;

		positionsList.add(*positionContainersList[positionContainersList.size() - 1]);
		positionsList.invalidate();
	}
}

void sequenceScreenView::DeletePositionButton_Clicked()
{

}
