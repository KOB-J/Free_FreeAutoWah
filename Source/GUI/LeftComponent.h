/*
  ==============================================================================

    LeftComponent.h
    Created: 29 Nov 2021 3:38:14pm
    Author:  dev

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Utils/Colors.h"
#include "Slider/AutoWahRotarySlider.h"
#include "../Utils/Strings.h"

class LeftComponent : public juce::Component
{
public:
    LeftComponent();
    ~LeftComponent();

    void paint(juce::Graphics& g) override;
    void resized() override;

    AutoWahRotarySlider* getLfoFrequencySlider() {return &lfoFrequencySlider;}
    AutoWahRotarySlider* getLfoWidthSlider() {return &lfoWidthSlider;}

private:
    AutoWahRotarySlider lfoFrequencySlider, lfoWidthSlider;
    juce::Label lfoFrequencyLabel, lfoWidthLabel, lfoTitleLabel;
};