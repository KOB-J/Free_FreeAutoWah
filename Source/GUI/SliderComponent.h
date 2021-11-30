/*
  ==============================================================================

    SliderComponent.h
    Created: 30 Nov 2021 12:53:12pm
    Author:  dev

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Slider/AutoWahRotarySlider.h"

class SliderComponent : public juce::Component
{
public:
    SliderComponent()
    {
        addAndMakeVisible(autoWahRotarySlider);
        addAndMakeVisible(label);
        label.setFont(juce::Font(12.0f, juce::Font::italic));
    }

    ~SliderComponent()
    {

    }

    void paint(juce::Graphics&) override
    {

    }
 
    void resized() override
    {
        auto bounds = getLocalBounds();
        auto width = bounds.getWidth();
        auto height = bounds.getHeight();

        autoWahRotarySlider.setBounds(0.2 * width, 0.2 * height, 0.6 * width, 0.6 * height);
        label.setBounds(0, 0, width, 0.2 * height);
    }

    void setLabelText(const juce::String labelText)
    {
        label.setText(labelText, juce::dontSendNotification);
    }

private:
    AutoWahRotarySlider autoWahRotarySlider;
    juce::Label label;
};
