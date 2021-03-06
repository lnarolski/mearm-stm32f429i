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

	xAxisSlider.setValue(DataStorageModel::xAxisSliderValue);
	yAxisSlider_L.setValue(DataStorageModel::yAxisSliderValue_L);
	yAxisSlider_R.setValue(DataStorageModel::yAxisSliderValue_R);
	manipulatorControlToggleButton.forceState(DataStorageModel::manipulatorState);
}

void mainScreenView::tearDownScreen()
{
	DataStorageModel::xAxisSliderValue = xAxisSlider.getValue();
	DataStorageModel::yAxisSliderValue_L = yAxisSlider_L.getValue();
	DataStorageModel::yAxisSliderValue_R = yAxisSlider_R.getValue();
	DataStorageModel::manipulatorState = manipulatorControlToggleButton.getState();

	mainScreenViewBase::tearDownScreen();
}

void mainScreenView::XAxisSliderValue_Changed(int value)
{
	xAxisPWMDuty = (uint32_t) (275 * 6 + 6 * 9.05 * value);
}

void mainScreenView::YAxisSlider_L_Value_Changed(int value)
{
	yAxisPWMDuty_L = (uint32_t) (842.0 * 6 + 6 * 4.4 * (float) value);
}

void mainScreenView::YAxisSlider_R_Value_Changed(int value)
{
	yAxisPWMDuty_R = (uint32_t) (842.0 * 6 + 6 * 3.42 * (float) value);
}

void mainScreenView::ManipulatorControlToggleButton_Clicked()
{
	static bool state = false;

	if (state)
	{
		manipulatorPWMDuty = 275 * 6;
		state = false;
	}
	else
	{
		manipulatorPWMDuty = 700 * 6;
		state = true;
	}
}
