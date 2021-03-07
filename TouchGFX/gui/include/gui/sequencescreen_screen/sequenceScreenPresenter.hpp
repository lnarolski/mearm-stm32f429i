#ifndef SEQUENCESCREENPRESENTER_HPP
#define SEQUENCESCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class sequenceScreenView;

class sequenceScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    sequenceScreenPresenter(sequenceScreenView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~sequenceScreenPresenter() {};

private:
    sequenceScreenPresenter();

    sequenceScreenView& view;
};

#endif // SEQUENCESCREENPRESENTER_HPP
