#include <gui/sequencescreen_screen/sequenceScreenView.hpp>
#include <vector>
#include <memory>
#include <gui/containers/positionContainer.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>

extern uint32_t xAxisPWMDuty;
extern uint32_t yAxisPWMDuty_L;
extern uint32_t yAxisPWMDuty_R;
extern uint32_t manipulatorPWMDuty;

static std::vector<positionContainer> positionContainersList;

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
	positionContainer newPosition;
	touchgfx::Unicode::UnicodeChar positionUnicodeChar[16];
	Unicode::snprintf(positionUnicodeChar, 16, "%d,%d,%d,%d", xAxisPWMDuty, yAxisPWMDuty_L, yAxisPWMDuty_R, manipulatorPWMDuty == 700 ? 1 : 0);
	newPosition.SetText(positionUnicodeChar);
	positionContainersList.push_back(newPosition);

	positionsList.add(positionContainersList[positionContainersList.size() - 1]);
	positionsList.initialize();
	positionsList.invalidate();
}

void sequenceScreenView::DeletePositionButton_Clicked()
{

}
