/*
  ==============================================================================

    CenterComponent.h
    Created: 29 Nov 2021 3:37:57pm
    Author:  dev

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Utils/Colors.h"


class CenterComponent : public juce::Component
{
public:
    CenterComponent();
    ~CenterComponent();

    void paint(juce::Graphics& g) override;
    void resized() override;

private:

};
