/*
  ==============================================================================

    RightComponent.h
    Created: 29 Nov 2021 3:38:27pm
    Author:  dev

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Utils/Colors.h"


class RightComponent : public juce::Component
{
public:
    RightComponent();
    ~RightComponent();

    void paint(juce::Graphics& g) override;
    void resized() override;

private:

};