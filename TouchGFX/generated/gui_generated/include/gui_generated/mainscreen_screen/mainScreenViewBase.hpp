/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef MAINSCREENVIEWBASE_HPP
#define MAINSCREENVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/mainscreen_screen/mainScreenPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/ToggleButton.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/containers/Slider.hpp>
#include <touchgfx/widgets/ButtonWithIcon.hpp>

class mainScreenViewBase : public touchgfx::View<mainScreenPresenter>
{
public:
    mainScreenViewBase();
    virtual ~mainScreenViewBase() {}
    virtual void setupScreen();

    /*
     * Virtual Action Handlers
     */
    virtual void XAxisSliderValue_Changed(int value)
    {
        // Override and implement this function in mainScreen
    }

    virtual void YAxisSlider_L_Value_Changed(int value)
    {
        // Override and implement this function in mainScreen
    }

    virtual void ManipulatorControlToggleButton_Clicked()
    {
        // Override and implement this function in mainScreen
    }

    virtual void YAxisSlider_R_Value_Changed(int value)
    {
        // Override and implement this function in mainScreen
    }

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::Image backgroundImage;
    touchgfx::ToggleButton manipulatorControlToggleButton;
    touchgfx::TextArea titleText;
    touchgfx::TextArea manipulatorText;
    touchgfx::Slider yAxisSlider_L;
    touchgfx::Slider xAxisSlider;
    touchgfx::Slider yAxisSlider_R;
    touchgfx::TextArea leftText;
    touchgfx::TextArea rightText;
    touchgfx::TextArea baseText;
    touchgfx::ButtonWithIcon sequenceScreenButton;

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<mainScreenViewBase, const touchgfx::AbstractButton&> buttonCallback;
    touchgfx::Callback<mainScreenViewBase, const touchgfx::Slider&, int> sliderValueChangedCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);
    void sliderValueChangedCallbackHandler(const touchgfx::Slider& src, int value);

};

#endif // MAINSCREENVIEWBASE_HPP
