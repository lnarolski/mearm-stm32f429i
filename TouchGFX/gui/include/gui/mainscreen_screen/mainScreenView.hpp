#ifndef MAINSCREENVIEW_HPP
#define MAINSCREENVIEW_HPP

#include <gui_generated/mainscreen_screen/mainScreenViewBase.hpp>
#include <gui/mainscreen_screen/mainScreenPresenter.hpp>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"

class mainScreenView : public mainScreenViewBase
{
public:
    mainScreenView();
    virtual ~mainScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
private:
    void XAxisSliderValue_Changed(int value);
    void YAxisSlider_L_Value_Changed(int value);
    void YAxisSlider_R_Value_Changed(int value);
    void ManipulatorControlToggleButton_Clicked();
};

#endif // MAINSCREENVIEW_HPP
