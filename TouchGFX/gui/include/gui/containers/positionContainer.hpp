#ifndef POSITIONCONTAINER_HPP
#define POSITIONCONTAINER_HPP

#include <gui_generated/containers/positionContainerBase.hpp>

class positionContainer : public positionContainerBase
{
public:
    positionContainer();
    virtual ~positionContainer() {}

    virtual void initialize();
	void SetText(char* t);
	void SetText(touchgfx::Unicode::UnicodeChar* t);
	touchgfx::Unicode::UnicodeChar* GetText();
protected:
};

#endif // POSITIONCONTAINER_HPP
