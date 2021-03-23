#ifndef SEQUENCESCREENVIEW_HPP
#define SEQUENCESCREENVIEW_HPP

#include <gui_generated/sequencescreen_screen/sequenceScreenViewBase.hpp>
#include <gui/sequencescreen_screen/sequenceScreenPresenter.hpp>
#include <Vector.hpp>
#include <gui/containers/positionContainer.hpp>

class sequenceScreenView : public sequenceScreenViewBase
{
public:
    sequenceScreenView();
    virtual ~sequenceScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void SaveSequenceButton_Clicked();
    void PlaySequenceButton_Clicked();
    void AddNewPositionButton_Clicked();
    void DeletePositionButton_Clicked();
protected:
    mearm::vector<positionContainer*> positionContainersList;
};

#endif // SEQUENCESCREENVIEW_HPP
