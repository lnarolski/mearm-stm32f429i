#include <gui/mainscreen_screen/mainScreenView.hpp>

extern uint32_t xAxisPWMDuty;
extern uint32_t yAxisPWMDuty_L;
extern uint32_t yAxisPWMDuty_R;
extern uint32_t manipulatorPWMDuty;

mainScreenView::mainScreenView()
{
	/* Initialize all configured peripherals */
}

void mainScreenView::setupScreen()
{
    mainScreenViewBase::setupScreen();
}

void mainScreenView::tearDownScreen()
{
    mainScreenViewBase::tearDownScreen();
}

void mainScreenView::XAxisSliderValue_Changed(int value)
{

}

void mainScreenView::YAxisSliderValue_Changed(int value)
{

}

void mainScreenView::ManipulatorControlToggleButton_Clicked()
{
	static bool state = false;


}
