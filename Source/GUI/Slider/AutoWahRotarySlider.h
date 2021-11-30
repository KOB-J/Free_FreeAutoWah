/*
  ==============================================================================

    AutoWahRotarySlider.h
    Created: 30 Nov 2021 12:53:42pm
    Author:  dev

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AutoWahSliderLookAndFeel.h"


class AutoWahRotarySlider : public juce::Slider
{
public:
    AutoWahRotarySlider()
    {
        setLookAndFeel(&autoWahSliderLookAndFeel);
        setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
        setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);

    }

    ~AutoWahRotarySlider()
    {
        setLookAndFeel(nullptr);
    }

private:
    AutoWahSliderLookAndFeel autoWahSliderLookAndFeel;

};