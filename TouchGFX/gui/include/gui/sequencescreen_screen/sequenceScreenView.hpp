#ifndef SEQUENCESCREENVIEW_HPP
#define SEQUENCESCREENVIEW_HPP

#include <gui_generated/sequencescreen_screen/sequenceScreenViewBase.hpp>
#include <gui/sequencescreen_screen/sequenceScreenPresenter.hpp>
#include <gui/containers/positionContainer.hpp>
#include <stdio.h>
#include <../STM32CubeIDE/DataStorageModel.h>
#include <../STM32CubeIDE/SequencePlaybackControl.h>
#include <string.h>

class sequenceScreenView: public sequenceScreenViewBase
{
public:
	sequenceScreenView();
	virtual ~sequenceScreenView();
	virtual void setupScreen();
	virtual void tearDownScreen();

	void SaveSequenceButton_Clicked();
	void PlaySequenceButton_Clicked();
	void StopSequenceButton_Clicked();
	void AddNewPositionButton_Clicked();
	void ChangeSequenceSpeedButton_Clicked();
	void PauseSequenceButton_Clicked();
	void ResumeSequenceButton_Clicked();
	void ShowSequenceSpeed();

	bool invalidateScrollableContainer = false;
	bool invalidateInfoTextArea = false;

	void handleTickEvent();
	void handleClickEvent(ClickEvent& evt);

	void LongPressDeleteButton_Clicked();
	void ShortPressDeleteButton_Clicked();

	void YesDeleteAllButton_Clicked();

	uint32_t FlashRead();
	uint32_t FlashWrite(uint32_t StartPageAddress, uint32_t* DATA_32);

	positionContainer positionContainersList[MAX_NUM_OF_POSITIONS];
protected:
	Callback<sequenceScreenView, const touchgfx::ButtonWithIcon&, const ClickEvent&> deleteCallback;
	void onDeleteButton_Clicked(const touchgfx::ButtonWithIcon&, const ClickEvent&);

	Callback<sequenceScreenView, const touchgfx::TextAreaWithOneWildcard&, const ClickEvent&> positionListCallback;
	void onPositionList_Clicked(const touchgfx::TextAreaWithOneWildcard&, const ClickEvent&);
};

#endif // SEQUENCESCREENVIEW_HPP
