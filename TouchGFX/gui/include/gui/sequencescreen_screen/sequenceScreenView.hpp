#ifndef SEQUENCESCREENVIEW_HPP
#define SEQUENCESCREENVIEW_HPP

#include <gui_generated/sequencescreen_screen/sequenceScreenViewBase.hpp>
#include <gui/sequencescreen_screen/sequenceScreenPresenter.hpp>
#include <gui/containers/positionContainer.hpp>
#include <stdio.h>
#include <../STM32CubeIDE/DataStorageModel.h>
#include <string.h>

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

    positionContainer positionContainersList[MAX_NUM_OF_POSITIONS];
protected:
};

#endif // SEQUENCESCREENVIEW_HPP
