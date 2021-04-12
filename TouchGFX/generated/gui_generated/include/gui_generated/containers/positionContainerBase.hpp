/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef POSITIONCONTAINERBASE_HPP
#define POSITIONCONTAINERBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/mixins/ClickListener.hpp>

class positionContainerBase : public touchgfx::Container
{
public:
    positionContainerBase();
    virtual ~positionContainerBase() {}
    virtual void initialize();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::ClickListener< touchgfx::TextAreaWithOneWildcard > positionText;

    /*
     * Wildcard Buffers
     */
    static const uint16_t POSITIONTEXT_SIZE = 25;
    touchgfx::Unicode::UnicodeChar positionTextBuffer[POSITIONTEXT_SIZE];

private:

};

#endif // POSITIONCONTAINERBASE_HPP
