#include <gui/containers/positionContainer.hpp>

positionContainer::positionContainer()
{

}

void positionContainer::initialize()
{
	positionContainerBase::initialize();
}

void positionContainer::SetText(char* t)
{
	Unicode::snprintf(positionTextBuffer, POSITIONTEXT_SIZE, t);
}

void positionContainer::SetText(touchgfx::Unicode::UnicodeChar* t)
{
	Unicode::snprintf(positionTextBuffer, POSITIONTEXT_SIZE, "%s", t);
}

touchgfx::Unicode::UnicodeChar* positionContainer::GetText()
{
	return positionTextBuffer;
}
