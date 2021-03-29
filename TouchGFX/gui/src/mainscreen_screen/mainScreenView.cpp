#include <gui/mainscreen_screen/mainScreenView.hpp>
#include <gui/containers/positionContainer.hpp>

extern uint32_t xAxisPWMDuty;
extern uint32_t yAxisPWMDuty_L;
extern uint32_t yAxisPWMDuty_R;
extern uint32_t manipulatorPWMDuty;

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;

mainScreenView::mainScreenView()
{
	/* Initialize all configured peripherals */
	HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_4, &xAxisPWMDuty, 1);
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
	xAxisPWMDuty = 275 + 9 * value;
}

void mainScreenView::YAxisSlider_L_Value_Changed(int value)
{
	yAxisPWMDuty_L = (int) (842.0 + 5.06 * (float)value);
}

void mainScreenView::YAxisSlider_R_Value_Changed(int value)
{
	yAxisPWMDuty_R = (int) (842.0 + 3.42 * (float)value);
}

void mainScreenView::ManipulatorControlToggleButton_Clicked()
{
	static bool state = false;

	if (state)
	{
		manipulatorPWMDuty = 275;
		state = false;
	}
	else
	{
		manipulatorPWMDuty = 700;
		state = true;
	}
}
