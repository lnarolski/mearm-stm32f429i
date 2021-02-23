#include <gui/mainscreen_screen/mainScreenView.hpp>

uint32_t xAxisPWMDuty;
uint32_t yAxisPWMDuty_L;
uint32_t yAxisPWMDuty_R;
uint32_t manipulatorPWMDuty;

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;

mainScreenView::mainScreenView()
{
	/* Initialize all configured peripherals */
	HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_2, &xAxisPWMDuty, 1);
	HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_2, &yAxisPWMDuty_L, 1);
	HAL_TIM_PWM_Start_DMA(&htim4, TIM_CHANNEL_1, &yAxisPWMDuty_R, 1);
	HAL_TIM_PWM_Start_DMA(&htim5, TIM_CHANNEL_1, &manipulatorPWMDuty, 1);
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
	xAxisPWMDuty = value * 100;
}

void mainScreenView::YAxisSliderValue_Changed(int value)
{
	yAxisPWMDuty_L = value * 100;
	yAxisPWMDuty_R = value * 100;
}

void mainScreenView::ManipulatorControlToggleButton_Clicked()
{
	static bool state = false;

	if (state)
	{
		manipulatorPWMDuty = 0;
		state = false;
	}
	else
	{
		manipulatorPWMDuty = 10000;
		state = true;
	}
}
